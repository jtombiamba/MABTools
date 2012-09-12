/*
Test file name:  sortie
This test file was created with the following script : 
./GenGramTest.sh
 using awk scripts: 
 AWKGENGRAM= GenGramTest-V5.awk
 and the files: 
Instruction List file:  ../InstructionLists/x86_Full_InsnList.csv
*/
Label:
CBW 
CLTD 
CLTQ 
CLC 
CLD 
CLI 
CLTS 
CMC 
CMPSL %es:(%edi),%ds:(%esi)
CMPSL %es:(%edi),%ds:(%esi)
CMPSL %es:(%edi),%ds:(%esi)
CMPSQ (%rdi),(%rsi)
CMPSL (%edi),(%esi)
CMPSB 
CMPSD 
CMPSQ 
CMPSL 
CPUID 
CQTO 
CWD 
CWTL 
EMMS 
F2XM1 
FABS 
FADDP 
FCHS 
FCLEX 
FCOM 
FCOMP 
FCOMPP 
FCOS 
FDECSTP 
FDIVP 
FDIVRP 
FEMMS 
FINCSTP 
FINIT 
FLD1 
FLDL2E 
FLDL2T 
FLDLG2 
FLDLN2 
FLDPI 
FLDZ 
FMULP 
FNCLEX 
FNINIT 
FNOP 
FNSTSW %AX
FPATAN 
FPREM 
FPREM1 
FPTAN 
FRNDINT 
FSCALE 
FSIN 
FSINCOS 
FSQRT 
FSTSW %AX
FSUBP 
FSUBRP 
FTST 
FUCOM 
FUCOMP 
FUCOMPP 
FWAIT 
FXAM 
FXCH 
FXTRACT 
FYL2X 
FYL2XP1 
GETSEC 
HLT 
IN %DX,%AL
IN %DX,%EAX
IN %DX,%AX
INSL %DX,%es:(%edi)
INSL %DX,%es:(%edi)
INSL %DX,%es:(%edi)
INSB 
INSL 
INSW 
INT $3
INVD 
IRET 
IRETL 
IRETQ 
LEAVE 
LEAVE 
LFENCE 
LOCK 
LODSL (%rsi)
LODSL (%rsi)
LODSL (%rsi)
LODSL (%rsi)
LODSB 
LODSL 
LODSQ 
LODSW 
MFENCE 
MONITOR 
MOVSL %ds:(%esi),%es:(%edi)
MOVSL %ds:(%esi),%es:(%edi)
MOVSL %ds:(%esi),%es:(%edi)
MOVSL %ds:(%esi),%es:(%edi)
MOVSB 
MOVSL 
MOVSQ 
MOVSW 
MWAIT 
NOP 
OUT %AL,%DX
OUT %AX,%DX
OUT %EAX,%DX
OUTSL %ds:(%esi),%DX
OUTSL %ds:(%esi),%DX
OUTSL %ds:(%esi),%DX
OUTSB 
OUTSL 
OUTSW 
PAUSE 
POP %FS
POP %FS
POP %GS
POP %GS
POPF 
POPFQ 
PUSH %FS
PUSH %FS
PUSH %GS
PUSH %GS
PUSHF 
PUSHFQ 
RDMSR 
RDMSR 
RDPMC 
RDTSC 
RDTSCP 
REP INSL %DX,(%rdi)
REP INSL %DX,%es:(%edi)
REP INSL %DX,(%rdi)
REP INSL %DX,%es:(%edi)
REP INSL %DX,%es:(%edi)
REP LODS (%rsi),%AL
REP LODS %ds:(%esi),%AL
REP LODS (%rsi),%RAX
REP LODS %ds:(%esi),%EAX
REP LODS %ds:(%esi),%AX
REP MOVSL (%rsi),(%rdi)
REP MOVSL %ds:(%esi),%es:(%edi)
REP MOVSL %ds:(%esi),%es:(%edi)
REP MOVSL %ds:(%esi),%es:(%edi)
REP MOVSL (%rsi),(%rdi)
REP OUTSL %ds:(%esi),%DX
REP OUTSL (%rsi),%DX
REP OUTSL (%rsi),%DX
REP OUTSL %ds:(%esi),%DX
REP OUTSL %ds:(%esi),%DX
REP STOSL (%rdi)
REP STOSL %es:(%edi)
REP STOSL %es:(%edi)
REP STOSL (%rdi)
REP STOSL %es:(%edi)
REPE CMPSL %es:(%edi),%ds:(%esi)
REPE CMPSL (%rdi),(%rsi)
REPE CMPSL %es:(%edi),%ds:(%esi)
REPE CMPSL %es:(%edi),%ds:(%esi)
REPE CMPSL (%rdi),(%rsi)
REPE SCASL %es:(%edi)
REPE SCASL (%rdi)
REPE SCASL (%rdi)
REPE SCASL %es:(%edi)
REPE SCASL %es:(%edi)
REPNE CMPSL %es:(%edi),%ds:(%esi)
REPNE CMPSL (%rdi),(%rsi)
REPNE CMPSL (%rdi),(%rsi)
REPNE CMPSL %es:(%edi),%ds:(%esi)
REPNE CMPSL %es:(%edi),%ds:(%esi)
REPNE SCASL %es:(%edi)
REPNE SCASL (%rdi)
REPNE SCASL %es:(%edi)
REPNE SCASL %es:(%edi)
REPNE SCASL (%rdi)
RET 
RET 
SCASL %es:(%edi)
SCASQ (%rdi)
SCASL (%edi)
SCASL %es:(%edi)
SCASL %es:(%edi)
SCASB 
SCASL 
SCASQ 
SCASW 
SFENCE 
STC 
STD 
STI 
STOSL (%rdi)
STOSL (%rdi)
STOSL (%rdi)
STOSQ (%edi)
STOSB 
STOSL 
STOSQ 
STOSW 
SWAPGS 
SYSCALL 
SYSENTER 
SYSEXIT 
SYSEXIT 
SYSRET 
UD2 
VMCALL 
VMLAUNCH 
VMRESUME 
VMXOFF 
VZEROALL 
VZEROUPPER 
WAIT 
WBINVD 
WRMSR 
WRMSR 
XGETBV 
XLAT %ds:(%rbx)
XLAT %ds:(%ebx)
XLATB 
XLATB 
XSETBV 
