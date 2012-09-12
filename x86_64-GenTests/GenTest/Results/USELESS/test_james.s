/*
Test file name:  test_james
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
Label:
MOV $100,%RCX
LL:
ADC $1,%EAX
ADD %EAX,%EAX
SUB $2, %RCX
JNZ LL
RET
