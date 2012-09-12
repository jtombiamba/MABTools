#include<bench.h>

/*
Test file name:  test_PMOVZXBW_xmm_xmm
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_PMOVZXBW_xmm_xmm(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"PMOVZXBW %%XMM0,%%XMM1;"
		"PMOVZXBW %%XMM3,%%XMM0;"
		"PMOVZXBW %%XMM2,%%XMM3;"
		"PMOVZXBW %%XMM0,%%XMM1;"
		"PMOVZXBW %%XMM3,%%XMM0;"
		"PMOVZXBW %%XMM2,%%XMM3;"
		"PMOVZXBW %%XMM0,%%XMM1;"
		"PMOVZXBW %%XMM3,%%XMM0;"
		"PMOVZXBW %%XMM2,%%XMM3;"
		"PMOVZXBW %%XMM0,%%XMM1;"
		"PMOVZXBW %%XMM3,%%XMM0;"
		"PMOVZXBW %%XMM2,%%XMM3;"
		"PMOVZXBW %%XMM0,%%XMM1;"
		"PMOVZXBW %%XMM3,%%XMM0;"
		"PMOVZXBW %%XMM2,%%XMM3;"
		"PMOVZXBW %%XMM0,%%XMM1;"
"SUB $16, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: 
);
	}
return ret ;
}
