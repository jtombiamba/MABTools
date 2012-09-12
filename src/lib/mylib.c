#include"mylib.h"

perf_t add_bench(stream_t *source){

	perf_t ret = {0, 0, 0} ;

	__asm__ __volatile__(
												"rdtsc;"
												"shl $32, %%rdx;"
												"add %%rdx, %%rax;"
												"mov %%rax, %%rbx;"
												"_loop:"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"sub $8, %%rcx;"
												"jnz _loop;"
												"rdtsc;"
												"shl $32, %%rdx;"
												"add %%rdx, %%rax;"
												"sub %%rbx, %%rax;"
												: "=a" (ret.clock_cycles)
												: "c" (source->size)
												: "%rbx", "%rdx"
											);
					ret.instructions = source->size;
	return ret;
}

inline uint64_t rdtsc(){
	uint64_t tsc;
	__asm__ __volatile__(
												"rdtsc;"
												"shl $32, %%rdx;"
												"add %%rdx, %%rax;"
												:"=a" (tsc)
											);
	return tsc;

}
