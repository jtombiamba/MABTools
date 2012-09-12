#include<bench.h>


perf_t mov_i_reg_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loop:"
												"mov $1, %%rax;"
												"mov $1, %%r10;"
												"mov $1, %%r8;"
												"mov $1, %%r9;"
												"mov $1, %%rax;"
												"mov $1, %%r10;"
												"mov $1, %%r8;"
												"mov $1, %%r9;"
												"mov $1, %%rax;"
												"mov $1, %%r10;"
												"mov $1, %%r9;"
												"mov $1, %%r8;"
												"mov $1, %%r9;"
												"mov $1, %%rax;"
												"mov $1, %%r10;"
												"mov $1, %%r8;"
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

perf_t mov_i_reg_nop_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loopl:"
												"mov $1, %%rax;"
												//"nop;"
												"mov $1, %%r10;"
												"nop;"
												"nop;"
												"mov $1, %%r8;"
												//"nop;"
												"mov $1, %%r9;"
												"nop;"
												"nop;"
												"mov $1, %%rax;"
												//"nop;"
												"mov $1, %%r10;"
												"nop;"
												"nop;"
												"mov $1, %%r8;"
												//"nop;"
												"mov $1, %%r9;"
												"nop;"
												"nop;"
												"mov $1, %%rax;"
												//"nop;"
												"mov $1, %%r10;"
												"nop;"
												"nop;"
												"mov $1, %%r9;"
												//"nop;"
												"mov $1, %%r8;"
												"nop;"
												"nop;"
												"mov $1, %%r9;"
												//"nop;"
												"mov $1, %%rax;"
												"nop;"
												"nop;"
												"mov $1, %%r10;"
												//"nop;"
												"mov $1, %%r8;"
												"nop;"
												"nop;"
												"sub $16, %%rcx;"
												"jnz _loopl;"
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



perf_t mov_i_unroll_8_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loopi:"
												"mov $1, %%rax;"
												"mov $1, %%r10;"
												"mov $1, %%r8;"
												"mov $1, %%r9;"
												"mov $1, %%rax;"
												"mov $1, %%r10;"
												"mov $1, %%r8;"
												"mov $1, %%r9;"
												"sub $8, %%rcx;"
												"jnz _loopi;"
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


perf_t mov_reg_mem_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loop1:"
												"mov %%rbx, %%rax;"
												"mov %%rbx, %%r10;"
												"mov %%rbx, %%r8;"
												"mov %%rbx, %%r9;"
												"mov %%rbx, (%%rax);"
												"mov %%rbx, (%%r10);"
												"mov %%rbx, (%%r8);"
												"mov %%rbx, (%%r9);"
												"mov %%rbx, 8(%%rax);"
												"mov %%rbx, 8(%%r10);"
												"mov %%rbx, 8(%%r9);"
												"mov %%rbx, 8(%%r8);"
												"mov %%rbx, 16(%%r9);"
												"mov %%rbx, 16(%%rax);"
												"mov %%rbx, 16(%%r10);"
												"mov %%rbx, 16(%%r8);"
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

perf_t push_reg_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 128){
	printf("%ld\n", source->size);
	__asm__ __volatile__(
												
												"nop;"
												"_loop2:"
												"mov (%%rbx), %%rax;"
												"mov 8(%%rbx), %%r8;"
												"mov 16(%%rbx), %%r9;"
												"mov 24(%%rbx), %%r10;"
												"mov 32(%%rbx), %%r8;"
												"mov 40(%%rbx), %%r10;"
												"mov 48(%%rbx), %%rax;"
												"mov 56(%%rbx), %%r9;"
												"mov 64(%%rbx), %%r10;"
												"mov 72(%%rbx), %%r8;"
												"mov 80(%%rbx), %%r9;"
												"mov 88(%%rbx), %%r8;"
												"mov 96(%%rbx), %%rax;"
												"mov 104(%%rbx), %%r10;"
												"mov 112(%%rbx), %%rax;"
												"mov 120(%%rbx), %%r9;"
												//"add $16, %%st(0);"
												"sub $128, %%rcx;"
												"jnz _loop2;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size), "b" (source->stream) 
												: "%rax", "%r8", "%r9", "%r10"
											);
	ret.instructions = 2*source->size/15;
	printf("%ld\n", source->size);
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}
perf_t mov_latency_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){
	uint64_t save = source->size;

	__asm__ __volatile__(
												
												"nop;"
												"mov $1, %%rax;"
												"_loop3:"
												"mov %%rax, %%rbx;"
												"mov %%rbx, %%rax;"
												"mov %%rax, %%rbx;"
												"mov %%rbx, %%rax;"
												"mov %%rax, %%rbx;"
												"mov %%rbx, %%rax;"
												"mov %%rax, %%rbx;"
												"mov %%rbx, %%rax;"
												"mov %%rax, %%rbx;"
												"mov %%rbx, %%rax;"
												"mov %%rax, %%rbx;"
												"mov %%rbx, %%rax;"
												"mov %%rax, %%rbx;"
												"mov %%rbx, %%rax;"
												"mov %%rax, %%rbx;"
												"mov %%rbx, %%rax;"
												"sub $16, %%rcx;"
												"jnz _loop3;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: "%rax", "%rbx"
											);
	ret.instructions = save;
	ret.bytes = save;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t mov_latency_1reg_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){
	uint64_t save = source->size;

	__asm__ __volatile__(
												
												"nop;"
												"mov $1, %%rax;"
												"_loop4:"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"mov $0x1000, %%rax;"
												"nop;"
												"nop;"
												"nop;"
												"sub $32, %%rcx;"
												"jnz _loop4;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: "%rax"
											);
	ret.instructions = save;
	ret.bytes = save;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t lea_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 128){
	//printf("%ld\n", source->size);
	__asm__ __volatile__(
												
												"nop;"
												"_loopil:"
												"lea (%%rbx), %%rax;"
												"lea (%%rbx), %%rax;"
												"lea (%%rbx), %%rax;"
												"lea (%%rbx), %%rax;"
												"lea (%%rbx), %%rax;"
												"lea (%%rbx), %%rax;"
												"lea (%%rbx), %%rax;"
												"lea (%%rbx), %%rax;"
												"lea (%%rbx), %%rax;"
												"lea (%%rbx), %%rax;"
												"lea (%%rbx), %%rax;"
												"lea (%%rbx), %%rax;"
												"lea (%%rbx), %%rax;"
												"lea (%%rbx), %%rax;"
												"lea (%%rbx), %%rax;"
												"lea (%%rbx), %%rax;"
												//"add $16, %%st(0);"
												"sub $16, %%rcx;"
												"jnz _loopil;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size), "b" (source->stream) 
												: "%rax", "%r8", "%r9", "%r10"
											);
	ret.instructions = source->size;
	//printf("%ld\n", source->size);
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

