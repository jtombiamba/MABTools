#include<bench.h>

/*
Test file name:  test_vcvtsi2sd
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_vcvtsi2sd(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"VCVTSI2SD %%RAX,%%XMM0,%%XMM1;"
		"VCVTSI2SD %%R8,%%XMM0,%%XMM1;"
		"VCVTSI2SD %%R9,%%XMM0,%%XMM1;"
		"VCVTSI2SD %%R10,%%XMM0,%%XMM1;"
		"VCVTSI2SD %%RAX,%%XMM0,%%XMM1;"
		"VCVTSI2SD %%R8,%%XMM0,%%XMM1;"
		"VCVTSI2SD %%R9,%%XMM0,%%XMM1;"
		"VCVTSI2SD %%R10,%%XMM0,%%XMM1;"
		"VCVTSI2SD %%RAX,%%XMM0,%%XMM1;"
		"VCVTSI2SD %%R8,%%XMM0,%%XMM1;"
		"VCVTSI2SD %%R9,%%XMM0,%%XMM1;"
		"VCVTSI2SD %%R10,%%XMM0,%%XMM1;"
		"VCVTSI2SD %%RAX,%%XMM0,%%XMM1;"
		"VCVTSI2SD %%R8,%%XMM0,%%XMM1;"
		"VCVTSI2SD %%R9,%%XMM0,%%XMM1;"
		"VCVTSI2SD %%R10,%%XMM0,%%XMM1;"
"SUB $16, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: 
);
	}
return ret ;
}
