#include<bench.h>

/*
Test file name:  test_VMOVSLDUP_m_x
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_VMOVSLDUP_m_x(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"VMOVSLDUP 0(%%RBX),%%XMM1;"
		"VMOVSLDUP 0(%%RBX),%%XMM0;"
		"VMOVSLDUP 0(%%RBX),%%XMM2;"
		"VMOVSLDUP 0(%%RBX),%%XMM3;"
		"VMOVSLDUP 0(%%RBX),%%XMM1;"
		"VMOVSLDUP 0(%%RBX),%%XMM0;"
		"VMOVSLDUP 0(%%RBX),%%XMM2;"
		"VMOVSLDUP 0(%%RBX),%%XMM3;"
		"VMOVSLDUP 0(%%RBX),%%XMM1;"
		"VMOVSLDUP 0(%%RBX),%%XMM0;"
		"VMOVSLDUP 0(%%RBX),%%XMM2;"
		"VMOVSLDUP 0(%%RBX),%%XMM3;"
		"VMOVSLDUP 0(%%RBX),%%XMM1;"
		"VMOVSLDUP 0(%%RBX),%%XMM0;"
		"VMOVSLDUP 0(%%RBX),%%XMM2;"
		"VMOVSLDUP 0(%%RBX),%%XMM3;"
"SUB $16, %%RDI;"
"JNZ LL;"
	:
	:"D"(source->size),"b"(source->stream)
	:"%xmm1","%xmm0","%xmm2","%xmm3"
);
	}
return ret ;
}
