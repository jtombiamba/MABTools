#ifndef MYLIB_H
#define MYLIB_H

#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct {
				uint64_t instructions;
				uint64_t bytes;
				uint64_t clock_cycles;
			}perf_t;

typedef struct {
				char * stream;
				uint64_t  size;
			} stream_t;

inline uint64_t rdtsc();

perf_t add_bench(stream_t *source);


#endif
