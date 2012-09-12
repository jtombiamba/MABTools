#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<getopt.h>
#include"mylib.h"


//function used to split all operand lines and fill the structure operandLine
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
//for debugging mode, see if the structure is well filled
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

//For results printing of output of the parameters after fetching
void mylib_print_param_list(instructionLine* List_of_param, int all,  FILE *file){

	int j;

		for(j=0; j<all; j++)	fprintf(file, "%s\n", List_of_param[j].InstLine);
	return;
}
//this function returns the pointer to the index wanted
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

//this function writes the value of a parameter and increments the number of rounds
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

//this function returns the index of a sub-string cs in a string ct
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

//this function finds the occurence of a string in file1 that appears in string1 and replaces it by change
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

operandLine* mylib_operandLine_find(operandLine* List_operandLine, char* index){

	operandLine* help_line = malloc(sizeof(operandLine));
	help_line  = List_operandLine;
	while(help_line->next!=NULL){
		if(!strcmp(help_line->tab[0], index)){
			return help_line ;
		}
		help_line = help_line->next;
	}
return NULL;
}

void mylib_fetch_register(operandLine* List_operandLine, instructionLine* List_of_fetch, int number, int rank){

	int i, j;
	operandLine* help_operandLine = malloc(sizeof(operandLine));
	if(!help_operandLine){
		printf("unsufficient memory!!!\n");
		exit(EXIT_FAILURE);
	}

	char* token = (char*)malloc(TOKEN_SIZE*sizeof(char));
	char* help_string = (char*)malloc(STRING_SIZE*sizeof(char));
	char* output = (char*)malloc(TOKEN_SIZE*sizeof(char));
	if(!token || !output || !help_string){
		printf("unsufficient memory\n");
		exit(EXIT_FAILURE);
	}
	for(j=1; j<=number; j++){
		for(i=1; i<=rank; i++){//il faudra savoir le nombre de ligne a remplir #RANK
			strcpy(help_string, List_of_fetch[i - 1].InstLine);
			token = strtok(help_string, ";");
			help_operandLine = mylib_operandLine_find(List_operandLine, token);
			help_operandLine->round = call_register(help_operandLine->tab, help_operandLine->sum - 1, &help_operandLine->round, output);

			if(j!=1)strcat(List_of_fetch[i - 1].InstLine, ";");
			strcat(List_of_fetch[i - 1].InstLine, output);
		}
	}
	return;	
}

/****
** The function will be used to extract the lists for clobber and mem list
** Useful in automatically fill clobber list and memory list
****/
instructionLine * mylib_unique_list(char * string, int *total){

	int i, j;
	instructionLine * help_list = malloc(sizeof(instructionLine));
	help_list[0].InstLine = (char*)malloc(STRING_SIZE*sizeof(char));
	help_list[0].rank = 0;
	char * token = (char*)malloc(TOKEN_SIZE*sizeof(char));
	if(!token){
		printf("token not initialized\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while((token=strtok(string, ";"))!=NULL){
		for(j=0; j<i; j++){
			if(!strcmp(help_list[j].InstLine, token)) {
				help_list[j].rank ++;
				j = -1;
				break;
			}	
		}
		if(j!=-1){
			i++;
			help_list = realloc(help_list, sizeof(instructionLine) * i);
			help_list[i - 1].InstLine = (char*)malloc(STRING_SIZE*sizeof(char));
			strcpy(help_list[i-1].InstLine, token);
			help_list[i-1].rank = 1;
		}
		string = NULL;
	}
	*total = i;
	return help_list;
}
