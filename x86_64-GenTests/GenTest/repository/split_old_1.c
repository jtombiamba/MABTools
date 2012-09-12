#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<getopt.h>


typedef struct _operandLine{
		char** tab;
		int round;
		int sum;
		struct _operandLine *next;
} operandLine;

typedef struct _instructionLine{
		char* InstLine;
		int rank;
} instructionLine;

char** str_split(char *s, const char *ct, int *sum){

	char **tab = NULL;

	if(s !=NULL && ct !=NULL){
		int i;
		char *cs =NULL;
		size_t size = 1;

		for(i=0; (cs = strtok(s, ct)); i++){
			if(size<= i+1){
				void *tmp = NULL;

				size<<=1;
				tmp =realloc(tab, sizeof(*tab) * size);
				if(tmp!=NULL){
					tab=tmp;
				}
				else {
					fprintf(stderr, "memoire insuffisante\n");
					free(tab);
					tab = NULL;
					exit(EXIT_FAILURE);
				}
			}
			tab[i] = cs;
			s=NULL;

		}
		tab[i] = NULL;
		*sum = i;
	}
	return tab;
}

void mylib_print_all(operandLine* List_operandLine){

	int i=0;
	int j;
	operandLine* help_print = malloc(sizeof(operandLine));
	help_print = List_operandLine;
	while (help_print->next!=NULL){
		for(j=0; j<help_print->next->sum; j++)	printf("%s ", help_print->next->tab[j]);
		printf("\n");
		help_print = help_print->next;
	}
	return;
}

operandLine* mylib_operandLine_i(operandLine* List_operandLine, int index){
	int i;
	operandLine* help_line = malloc(sizeof(operandLine));
	help_line  = List_operandLine;
	for(i=0; i<index && help_line->next!=NULL; i++){
		help_line = help_line->next;
	}
	if(help_line==NULL){
		return NULL;
	} else {
		return help_line ;
	}
}

void mylib_copy_instructionLine(instructionLine InstrLineA, instructionLine* InstrLineB){
		strcpy((*InstrLineB).InstLine, InstrLineA.InstLine);
		(*InstrLineB).rank = InstrLineA.rank;
		return;
}

void mylib_copy_operandLine(operandLine operandLineA, operandLine* operandLineB){
	int i;
	for(i=0; i<operandLineA.sum; i++) {
		operandLineB->tab[i] =(char*)malloc(10*sizeof(char));
		strcpy((*operandLineB).tab[i], operandLineA.tab[i]);
	}		
	//printf("copie reussie %s %s\n", (*operandLineB).tab[1], operandLineA.tab[1]);
	(*operandLineB).sum = operandLineA.sum;
	(*operandLineB).round =0;
	operandLineA.sum=0;
	return;
}

void mylib_sort_instructionLine(){

}



operandLine* mylib_add_operandLine(operandLine *list_operandLine, operandLine operandLineA){
  int i;
	operandLine* new_element = malloc(sizeof(operandLine));
	new_element->tab = (char**)malloc(10*10*sizeof(char));
	mylib_copy_operandLine(operandLineA, new_element);//fonction a développer
	new_element->next = NULL;
	if(list_operandLine==NULL){
		return new_element ;
	}
	else {
		operandLine* help = list_operandLine;
		while(help->next!=NULL){
			help = help->next;
		}
		help->next = malloc(sizeof(operandLine));
		help->next = new_element;
	}
	return list_operandLine;
}

int mylib_nbr_Listoperand(operandLine* List_operandList){
	if(List_operandList == NULL) return 0;
	return mylib_nbr_Listoperand(List_operandList->next) + 1;
}

int call_register(char **tab, int sum, int *previous, char *output){
	sprintf(output,"%s",tab[*previous%sum+1]);
	*previous = *previous + 1;
	return previous[0];
}

char *str_replace(const char *s, long unsigned int start, long unsigned int lenght, const char *ct){
	char *new_s = NULL;
	if(s !=NULL && ct !=NULL && start>=0 && lenght > 0){
		size_t size = strlen(s);
		new_s = (char*)malloc(sizeof (char) * (size - lenght + strlen(ct) + 1));
		if (new_s != NULL){
			memcpy(new_s, s, start);
			memcpy(&new_s[start], ct, strlen(ct));
			memcpy(&new_s[start+strlen(ct)], &s[start + lenght], size - lenght- start+1);
		}
	}
	else{
		fprintf(stderr, "unsufficient memory\n");
		exit(EXIT_FAILURE);
	}
	return new_s;
}

int str_istr(const char* cs, const char *ct){
	int index = -1;
	if(cs !=NULL && ct !=NULL){
		char *ptr_pos = NULL;
		ptr_pos = strstr(cs,ct);
		if(ptr_pos !=NULL){
			index = ptr_pos - cs;
		}
	}
	return index;
}

char* mylib_find_and_replace(const char *string1, FILE* file1, char* change){
	char* string3 = (char*)malloc(10*sizeof(char));
	char* string = (char*)malloc(10*sizeof(char));
	long int  start, length;
	int i=0;
	fseek(file1, 0, SEEK_SET);
	while(fgets(string, 10, file1)!=NULL){
		string[strlen(string)-1] = '\0';
		start = str_istr(string1, string);
		if(start>=0){
			length = strlen(string);
			string = str_replace(string1, start, length, change);
			return string;
		}
		else i++;
	}
	return "";
}

int main (int argc, char** argv){
	FILE *filein, *fileinit;
	FILE *fileout;
	char *string = (char*)malloc(50*sizeof(char));
	char *cs = (char*)malloc(10*sizeof(char));
	char *sorting_string = (char*)malloc(50*sizeof(char));
	char *string1 = (char*)malloc(50*sizeof(char));
	char *string2 = (char*)malloc(50*sizeof(char));
	char *param_string = (char*)malloc(75*sizeof(char));
	instructionLine* Linetab;

	operandLine *List_operandLine = malloc(sizeof(operandLine));
	operandLine my_operandLine;
	operandLine* basic_operandLine = malloc(sizeof(operandLine));
	char *output = (char*)malloc(10*sizeof(char));
	char * token = (char*)malloc(10*sizeof(char)); 
	char * token1 = (char*)malloc(10*sizeof(char)); 
	char * token2 = (char*)malloc(10*sizeof(char)); 
	my_operandLine.tab = (char**)malloc(10*10*sizeof(char));
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
	while(fgets(string, 50, fileinit)!=NULL){
		string[strlen(string)-1]='\0';
		my_operandLine.tab = str_split(string, ";", &my_operandLine.sum);
		fprintf(filein, "%s\n", my_operandLine.tab[0]);
		//printf("%d %s\n", my_operandLine.sum,  my_operandLine.tab[0]);
		List_operandLine = mylib_add_operandLine(List_operandLine, my_operandLine);

		free(string), string=NULL;
		string=(char*)malloc(50*sizeof(char));
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
	while(fgets(sorting_string, 50, filein)!=NULL){
		sorting_i ++;
		Linetab = realloc(Linetab, sizeof(instructionLine) * sorting_i);
		Linetab[sorting_i - 1].InstLine = (char*)malloc(40 * sizeof(char));
		sorting_string[strlen(sorting_string)-1] = '\0';
		strcpy(string, sorting_string);
		sorting_j = 0;
		cs = (char*)malloc(5*sizeof(char));
		cs = strrchr(sorting_string, ';');
		strncpy(Linetab[sorting_i - 1].InstLine, string, strlen(string) - strlen(cs));
		sprintf(cs,"%s", &cs[1]);
		Linetab[sorting_i - 1].rank = atoi(cs);
		
		sorting_string = (char*)malloc(50*sizeof(char));
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
			while(fgets(string1, 50, filein)!=NULL){
				string[strlen(string1)-1]='\0';
 				strcpy(string2, string1);
				token = strtok(string1, ";");
				fprintf(fileout, "%s;", token);
				for(i=0; (token = strtok(NULL, ";")); i++){
								
					token[strlen(token)]='\0';
					if(strcmp(token,"\n")!=0){ //START
							
						basic_operandLine = mylib_operandLine_i(List_operandLine, line%sum);

						basic_operandLine->next->round = call_register(basic_operandLine->next->tab, basic_operandLine->next->sum - 1, &basic_operandLine->next->round, output);

						token2 = mylib_find_and_replace(token, fileinit, output);
						fprintf(fileout, "%s;", token2);
						line ++;
					}//string1=NULL; END
				
				}
				fprintf(fileout,"\n");
		
				free(string1), string1=NULL;
				string1=(char*)malloc(50*sizeof(char));
			}
			fclose(filein);
  	
		} else printf("file not found\n");
	}
	fclose(fileout);
	//mylib_print_all(List_operandLine);
	remove("temp.tmp");
	return 0;
}
