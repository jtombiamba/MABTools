#!/bin/bash
i=0
IFS=';'
path1=$HOME/work_folder/Benchmark
path2=$HOME/local/x86_64-GenTests/GenTest
while getopts "F:" OPTION;
do 
	case $OPTION in
		F) XFile=${OPTARG};;
	esac
done
let decalage=$OPTIND-1
shift $decalage

while read line
	do
		temp="/tmp/tmp.$$.csv"
		#i=`expr $i + 1`
		#split the line read to take the name of the test
		array=($line)
		i=$(echo ${array[0]})
		param=$(echo ${array[1]})
		Xsize=$(echo ${array[2]})
		out=$(echo ${array[3]}";"${array[4]}";"${array[5]}";"${array[6]}";"${array[7]})
		#echo $i $param
		echo -e "$out" > $temp
		echo ">> File generated test_$i"
		./GenGramTest.sh -I ../InstructionLists/x86_Full_InsnList.csv -C Config/Config_64_james.csv -L $temp -D test_$i -X $Xsize -P $param
		rm $temp
	done < $XFile

 cd $HOME/work_folder/Benchmark/mbench/BUILD/
 make clean install
 cd ../..
 echo "Launching all generated benchs"
 #for i in $`ls test_*.b`; do
	#	launch=${i%.b}
	#	echo ">> generating $launch"
	#	mbench_bc $i $launch;
	#	./$launch -s 32mb;
	#done
	./script_benching -s 32mb

