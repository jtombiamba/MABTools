#include <libmbench.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <bench.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

#define STR_SIZE 100

#define END		0
#define CHAR		1
#define SIZE		2
#define BANDWIDTH	3
#define LATENCY		4



uint64_t mbench_size = 0;
uint64_t mbench_size_max = 0;
uint64_t mbench_size_range = 0;
static uint64_t cpu_freq;
static int write_results = 1;

static char format[STR_SIZE];
static int output[STR_SIZE];
static FILE *csv_fd;
static FILE *dat_fd;

stream_t *mbench_stream_new (uint64_t size) {
    stream_t *s;
    int i, page_size = getpagesize ();

    s = malloc (sizeof (*s));
    if (!s) {
	fprintf (stderr, "Out of mem\n");
	exit (EXIT_FAILURE);
    }

    s->stream = valloc (size);
    if (!s->stream) {
	fprintf (stderr, "Out of mem\n");
	exit (EXIT_FAILURE);
    }

    void **addr = (void**) s->stream;
    for (i=0; i<size / sizeof (uint64_t); i++) {
	*addr = s->stream;
	addr++;
    }
    s->size = size;
    return s;
}


inline uint64_t rdtsc () {
    uint64_t ret;
    __asm__ __volatile__(
	"rdtsc;"
	"shl $32, %%rdx;"
	"add %%rdx, %%rax;"
	: "=a" (ret)
	);
    return ret;
}

uint64_t mbench_get_cpu_freq () {
    uint64_t ts_start, ts_stop;
    struct timeval tv_start, tv_stop;
    struct timespec delay = { 0, 800000000 };

    if (cpu_freq != -1) {

	ts_start = rdtsc ();
	gettimeofday (&tv_start, NULL);
	nanosleep (&delay, NULL);
	ts_stop = rdtsc ();
	gettimeofday (&tv_stop, NULL);

	uint64_t f = 1000000 * (ts_stop - ts_start) /
	    (((uint64_t)tv_stop.tv_sec * 1000000 + tv_stop.tv_usec) -
	     ((uint64_t)tv_start.tv_sec * 1000000 + tv_start.tv_usec));
	cpu_freq = f;
    }
    return cpu_freq;
}


void mbench_parse_args (int argc, char *argv[]) {
    int c, i;
    int option_index;
    char *filename = NULL;
    char hostname[20];
    struct option long_options[] = {
	{"size", 1, 0, 's'},
	{0, 0, 0, 0}
    };
    int o_option = 0;


    while ((c = getopt_long (argc, argv, "o:s:", long_options, &option_index)) != -1) {
	switch (c) {
	case 'o':
	    o_option = 1;
	    asprintf (&filename, "%s", optarg);
	    break;
	case 's':
	    mbench_size = atoi (optarg);
	    if (strstr (optarg, "kb") || strstr (optarg, "kB") || 
		strstr (optarg, "Kb") || strstr (optarg, "KB")) {
		mbench_size *= 1024;
	    } else {	
		if (strstr (optarg, "mb") || strstr (optarg, "mB") || 
		    strstr (optarg, "Mb") || strstr (optarg, "MB")) {
		    mbench_size *= 1024 * 1024;
		} else {	
		    if (strstr (optarg, "gb") || strstr (optarg, "gB") || 
			strstr (optarg, "Gb") || strstr (optarg, "GB")) {
			mbench_size *= 1024 * 1024 * 1024;
		    }
		}
	    }
	    if (strstr (optarg, ":")) {
		mbench_size_range = 1;
		optarg = strstr (optarg, ":") + 1;	
		mbench_size_max = atoi (optarg);
		if (strstr (optarg, "kb") || strstr (optarg, "kB") || 
		    strstr (optarg, "Kb") || strstr (optarg, "KB")) {
		    mbench_size_max *= 1024;
		} else {	
		    if (strstr (optarg, "mb") || strstr (optarg, "mB") || 
			strstr (optarg, "Mb") || strstr (optarg, "MB")) {
			mbench_size_max *= 1024 * 1024;
		    } else {
			if (strstr (optarg, "gb") || strstr (optarg, "gB") || 
			    strstr (optarg, "Gb") || strstr (optarg, "GB")) {
			    mbench_size_max *= 1024 * 1024 * 1024;
			}
		    }
		}
	    }
	    else {
		mbench_size_max = mbench_size;
	    }
	    break;
	}
    }
    if (!o_option) {
	gethostname(hostname, 20);

	asprintf (&filename, "output/%s/%s", hostname, argv[0]);
    }
    char *dir_name = strdup (filename);
    char *csv_filename;
    char *dat_filename;
    for (i=0; filename[i] != '\0'; i++) {
	if (filename[i] == '/') {
	    strncpy (dir_name, filename, i+1);
	    dir_name[i] = '\0';
	    if (access (dir_name, "w")) {
		mkdir (dir_name, 0755);
	    }
	}
    }
    free (dir_name);

    asprintf (&csv_filename, "%s.csv", filename);
    csv_fd = fopen (csv_filename, "w");
    if (!csv_fd) {
	fprintf (stderr, "Error: Could not open %s: ", csv_filename);
	perror ("");
	exit (EXIT_FAILURE);
    }
    free (csv_filename);

    asprintf (&dat_filename, "%s.dat", filename);
    dat_fd = fopen (dat_filename, "w");
    if (!csv_fd) {
	fprintf (stderr, "Error: Could not open %s: ", dat_filename);
	perror ("");
	exit (EXIT_FAILURE);
    }
    free (dat_filename);
    free (filename);
    printf ("%s:\n", argv[0]);
}


void mbench_flush_stream (stream_t *s) {
    uint64_t i;
    char *addr = s->stream;

    if (s->stream) {
	__asm__ __volatile__("mfence;"::);
	for (i=0; i<s->size; i+=16) {
	    __asm__ __volatile__("clflush (%%rax);":: "a" (&addr[i]));
	}
	__asm__ __volatile__("mfence;"::);
    }
}


void mbench_add_run (run_t *tab, perf_t perf, uint64_t c, int rep, int th) {
    tab[th*REPS + rep].perf = perf;
    tab[th*REPS + rep].runtime = c;
}


void mbench_print_results (run_t *run_table, int nthreads) {
    int i, r;

    static int count = 0;

    if (count == 0) {
	fprintf (csv_fd, ";Bandwidth (GB/s)\n");
	fprintf (csv_fd, "Size (KB);");
	for (r=0; r<REPS; r++) fprintf (csv_fd, ";");
	fprintf (csv_fd, "BEST; STD DEV\n");
    }

    for (i=0; i<nthreads; i++) {
	uint64_t bytes = run_table[i*REPS].perf.bytes;
	double size_kb = (double) bytes / 1024;
	double best_bandwidth = 0;
	double best_latency = 0;
	if (bytes > 0) {
			printf("oui\r");
	    fprintf (csv_fd, "%.2f;", size_kb);
	    for (r=0; r<REPS; r++) {
		uint64_t cycles = run_table[i*REPS + r].runtime;
		uint64_t instructions = run_table[i*REPS + r].perf.instructions;
		
		double bandwidth = (double) bytes / 1e9 * mbench_get_cpu_freq () / (cycles);
		double latency = (double) cycles / instructions;

		fprintf (csv_fd, "%.2lf;",
			bandwidth);

		if (best_bandwidth < bandwidth || r == 0) {
		    best_bandwidth = bandwidth;
		    best_latency = latency;
		}
	    }
	    fprintf (csv_fd, "=MAX(%c%d:%c%d);",
		    'B', count+i+3,
		    'B' + REPS-1, count+i+3);
	    fprintf (csv_fd, "=STDEVP(%c%d:%c%d);",
		    'B', count+i+3,
		    'B' + REPS-1, count+i+3);
	    fprintf (csv_fd, "\n");
	    fprintf (dat_fd, "%.2f\t%.2f\t%.2f\n", size_kb, best_bandwidth, best_latency);
	}
	//printf ("%ld bytes\n", bytes);
    }
    fflush (dat_fd);
    fflush (csv_fd);
    count ++;
}


void mbench_cleanup () {
    fclose (csv_fd);
    fclose (dat_fd);
}



void mbench_progress_bar (float percent) {
    struct winsize w;
    int columns, i, bar_size;
    ioctl(0, TIOCGWINSZ, &w);
    columns = w.ws_col - 11;

    bar_size = percent * columns;
    printf ("|");
    for (i=0; i<bar_size-1; i++)
	printf ("=");
    if (bar_size == columns)
	printf ("=");
    else
	printf (">");
    for (i=bar_size; i<columns; i++)
	printf (" ");
    printf ("| %5.2f%% ", 100*percent);
    fflush (stdout);
    printf ("\r");
}
