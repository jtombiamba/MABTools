#include<bench.h>

/*
Test file name:  subpd_james
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t subpd_james(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"SUBPD %%XMM1,%%XMM0;"
		"SUBPD %%XMM0,%%XMM2;"
		"SUBPD %%XMM2,%%XMM3;"
		"SUBPD %%XMM3,%%XMM1;"
		"SUBPD %%XMM1,%%XMM0;"
		"SUBPD %%XMM0,%%XMM2;"
		"SUBPD %%XMM2,%%XMM3;"
		"SUBPD %%XMM3,%%XMM1;"
		"SUBPD %%XMM1,%%XMM0;"
		"SUBPD %%XMM0,%%XMM2;"
		"SUBPD %%XMM2,%%XMM3;"
		"SUBPD %%XMM3,%%XMM1;"
		"SUBPD %%XMM1,%%XMM0;"
		"SUBPD %%XMM0,%%XMM2;"
		"SUBPD %%XMM2,%%XMM3;"
		"SUBPD %%XMM3,%%XMM1;"
"SUB $16, %%RDI;"
"JNZ LL;"
	:
	:"D"(source->size)
	:"%xmm1","%xmm0","%xmm2","%xmm3"
);
	}
return ret ;
}
