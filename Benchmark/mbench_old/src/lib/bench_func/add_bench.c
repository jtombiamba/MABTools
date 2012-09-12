#include<bench.h>

perf_t add_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loop:"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"sub $16, %%rcx;"
												"jnz _loop;"
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

perf_t add_unroll_lea_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loopul:"
												"lea (%%rbx), %%r9;"
												"bsf 8(%%rbx), %%rax;"
												"add $1, %%rdi;"
												"lea (%%rbx), %%r10;"
												"bsf 8(%%rbx), %%rax;"
												"add $1, %%r9;"
												"lea (%%rbx), %%rax;"
												"bsf 8(%%rbx), %%rax;"
												"add $1, %%rdi;"
												"lea (%%rbx), %%r10;"
												"bsf 8(%%rbx), %%rax;"
												"add $1, %%rax;"
												"lea (%%rbx), %%r10;"
												"bsf 8(%%rbx), %%rax;"
												"add $1, %%r9;"
												"lea (%%rbx), %%rdi;"
												"bsf 8(%%rbx), %%rax;"
												"add $1, %%rax;"
												"lea (%%rbx), %%r10;"
												"bsf 8(%%rbx), %%rax;"
												"add $1, %%rdi;"
												"lea (%%rbx), %%r9;"
												"bsf 8(%%rbx), %%rax;"
												"add $1, %%rax;"
												"sub $24, %%rcx;"
												"jnz _loopul;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size), "b" (source->stream) 
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


perf_t add_unroll_32_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loopz:"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r8;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"sub $32, %%rcx;"
												"jnz _loopz;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: "%rax", "%rdi", "%r9", "%r10", "%r8"
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t add_unroll_64_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 64){

	__asm__ __volatile__(
												
												"nop;"
												"_loopzi:"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"sub $64, %%rcx;"
												"jnz _loopzi;"
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

perf_t add_unroll_128_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 128){

	__asm__ __volatile__(
												
												"nop;"
												"_loop128:"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"sub $128, %%rcx;"
												"jnz _loop128;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: "%rax", "%rdi", "%r9", "%r10", "%r8"
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}



perf_t add_i_nop_bench(stream_t *source){
	uint64_t save ;
	perf_t ret = {0, 0} ;
	if (source->size >= 16){
	save = source->size;
	//printf("init_save %ld\n", save);
	__asm__ __volatile__(
												
												"nop;"
												"_L1:"
												"add $1, %%r8;"
												"nop;"
												"nop;"
												"nop;"
												"add $1, %%r9;"
												"nop;"
												"nop;"
												"nop;"
												"add $1, %%rdi;"
												"nop;"
												"nop;"
												"nop;"
												"add $1, %%r10;"
												"nop;"
												"nop;"
												"nop;"
												"add $1, %%r9;"
												"nop;"
												"nop;"
												"nop;"
												"add $1, %%r8;"
												"nop;"
												"nop;"
												"nop;"
												"add $1, %%rdi;"
												"nop;"
												"nop;"
												"nop;"
												"add $1, %%r10;"
												"nop;"
												"nop;"
												"nop;"
												"add $1, %%r8;"
												"nop;"
												"nop;"
												"nop;"
												"add $1, %%r10;"
												"nop;"
												"nop;"
												"nop;"
												"add $1, %%r9;"
												"nop;"
												"nop;"
												"nop;"
												"add $1, %%rdi;"
												"nop;"
												"nop;"
												"nop;"
												"add $1, %%r8;"
												"nop;"
												"nop;"
												"nop;"
												"add $1, %%r10;"
												"nop;"
												"nop;"
												"nop;"
												"add $1, %%rdi;"
												"nop;"
												"nop;"
												"nop;"
												"add $1, %%r9;"
												"nop;"
												"nop;"
												"nop;"
												"sub $64, %%rcx;"
												"jge _L1;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: "%r8", "%rdi", "%r9", "%r10"
											);
	//printf("save %ld\n", save);
	ret.instructions = save;
	ret.bytes = save;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}


perf_t add_reg_mem_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){
	uint64_t save = source->size;
	__asm__ __volatile__(

												
												"nop;"
												"mov $0xff, %%rax;"
												"mov $0xff, %%r9;"
												"mov $0xff, %%r10;"
												"mov $0xff, %%r8;"
												"_loopi:"
												"add  (%%rbx), %%rax;"
												"add  8(%%rbx), %%r10;"
												"add  16(%%rbx), %%r8;"
												"add  24(%%rbx), %%r9;"
												"add  32(%%rbx), %%r10;"
												"add  40(%%rbx), %%rax;"
												"add  48(%%rbx), %%r9;"
												"add  56(%%rbx), %%r8;"
												"add  64(%%rbx), %%r9;"
												"add  72(%%rbx), %%r10;"
												"add  80(%%rbx), %%rax;"
												"add  88(%%rbx), %%r8;"
												//"add $12, %%rbx;"
												"sub $12, %%rcx;"
												"jnz _loopi;"
												: //"=a" (ret.instructions)
												: "c" (source->size), "b" (source->stream)
												: "%rax", "%r8", "%r9", "%r10"
											);
	ret.instructions = source->size;
	ret.bytes = save;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t add_mem_reg_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){
	uint64_t save = source->size;
	__asm__ __volatile__(

												
												"nop;"
												"mov $0xff, %%rax;"
												"mov $0xff, %%r9;"
												"mov $0xff, %%r10;"
												"mov $0xff, %%r8;"
												"_loopi1:"
												"add  %%rax, (%%rbx);"
												"add  %%r10, 8(%%rbx); "
												"add  16(%%rbx), %%r8;"
												"add  24(%%rbx), %%r9;"
												"add  %%r10, 32(%%rbx); "
												"add  %%rax, 40(%%rbx); "
												"add  48(%%rbx), %%r9;"
												"add  56(%%rbx), %%r8;"
												"add  %%r9, 64(%%rbx); "
												"add  %%r10, 72(%%rbx); "
												"add  80(%%rbx), %%rax;"
												"add  88(%%rbx), %%r8;"
												//"add $12, %%rbx;"
												"sub $12, %%rcx;"
												"jnz _loopi1;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size), "b" (source->stream)
												: "%rax", "%r8", "%r9", "%r10"
											);
	ret.instructions = source->size;
	ret.bytes = save;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t add_unroll_1_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 8){

	__asm__ __volatile__(
												
												"nop;"
												"_loop11:"
											/*	"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"*/
												"add $1, %%rax;"
												"add $1, %%rax;"
												//"nop;"
												"sub $2, %%rcx;"
												"jnz _loop11;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												:// "%rax", "%rbx"
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t add_unroll_8_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 8){

	__asm__ __volatile__(
												
												"nop;"
												"_loop1:"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"add $1, %%rax;"
												"sub $8, %%rcx;"
												"jnz _loop1;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: "%rax"
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}
perf_t add_unroll_mov_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 8){

	__asm__ __volatile__(
												
												"nop;"
												"_loop1m:"
												"add $1, %%rax;"
												"mov %%rax, %%rbx;"
												"nop;"
												"add $1, %%rax;"
												"mov %%rax, %%rbx;"
												"nop;"
												"add $1,%%rax;"
												"mov %%rax, %%rbx;"
												"nop;"
												"add $1, %%rax;"
												"mov %%rax, %%rbx;"
												"nop;"
												"add $1, %%rax;"
												"mov %%rax, %%rbx;"
												"nop;"
												"add $1, %%rax;"
												"mov %%rax, %%rbx;"
												"nop;"
												"add $1, %%rax;"
												"mov %%rax, %%rbx;"
												"nop;"
												"add $1, %%rax;"
												"mov %%rax, %%rbx;"
												"nop;"
												"sub $24, %%rcx;"
												"jnz _loop1m;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: "%rax", "%rbx"
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}


perf_t add_5_reg_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loop2:"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"sub $16, %%rcx;"
												"jnz _loop2;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: "%rax", "%rdi", "%r9", "%r10", "%r8"
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t add_latency_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){
	uint64_t save = source->size;
	__asm__ __volatile__(
												
												"nop;"
												"mov $1, %%rax;"
												"mov $1, %%r10;"
												"mov $1, %%rbx;"
												"mov $1, %%r8;"
												"mov $1, %%r9;"
												"_loop3:"
												"add %%rax, %%r10;"
												"add %%r10, %%rbx;"
												"add %%r8, %%r9;"
												"add %%rbx, %%rax;"
												"add %%r9, %%r10;"
												"add %%rax, %%r8;"
												"add %%r10, %%rax;"
												"add %%rbx, %%r9;"
												"add %%rax, %%r10;"
												"add %%r8, %%rbx;"
												"add %%r9, %%rax;"
												"add %%r10, %%r8;"
												"add %%rbx, %%r9;"
												"add %%r8, %%r10;"
												"add %%rax, %%rbx;"
												"add %%r10, %%rax;"
												"add %%rax, %%r10;"
												"add %%rbx, %%r8;"
												"add %%r9, %%rax;"
												"add %%rax, %%rbx;"
												"add %%r10, %%r9;"
												"add %%r8, %%r10;"
												"add %%rbx, %%rax;"
												"add %%r10, %%r8;"
												"add %%rax, %%r10;"
												"add %%r9, %%rbx;"
												"add %%r8, %%rax;"
												"add %%rax, %%r9;"
												"add %%rax, %%r10;"
												"add %%r10, %%rax;"
												"add %%r9, %%r8;"
												"sub $32, %%rcx;"
												"jnz _loop3;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: "%rax", "%r10", "%r9", "%r8", "%rbx"
											);
	ret.instructions = save;
	ret.bytes = save;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t crc32_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 16){

	__asm__ __volatile__(
												
												"nop;"
												"_loopc:"
												"crc32 %%rbx, %%rax;"
												"crc32 %%r8, %%r9;"
												"crc32 %%rax, %%rdi;"
												"crc32 %%r9, %%r10;"
												"crc32 %%rbx, %%r9;"
												"crc32 %%rdi, %%rax;"
												"crc32 %%rax, %%rdi;"
												"crc32 %%r9, %%r10;"
												"crc32 %%rbx, %%rax;"
												"crc32 %%r8, %%r10;"
												"crc32 %%rax, %%r9;"
												"crc32 %%r10, %%rdi;"
												"crc32 %%rbx, %%rax;"
												"crc32 %%rdi, %%r10;"
												"crc32 %%rbx, %%rdi;"
												"crc32 %%rbx, %%r9;"
												"sub $16, %%rcx;"
												"jnz _loopc;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: "%rax", "%rdi", "%r9", "%r10", "%rbx", "%r8"
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t add_unroll_256_bench(stream_t *source){

	perf_t ret = {0, 0} ;
	if (source->size >= 256){

	__asm__ __volatile__(
												
												"nop;"
												"_loop256:"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%rdi;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r8;"
												"add $1, %%r9;"
												"add $1, %%rax;"
												"add $1, %%r9;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rdi;"
												"add $1, %%r10;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%r9;"
												"add $1, %%r8;"
												"add $1, %%rax;"
												"add $1, %%r10;"
												"add $1, %%rdi;"
												"add $1, %%r9;"
												"add $1, %%r9;"
												"sub $256, %%rcx;"
												"jnz _loop256;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size) 
												: "%rax", "%rdi", "%r9", "%r10", "%r8"
											);
	ret.instructions = source->size;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}



