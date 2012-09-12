#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<getopt.h>
#include"mylib.h"



int main (int argc, char** argv){
	FILE *filein, *fileinit;
	FILE *fileout;
	char *string = (char*)malloc(STRING_SIZE*sizeof(char));
	char *cs = (char*)malloc(TOKEN_SIZE*sizeof(char));
	char *ct = (char*)malloc(TOKEN_SIZE*sizeof(char));
	char *sorting_string = (char*)malloc(STRING_SIZE*sizeof(char));
	char *string1 = (char*)malloc(STRING_SIZE*sizeof(char));
	char *string2 = (char*)malloc(STRING_SIZE*sizeof(char));
	char *param_string = (char*)malloc(75*sizeof(char));
	char *mem_string = (char*)malloc(2*STRING_SIZE*sizeof(char));//store registers in mem operands
	char *reg_string = (char*)malloc(2*STRING_SIZE*sizeof(char));//store registers in register operands
	instructionLine* Linetab;

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
		
		cs = (char*)malloc(5*sizeof(char));
		
		cs = strrchr(sorting_string, ';');
		
		strncpy(Linetab[sorting_i - 1].InstLine, string, strlen(string) - strlen(cs));
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
				
				token = strtok(string1, ";");
				
				fprintf(fileout, "%s;", token);
				
				for(i=0; (token = strtok(NULL, ";")); i++){
								
					token[strlen(token)]='\0';
					
					if(strcmp(token,"\n")!=0){ //START
						
						if(strchr(token, '(')==NULL){//NOT A MEMORY OPERAND

							if(strchr(token,'$')==NULL){// A REGISTER OPERAND

								basic_operandLine = mylib_operandLine_i(List_operandLine, line%sum);

								basic_operandLine->next->round = call_register(basic_operandLine->next->tab, basic_operandLine->next->sum - 1, &basic_operandLine->next->round, output);

								token2 = mylib_find_and_replace(token, fileinit, output);

								//reg_string = realloc(reg_string, (strlen(reg_string)+strlen(output))*sizeof(char));

								//if(!reg_string){printf("realloc reg_string failed!!!!\n"); exit(EXIT_FAILURE);}

								strcat(reg_string, output);
								strcat(reg_string, ";");
							
								fprintf(fileout, "%s;", token2);
							}
							else{//AN IMMEDIATE OPERAND

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
							
							//mem_string = realloc(mem_string, (strlen(mem_string)+strlen(output))*sizeof(char));

							//if(!mem_string){printf("realloc mem_string failed!!!!\n"); exit(EXIT_FAILURE);}

							strcat(mem_string, output);
							strcat(mem_string, ";");

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
	remove("InstrArgs2.tmp");
	rename("InstrArgs2_old.tmp", "InstrArgs2.tmp");
	printf("the end\n");
	mylib_print_param_list(mylib_unique_list(reg_string, &i), i, stdout);
	return 0;
}
