#include<bench.h>

/*
Test file name:  test_imul_imm_r_r
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_imul_imm_r_r(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"IMUL $1,%%RAX,%%RBX;"
		"IMUL $1,%%RBX,%%RDX;"
		"IMUL $1,%%RDX,%%RBP;"
		"IMUL $1,%%RBP,%%RBX;"
		"IMUL $1,%%RAX,%%RDX;"
		"IMUL $1,%%RBX,%%RBP;"
		"IMUL $1,%%RDX,%%RBX;"
		"IMUL $1,%%RBP,%%RDX;"
		"IMUL $1,%%RAX,%%RBP;"
		"IMUL $1,%%RBX,%%RBX;"
		"IMUL $1,%%RDX,%%RDX;"
		"IMUL $1,%%RBP,%%RBP;"
		"IMUL $1,%%RAX,%%RBX;"
		"IMUL $1,%%RBX,%%RDX;"
		"IMUL $1,%%RDX,%%RBP;"
		"IMUL $1,%%RBP,%%RBX;"
"SUB $16, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: 
);
	}
return ret ;
}
