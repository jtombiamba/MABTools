#!/bin/bash

# Script used to generate a .s file containing as much instruction as possible from the x86 grammar
# Only 64 bits mode in this version
trap "clean" 15
AWKGENGRAM=GenGramTest-V5.awk
IFS=';'
function usage() {
	echo "Usage : $0 -I <InstructionList> -C <Configuration> -F <FileSize> -S <ArchitectureSize> -D <DestinationFile> -L <LauncherFile> -P <ListParameters> -X <Unroll>" 
	echo "InstructionList (mandatory) : List of instructions in CSV format (as required by the awk script)"
	echo "Configuration (mandatory) : List of arguments use to generate the test file (in CSV format)"
	echo "Launcher (mandatory) : List of specific instructions to be present in the output file (in CSV format)"
	echo "ListParameters(mandatory) : List of specific parameters to be included in Output file (in CSV format)"
	echo "Unroll (mandatory) : Specify the size of the unrolling generation"
	echo " FileSize (-F)		: Specify the size of the generated instructions. (Att/Intel)"
	echo "Options:"
	echo " ArchitectureSize (-S)	: Specify the architecture's size. (32/64)"
	echo " DestinationFile (-D)	: Specify the output file (No path accepted, only file's name)"
	exit
}

function recap() {
	echo -e "#include<bench.h>\n" >> FinalFile.tmp
	echo "/*" >> FinalFile.tmp
	echo "Test file name: " $TestFile >> FinalFile.tmp
	echo "This test file was created with the following script : " >> FinalFile.tmp
	echo "$0" >> FinalFile.tmp
	echo " using awk scripts: " >> FinalFile.tmp
	echo " AWKGENGRAM=" $AWKGENGRAM >> FinalFile.tmp
	echo " and the files: " >> FinalFile.tmp
	echo "Instruction List file: " $ListFile >> FinalFile.tmp
	echo "*/" >> FinalFile.tmp
	echo " " >> FinalFile.tmp
	echo -e "/* start code here */\n" >> FinalFile.tmp
	echo "perf_t $TestFile(stream_t *source){" >> FinalFile.tmp
	echo "		perf_t ret ={source->size, source->size};" >> FinalFile.tmp
	echo "		if (source->size>=16){" >> FinalFile.tmp
	echo "			__asm__ __volatile__ (" >> FinalFile.tmp
	#echo "Label:" >> FinalFile.tmp
	#echo "\"MOV $""100,%%RCX;\"" >> FinalFile.tmp # 100 will be a parameter
	echo "\"LL:\"" >> FinalFile.tmp
}

function clobber() {
	while read line
	do
		array=($line)
	done < $1	
	echo $array
}

function close(){
	lines=`cat InstrArgs.tmp| wc -l`
#	echo "ENDREP" >> InstrArgs.tmp
	echo "\"SUB $""${lines}"", %%RDI;\"">> InstrArgs.tmp
	#echo "DEC $""EBP" >> InstrArgs.tmp
	echo "\"JNZ LL;\"" >> InstrArgs.tmp
	echo "	:" >> InstrArgs.tmp
	#echo "	: \"D\" (source->size) ">> InstrArgs.tmp

	head -n 1 temp_mem.tmp | tail -n 1 >> InstrArgs.tmp
	#echo "	: " >> InstrArgs.tmp
	head -n 1 temp_reg.tmp | tail -n 1 >> InstrArgs.tmp
	#echo $(clobber temp_reg.tmp) >> InstrArgs.tmp
	echo ");" >> InstrArgs.tmp
	echo "	}" >> InstrArgs.tmp
	echo "return ret ;" >> InstrArgs.tmp
	echo "}" >> InstrArgs.tmp
}

#function to create bench and add the function in the header file

function create_bench(){
	echo "s_test = runtime;" >> BenchFile.tmp
	echo "thread:0.$TestFile(s_test);" >> BenchFile.tmp
	echo "time(thread:0.$TestFile(s_test););" >> BenchFile.tmp
	echo "perf_t $TestFile(stream_t *source);" >> $HOME/work_folder/Benchmark/mbench/src/lib/include/custom.h
}

function clean() {
rm Instrb.tmp
rm InstrArgs.tmp
rm InstrArgs2.tmp
rm BenchFile.tmp
rm FinalFile.tmp
if [ "$Format" = "Att" ]; then rm InstrAT_T.tmp 
fi
rm Compilation/Compilation_error_o_$TestFile.txt
if [ -f Compilation/dot_o/$TestFile.o ]; then rm Compilation/Compilation_error_exe_$TestFile.txt 
fi
}

if [ $# -le 3 ];then
	usage
fi

#Default options
Format="Att"
Size="64"

#Generates output directories if they don't exist
if [ ! -d Results ];then
	mkdir Results
fi
if [ ! -d Compilation ];then
	mkdir Compilation
fi
if [ ! -d Compilation/dot_o ];then
	mkdir Compilation/dot_o
fi
if [ ! -d Checks ];then
	mkdir Checks
fi

if [ ! -d ../../custom ];then
	mkdir ../../custom
fi

#Handle parameters
while getopts "I:C:S:D:L:P:X:" OPTION;
do	
	case $OPTION in
		I )	ListFile=${OPTARG};;
  		C )	ConfigFile=${OPTARG};;
  		X )	LineSize=${OPTARG};;
  		S )	Size=${OPTARG};;
		D )	TestFile=${OPTARG};;
		P ) ListParam=${OPTARG};;
		L ) LaunchFile=${OPTARG};;
		* )	usage;;
 	esac
done
let decalage=$OPTIND-1
shift $decalage

if [ -f "$ListFile" ]; then

	#Intel/Att instructions
	if [ "$Format" = "Att" ]; then
		echo "Switch Intel format to AT&T format"
		gawk -F";" 'BEGIN{OFS=";"} {print $20,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$1,$21,$22}' $ListFile > InstrAT_T.tmp
		cat InstrAT_T.tmp > InstrArgs.tmp
	else 	
		cat $ListFile > InstrArgs.tmp
	fi
else 
	echo "Instruction List File does not exist"
	exit
fi

#Filter 64/32 bits instructions
if [ "$Size" = "32" ]; then
	echo "Filter 32 bits instructions from list"
	gawk -F";" '{ if($17=="Valid") print $0; }' InstrArgs.tmp > Instrb.tmp
	cat Instrb.tmp > InstrArgs.tmp
else 
	echo "Filter 64 bits instructions from list"
	gawk -F";" '{ if($16=="Valid") print $0; }' InstrArgs.tmp > Instrb.tmp
	cat Instrb.tmp > InstrArgs.tmp
fi

if [ -f "$ConfigFile" ]; then	
	#Generates instructions per each argument
	for i in 0 1 2 3 4
	do
		echo "Generates instruction list for argument $i"
		gawk --re-interval -v launch="$LaunchFile" -v config="$ConfigFile" -f $AWKGENGRAM argpos=$i InstrArgs.tmp > InstrArgs2.tmp
		cat InstrArgs2.tmp > InstrArgs.tmp
		#cat InstrArgs2.tmp > InstrArgs$i+5.tmp
	done
else
	echo "Configuration file does not exist"
	clean
	exit
fi

#Writes the operande size suffix (depends on instructions)
echo "Print recap in final file"
recap
echo "Defines operand size"
#JECXZ/JRXCXZ/LOOP not handled due to gcc's checks
gawk --re-interval -F';' 'BEGIN{OFS=";"}
	{
		if(((match($8,"MEM")>0)||(match($8,"IMM")>0))&&((match($9,"MEM")>0)||(match($9,"IMM")>0)||($9=="-"))&&((match($10,"MEM")>0)||(match($10,"IMM")>0)||($10=="-"))&&((match($11,"MEM")>0)||(match($11,"IMM")>0)||($11=="-"))&&($1!="XLAT")&&($1!="PINSRW")&&($1!="PINSRQ")&&($1!="PINSRD")&&($1!="SMSW")&&($1!="SLDT")&&($1!="JMP")&&($1!="FSTP")&&($1!="FLD")&&($1!="FBSTP")&&($1!="FBLD")&&($1!="CMPSD")&&($1!="CMPSQ")&&($1!="CMPSW")&&($1!="CALL")&&($1!="CMPSB")&&(index($1,"MXCSR")==0)&&($1!="CLFLUSH")&&(match($1,"PREF|ETCH")==0)&&(match($1,/^VM/)==0)||($1=="CRC32")||($1=="REP INS")||($1=="INS")||(index($1,"OUTS")>0))
		{
			if(($8=="MEMB")||($9=="MEMB")||($10=="MEMB")||($11=="MEMB")) print $1 "B",$2,$3,$4,"",$12;
			else if(($8=="MEMS")||($9=="MEMS")||($10=="MEMS")||($11=="MEMS")) print $1 "S",$2,$3,$4,"",$12;
			else if(($8=="MEMW")||($9=="MEMW")||($10=="MEMW")||($11=="MEMW")) print $1 "W",$2,$3,$4,"",$12;
			else if(($8=="MEML")||($9=="MEML")||($10=="MEML")||($11=="MEML")) print $1 "L",$2,$3,$4,"",$12;
			else if(($8=="MEMQ")||($9=="MEMQ")||($10=="MEMQ")||($11=="MEMQ")) print $1 "Q",$2,$3,$4,"",$12;
			else print $1,$2,$3,$4,$5,$12;
		} 
		else if (($1=="JECXZ")||($1=="JRCXZ")||(index($1,"LOOP")==1)){
			print "//"$1,$2,$3,$4,$5;
		}
		else  
			{print $1,$2,$3,$4,$5,$12;}
	}' InstrArgs.tmp > InstrArgs2.tmp
	cat InstrArgs2.tmp > InstrArgs7.tmp
	
	gcc -o split_old mylib.h mylib_old.c split_old.c 
	./split_old -s $LineSize -p $ListParam
	cp InstrArgs6.tmp InstrArgs2.tmp
	rm split_old


#Creates the assembly file
echo "Set instruction list to ASM format"
gawk -F";" '{ out=$1 " "; if($2!="") out=out $2; if($3!="") out=out "," $3; if($4!="") out=out "," $4; if($5!="") out=out "," $5;print "		\""out";\"";}' InstrArgs2.tmp > InstrArgs.tmp
close
#cat FinalFile.tmp InstrArgs.tmp > Results/$TestFile.s
cat FinalFile.tmp InstrArgs.tmp > Results/$TestFile.c
cat FinalFile.tmp InstrArgs.tmp > ../../custom/$TestFile.c
create_bench
cat BenchFile.tmp > ../../../work_folder/Benchmark/$TestFile.b

#Compiles the generated file
echo "Compilation"
if [ "$Format" = "Intel" ]; then
	echo "Intel format compilation not yet implemented"
	#icc -c $TestFile -o Compilation/InstrList.o 2>Compilation/Compilation_error.txt
else if [ "$Size" = "32" ]; then
		gcc -m32 -c Results/$TestFile.c -o Compilation/dot_o/$TestFile.o 2>Compilation/Compilation_error_o_$TestFile.txt
	else 
		gcc -m64 -c Results/$TestFile.c -o Compilation/dot_o/$TestFile.o 2>Compilation/Compilation_error_o_$TestFile.txt
	fi
fi


if [ -f Compilation/dot_o/$TestFile.o ]; then
	#Apply objdump on the compiled file if it was succesfully compiled
	echo "Objdump on the compiled instruction list"
	objdump -d Compilation/dot_o/$TestFile.o > Checks/Objdump_$TestFile.txt

	#Linking to stand alone .c to check for undeclared symbols
	echo "Linking with a main"
	gcc -o Compilation/exe/$TestFile Compilation/main.c Compilation/dot_o/$TestFile.o 2>Compilation/Compilation_error_exe_$TestFile.txt
	cat Compilation/Compilation_error_o_$TestFile.txt Compilation/Compilation_error_exe_$TestFile.txt > Compilation/Compilation_error_$TestFile.txt
else
	echo "The compilation failed, objdump cancelled"
	cat Compilation/Compilation_error_o_$TestFile.txt > Compilation/Compilation_error_$TestFile.txt
fi

clean
