/* -*-mode: c-mode-*- */

%{
#include <symbol.h>
#include <parser.h>

stream_tab_t *stream_tab = NULL;
run_tab_t *run_tab = NULL;
%}

%union {
    int num;
    char *str;
    stream_t stream;
    func_t func;
    run_t run;
    binding_t binding;
    num_tab_t *num_table;
}

%token <num> NUM UNIT
%token <str> ID
%token THREAD TIME RUNTIME_SIZE

%type <num>		size
%type <stream>		def
%type <run>		run basic_run
%type <func>		function
%type <binding>		binding
%type <num_table>	num_lst
%type <str>		arg_lst

%start benchmark

%%

benchmark
: stream_def_lst run_lst
;

stream_def_lst
:  stream_def_lst def ';'		{stream_table_add (stream_tab, $2);}
|
;

def
: ID '=' size				{$$.id = $1; if ($3==-1) {; $$.type=DYNAMIC;} else {$$.byte_size = $3; $$.type=STATIC;}}
;

size
: NUM UNIT				{$$ = $1 * $2;}
| RUNTIME_SIZE				{$$ = -1;}
;

run_lst
: run_lst run ';'			{run_table_add (run_tab, $2);}
|
;

run
: basic_run				{$$ = $1;}
| TIME '('basic_run ')'			{$$ = $3; $$.timer = 1;}
;

basic_run
: THREAD ':' binding '.' function	{$$.binding = $3; $$.func = $5;}
;

binding
: num_lst	       			{$$.num_table = $1;; $$.type=LIST;}
| NUM '-' NUM				{$$.start = $1; $$.stop = $3; $$.type=RANGE;}
;

num_lst
: num_lst ',' NUM			{num_table_add ($$, $3);}
| NUM					{$$ = num_table_new (); num_table_add ($$, $1);}
;

function
: ID '(' arg_lst ')'			{$$.name = $1; $$.arg = $3;}
;

arg_lst
: ID					{$$ = $1;}
| arg_lst ',' ID			{asprintf (&$$, "%s,%s", $1, $3);}
;

%%

#include <getopt.h>

extern int line;
extern FILE *yyin;

char *file_name = "STDIN";
FILE *outfile = NULL;

int yyerror (char *s) {
    fprintf (stderr, "\n%s at in %s line %d\n\n", s, file_name, line);
    exit (1);
}

extern void code_generator();

int main (int argc, char* argv[]) {
    outfile = stdout;

    char c;
    while ((c = getopt (argc, argv, "o:")) != EOF) {
	switch (c) {
	case 'o':
	    outfile = fopen (optarg, "w");
	    break;
	}
    }
    if (optind < argc) {
	int file = 0;
        while ((optind + file) < argc) {
	    yyin = fopen (argv[optind + file], "r");
	    file_name = argv[optind + file];
	    file ++;
	}
	if (file != 1) {
	    fprintf (stderr, "Error: too many benchmark files\n");
	    exit (EXIT_FAILURE);
	}
    }

    stream_tab = stream_table_new ();
    run_tab = run_table_new ();

    yyparse ();

    code_generator ();


    fclose (outfile);
    fclose (yyin);
    return 0;
}
