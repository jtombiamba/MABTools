#include<bench.h>

/*
Test file name:  test_vaddpd_ymm_ymm
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_vaddpd_ymm_ymm(stream_t *source){
		perf_t ret ={0, 0};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"VADDPD %%YMM1,%%YMM1,%%YMM3;"
		"VADDPD %%YMM3,%%YMM2,%%YMM1;"
		"VADDPD %%YMM2,%%YMM3,%%YMM1;"
		"VADDPD %%YMM1,%%YMM4,%%YMM3;"
		"VADDPD %%YMM1,%%YMM1,%%YMM3;"
		"VADDPD %%YMM3,%%YMM2,%%YMM1;"
		"VADDPD %%YMM2,%%YMM3,%%YMM1;"
		"VADDPD %%YMM1,%%YMM4,%%YMM3;"
		"VADDPD %%YMM1,%%YMM1,%%YMM3;"
		"VADDPD %%YMM3,%%YMM2,%%YMM1;"
		"VADDPD %%YMM2,%%YMM3,%%YMM1;"
		"VADDPD %%YMM1,%%YMM4,%%YMM3;"
		"VADDPD %%YMM1,%%YMM1,%%YMM3;"
		"VADDPD %%YMM3,%%YMM2,%%YMM1;"
		"VADDPD %%YMM2,%%YMM3,%%YMM1;"
		"VADDPD %%YMM1,%%YMM4,%%YMM3;"
"SUB $16, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: 
);
		ret.instructions = source->size;
		ret.bytes = source->size;
	} else { 
		ret.instructions = 0 ;
	}
return ret ;
}
