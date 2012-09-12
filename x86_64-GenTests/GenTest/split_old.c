#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<getopt.h>
#include"mylib.h"


static char *Mem_regs[10] = {"RAX", "RBX", "RCX", "RDX", "RSI", "EAX",
										"EBX", "ECX", "EDX", "ESI"};

static char *match_Mem_regs[10] = {"a", "b", "c", "d", "S", "a", "b", "c", "d", "S"};

int main (int argc, char** argv){
	FILE *filein, *fileinit;
	FILE *fileout, *filemem;
	char *string = (char*)malloc(STRING_SIZE*sizeof(char));
	char *cs = (char*)malloc(TOKEN_SIZE*sizeof(char));
	char *ct = (char*)malloc(TOKEN_SIZE*sizeof(char));
	char *ts = (char*)malloc(TOKEN_SIZE*sizeof(char));
	char *sorting_string = (char*)malloc(STRING_SIZE*sizeof(char));
	char *string1 = (char*)malloc(STRING_SIZE*sizeof(char));
	char *string2 = (char*)malloc(STRING_SIZE*sizeof(char));
	char *param_string = (char*)malloc(75*sizeof(char));
	char *reg_string = (char*)malloc(10*STRING_SIZE*sizeof(char));//store registers in reg op
	char *mem_string = (char*)malloc(10*STRING_SIZE*sizeof(char));//store registers in mem op
	instructionLine* Linetab;
	instructionLine* mem_Linetab;
	instructionLine* clobber_Linetab;

	operandLine *List_operandLine = malloc(sizeof(operandLine));
	operandLine my_operandLine;
	operandLine* basic_operandLine = malloc(sizeof(operandLine));
	
	char *output = (char*)malloc(TOKEN_SIZE*sizeof(char));
	char * token = (char*)malloc(TOKEN_SIZE*sizeof(char)); 
	char * token1 = (char*)malloc(TOKEN_SIZE*sizeof(char)); 
	char * token2 = (char*)malloc(TOKEN_SIZE*sizeof(char)); 
	my_operandLine.tab = (char**)malloc(TOKEN_SIZE*TOKEN_SIZE*sizeof(char));
	
	int i ;
	int j ;
	int k ;
	int sorting_i;
	int sorting_j;
	int sum;
	int line;
	int size = 10*STRING_SIZE;
//	int acces = 0;

	while((i=getopt(argc, argv, "s:p:"))!=EOF){
		switch(i){
			case 's': k = atoi(optarg);
			break;
			case 'p': strcpy(param_string,optarg);
			break;
			default: k = 8;
			break;
		}
	}/*inserer le getopt pour récupérer le nombre de fois qu'on doit dérouler le code de sortie*/	

	my_operandLine.round  = 0;
	i=0;
	fileinit = fopen(param_string, "r");
	filein = fopen("temp.tmp", "w");
	
	while(fgets(string, STRING_SIZE, fileinit)!=NULL){

		string[strlen(string)-1]='\0';
		
		my_operandLine.tab = str_split(string, ";", &my_operandLine.sum);
		
		fprintf(filein, "%s\n", my_operandLine.tab[0]);
		
		List_operandLine = mylib_add_operandLine(List_operandLine, my_operandLine);

		free(string), string=NULL;
		
		string=(char*)malloc(STRING_SIZE*sizeof(char));
	}

 	sum =	mylib_nbr_Listoperand(List_operandLine) - 1;// calculate all lines in the register input file
	line = 0;

	fclose(fileinit);
	fclose(filein);
	
	// end of input registering in data structure
	
	//start sorting input Instructions Lines

	filein = fopen("InstrArgs2.tmp", "r");
	fileout = fopen("temp1.tmp", "w");
	sorting_i = 0;
	
	while(fgets(sorting_string, STRING_SIZE, filein)!=NULL){
		sorting_i ++;
		
		Linetab = realloc(Linetab, sizeof(instructionLine) * sorting_i);
		
		Linetab[sorting_i - 1].InstLine = (char*)malloc(STRING_SIZE * sizeof(char));
		
		sorting_string[strlen(sorting_string)-1] = '\0';
		
		strcpy(string, sorting_string);
		
		sorting_j = 0;
		
		cs = (char*)malloc(TOKEN_SIZE*sizeof(char));
		
		cs = strrchr(sorting_string, ';');
		
		strncat(Linetab[sorting_i - 1].InstLine, string, strlen(string) - strlen(cs));
		//strncpy(Linetab[sorting_i - 1].InstLine, string, strlen(string) - strlen(cs));
		
		
		printf("%s\n", Linetab[sorting_i -1].InstLine);
		sprintf(cs,"%s", &cs[1]);
		
		Linetab[sorting_i - 1].rank = atoi(cs);
		/*while((cs = strtok(sorting_string, ";"))!=NULL){
			printf("%d\n", sorting_j);
			if(sorting_j==5) {
				printf("final %s\n", cs);
				Linetab[sorting_i - 1].rank = atoi(cs);
			} else {
					//strcat(out_string, cs);
					strcat(Linetab[sorting_i - 1].InstLine, cs);	
					strcat(Linetab[sorting_i - 1].InstLine, ";");
				}
			sorting_string = NULL;	
			sorting_j ++;	
		}*/
		sorting_string = (char*)malloc(STRING_SIZE*sizeof(char));
	}
	for(i=1; i<=sorting_i; i++){
		for(sorting_j=0;sorting_j<sorting_i;sorting_j++){
			if(Linetab[sorting_j].rank==i) fprintf(fileout, "%s\n", Linetab[sorting_j].InstLine);
		}
	}
	fclose(filein);
	fclose(fileout);

	rename("InstrArgs2.tmp", "InstrArgs2_old.tmp");
	rename("temp1.tmp", "InstrArgs2.tmp");

	// End sorting 

	//start creating output file

	fileout = fopen("InstrArgs6.tmp", "w");
	
	fileinit = fopen("temp.tmp", "r");
	
	for(j=0; j<k; j++){
		
		filein = fopen("InstrArgs2.tmp", "r");
		
		if(filein !=NULL){
			
			while(fgets(string1, STRING_SIZE, filein)!=NULL){
				
				string[strlen(string1)-1]='\0';
 				
				strcpy(string2, string1);
				
				token = strtok(string2, ";");
				
				fprintf(fileout, "%s;", token);
				
				for(i=0; (token = strtok(NULL, ";")); i++){
								
					token[strlen(token)]='\0';
					
					if(strcmp(token,"\n")!=0){ //START
						
						if(strchr(token, '(')==NULL){//NOT A MEMORY OPERAND

							if(strchr(token, '$')==NULL){// A REGISTER OPERAND

								basic_operandLine = mylib_operandLine_i(List_operandLine, line%sum);

								basic_operandLine->next->round = call_register(basic_operandLine->next->tab, basic_operandLine->next->sum - 1, &basic_operandLine->next->round, output);

								token2 = mylib_find_and_replace(token, fileinit, output);

								/*if(strlen(reg_string)<=size && strlen(reg_string)>=size - 5){
									
									size<<=1;
									free(sorting_string), sorting_string = NULL;
									sorting_string = (char*)malloc(size*sizeof(char));
									if(!sorting_string){
										printf("realloc failed !!!!\n");
										exit(EXIT_FAILURE);
									}
									reg_string = sorting_string;
								}*/

								strcat(reg_string, output);strcat(reg_string, ";");//Storing the registers from register operands
							
								fprintf(fileout, "%s;", token2);
							}
							else if(strchr(token, '$')!=NULL){//AN IMMEDIATE OPERAND

								basic_operandLine = mylib_operandLine_i(List_operandLine, line%sum);

								basic_operandLine->next->round = call_register(basic_operandLine->next->tab, basic_operandLine->next->sum - 1, &basic_operandLine->next->round, output);

								token2 = mylib_find_and_replace(token, fileinit, output);
							
								fprintf(fileout, "%s;", token2);
							}
						}
						else{//MEMORY OPERAND
							cs = strchr(token, '(');
							
							strncpy(ct, token, strlen(token) - strlen(cs));

							basic_operandLine = mylib_operandLine_i(List_operandLine, line%sum);
							basic_operandLine->next->round = call_register(basic_operandLine->next->tab, basic_operandLine->next->sum - 1, &basic_operandLine->next->round, output);
							token1 = mylib_find_and_replace(ct, fileinit, output);
							
							line++;

							basic_operandLine = mylib_operandLine_i(List_operandLine, line%sum);
							basic_operandLine->next->round = call_register(basic_operandLine->next->tab, basic_operandLine->next->sum - 1, &basic_operandLine->next->round, output);
							token2 = mylib_find_and_replace(cs, fileinit, output);

								/*if(strlen(mem_string)<=size && strlen(mem_string)>=size - 5){
									
									size<<=1;
									free(sorting_string), sorting_string = NULL;
									sorting_string = (char*)malloc(size*sizeof(char));
									if(!sorting_string){
										printf("realloc failed !!!!\n");
										exit(EXIT_FAILURE);
									}
									mem_string = sorting_string;
								}*/
							
							//printf("mem_string = %s\n", mem_string);
							//printf("output = %s\n", output);
							strcat(mem_string, output);strcat(mem_string, ";");//Storing the register from memory operands
							//printf("mem_string_out = %s\n", mem_string);
								
							strcat(token1, token2);
							
							fprintf(fileout, "%s;", token1);
						}
						line ++;
					}//string1=NULL; END
				
				}
				fprintf(fileout,"\n");
		
				free(string1), string1=NULL;
				string1=(char*)malloc(STRING_SIZE*sizeof(char));
			}
			fclose(filein);
  	
		} else printf("file not found\n");
	}
	fclose(fileout);
	//mylib_print_all(List_operandLine);
	remove("temp.tmp");
	rename("InstrArgs2.tmp", "InstrArgs3.tmp");
	rename("InstrArgs2_old.tmp", "InstrArgs2.tmp");
/***
** This section parses the mem and reg strings to fill the clobber and memory list
***/
	filein = fopen("temp_reg_old.tmp", "w");
	fileout = fopen("temp_mem_old.tmp", "w");

	//printf("mem_string = %s\n", mem_string);
	mem_Linetab = malloc(sizeof(instructionLine));
	mem_Linetab = mylib_unique_list(mem_string, &i);
	printf("i_mem = %d\n", i);

	//printf("reg_string = %s\n", reg_string);
	clobber_Linetab = malloc(sizeof(instructionLine));
	clobber_Linetab = mylib_unique_list(reg_string, &j);
	printf("i_reg = %d\n", j);
	
	mylib_clear_copy(mem_Linetab, i, clobber_Linetab, j);

	mylib_print_param_list(mem_Linetab, i, fileout);
	printf("\n\n");
	mylib_print_param_list(clobber_Linetab, j, filein);
	fclose(filein);
	fclose(fileout);
	filein = fopen("temp_mem_old.tmp", "r");
	fileout = fopen("temp_reg_old.tmp", "r");
	filemem = fopen("temp_mem.tmp", "w");
	fileinit = fopen("temp_reg.tmp", "w");
	//fprintf(filemem, "\t");

	//free(sorting_string), sorting_string = NULL;
	//sorting_string = (char*)malloc(2*STRING_SIZE*sizeof(char));
	fprintf(filemem, "\t:\"D\"(source->size)");
	while(fgets(string, TOKEN_SIZE, filein)!=NULL){
		string[strlen(string)-1] = '\0';
		for(i=0; i<10; i++){
			cs = Mem_regs[i];
			if(!strcmp(cs, string)) fprintf(filemem, ",\"%s\"(source->stream)", match_Mem_regs[i]);
		}
	}
	fprintf(filemem, "\n");
	free(sorting_string), sorting_string = NULL;
	sorting_string = (char*)malloc(2*STRING_SIZE*sizeof(char));
	//free(string2), string2 = NULL;
	//string2 = (char*)malloc(TOKEN_SIZE*sizeof(char));
	while(fgets(string, TOKEN_SIZE, fileout)!=NULL){
		string[strlen(string)-1] = '\0';
		for(i=0; i<strlen(string); i++){
			strcpy(&ts[i],"m");
			ts[i] = tolower(string[i]);
		}
		sprintf(string1, "\"%%%s\"", ts);
		if(strlen(sorting_string)==0) {
			strcat(sorting_string, "\t:");
			strcat(sorting_string, string1);
		}
		else {
			strcat(sorting_string, ",");
			strcat(sorting_string, string1);
		}
	}
	fprintf(fileinit, "%s\n", sorting_string);
	fclose(filein);
	fclose(fileout);
	fclose(filemem);
	fclose(fileinit);
	return 0;
}
