#include<bench.h>

/*
Test file name:  test_rol_i_r
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_rol_i_r(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"VBROADCASTSD 0(%%RBX),%%YMM0;"
		"VBROADCASTSD 0(%%RBX),%%YMM1;"
		"VBROADCASTSD 0(%%RBX),%%YMM2;"
		"VBROADCASTSD 0(%%RBX),%%YMM4;"
		"VBROADCASTSD 0(%%RBX),%%YMM0;"
		"VBROADCASTSD 0(%%RBX),%%YMM1;"
		"VBROADCASTSD 0(%%RBX),%%YMM2;"
		"VBROADCASTSD 0(%%RBX),%%YMM4;"
		"VBROADCASTSD 0(%%RBX),%%YMM0;"
		"VBROADCASTSD 0(%%RBX),%%YMM1;"
		"VBROADCASTSD 0(%%RBX),%%YMM2;"
		"VBROADCASTSD 0(%%RBX),%%YMM4;"
		"VBROADCASTSD 0(%%RBX),%%YMM0;"
		"VBROADCASTSD 0(%%RBX),%%YMM1;"
		"VBROADCASTSD 0(%%RBX),%%YMM2;"
		"VBROADCASTSD 0(%%RBX),%%YMM4;"
"SUB $16, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: 
);
	}
return ret ;
}
