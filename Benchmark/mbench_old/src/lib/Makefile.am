AM_CFLAGS	= -I$(srcdir)/include

lib_LTLIBRARIES	= libmbench.la
libmbench_la_SOURCES	= libmbench.c bench_func/load.c bench_func/store.c \
	bench_func/latency_load.c bench_func/copy.c bench_func/add_bench.c bench_func/mov_bench.c \
	bench_func/mult_div_bench.c bench_func/and_or_bench.c bench_func/jump_bench.c \
	bench_func/sse_bench.c bench_func/avx_bench.c bench_func/useless.s bench_func/output_james.c

library_includedir	= $(includedir)/
library_include_HEADERS	= $(srcdir)/include/libmbench.h $(srcdir)/include/bench.h $(srcdir)/include/custom.h
