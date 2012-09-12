#include<bench.h>

/*
Test file name:  test_VCVTPD2DQ_xmm_xmm
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
 
/* start code here */

perf_t test_VCVTPD2DQ_xmm_xmm(stream_t *source){
		perf_t ret ={source->size, source->size};
		if (source->size>=16){
			__asm__ __volatile__ (
"LL:"
		"VCVTPD2DQ %%XMM0,%%XMM1;"
		"VCVTPD2DQ %%XMM3,%%XMM0;"
		"VCVTPD2DQ %%XMM2,%%XMM3;"
		"VCVTPD2DQ %%XMM0,%%XMM1;"
		"VCVTPD2DQ %%XMM3,%%XMM0;"
		"VCVTPD2DQ %%XMM2,%%XMM3;"
		"VCVTPD2DQ %%XMM0,%%XMM1;"
		"VCVTPD2DQ %%XMM3,%%XMM0;"
		"VCVTPD2DQ %%XMM2,%%XMM3;"
		"VCVTPD2DQ %%XMM0,%%XMM1;"
		"VCVTPD2DQ %%XMM3,%%XMM0;"
		"VCVTPD2DQ %%XMM2,%%XMM3;"
		"VCVTPD2DQ %%XMM0,%%XMM1;"
		"VCVTPD2DQ %%XMM3,%%XMM0;"
		"VCVTPD2DQ %%XMM2,%%XMM3;"
		"VCVTPD2DQ %%XMM0,%%XMM1;"
"SUB $16, %%RCX;"
"JNZ LL;"
	:
	: "c" (source->size), "b"(source->stream) 
	: 
);
	}
return ret ;
}
