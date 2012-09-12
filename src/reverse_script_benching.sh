#!/bin/bash
i=0
IFS=';'
while getopts "F:s:" OPTION;
do
	case $OPTION in
		F) XFile = ${OPTARG};;
		s) Xsize = ${OPTARG};;
	esac
done
let decalage=$OPTIND-1
shift decalage

while read line
	do
		array=($line)
		i=$(echo ${array[0]})
		param=$(echo ${array[1]})
		./GenGramTest -I ../InstructionLists/x86_Full_InsnList.csv -C Config/Config_64_james.csv -L $i -D test_$i -X $Xsize -P $param
	done < $XFile	

	cd $HOME/work_folder/Benchmark/mbench/BUILD
	make clean install
	cd ../..
	echo "Launching all generated arrangements"
	./script_benching

