#include<bench.h>

perf_t and_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loop:"
												"and $1, %%rax;"
												"and $1, %%r9;"
												"and $1, %%r8;"
												"and $1, %%r10;"
												"and $1, %%r9;"
												"and $1, %%rax;"
												"and $1, %%r8;"
												"and $1, %%r10;"
												"and $1, %%rax;"
												"and $1, %%r10;"
												"and $1, %%r9;"
												"and $1, %%r8;"
												"and $1, %%rax;"
												"and $1, %%r10;"
												"and $1, %%r8;"
												"and $1, %%r9;"
												"sub $16, %%rcx;"
												"jnz _loop;"
												"nop;"
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

perf_t or_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loop1:"
												"or %%rbx, %%rax;"
												"or %%rbx, %%r9;"
												"or %%rbx, %%r8;"
												"or %%rbx, %%r10;"
												"or %%rbx, %%r9;"
												"or %%rbx, %%rax;"
												"or %%rbx, %%r8;"
												"or %%rbx, %%r10;"
												"or %%rbx, %%rax;"
												"or %%rbx, %%r10;"
												"or %%rbx, %%r9;"
												"or %%rbx, %%r8;"
												"or %%rbx, %%rax;"
												"or %%rbx, %%r10;"
												"or %%rbx, %%r8;"
												"or %%rbx, %%r9;"
												"sub $16, %%rcx;"
												"jnz _loop1;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size), "b" (source->stream)
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

perf_t ror_rol_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loop2:"
												"ror $1, %%rax;"
												"ror $1, %%r9;"
												"ror $1, %%r8;"
												"ror $1, %%r10;"
												"ror $1, %%r9;"
												"ror $1, %%rax;"
												"ror $1, %%r8;"
												"ror $1, %%r10;"
												"ror $1, %%rax;"
												"ror $1, %%r10;"
												"ror $1, %%r9;"
												"ror $1, %%r8;"
												"ror $1, %%rax;"
												"ror $1, %%r10;"
												"ror $1, %%r8;"
												"ror $1, %%r9;"
												"sub $16, %%rcx;"
												"jnz _loop2;"
												"nop;"
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

perf_t xor_reg_mem_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loop3:"
												"xor (%%rbx), %%rax;"
												"xor (%%rbx), %%r9;"
												"xor (%%rbx), %%r8;"
												"xor (%%rbx), %%r10;"
												"xor (%%rbx), %%r9;"
												"xor (%%rbx), %%rax;"
												"xor (%%rbx), %%r8;"
												"xor (%%rbx), %%r10;"
												"xor (%%rbx), %%rax;"
												"xor (%%rbx), %%r10;"
												"xor (%%rbx), %%r9;"
												"xor (%%rbx), %%r8;"
												"xor (%%rbx), %%rax;"
												"xor (%%rbx), %%r10;"
												"xor (%%rbx), %%r8;"
												"xor (%%rbx), %%r9;"
												"sub $16, %%rcx;"
												"jnz _loop3;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size), "b" (source->stream) 
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


