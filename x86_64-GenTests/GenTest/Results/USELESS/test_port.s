#include<bench.h>

/*
Test file name:  test_port
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_port(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"ADDPD %%XMM1,%%XMM0;"
		"ADDPD %%XMM3,%%XMM2;"
		"ADDPD %%XMM4,%%XMM5;"
		"ADDPD %%XMM6,%%XMM7;"
		"ADDPD %%XMM3,%%XMM5;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADDPD %%XMM3,%%XMM2;"
		"ADDPD %%XMM4,%%XMM5;"
		"ADDPD %%XMM6,%%XMM7;"
		"ADDPD %%XMM3,%%XMM5;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADDPD %%XMM3,%%XMM2;"
		"ADDPD %%XMM4,%%XMM5;"
		"ADDPD %%XMM6,%%XMM7;"
		"ADDPD %%XMM3,%%XMM5;"
		"ADDPD %%XMM1,%%XMM0;"
"SUB $16, %%RDI;"
"JNZ LL;"
	:
	:"D"(source->size)
	:"%xmm1","%xmm0","%xmm3","%xmm2","%xmm4","%xmm5","%xmm6","%xmm7"
);
	}
return ret ;
}
