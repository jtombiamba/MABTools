#include<bench.h>

/*
Test file name:  test_bsf_m_r
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_bsf_m_r(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"BSF 0(%%RBX),%%R8;"
		"BSF 0(%%RBX),%%RAX;"
		"BSF 0(%%RBX),%%R10;"
		"BSF 0(%%RBX),%%R8;"
		"BSF 0(%%RBX),%%RAX;"
		"BSF 0(%%RBX),%%R10;"
		"BSF 0(%%RBX),%%R8;"
		"BSF 0(%%RBX),%%RAX;"
		"BSF 0(%%RBX),%%R10;"
		"BSF 0(%%RBX),%%R8;"
		"BSF 0(%%RBX),%%RAX;"
		"BSF 0(%%RBX),%%R10;"
		"BSF 0(%%RBX),%%R8;"
		"BSF 0(%%RBX),%%RAX;"
		"BSF 0(%%RBX),%%R10;"
		"BSF 0(%%RBX),%%R8;"
"SUB $16, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: 
);
	}
return ret ;
}
