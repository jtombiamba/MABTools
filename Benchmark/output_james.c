#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>
#include <omp.h>
#include <bench.h>

#include <libmbench.h>

stream_t *s1;
uint64_t mbench_size = 0;
run_t *run_table = NULL;

int main (int argc, char *argv[]) {
    mbench_parse_args (argc, argv);
    uint64_t *runtime_cycles;
    perf_t *perf;
    uint64_t cur;
    int nthreads, r;
    BEGIN_SIZE_LOOP
    #pragma omp parallel private(r)
    {
        #pragma omp master
        {
        nthreads = omp_get_num_threads ();
        runtime_cycles = 
            malloc (nthreads * sizeof *runtime_cycles);
        perf = 
            malloc (nthreads * sizeof *perf);
        run_table = 
            calloc (REPS * nthreads, sizeof *run_table);
        }
        for (r=0; r<REPS; r++) {
            cur = 0;
            perf_t tmp = {0, 0};
        #pragma omp master
        {
    s1 = mbench_stream_new (mbench_size);
        cur = 0;
        }
            #pragma omp barrier
            mbench_flush_stream (s1);
            uint64_t t = 0;
            perf_t p = {0, 0};
            int omp_id = omp_get_thread_num();
            #pragma omp barrier
            if ((omp_id == 0)) tmp = output_james(s1);
 p.bytes += tmp.bytes;
 p.instructions += tmp.instructions;
            #pragma omp barrier
            TIMER_START;
            if ((omp_id == 0)) tmp = output_james(s1);
 p.bytes += tmp.bytes;
 p.instructions += tmp.instructions;
            TIMER_STOP;
            #pragma omp barrier
            if ((p.bytes > 0)) {
                #pragma omp critical
                {
                    cur += t;
                }
            }
            #pragma omp barrier
        #pragma omp master
        {
    free (s1->stream); free (s1);
        }
                #pragma omp master
                {
    mbench_add_run (run_table, p, t, r, 0);
                }
        #pragma omp barrier
        }
    }
    mbench_print_results (run_table, nthreads);
    free (runtime_cycles); free (perf);
    free (run_table);
    END_SIZE_LOOP
    mbench_cleanup ();
    return EXIT_SUCCESS;
}
