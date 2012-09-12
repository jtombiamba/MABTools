#include<bench.h>

/*
Test file name:  test_lea_m_r
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_lea_m_r(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"LEA 0(%%RBX),%%R8;"
		"LEA 0(%%RBX),%%RAX;"
		"LEA 0(%%RBX),%%R10;"
		"LEA 0(%%RBX),%%R8;"
		"LEA 0(%%RBX),%%RAX;"
		"LEA 0(%%RBX),%%R10;"
		"LEA 0(%%RBX),%%R8;"
		"LEA 0(%%RBX),%%RAX;"
		"LEA 0(%%RBX),%%R10;"
		"LEA 0(%%RBX),%%R8;"
		"LEA 0(%%RBX),%%RAX;"
		"LEA 0(%%RBX),%%R10;"
		"LEA 0(%%RBX),%%R8;"
		"LEA 0(%%RBX),%%RAX;"
		"LEA 0(%%RBX),%%R10;"
		"LEA 0(%%RBX),%%R8;"
"SUB $16, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: 
);
	}
return ret ;
}
