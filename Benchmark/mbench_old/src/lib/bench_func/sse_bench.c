#include<bench.h>

perf_t addps_bench(stream_t *source){
	uint64_t save = 1;
	perf_t ret = {0, 0} ;
	if (source->size >= 16){
	
	__asm__ __volatile__(
												
												"nop;"
												"movaps (%%rbx), %%xmm1;"
												"movaps (%%rbx), %%xmm2;"
												"_loop:"
												"addps %%xmm1, %%xmm1;"
												"addps %%xmm2, %%xmm1;"
												"addps %%xmm1, %%xmm1;"
												"addps %%xmm2, %%xmm1;"
												"addps %%xmm1, %%xmm1;"
												"addps %%xmm2, %%xmm1;"
												"addps %%xmm1, %%xmm1;"
												"addps %%xmm2, %%xmm1;"
												"addps %%xmm1, %%xmm1;"
												"addps %%xmm2, %%xmm1;"
												"addps %%xmm1, %%xmm1;"
												"addps %%xmm2, %%xmm1;"
												"addps %%xmm1, %%xmm1;"
												"addps %%xmm2, %%xmm1;"
												"addps %%xmm1, %%xmm1;"
												"addps %%xmm2, %%xmm1;"
												"sub $16, %%rcx;"
												"jnz _loop;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size), "b" (source->stream) 
												: "%xmm2"
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t movd_bench(stream_t *source){
	uint64_t save = 1;
	perf_t ret = {0, 0} ;
	if (source->size >= 16){
	
	__asm__ __volatile__(
												
												"nop;"
												"_loopmov:"
												"movd %%xmm1, %%rax;"
												"movd %%xmm1, %%r9;"
												"movd %%xmm1, %%rdi;"
												"movd %%xmm1, %%rdi;"
												"movd %%xmm1, %%rax;"
												"movd %%xmm1, %%rdi;"
												"movd %%xmm1, %%r9;"
												"movd %%xmm1, %%rdi;"
												"movd %%xmm1, %%r9;"
												"movd %%xmm1, %%rax;"
												"movd %%xmm1, %%rdi;"
												"movd %%xmm1, %%rdi;"
												"movd %%xmm1, %%rax;"
												"movd %%xmm1, %%rdi;"
												"movd %%xmm1, %%rdi;"
												"movd %%xmm1, %%r9;"
												"sub $16, %%rcx;"
												"jnz _loopmov;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: "%rax", "%rdi", "%xmm1", "%r9"
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}


perf_t pmulld_bench(stream_t *source){
	uint64_t save = 1;
	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"movaps (%%rbx), %%xmm1;"
												"movaps (%%rbx), %%xmm2;"
												"_loop1:"
												"pmulld %%xmm1, %%xmm2;"
												"pmulld %%xmm1, %%xmm1;"
												"pmulld %%xmm1, %%xmm2;"
												"pmulld %%xmm1, %%xmm1;"
												"pmulld %%xmm1, %%xmm2;"
												"pmulld %%xmm1, %%xmm1;"
												"pmulld %%xmm1, %%xmm2;"
												"pmulld %%xmm1, %%xmm1;"
												"pmulld %%xmm1, %%xmm2;"
												"pmulld %%xmm1, %%xmm1;"
												"pmulld %%xmm1, %%xmm2;"
												"pmulld %%xmm1, %%xmm1;"
												"pmulld %%xmm1, %%xmm2;"
												"pmulld %%xmm1, %%xmm1;"
												"pmulld %%xmm1, %%xmm2;"
												"pmulld %%xmm1, %%xmm1;"
												"sub $16, %%rcx;"
												"jnz _loop1;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size), "b" (source->stream) 
												: "%xmm2", "%xmm1"
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t mfence_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loop2:"
												"mfence;"
												"mfence;"
												"mfence;"
												"mfence;"
												"mfence;"
												"mfence;"
												"mfence;"
												"mfence;"
												"mfence;"
												"mfence;"
												"mfence;"
												"mfence;"
												"mfence;"
												"mfence;"
												"mfence;"
												"mfence;"
												"sub $16, %%rcx;"
												"jnz _loop2;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: "%rax", "%rdi", "%r9", "%r10"
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t clflush_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loopfl:"
												"clflush (%%rbx);"
												"clflush 1(%%rbx);"
												"clflush 2(%%rbx);"
												"clflush 3(%%rbx);"
												"clflush 4(%%rbx);"
												"clflush 5(%%rbx);"
												"clflush 6(%%rbx);"
												"clflush 7(%%rbx);"
												"clflush 8(%%rbx);"
												"clflush 9(%%rbx);"
												"clflush 10(%%rbx);"
												"clflush 11(%%rbx);"
												"clflush 12(%%rbx);"
												"clflush 13(%%rbx);"
												"clflush 14(%%rbx);"
												"clflush 15(%%rbx);"
												"sub $16, %%rcx;"
												"jnz _loopfl;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size), "b" (source->stream)
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


perf_t addpd_bench(stream_t *source){
	uint64_t save = 1;
	perf_t ret = {0, 0} ;
	if (source->size >= 16){
	
	__asm__ __volatile__(
												
												"nop;"
												"movaps (%%rbx), %%xmm1;"
												"movaps (%%rbx), %%xmm2;"
												"_loopd:"
												"addpd %%xmm1, %%xmm1;"
												"addpd %%xmm2, %%xmm1;"
												"addpd %%xmm1, %%xmm1;"
												"addpd %%xmm2, %%xmm1;"
												"addpd %%xmm1, %%xmm1;"
												"addpd %%xmm2, %%xmm1;"
												"addpd %%xmm1, %%xmm1;"
												"addpd %%xmm2, %%xmm1;"
												"addpd %%xmm1, %%xmm1;"
												"addpd %%xmm2, %%xmm1;"
												"addpd %%xmm1, %%xmm1;"
												"addpd %%xmm2, %%xmm1;"
												"addpd %%xmm1, %%xmm1;"
												"addpd %%xmm2, %%xmm1;"
												"addpd %%xmm1, %%xmm1;"
												"addpd %%xmm2, %%xmm1;"
												"sub $16, %%rcx;"
												"jnz _loopd;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size), "b" (source->stream) 
												: "%xmm2"
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t nop_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loop2n:"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"nop;"
												"sub $64, %%rcx;"
												"jnz _loop2n;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: //"%rax", "%rdi", "%r9", "%r10"
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}


