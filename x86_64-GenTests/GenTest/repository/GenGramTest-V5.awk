# Script used to generate an asm test of the grammar
# Must be run on a CSV file with following columns order:
# Instruction;Arg1;Arg2;Arg3;Legacy;REX;Opcode;ModR/M;Disp;Imm;64-bits Mode;Legacy Mode;Special;Description;Notes
# Needs parameter : argpos

# Version 6 : Added a specific launching file
# Version 5 : Added extended registries (%R9-15, %R9-15W, %R9-15D,...)
# Version 4 : Corrected bug with the size name
# Version 3 : Changed the registry names
# Version 2 : Added a type for the arguments

BEGIN {
	FS=";"
	OFS=";"

	#Avec l'option -v de awk config est chargée avant begin
	#On récupère le nombre de champs 
	cmd=("sed -n '1p' " config " | tr -cd ';' | wc -c")
	cmd|getline
	nb_champs=$1
	close(cmd)

	nb_champs++

	#On stocke les données dans un tableau
	cmd=("cut -d';' -f1-" nb_champs " " config)
	while (cmd|getline){
		for(cpt=2;cpt<=nb_champs;cpt++){
			tests_lists[$1,cpt-1]=$cpt
		}
	}
	close(cmd)

	cmd=("cut -d';' -f1-6 " launch " ")
	launcher_lines=1
	while (cmd|getline){
		if($1!=""){
			for(cpt=1;cpt<=6;cpt++){
				launcher[launcher_lines,cpt]=$cpt
			}
			launcher_lines++
		}
	}
	close(cmd)

	rel="Relatifs"
	imm="Immédiats"
	reg8="Reg8"
	reg8ext="Reg8ext"
	reg16="Reg16"
	reg16ext="Reg16ext"
	reg32="Reg32"
	reg32ext="Reg32ext"
	reg64="Reg64"
	reg64ext="Reg64ext"
	xmm="Xmm reg"
	xmmext="Xmm reg ext"
	ymm="Ymm reg"
	mmx="Mmx reg"
	float="Float reg"
	control="Control reg"
	debug="Debug reg"
	mem_seg="Mem:seg"
	mem_disp="Mem:disp"
	mem_base32="Mem:base32"
	mem_base32ext="Mem:base32ext"
	mem_base64="Mem:base64"
	mem_base64ext="Mem:base64ext"
	mem_index32="Mem:index32"
	mem_index32ext="Mem:index32ext"
	mem_index64="Mem:index64"
	mem_index64ext="Mem:index64ext"
	mem_scale="Mem:scale"
	mem_config="Mem:config"
	mem_szconfig="Mem:szconfig"

	gen_reg(mem_base32,mem_base32_std)
	gen_reg(mem_base32ext,mem_base32_ext)
	gen_reg(mem_base64,mem_base64_std)
	gen_reg(mem_base64ext,mem_base64_ext)
	gen_reg(mem_index32,mem_index32_std)
	gen_reg(mem_index32ext,mem_index32_ext)
	gen_reg(mem_index64,mem_index64_std)
	gen_reg(mem_index64ext,mem_index64_ext)
	gen_reg(mem_szconfig,mem_szconfig_std)
	gen_reg(mem_config, mem_config_std)
	gen_reg(reg32,reg32_std)
	gen_reg(imm,imm_std)
	gen_reg(reg32ext,reg32_ext)
	gen_reg(reg64,reg64_std)
	gen_reg(reg64ext,reg64_ext)

	argpos=0

};

function gen_reg(INDEX,DESTINATION,		cpt_dest,cpt_index,cpt_reg) {
	cpt_dest=1
	cpt_index=1
	while (tests_lists[INDEX,cpt_index]!=""){
		#Si ce test réussi c'est qu'il existe une ligne registre correspondante dans le fichier de config (i.e entrée référence "Reg32")
		if ((tests_lists[INDEX,cpt_index],1) in tests_lists) {
			cpt_reg=1
			while (tests_lists[tests_lists[INDEX,cpt_index],cpt_reg]!=""){
				DESTINATION[cpt_dest]=tests_lists[tests_lists[INDEX,cpt_index],cpt_reg]
				cpt_dest++
				cpt_reg++
			}
		}
		#Sinon c'est une entrée standard
		else {
			DESTINATION[cpt_dest]=tests_lists[INDEX,cpt_index]
			cpt_dest++
		}
		cpt_index++
	}
}

#Indice doivent commencer à 1 (thx to awk arrays handling !)
function copy(SOURCE,DESTINATION		,cpt_destination,cpt_source){

	for(cpt_destination in DESTINATION){
		delete DESTINATION[cpt_destination]
	}

	cpt_source=1
	while(SOURCE[cpt_source]!=""){
		DESTINATION[cpt_source]=SOURCE[cpt_source]
		cpt_source++
	}
}

function SizeName(SIZE,      tmp) {
	if(SIZE=="8") {
		tmp="B"
	} 
	else if(SIZE=="16") {
		# Cas x87
		if(($1=="FADD")||($1=="FCOM")||($1=="FCOMP")||($1=="FDIV")||($1=="FDIVR")||($1=="FIADD")||($1=="FICOM")||($1=="FICOMP")||($1=="FIDIV")||($1=="FIDIVR")||($1=="FILD")||($1=="FIMUL")||($1=="FIST")||($1=="FISTP")||($1=="FISTTP")||($1=="FISUB")||($1=="FISUBR")||($1=="FLD")||($1=="FMUL")||($1=="FST")||($1=="FSTP")||($1=="FSUB")||($1=="FSUBR")) {
			tmp="S"
		} 
		else {
			tmp="W"
		}
	} 
	else if(SIZE=="32") {
		# Cas x87
		if(($1=="FADD")||($1=="FCOM")||($1=="FCOMP")||($1=="FDIV")||($1=="FDIVR")) {
			tmp="S"
		} 
		else {
			tmp="L"
		}
	} 
	else if(SIZE=="64") {
		# Cas x87
		if(($1=="FADD")||($1=="FCOM")||($1=="FCOMP")||($1=="FDIV")||($1=="FDIVR")||($1=="FIADD")||($1=="FICOM")||($1=="FICOMP")||($1=="FIDIV")||($1=="FIDIVR")||($1=="FILD")||($1=="FIMUL")||($1=="FIST")||($1=="FISTP")||($1=="FISTTP")||($1=="FISUB")||($1=="FISUBR")||($1=="FLD")||($1=="FMUL")||($1=="FST")||($1=="FSTP")||($1=="FSUB")||($1=="FSUBR")) {
			tmp="L"
		} 
		else {
			tmp="Q"
		}
	} 
	else {
		tmp="_" # A CHANGER
	}
	return tmp
};

function printmem(START,FINISH,SIZE,BASE32,INDEX32,BASE64,INDEX64,DISP,NUMBER,		cpt_szconfig,cpt_config,cpt_disp,cpt_seg,tmp_disp,tmp_seg,tmp_base,cpt_tmp_base,tmp_index,cpt_tmp_index,tmp_string_base) {
	
	if ((match(START,"CALL")>0)||(match(START,"JMP")>0)) {brn="*"} else {brn=""} # Cas particuliers (branchements)


	#Pour chaque taille de registres spécifiée
	cpt_szconfig=1
	while (tests_lists[mem_szconfig,cpt_szconfig]!=""){

		if (tests_lists[mem_szconfig,cpt_szconfig]=="32"){
			copy(BASE32,tmp_base)
			copy(INDEX32,tmp_index)
		} 
		else if (tests_lists[mem_szconfig,cpt_szconfig]=="64"){
			copy(BASE64,tmp_base)
			copy(INDEX64,tmp_index)
		}
		else {break}

		cpt_config=1
		while (tests_lists[mem_config,cpt_config]!="") {
		
			if ((tests_lists[mem_config,cpt_config]=="disp")&&(cpt_szconfig==1)&&(DISP==1)){
				cpt_disp=1
				while (tests_lists[mem_disp,cpt_disp]!=""){
					print START,brn tests_lists[mem_disp,cpt_disp],FINISH,"MEM" SIZE,NUMBER
					cpt_disp++
				}
			}
			else if (tests_lists[mem_config,cpt_config]=="base"){
				cpt_tmp_base=1
				while (tmp_base[cpt_tmp_base]!=""){
					if ((tmp_base[cpt_tmp_base]!="RIP")||(cpt_szconfig<=1)){
						print START,brn "(%%" tmp_base[cpt_tmp_base] ")",FINISH,"MEM" SIZE,NUMBER
					}
					cpt_tmp_base++
				}
			}
			else if (tests_lists[mem_config,cpt_config]=="disp+base"){
				cpt_tmp_base=1
				while (tmp_base[cpt_tmp_base]!=""){
					tmp_string_base="(%%" tmp_base[cpt_tmp_base] ")"
					cpt_disp=1
					while (tests_lists[mem_disp,cpt_disp]!=""){
						if ((tmp_base[cpt_tmp_base]!="RIP")||(cpt_szconfig<=1)){
							print START,brn tests_lists[mem_disp,cpt_disp] tmp_string_base,FINISH,"MEM" SIZE,NUMBER
						}
						cpt_disp++
					}
					cpt_tmp_base++
				}
			}
			else if (tests_lists[mem_config,cpt_config]=="seg+base"){
				cpt_tmp_base=1
				while (tmp_base[cpt_tmp_base]!=""){
					tmp_string_base="(%%" tmp_base[cpt_tmp_base] ")"
					cpt_seg=1
					while (tests_lists[mem_seg,cpt_seg]!=""){
						if (((tmp_base[cpt_tmp_base]!="RIP")||(cpt_szconfig<=1))&&(match(START,"LEA")==0)){
							print START,brn "%%" tests_lists[mem_seg,cpt_seg] ":" tmp_string_base,FINISH,"MEM" SIZE,NUMBER
						}
						cpt_seg++
					}
					cpt_tmp_base++
				}
			}
			else if (tests_lists[mem_config,cpt_config]=="seg+disp+base"){
				cpt_tmp_base=1
				while (tmp_base[cpt_tmp_base]!=""){
					tmp_string_base="(%%" tmp_base[cpt_tmp_base] ")"
					cpt_disp=1
					while (tests_lists[mem_disp,cpt_disp]!=""){
						tmp_disp=tests_lists[mem_disp,cpt_disp]
						cpt_seg=1
						while (tests_lists[mem_seg,cpt_seg]!=""){
							if (((tmp_base[cpt_tmp_base]!="RIP")||(cpt_szconfig<=1))&&(match(START,"LEA")==0)){
								print START,brn "%%" tests_lists[mem_seg,cpt_seg] ":" tmp_disp tmp_string_base,FINISH,"MEM" SIZE,NUMBER
							}
							cpt_seg++
						}
						cpt_disp++
					}
					cpt_tmp_base++
				}
			}
			else if (tests_lists[mem_config,cpt_config]=="base+index+scale"){
				cpt_tmp_base=1
				while (tmp_base[cpt_tmp_base]!=""){
					tmp_string_base="(%%" tmp_base[cpt_tmp_base]
					cpt_tmp_index=1
					while (tmp_index[cpt_tmp_index]!=""){
						tmp_string_index=",%%" tmp_index[cpt_tmp_index]
						cpt_scale=1
						while (tests_lists[mem_scale,cpt_scale]!=""){
							if ((tmp_base[cpt_tmp_base]!="RIP")&&(tmp_index[cpt_tmp_index]!="ESP")&&(tmp_index[cpt_tmp_index]!="RSP")){
								print START,brn tmp_string_base tmp_string_index "," tests_lists[mem_scale,cpt_scale] ")",FINISH,"MEM" SIZE,NUMBER
							}
							cpt_scale++
						}
						cpt_tmp_index++
					}
					cpt_tmp_base++
				}
			}
			else if (tests_lists[mem_config,cpt_config]=="seg+base+index+scale"){
				cpt_tmp_base=1
				while (tmp_base[cpt_tmp_base]!=""){
					tmp_string_base="(%%" tmp_base[cpt_tmp_base]
					cpt_seg=1
					while (tests_lists[mem_seg,cpt_seg]!=""){
						tmp_seg="%%" tests_lists[mem_seg,cpt_seg] ":"
						cpt_tmp_index=1
						while (tmp_index[cpt_tmp_index]!=""){
							tmp_string_index=",%%" tmp_index[cpt_tmp_index]
							cpt_scale=1
							while (tests_lists[mem_scale,cpt_scale]!=""){
								if ((tmp_base[cpt_tmp_base]!="RIP")&&(tmp_index[cpt_tmp_index]!="ESP")&&(tmp_index[cpt_tmp_index]!="RSP")&&(match(START,"LEA")==0)){
									print START,brn tmp_seg tmp_string_base tmp_string_index "," tests_lists[mem_scale,cpt_scale] ")",FINISH,"MEM" SIZE,NUMBER
								}
								cpt_scale++
							}
							cpt_tmp_index++
						}
						cpt_seg++
					}
					cpt_tmp_base++
				}
			}
			else if (tests_lists[mem_config,cpt_config]=="disp+base+index+scale"){
				cpt_tmp_base=1
				while (tmp_base[cpt_tmp_base]!=""){
					tmp_string_base="(%%" tmp_base[cpt_tmp_base] 
					cpt_disp=1
					while (tests_lists[mem_disp,cpt_disp]!=""){
						tmp_disp=tests_lists[mem_disp,cpt_disp]
						cpt_tmp_index=1
						while (tmp_index[cpt_tmp_index]!=""){
							tmp_string_index=",%%" tmp_index[cpt_tmp_index]
							cpt_scale=1
							while (tests_lists[mem_scale,cpt_scale]!=""){
								if ((tmp_base[cpt_tmp_base]!="RIP")&&(tmp_index[cpt_tmp_index]!="ESP")&&(tmp_index[cpt_tmp_index]!="RSP")){
									print START,brn tmp_disp tmp_string_base tmp_string_index "," tests_lists[mem_scale,cpt_scale] ")",FINISH,"MEM" SIZE,NUMBER
								}
								cpt_scale++
							}
							cpt_tmp_index++
						}
						cpt_disp++
					}
					cpt_tmp_base++
				}
			}
			else if (tests_lists[mem_config,cpt_config]=="seg+disp+base+index+scale"){ #TODO match
				cpt_tmp_base=1
				while (tmp_base[cpt_tmp_base]!=""){
					tmp_string_base="(%%" tmp_base[cpt_tmp_base]
					cpt_seg=1
					while (tests_lists[mem_seg,cpt_seg]!=""){
						tmp_seg="%%" tests_lists[mem_seg,cpt_seg] ":"
						cpt_disp=1
						while (tests_lists[mem_disp,cpt_disp]!=""){
							tmp_disp=tests_lists[mem_disp,cpt_disp]
							cpt_tmp_index=1
							while (tmp_index[cpt_tmp_index]!=""){
								tmp_string_index=",%%" tmp_index[cpt_tmp_index]
								cpt_scale=1
								while (tests_lists[mem_scale,cpt_scale]!=""){
									if ((tmp_base[cpt_tmp_base]!="RIP")&&(tmp_index[cpt_tmp_index]!="ESP")&&(tmp_index[cpt_tmp_index]!="RSP")&&(match(START,"LEA")==0)){
										print START,brn tmp_seg tmp_disp tmp_string_base tmp_string_index "," tests_lists[mem_scale,cpt_scale] ")",FINISH,"MEM" SIZE,NUMBER
									}
									cpt_scale++
								}
								cpt_tmp_index++
							}
							cpt_disp++
						}
						cpt_seg++
					}
					cpt_tmp_base++
				}
			}
			cpt_config++
		}
		cpt_szconfig++
	}

}

function printrel(START,FINISH,		cpt_rel,brn){
	if ((match(START,"CALL")>0)||(match(START,"JMP")>0)) {brn="*"} else {brn=""}
	cpt_rel=1
	while (tests_lists[rel,cpt_rel]!=""){
		print START,brn tests_lists[rel,cpt_rel],FINISH,"REL"
		cpt_rel++
	}
}

function printreg(START,FINISH,INDEX,WITHOUT,NUMBER,		cpt_reg){
	if ((match(START,"CALL")>0)||(match(START,"JMP")>0)) {brn="*"} else {brn=""}
	cpt_reg=1
	while (tests_lists[INDEX,cpt_reg]!=""){
		if ((WITHOUT=="")||(match(tests_lists[INDEX,cpt_reg],WITHOUT)==0)){
			print START, brn "%%" tests_lists[INDEX,cpt_reg],FINISH,"REG",NUMBER
		}
		cpt_reg++
	}
}

#in the next function I commented the test comparison because I didn't need it for my work
function printimm(START,FINISH,SIZE,MIN,MAX,NUMBER,		cpt_imm){			
	cpt_imm=1
	#print START
	while (tests_lists[imm,cpt_imm]!=""){
		#print "IMM",tests_lists[imm,cpt_imm],MIN,MAX
		#if ((tests_lists[imm,cpt_imm]>=MIN)&&(tests_lists[imm,cpt_imm]<=MAX)){
			print START, "$" tests_lists[imm,cpt_imm],FINISH,"IMM" SIZE,NUMBER
		#}
		cpt_imm++
	}
}

function genparams(START,ARG,FINISH,NUMBER,     	tmp,equal,size) {
	tmp=""

	# cherche "=" dans ARG et renvoi l'indice
	equal=index(ARG,"=") 

	# présence d'un "=" => argument fixe
	if(equal>0) {
		# renvoi la partie de la chaine ARG commencant à l'indice equal+1 (renvoi l'argument après le "=")
		tmp=substr(ARG,equal+1) 

		# applique une regex sur ARG
		if((match(ARG,/r[123468]{1,2}/)>0)||(match(ARG,/CR[0-9]/)>0)) {
			tmp = "%%" tmp
			size= "REG"
		} else if(match(ARG,/imm[123468]{1,2}/)>0) {
			tmp = "$" tmp
			size= "IMM" SizeName(gensub(/imm([123468]{1,2}).*/,"\\1","g",ARG))
		} else if(match(ARG,/mem/)>0) {
			tmp = "" 
			size= "MEMQ"
		} else if(match(tmp,/DS\:\(E\)SI/)>0) {
			tmp = "%%ds:(%%esi)"
			size= "MEML"
		} else if(match(tmp,/ES\:\(E\)DI/)>0) {
			tmp = "%%es:(%%edi)"
			size= "MEML"
		} else if(match(tmp,/\(R\)DI\/\(E\)DI/)>0) {
			if (match(FINISH,"MEMQ")>0) {
				tmp ="(%%rdi)"
				size="MEMQ"
			}
			else if (match(FINISH,"MEML")>0) {
				tmp ="(%%edi)"
				size="MEML"
			}
			else {
				print START,"(%%rdi)",FINISH,"MEMQ" 
				tmp ="(%%edi)"
				size="MEML"
			}
		} else if(match(tmp,/\(R\)SI\/\(E\)SI/)>0) {
			if (match(FINISH,"MEMQ")>0) {
				tmp ="(%%rsi)"
				size="MEMQ"
			}
			else if (match(FINISH,"MEML")>0) {
				tmp ="(%%esi)"
				size="MEML"
			}
			else {
				print START,"(%%rsi)",FINISH,"MEMQ" 
				tmp ="(%%esi)"
				size="MEML"
			}
		} else if(match(tmp,/DS\:\(R\)BX\/DS\:\(E\)BX/)>0) {
			print START,"%%ds:(%%rbx)",FINISH,"MEMQ" 
			tmp ="%%ds:(%%ebx)"
			size="MEML"
		} else if(match(tmp,/\(R\)DI/)>0) {
			tmp ="(%%rdi)"
			size="MEML"
		} else if(match(tmp,/\(E\)DI/)>0) {
			tmp ="(%%edi)"
			size="MEMQ"
		} else if(match(tmp,/\(R\)SI/)>0) {
			tmp ="(%%rsi)"
			size="MEML"
		} else if(match(ARG,/XMM0/)>0) {

			# Xmm0 implicite => version de l'instruction sans Xmm0 et version qui l'indique
			# On génére ici les possibilités du premier opérande de la version sans Xmm0
			equal=index(FINISH,";") # On récupère l'opérande suivant
			tmp=substr(FINISH,0,equal) # pour le faire passer en premier opérande
			tmp2=substr(FINISH,equal+1) # Et on ajoute un nouveau séparateur 
			tmp2= tmp2 ";" # à la fin des paramètres
			genparams(START,tmp,tmp2,NUMBER)

			# Génération de la version avec mention du Xmm0
			tmp = "%%XMM0"
			size= "REG"
		} else if(match(ARG,/ST\(0\)/)>0) {
			tmp = "%%" tmp
			size= "REG"
		} else if(match(ARG,/[CEFDGS]S/)>0) {
			tmp = "%%" tmp
			size= "REG"
		}
		print START,tmp,FINISH,size,NUMBER
	} 
	#Fin arguments fixes
	else if((match(ARG,/rel[123468]{1,2}/)==1)||(match(ARG,/ptr16:[12346]{2}/)==1)) {
		printrel(START,FINISH)
	}  
	else if(ARG=="r8") {
		if(index($6,"EX")>0) {
			printreg(START,FINISH,reg8ext,"",NUMBER)
		}
		printreg(START,FINISH,reg8,"",NUMBER)
	} 
	else if(ARG=="r8<>[ABCD]H") {
		if(index($6,"EX")>0) {
			printreg(START,FINISH,reg8ext,"",NUMBER)
			printreg(START,FINISH,reg8,"[ABCD]H",NUMBER)
		} 
		else {
			printreg(START,FINISH,reg8,"",NUMBER)
		}
	} 
	else if(ARG=="r16") { 
		if(index($6,"EX")>0) {
			printreg(START,FINISH,reg16ext,"",NUMBER)
		} 
		printreg(START,FINISH,reg16,"",NUMBER)
	} 
	else if(ARG=="r32") { 
		if(index($6,"EX")>0) {
			printreg(START,FINISH,reg32ext,"",NUMBER)
		} 
		printreg(START,FINISH,reg32,"",NUMBER)
	} 
	else if(ARG=="r64") { 
		if(index($6,"EX")>0) {
			printreg(START,FINISH,reg64ext,"",NUMBER)
		} 
		printreg(START,FINISH,reg64,"",NUMBER)
	} 
	else if(ARG=="imm8") {
		printimm(START,FINISH,SizeName("8"),-128,127,NUMBER)
	} 
	else if(ARG=="imm") {
		printimm(START,FINISH,SizeName("8"),-128,127,NUMBER)
	} 
	else if(ARG=="imm16") {
		printimm(START,FINISH,SizeName("16"),-32768,32767,NUMBER)
	} 
	else if(ARG=="imm32") {
		printimm(START,FINISH,SizeName("32"),-2147483648,2147483647,NUMBER)
	} 
	else if(ARG=="imm64") {			  
		printimm(START,FINISH,SizeName("64"),-9223372036854775808,9223372036854775807,NUMBER)
	} 
	else if(ARG=="m/r8") {
		if((index($6,"EX")>0)||(index($6,"VEX")>0)) {
			printreg(START,FINISH,reg8ext,"",NUMBER)
			printmem(START,FINISH,"B",mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0,NUMBER)
			printreg(START,FINISH,reg8,"[ABCD]H",NUMBER)
		} 
		else {
			printreg(START,FINISH,reg8,"",NUMBER)
		}
		printmem(START,FINISH,"B",mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1,NUMBER)
	}
	else if (ARG=="m/r8<>[ABCD]H") {
		if(index($6,"EX")>0) {
			printreg(START,FINISH,reg8ext,"[ABCD]H",NUMBER)
			printmem(START,FINISH,"B",mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0,NUMBER)
		} 
		printreg(START,FINISH,reg8,"[ABCD]H",NUMBER)
		printmem(START,FINISH,"B",mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1,NUMBER)
	}
	else if((ARG=="m/r16")||(ARG=="r16/m16")) {
		if(index($6,"EX")>0) {
			printreg(START,FINISH,reg16ext,"",NUMBER)
			printmem(START,FINISH,"W",mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0,NUMBER)
		} 
		printreg(START,FINISH,reg16,"",NUMBER)
		printmem(START,FINISH,"W",mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1,NUMBER)
	} 
	else if((ARG=="m/r32")||(ARG=="r32/m16")||(ARG=="r32/m32")||(ARG=="r32/m8")||(ARG=="m32/r32")) {
		if(index($6,"EX")>0) {
			printreg(START,FINISH,reg32ext,"",NUMBER)
			printmem(START,FINISH,"L",mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0,NUMBER)
		} 
		printreg(START,FINISH,reg32,"",NUMBER)
		printmem(START,FINISH,"L",mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1,NUMBER)
	} 
	else if((ARG=="m/r64")||(ARG=="r64/m16")||(ARG=="r64/m64")) {
		if(index($6,"EX")>0) {
			printreg(START,FINISH,reg64ext,"",NUMBER)
			printmem(START,FINISH,"Q",mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0,NUMBER)
		} 
		printreg(START,FINISH,reg64,"",NUMBER)
		printmem(START,FINISH,"Q",mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1,NUMBER)
	} 
	else if(match(ARG,/m16:[12346]{2}/)==1) { 
		size=SizeName(gensub(/m16:([12346]{2}).*/,"\\1","g",ARG))
		if(index($6,"EX")>0) {		
			printmem(START,FINISH,size,mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0,NUMBER)
		}
		printmem(START,FINISH,size,mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1,NUMBER)
	} 
	else if(match(ARG,/m[1236]{2}&[12346]{2}/)==1) {
		size=SizeName(gensub(/m[1236]{2}&([12346]{2}).*/,"\\1","g",ARG))
		if(index($6,"EX")>0) {		
			printmem(START,FINISH,size,mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0,NUMBER)
		}
		printmem(START,FINISH,size,mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1,NUMBER)
	} 
	else if((match(ARG,/m[0123468]{2}fp/)==1)||(match(ARG,/m80bcd/)==1)) {
		size=SizeName(gensub(/m([0123468]{2}).*/,"\\1","g",ARG))
		if(index($6,"EX")>0) {		
			printmem(START,FINISH,size,mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0,NUMBER)
		}
		printmem(START,FINISH,size,mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1,NUMBER)
	} 
	else if(match(ARG,/m[123468]{2}int/)==1) { 
		size=SizeName(gensub(/m([123468]{2})int.*/,"\\1","g",ARG))
		if(index($6,"EX")>0) {		
			printmem(START,FINISH,size,mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0,NUMBER)
		}
		printmem(START,FINISH,size,mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1,NUMBER)
	} 
	else if((match(ARG,/m[123468]{1,2}/)==1)) { 
		size=SizeName(gensub(/m([123468]{1,2}).*/,"\\1","g",ARG))
		#print "lol"
		if(index($6,"EX")>0){		
			printmem(START,FINISH,size,mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0,NUMBER)
		}
		printmem(START,FINISH,size,mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1,NUMBER)
	} 
	else if(match(ARG,/moffs[123468]{1,2}/)==1) {
		size=SizeName(gensub(/moffs([123468]{1,2}).*/,"\\1","g",ARG))
		if(index($6,"EX")>0){		
			printmem(START,FINISH,size,mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0,NUMBER)
		}
		printmem(START,FINISH,size,mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1,NUMBER)
	} 
	else if(match(ARG,/Sreg/)==1) { 
		printreg(START,FINISH,mem_seg,NUMBER)
	} 
	else if((ARG=="ST")||(ARG=="ST(0)")) { 
		print START,"%%ST(0)",FINISH,"REG"
	} 
	else if(ARG=="ST(i)") { 				
		printreg(START,FINISH,float,NUMBER)
	} 
	else if(match(ARG,/xmm[12]{0,1}\/m[123468]{2}/)==1) {
		size=SizeName(gensub(/xmm[12]{0,1}\/m([123468]{2}).*/,"\\1","g",ARG))
		if(index($6,"EX")>0) {		
			#printmem(START,FINISH,size,mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0)
			printreg(START,FINISH,xmmext,NUMBER)
		}
		printmem(START,FINISH,size,mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1)
		#print "win"
		printreg(START,FINISH,xmm,NUMBER)
	} 
	else if(match(ARG,/xmm[12]{0,1}/)==1) { 
	#	printreg(START,FINISH,xmmext,NUMBER)
		printreg(START,FINISH,xmm,"",NUMBER)
		#print "win2"
	} 
	else if(match(ARG,/ymm[12]{0,1}\/m[123468]{2}/)==1) {
		size=SizeName(gensub(/ymm[12]{0,1}\/m([123468]{2}).*/,"\\1","g",ARG))
		if(index($6,"EX")>0) {		
			printmem(START,FINISH,size,mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0,NUMBER)
			printreg(START,FINISH,ymmext,NUMBER)
		}
		printmem(START,FINISH,size,mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1,NUMBER)
		printreg(START,FINISH,ymm,"",NUMBER)
	}
	else if(match(ARG,/ymm[12]{0,1}/)==1) { 
		printreg(START,FINISH,ymm,"",NUMBER)
	} 
	else if(match(ARG,/mm[12]{0,1}\/m[2346]{2}/)==1) {
		size=SizeName(gensub(/mm[12]{0,1}\/m([2346]{2}).*/,"\\1","g",ARG))
		if(index($6,"EX")>0) {		
			printmem(START,FINISH,size,mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0,NUMBER)
		}
		printmem(START,FINISH,size,mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1,NUMBER)
		printreg(START,FINISH,mmx,"",NUMBER)
	} 
	else if(ARG=="mm") { 
		printreg(START,FINISH,mmx,"",NUMBER)
	} 
	else if(match(ARG,/creg/)==1) {					
		printreg(START,FINISH,control,NUMBER)
	} 
	else if(match(ARG,/dreg/)==1) { 				
		printreg(START,FINISH,debug,NUMBER)
	} 
	else if(index(ARG,"B")>1) {
		if(index($6,"EX")>0){		
			printmem(START,FINISH,"-",mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0,NUMBER)
		}
		printmem(START,FINISH,"-",mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1,NUMBER)
	} 
	else if(ARG=="m") { 
		size=SizeName("")
		if(index($6,"EX")>0) {		
			printmem(START,FINISH,size,mem_base32_ext,mem_index32_ext,mem_base64_ext,mem_index64_ext,0,NUMBER)
		}
		printmem(START,FINISH,size,mem_base32_std,mem_index32_std,mem_base64_std,mem_index64_std,1,NUMBER)
	}
	else {
		print START,ARG,FINISH,"-",NUMBER
	}
	return
}

{		
#	print $1,launcher[1,1]
	if(argpos==0) {
		for(cpt_it=1;cpt_it<launcher_lines;cpt_it++)	
			if($1==launcher[cpt_it,1])	print $1,$2,$3,$4,$5,$11,"0",cpt_it
	} 
	else if(argpos==1) {
	#	for(cpt_it=1;cpt_it<launcher_lines;cpt_it++)
	    #if($2==launcher[$8,2])	{
			if(match($2,launcher[$8,2])>0){
		 	 #print launcher[$8,2]
				#genparams($1,$2,$3 ";" $4 ";" $5 ";" $6 ";" $7,$8)
				genparams($1,launcher[$8,2],$3 ";" $4 ";" $5 ";" $6 ";" $7,$8)
			}
	} 
	else if(argpos==2) {
		 #if($3==launcher[$9,3]){
		 if(match($3,launcher[$9,3])>0){
		 #print $3,launcher[$9,3]
		 	#genparams($1 ";" $2,$3,$4 ";" $5 ";" $6 ";" $7 ";" $8,$9)
		 	genparams($1 ";" $2,launcher[$9,3],$4 ";" $5 ";" $6 ";" $7 ";" $8,$9)
		}
	} 
	else if(argpos==3) {
		#if($4==launcher[$10,4]){
		if(match($4,launcher[$10,4])>0){
			#genparams($1 ";" $2 ";" $3,$4,$5 ";" $6 ";" $7 ";" $8 ";" $9,$10)
			genparams($1 ";" $2 ";" $3,launcher[$10,4],$5 ";" $6 ";" $7 ";" $8 ";" $9,$10)
		}
	}
	else if(argpos==4) {
	#	for(cpt_it=1;cpt_it<launcher_lines;cpt_it++)
		#if($5==launcher[$11,5]){
		if(match($5,launcher[$11,5])>0){
			#genparams($1 ";" $2 ";" $3 ";" $4,$5,$6 ";" $7 ";" $8 ";" $9 ";" $10,$11)
			genparams($1 ";" $2 ";" $3 ";" $4,launcher[$11,5],$6 ";" $7 ";" $8 ";" $9 ";" $10,$11)
		}
	} 
}
