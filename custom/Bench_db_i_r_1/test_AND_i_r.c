#include<bench.h>

/*
Test file name:  test_AND_i_r
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_AND_i_r(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"AND $1,%%RAX;"
		"AND $1,%%R10;"
		"AND $1,%%R8;"
		"AND $1,%%R9;"
		"AND $1,%%RAX;"
		"AND $1,%%R10;"
		"AND $1,%%R8;"
		"AND $1,%%R9;"
		"AND $1,%%RAX;"
		"AND $1,%%R10;"
		"AND $1,%%R8;"
		"AND $1,%%R9;"
		"AND $1,%%RAX;"
		"AND $1,%%R10;"
		"AND $1,%%R8;"
		"AND $1,%%R9;"
		"AND $1,%%RAX;"
		"AND $1,%%R10;"
		"AND $1,%%R8;"
		"AND $1,%%R9;"
		"AND $1,%%RAX;"
		"AND $1,%%R10;"
		"AND $1,%%R8;"
		"AND $1,%%R9;"
		"AND $1,%%RAX;"
		"AND $1,%%R10;"
		"AND $1,%%R8;"
		"AND $1,%%R9;"
		"AND $1,%%RAX;"
		"AND $1,%%R10;"
		"AND $1,%%R8;"
		"AND $1,%%R9;"
"SUB $32, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: "%xmm0", "%xmm1", "%xmm2", "%xmm3"
);
	}
return ret ;
}
