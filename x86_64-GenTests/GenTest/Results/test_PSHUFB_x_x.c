#include<bench.h>

/*
Test file name:  test_PSHUFB_x_x
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_PSHUFB_x_x(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"PSHUFB %%XMM2,%%XMM1;"
		"PSHUFB %%XMM4,%%XMM3;"
		"PSHUFB %%XMM6,%%XMM5;"
		"PSHUFB %%XMM2,%%XMM1;"
		"PSHUFB %%XMM4,%%XMM3;"
		"PSHUFB %%XMM6,%%XMM5;"
		"PSHUFB %%XMM2,%%XMM1;"
		"PSHUFB %%XMM4,%%XMM3;"
		"PSHUFB %%XMM6,%%XMM5;"
		"PSHUFB %%XMM2,%%XMM1;"
		"PSHUFB %%XMM4,%%XMM3;"
		"PSHUFB %%XMM6,%%XMM5;"
		"PSHUFB %%XMM2,%%XMM1;"
		"PSHUFB %%XMM4,%%XMM3;"
		"PSHUFB %%XMM6,%%XMM5;"
		"PSHUFB %%XMM2,%%XMM1;"
		"PSHUFB %%XMM4,%%XMM3;"
		"PSHUFB %%XMM6,%%XMM5;"
		"PSHUFB %%XMM2,%%XMM1;"
		"PSHUFB %%XMM4,%%XMM3;"
		"PSHUFB %%XMM6,%%XMM5;"
		"PSHUFB %%XMM2,%%XMM1;"
		"PSHUFB %%XMM4,%%XMM3;"
		"PSHUFB %%XMM6,%%XMM5;"
		"PSHUFB %%XMM2,%%XMM1;"
		"PSHUFB %%XMM4,%%XMM3;"
		"PSHUFB %%XMM6,%%XMM5;"
		"PSHUFB %%XMM2,%%XMM1;"
		"PSHUFB %%XMM4,%%XMM3;"
		"PSHUFB %%XMM6,%%XMM5;"
		"PSHUFB %%XMM2,%%XMM1;"
		"PSHUFB %%XMM4,%%XMM3;"
"SUB $32, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: "%xmm1", "%xmm2"
);
	}
return ret ;
}
