#include<bench.h>

/*
Test file name:  test_vmovss
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_vmovss(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM1,%%XMM3;"
		"VMOVSS %%XMM0,%%XMM2,%%XMM3;"
"SUB $32, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: 
);
	}
return ret ;
}
