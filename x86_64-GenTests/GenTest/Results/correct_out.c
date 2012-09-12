#include<bench.h>

/*
Test file name:  correct_out
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t correct_out(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"ADDQ $1,0(%%RAX);"
		"ADDPD %%XMM1,%%XMM0;"
		"ADDQ $1,0(%%R8);"
		"ADDPD %%XMM1,%%XMM0;"
		"ADDQ $1,0(%%RAX);"
		"ADDPD %%XMM1,%%XMM0;"
		"ADDQ $1,0(%%R8);"
		"ADDPD %%XMM1,%%XMM0;"
		"ADDQ $1,0(%%RAX);"
		"ADDPD %%XMM1,%%XMM0;"
		"ADDQ $1,0(%%R8);"
		"ADDPD %%XMM1,%%XMM0;"
		"ADDQ $1,0(%%RAX);"
		"ADDPD %%XMM1,%%XMM0;"
		"ADDQ $1,0(%%R8);"
		"ADDPD %%XMM1,%%XMM0;"
"SUB $16, %%RDI;"
"JNZ LL;"
	:
	:"D"(source->size),"a"(source->stream)
	:"%XMM1","%XMM0"
);
	}
return ret ;
}
