#include<bench.h>

/*
Test file name:  test_CVTDQ2PD_x_x
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_CVTDQ2PD_x_x(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"CVTDQ2PD %%XMM2,%%XMM1;"
		"CVTDQ2PD %%XMM4,%%XMM3;"
		"CVTDQ2PD %%XMM6,%%XMM5;"
		"CVTDQ2PD %%XMM2,%%XMM1;"
		"CVTDQ2PD %%XMM4,%%XMM3;"
		"CVTDQ2PD %%XMM6,%%XMM5;"
		"CVTDQ2PD %%XMM2,%%XMM1;"
		"CVTDQ2PD %%XMM4,%%XMM3;"
		"CVTDQ2PD %%XMM6,%%XMM5;"
		"CVTDQ2PD %%XMM2,%%XMM1;"
		"CVTDQ2PD %%XMM4,%%XMM3;"
		"CVTDQ2PD %%XMM6,%%XMM5;"
		"CVTDQ2PD %%XMM2,%%XMM1;"
		"CVTDQ2PD %%XMM4,%%XMM3;"
		"CVTDQ2PD %%XMM6,%%XMM5;"
		"CVTDQ2PD %%XMM2,%%XMM1;"
		"CVTDQ2PD %%XMM4,%%XMM3;"
		"CVTDQ2PD %%XMM6,%%XMM5;"
		"CVTDQ2PD %%XMM2,%%XMM1;"
		"CVTDQ2PD %%XMM4,%%XMM3;"
		"CVTDQ2PD %%XMM6,%%XMM5;"
		"CVTDQ2PD %%XMM2,%%XMM1;"
		"CVTDQ2PD %%XMM4,%%XMM3;"
		"CVTDQ2PD %%XMM6,%%XMM5;"
		"CVTDQ2PD %%XMM2,%%XMM1;"
		"CVTDQ2PD %%XMM4,%%XMM3;"
		"CVTDQ2PD %%XMM6,%%XMM5;"
		"CVTDQ2PD %%XMM2,%%XMM1;"
		"CVTDQ2PD %%XMM4,%%XMM3;"
		"CVTDQ2PD %%XMM6,%%XMM5;"
		"CVTDQ2PD %%XMM2,%%XMM1;"
		"CVTDQ2PD %%XMM4,%%XMM3;"
"SUB $32, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: "%xmm1", "%xmm2"
);
	}
return ret ;
}
