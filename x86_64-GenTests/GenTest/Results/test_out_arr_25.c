#include<bench.h>

/*
Test file name:  test_out_arr_25
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_out_arr_25(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"MOVAPS 0(%%RAX),%%XMM3;"
		"MOVAPS 0(%%RBX),%%XMM1;"
		"MULPD %%XMM0,%%XMM2;"
		"MOVAPS %%XMM3,0(%%RAX);"
		"ADDPS %%XMM1,%%XMM0;"
		"MOVAPS 0(%%RBX),%%XMM2;"
		"MOVAPS 0(%%RAX),%%XMM3;"
		"MULPD %%XMM1,%%XMM0;"
		"MOVAPS %%XMM2,0(%%RBX);"
		"ADDPS %%XMM3,%%XMM1;"
		"MOVAPS 0(%%RAX),%%XMM0;"
		"MOVAPS 0(%%RBX),%%XMM2;"
		"MULPD %%XMM3,%%XMM1;"
		"MOVAPS %%XMM0,0(%%RAX);"
		"ADDPS %%XMM2,%%XMM3;"
		"MOVAPS 0(%%RBX),%%XMM1;"
		"MOVAPS 0(%%RAX),%%XMM0;"
		"MULPD %%XMM2,%%XMM3;"
		"MOVAPS %%XMM1,0(%%RBX);"
		"ADDPS %%XMM0,%%XMM2;"
		"MOVAPS 0(%%RAX),%%XMM3;"
		"MOVAPS 0(%%RBX),%%XMM1;"
		"MULPD %%XMM0,%%XMM2;"
		"MOVAPS %%XMM3,0(%%RAX);"
		"ADDPS %%XMM1,%%XMM0;"
		"MOVAPS 0(%%RBX),%%XMM2;"
		"MOVAPS 0(%%RAX),%%XMM3;"
		"MULPD %%XMM1,%%XMM0;"
		"MOVAPS %%XMM2,0(%%RBX);"
		"ADDPS %%XMM3,%%XMM1;"
		"MOVAPS 0(%%RAX),%%XMM0;"
		"MOVAPS 0(%%RBX),%%XMM2;"
		"MULPD %%XMM3,%%XMM1;"
		"MOVAPS %%XMM0,0(%%RAX);"
		"ADDPS %%XMM2,%%XMM3;"
		"MOVAPS 0(%%RBX),%%XMM1;"
		"MOVAPS 0(%%RAX),%%XMM0;"
		"MULPD %%XMM2,%%XMM3;"
		"MOVAPS %%XMM1,0(%%RBX);"
		"ADDPS %%XMM0,%%XMM2;"
"SUB $40, %%RDI;"
"JNZ LL;"
	:
	:"D"(source->size),"a"(source->stream),"b"(source->stream)
	:"%xmm3","%xmm1","%xmm0","%xmm2"
);
	}
return ret ;
}
