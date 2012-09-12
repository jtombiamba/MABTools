#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<getopt.h>
#include"mylib.h"


int main(int argc, char** argv){

	FILE*  filein;
	FILE* fileout;
	int i, sorting_i, sorting_j, k;
	char* paramstring = (char*)malloc(STRING_SIZE*sizeof(char));
	char* string = (char*)malloc(STRING_SIZE*sizeof(char));
	char* cs = NULL;//(char*)malloc(5*sizeof(char));
	char*  sorting_string = (char*)malloc(STRING_SIZE*sizeof(char));
	char*  help_string = (char*)malloc(TOKEN_SIZE*sizeof(char));

	while((i=getopt(argc, argv, "f:"))!=EOF){
		switch(i){
			case 'f': strcpy(paramstring, optarg);
			break;
		//	case 's': k = atoi(optarg);
		//	break;
		}
	}/*inserer le getopt pour récupérer le nombre de fois qu'on doit dérouler le code de sortie*/	

	instructionLine* Linetab;// = malloc(k*sizeof(instructionLine));
	instructionLine* help_Linetab = NULL;//malloc(k*sizeof(instructionLine));
	
	filein = fopen(paramstring, "r");
	fileout = fopen("out_data.dat", "w");
	sorting_i = 0;
	
	while(fgets(sorting_string, STRING_SIZE, filein)!=NULL){
		sorting_i ++;
		help_Linetab = realloc(Linetab, sizeof(instructionLine) * sorting_i);
		if(help_Linetab==NULL){
			free(Linetab);
		}
		Linetab = help_Linetab;
		Linetab[sorting_i - 1].InstLine = (char*)malloc(STRING_SIZE * sizeof(char));
		
		sorting_string[strlen(sorting_string)-1] = '\0';
		
		//strcpy(string, sorting_string);
		
		sorting_j = 0;
		
		cs = (char*)malloc(5*sizeof(char));
		
		cs = strrchr(sorting_string, '_');
		
		strcpy(Linetab[sorting_i - 1].InstLine, &cs[1]);
		string = strchr(&cs[1], '\t');
		strncpy(help_string, &cs[1], strlen(&cs[1])-strlen(string));//"%s\n", string);
		
		Linetab[sorting_i - 1].rank = atoi(help_string) ;
	//	printf("%d %s\n", Linetab[sorting_i -1].rank, Linetab[sorting_i - 1].InstLine);

		free(help_string), help_string = NULL;
		help_string = (char*)malloc(STRING_SIZE*sizeof(char));
	}
	//printf("erreur\n");
	for(i=0; i<sorting_i; i++){
		for(sorting_j=0;sorting_j<sorting_i;sorting_j++){
			if(Linetab[sorting_j].rank==i) fprintf(fileout, "%s\n", Linetab[sorting_j].InstLine);
		}
	}
	fclose(filein);
	fclose(fileout);
	return 0;
	}
