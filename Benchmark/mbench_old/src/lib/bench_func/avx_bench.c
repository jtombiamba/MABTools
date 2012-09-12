#include<bench.h>

perf_t vbroadcastsd_bench(stream_t *source){
	uint64_t save = 1;
	perf_t ret = {0, 0} ;
	if (source->size >= 16){
	
	__asm__ __volatile__(
												
												"nop;"
												//"movaps (%%rbx), %%xmm1;"
												//"movaps (%%rbx), %%xmm2;"
												"_loop:"
												"vbroadcastsd   (%%rbx), %%ymm0;"
												"vbroadcastsd  8(%%rbx), %%ymm1;"
												"vbroadcastsd  16(%%rbx), %%ymm2;"
												"vbroadcastsd  24(%%rbx), %%ymm3;"
												"vbroadcastsd  32(%%rbx), %%ymm4;"
												"vbroadcastsd  40(%%rbx), %%ymm5;"
												"vbroadcastsd  48(%%rbx), %%ymm6;"
												"vbroadcastsd  56(%%rbx), %%ymm7;"
												"vbroadcastsd  64(%%rbx), %%ymm8;"
												"vbroadcastsd  72(%%rbx), %%ymm9;"
												"vbroadcastsd  80(%%rbx), %%ymm10;"
												"vbroadcastsd  88(%%rbx), %%ymm11;"
												"vbroadcastsd  96(%%rbx), %%ymm12;"
												"vbroadcastsd  104(%%rbx), %%ymm13;"
												"vbroadcastsd  112(%%rbx), %%ymm14;"
												"vbroadcastsd  120(%%rbx), %%ymm15;"
												"sub $128, %%rcx;"
												"jnz _loop;"
												"nop;"
												: //"=a" (ret.instructions)
												: "c" (source->size), "b" (source->stream) 
												: "%xmm2", "%xmm1"
											);
	ret.instructions = source->size/8;
	ret.bytes = source->size;
			}else {
	ret.instructions = 0;
	ret.bytes= 0;
}
	return ret;
}

perf_t vaddpd_bench(stream_t *source){
	uint64_t save = 1;
	perf_t ret = {0, 0} ;
	if (source->size >= 16){
	
	__asm__ __volatile__(
												
												"nop;"
												"vmovaps (%%rbx), %%ymm1;"
												"vmovaps (%%rbx), %%ymm2;"
												"_loopd:"
												"vaddpd  %%ymm1, %%ymm1, %%ymm2;"
												"vaddpd  %%ymm2, %%ymm1, %%ymm1;"
												"vaddpd  %%ymm1, %%ymm2, %%ymm1;"
												"vaddpd  %%ymm1, %%ymm1, %%ymm2;"
												"vaddpd  %%ymm2, %%ymm1, %%ymm1;"
												"vaddpd  %%ymm1, %%ymm2, %%ymm1;"
												"vaddpd  %%ymm1, %%ymm1, %%ymm2;"
												"vaddpd  %%ymm2, %%ymm1, %%ymm1;"
												"vaddpd  %%ymm1, %%ymm2, %%ymm1;"
												"vaddpd  %%ymm1, %%ymm1, %%ymm2;"
												"vaddpd  %%ymm2, %%ymm1, %%ymm1;"
												"vaddpd  %%ymm1, %%ymm2, %%ymm1;"
												"vaddpd  %%ymm1, %%ymm1, %%ymm2;"
												"vaddpd  %%ymm2, %%ymm1, %%ymm1;"
												"vaddpd  %%ymm1, %%ymm2, %%ymm1;"
												"vaddpd  %%ymm1, %%ymm2, %%ymm1;"
												"sub $16, %%rcx;"
												"jnz _loopd;"
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


