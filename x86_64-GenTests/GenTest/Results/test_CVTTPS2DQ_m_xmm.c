#include<bench.h>

/*
Test file name:  test_CVTTPS2DQ_m_xmm
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_CVTTPS2DQ_m_xmm(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
		"CVTTPS2DQ 0(%%RBX),%%XMM1;"
"SUB $16, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: "%xmm0", "%xmm1", "%xmm2", "%xmm3"
);
	}
return ret ;
}
