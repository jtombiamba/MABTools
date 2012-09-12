#include<bench.h>

/*
Test file name:  couple_add_addpd_james
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t couple_add_addpd_james(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM0,%%XMM2;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM2,%%XMM3;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM3,%%XMM1;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM0,%%XMM2;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM2,%%XMM3;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM3,%%XMM1;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM0,%%XMM2;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM2,%%XMM3;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM3,%%XMM1;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM0,%%XMM2;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM2,%%XMM3;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM3,%%XMM1;"
"SUB $32, %%RDI;"
"JNZ LL;"
	:
	:"D"(source->size)
	:"%rax","%xmm1","%xmm0","%xmm2","%xmm3"
);
	}
return ret ;
}
