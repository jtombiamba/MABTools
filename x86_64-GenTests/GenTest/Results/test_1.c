#include<bench.h>

/*
Test file name:  test_1
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_1(stream_t *source){
		perf_t ret ={0, 0};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"MOV $1,%%RAX;"
		"MOV $1,%%RBX;"
		"MOV $1,%%R8;"
		"MOV $1,%%R9;"
		"MOV $1,%%RAX;"
		"MOV $1,%%RBX;"
		"MOV $1,%%R8;"
		"MOV $1,%%R9;"
		"MOV $1,%%RAX;"
		"MOV $1,%%RBX;"
		"MOV $1,%%R8;"
		"MOV $1,%%R9;"
		"MOV $1,%%RAX;"
		"MOV $1,%%RBX;"
		"MOV $1,%%R8;"
		"MOV $1,%%R9;"
"SUB $16, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: 
);
		ret.instructions = source->size;
		ret.bytes = source->size;
	} else { 
		ret.instructions = 0 ;
	}
return ret ;
}
