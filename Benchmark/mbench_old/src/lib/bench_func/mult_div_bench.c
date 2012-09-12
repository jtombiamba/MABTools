#include<bench.h>

perf_t mult_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"mfence;"
												"_loop:"
												"imul %%rbx, %%rax;"
												"imul %%rbx, %%r9;"
												"imul %%rbx, %%r8;"
												"imul %%rbx, %%r10;"
												"imul %%rbx, %%r9;"
												"imul %%rbx, %%rax;"
												"imul %%rbx, %%r8;"
												"imul %%rbx, %%r10;"
												"imul %%rbx, %%rax;"
												"imul %%rbx, %%r10;"
												"imul %%rbx, %%r9;"
												"imul %%rbx, %%r8;"
												"imul %%rbx, %%rax;"
												"imul %%rbx, %%r10;"
												"imul %%rbx, %%r8;"
												"imul %%rbx, %%r9;"
												"sub $16, %%rcx;"
												"jnz _loop;"
												"mfence;"
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


perf_t div_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	uint64_t ad = 2 ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"mfence;"
												//"mov $2, %%rax;"
												"fld %[aa];"
												"fld %[xx];"
												"_loop1:"
												"fdivp %%st(0), %%st(1);"
												"fdivp %%st(0), %%st(1);"
												"fdivp %%st(0), %%st(1);"
												"fdivp %%st(0), %%st(1);"
												"fdivp %%st(0), %%st(1);"
												"fdivp %%st(0), %%st(1);"
												"fdivp %%st(0), %%st(1);"
												"fdivp %%st(0), %%st(1);"
												"fdivp %%st(0), %%st(1);"
												"fdivp %%st(0), %%st(1);"
												"fdivp %%st(0), %%st(1);"
												"fdivp %%st(0), %%st(1);"
												"fdivp %%st(0), %%st(1);"
												"fdivp %%st(0), %%st(1);"
												"fdivp %%st(0), %%st(1);"
												"fdivp %%st(0), %%st(1);"
												"sub $16, %%rcx;"
												"jnz _loop1;"
												"mfence;"
												: //"=a" (ret.instructions)
												: "c" (source->size), [xx] "m" (source->stream), [aa] "m" (ad)
												: 
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t div_i_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	//uint64_t ad = 2 ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"mfence;"
												//"mov $2, %%rbx;"
												//"fld %[aa];"
												//"fld %[xx];"
												"_loop2:"
												"div %%rbx;"
												"div %%rbx;"
												"div %%rbx;"
												"div %%rbx;"
												"div %%rbx;"
												"div %%rbx;"
												"div %%rbx;"
												"div %%rbx;"
												"div %%rbx;"
												"div %%rbx;"
												"div %%rbx;"
												"div %%rbx;"
												"div %%rbx;"
												"div %%rbx;"
												"div %%rbx;"
												"div %%rbx;"
												"sub $16, %%rcx;"
												"jnz _loop2;"
												"mfence;"
												: //"=a" (ret.instructions)
												: "c" (source->size), "a" (source->stream), "b" (source->stream)
												: 
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}


