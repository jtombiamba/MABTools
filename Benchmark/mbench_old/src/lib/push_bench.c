#include<bench.h>

perf_t add_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"mfence;"
												"_loop:"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r8;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"sub $16, %%rcx;"
												"jnz _loop;"
												"mfence;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: "%rax", "%r8", "%r9", "%r10"
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}
