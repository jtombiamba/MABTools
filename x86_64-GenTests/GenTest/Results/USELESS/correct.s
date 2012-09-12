#include<bench.h>

/*
Test file name:  correct
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t correct(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%R8;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%R8;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%R8;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%R8;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%R8;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%R8;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%R8;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%RAX;"
		"ADDPD %%XMM1,%%XMM0;"
		"ADD $1,%%R8;"
		"ADDPD %%XMM1,%%XMM0;"
"SUB $32, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: "%xmm1", "%xmm2"
);
	}
return ret ;
}
