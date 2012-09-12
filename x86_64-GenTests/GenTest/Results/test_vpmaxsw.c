#include<bench.h>

/*
Test file name:  test_vpmaxsw
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_vpmaxsw(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"VPMAXSW %%XMM0,%%XMM1,%%XMM3;"
		"VPMAXSW %%XMM0,%%XMM2,%%XMM3;"
		"VPMAXSW %%XMM0,%%XMM1,%%XMM3;"
		"VPMAXSW %%XMM0,%%XMM2,%%XMM3;"
		"VPMAXSW %%XMM0,%%XMM1,%%XMM3;"
		"VPMAXSW %%XMM0,%%XMM2,%%XMM3;"
		"VPMAXSW %%XMM0,%%XMM1,%%XMM3;"
		"VPMAXSW %%XMM0,%%XMM2,%%XMM3;"
		"VPMAXSW %%XMM0,%%XMM1,%%XMM3;"
		"VPMAXSW %%XMM0,%%XMM2,%%XMM3;"
		"VPMAXSW %%XMM0,%%XMM1,%%XMM3;"
		"VPMAXSW %%XMM0,%%XMM2,%%XMM3;"
		"VPMAXSW %%XMM0,%%XMM1,%%XMM3;"
		"VPMAXSW %%XMM0,%%XMM2,%%XMM3;"
		"VPMAXSW %%XMM0,%%XMM1,%%XMM3;"
		"VPMAXSW %%XMM0,%%XMM2,%%XMM3;"
"SUB $16, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: 
);
	}
return ret ;
}
