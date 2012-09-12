#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<getopt.h>
#include<dirent.h>
#include"mylib.h"
#include"arrgt_new.h"

#define STRING_SIZE 50
#define TOKEN_SIZE 15

char* Qregs[16] = {"rax", "rbx" , "rcx" ,"rdx", "rsi", "rdi", "rbp", "rsp"
										, "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"};

char* Dregs[16] = {"eax", "ebx" , "ecx" ,"edx", "esi", "edi", "ebp", "esp"
										, "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d"};

char* Wregs[16] = {"ax", "bx" , "cx" ,"dx", "si", "di", "bp", "sp"
									, "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w"};

char* Bregs[16] = {"al", "bl" , "cl" ,"dl", "ah", "bh", "ch", "dh"
									, "r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b"};

char* Xregs[16] = {"xmm0", "xmm1" , "xmm2" ,"xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8",
									"xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"};

char* Yregs[16] = {"ymm0", "ymm1" , "ymm2" ,"ymm3", "ymm4", "ymm5", "ymm6", "ymm7", "ymm8",
									"ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"};



char* str_strip(char* string){
	char* strip =NULL;
	if(string!=NULL){
		strip = malloc(sizeof(*strip) * (strlen(string)+1));
		if(strip!=NULL){
			int i, j;
			int ps =0;//indice comptabilisant les espaces (1 au max)

			for(i=0, j=0; string[i]; i++){
				if(string[i]== ' '){
					if(ps == 0){
						strip[j] = string[i];
						ps = 1;//espace autorisé
						j++;
					}
					//j++;
				}
				else{
					strip[j] = string[i];
					ps = 0;// remise a zero des espaces 
					j++;
				}
			}
			strip[j] = '\0';
		}
		else{
			fprintf(stderr, "unsufficient memory\n");
			exit(EXIT_FAILURE);
		}
	}
return strip;
}

			/***Function for matching***/

char* Model_matching(char* string){
	
	char* help_string = NULL;
	help_string = (char*)malloc(STRING_SIZE*sizeof(char));
	char* Cs = (char*)malloc(TOKEN_SIZE*sizeof(char));
	char* Ct = (char*)malloc(TOKEN_SIZE*sizeof(char));
	char* out = (char*)malloc(TOKEN_SIZE*sizeof(char));
	char* out1 = (char*)malloc(TOKEN_SIZE*sizeof(char));
	int i, j;

	if(string!=NULL){
		/***TODO****/

		//if(!strcmp(string, "%rax") || !strcmp(string, "%rbx") || !strcmp(string, "%rcx") || !strcmp(string, "%rdx") || !strcmp(string, "%rsi") || !strcmp(string, "%rdi") || !strcmp(string, "%rbp") || !strcmp(string, "%rsp") || !strcmp(string, "%r8") || !strcmp(string, "%r9") || !strcmp(string, "%r10") || !strcmp(string, "%r11") || !strcmp(string, "%r12") || !strcmp(string, "%r13") || !strcmp(string, "%r14") || !strcmp(string, "%r15"))
	//	{
	//	strcpy(help_string, "r64");
			//printf("<%s_1>", string);
		//	return "r64";
	//	}

		for(i=0;i<16; i++){
			strcpy(Cs, Qregs[i]);
			for(j=0; j<strlen(Cs); j++) Ct[j] = toupper(Cs);
				sprintf(out, "%%%s", Cs);
				sprintf(out1, "%%%s", Ct);
				if(!strcmp(string,out)|| !strcmp(string, out1)) return "r64";
			}
		
		for(i=0;i<16; i++){
			strcpy(Cs, Dregs[i]);
			for(j=0; j<strlen(Cs); j++) Ct[j] = toupper(Cs);
				sprintf(out, "%%%s", Cs);
				sprintf(out1, "%%%s", Ct);
				if(!strcmp(string,out)|| !strcmp(string, out1)) return "r32";
			}

		for(i=0;i<16; i++){
			strcpy(Cs, Wregs[i]);
			for(j=0; j<strlen(Cs); j++) Ct[j] = toupper(Cs);
				sprintf(out, "%%%s", Cs);
				sprintf(out1, "%%%s", Ct);
				if(!strcmp(string,out)|| !strcmp(string, out1)) return "r16";
			}

		for(i=0;i<16; i++){
			strcpy(Cs, Bregs[i]);
			for(j=0; j<strlen(Cs); j++) Ct[j] = toupper(Cs);
				sprintf(out, "%%%s", Cs);
				sprintf(out1, "%%%s", Ct);
				if(!strcmp(string,out)|| !strcmp(string, out1)) return "r8";
			}

		for(i=0;i<16; i++){
			strcpy(Cs, Xregs[i]);
			for(j=0; j<strlen(Cs); j++) Ct[j] = toupper(Cs);
				sprintf(out, "%%%s", Cs);
				sprintf(out1, "%%%s", Ct);
				if(!strcmp(string,out)|| !strcmp(string, out1)) return "xmm";
			}

		for(i=0;i<16; i++){
			strcpy(Cs, Yregs[i]);
			for(j=0; j<strlen(Cs); j++) Ct[j] = toupper(Cs);
				sprintf(out, "%%%s", Cs);
				sprintf(out1, "%%%s", Ct);
				if(!strcmp(string,out)|| !strcmp(string, out1)) return "ymm";
			}

		if(strchr(string, '$')!=NULL)
		{
			return "imm";
		}

		else if(strchr(string, '(')!=NULL)
		{
			help_string = strchr(string, '(');

			for(i=0; i<16; i++){
				strcpy(Cs, Qregs[i]);
				for(j=0; j<strlen(Cs); j++) Ct[j] = toupper(Cs);
				sprintf(out, "%%%s", Cs);
				sprintf(out1, "%%%s", Ct);
				if(strstr(string, out)!=NULL || strstr(string, out1)!=NULL) return "m128";
			}

			for(i=0; i<16; i++){
				strcpy(Cs, Dregs[i]);
				for(j=0; j<strlen(Cs); j++) Ct[j] = toupper(Cs);
				sprintf(out, "%%%s", Cs);
				sprintf(out1, "%%%s", Ct);
				if(strstr(string, out)!=NULL || strstr(string, out1)!=NULL) return "m32";
			}
			 	
		}
	}
//return NULL;
}

void extract_operand(FILE *filein, FILE *fileout); // TODO
/*
* For each Instruction Line extract operands and put them 
	\in a file to set after that values who need to be tested  
 **/
void extract_operand(FILE *filein, FILE *fileout){

	int i, j;	
	char *string = (char*)malloc(STRING_SIZE*sizeof(char));
	char *token = (char*)malloc(STRING_SIZE*sizeof(char));
	if(!string && !token) {
		printf("unsufficient memory!!!\n");
		exit(EXIT_FAILURE);
	}
	while(fgets(string, STRING_SIZE, filein)!=NULL){

		string[strlen(string) - 1] = '\0';
		token = strtok(string, ";");
		for(i=0; (token = strtok(NULL, ";")); i++){

			if(token=="\0") fprintf(fileout, "DEFAULT_OPERAND\n");
			else{
				if(!strcmp(token,"m32")) fprintf(fileout, "1D;\nr32;\n");
				else if (!strcmp(token, "m128")) fprintf(fileout, "1D;\nr64;\n");
				else if (!strcmp(token, "m64")) fprintf(fileout, "1D;\nr64;\n");
				else if(!strcmp(token, "imm")){
					for(j=0; j<strlen(token); j++) token[j] = toupper(token[j]);
					fprintf(fileout, "%s;\n", token);
				}
				else fprintf(fileout, "%s;\n", token);
			}
		}
		free(string), string = NULL;
		string = (char*)malloc(STRING_SIZE*sizeof(char));
	}

return;	
}

int main(int argc, char **argv){
/*
for each line parse in csv file
then change each operand in the model it matches 

*/
	FILE* fileinput;
	FILE* filetemp;
	FILE* filehelp;
	char* string;
	char* param_string = (char*)malloc(STRING_SIZE*sizeof(char));
	char* config_string = (char*)malloc(STRING_SIZE*sizeof(char));
	char* help_string;
	char* token1;
	char* token2;
	char* token;
	char* output;
	char* this_file = NULL;
	char* new_file = NULL;
	int i;
	int j;
	int k;

	while((i=getopt(argc, argv, "f:C:s:"))!=EOF){
		switch(i){
			case 's': k = atoi(optarg);
			break;
			case 'f': strcpy(param_string,optarg);
			break;
			case 'C': strcpy(config_string,optarg);
			break;
			default: printf("Usage %s -f input_file -C Config_file -s size of unrollment\n", argv[0]);
							 exit(EXIT_FAILURE);
			break;
		}
	}//inserer le getopt pour récupérer le nombre de fois qu'on doit dérouler le code de sortie	
	
	operandLine my_operandLine;
	operandLine *List_operandLine = NULL;
	Malloc_type(List_operandLine, 1, operandLine)
	instructionLine *fetching_list = NULL;// = (instructionLine*)malloc(sizeof(instructionLine));
	instructionLine *test_list = NULL;

	struct dirent *results;
	DIR *lister;
	
			/*************Parsing Input File in CSV Format****************/

	fileinput = fopen(param_string, "r");
	
	char *param_modif = NULL;
	Malloc_InsnLine(param_modif)
 	param_modif = str_replace(param_string, strlen(param_string)-4, 1, "_temp.");
	filetemp = 	fopen(param_modif, "w");
	
	//fileinput = fopen("input.tmp", "r"); // devra etre donné en paramètre
	//filetemp = fopen("input_temp.tmp", "w");
	string = (char*)malloc(STRING_SIZE*sizeof(char));
	help_string = (char*)malloc(STRING_SIZE*sizeof(char));
	output = (char*)malloc(STRING_SIZE*sizeof(char));

	while(fgets(string, STRING_SIZE, fileinput)!=NULL){

		string[strlen(string) - 1]='\0';
		token1 = (char*)malloc(TOKEN_SIZE*sizeof(char));
		token2 = (char*)malloc(TOKEN_SIZE*sizeof(char));
		token  = (char*)malloc(TOKEN_SIZE*sizeof(char));

		token1 = strchr(string, ' ');//extract operands
		token2 = str_strip(token1);//remove useless spaces
		token1 = strtok(string, " ");//extract instruction from string

		for(j=0; j<strlen(token1); j++){
			token1[j] = toupper (token1[j]);
		}
		sprintf(output, "%s;", token1);

		for(i=0; (token = strtok(token2, ",")); i++){
			if(token[0]==' '){
				strcat(output, &token[1]);
			}else{
				strcat(output, token);
			}
			strcat(output, ";");
			token2 = NULL;
			
		}

		fprintf(filetemp, "%s\n", output);

		free(string), string = NULL;
		string =(char*)malloc(STRING_SIZE*sizeof(char));
	}
	fclose(fileinput);
	fclose(filetemp);
	
			/*******************Detecting models of all operands**********************/
	
	//filetemp = fopen("input_temp.tmp", "r");
	//fileinput = fopen("output_correct.tmp", "w");
	
	filetemp = fopen(param_modif, "r");
	char *gen_string = NULL;
	Malloc_InsnLine(gen_string)
 	gen_string = str_replace(param_string, strlen(param_string)-4, 1, "_gen.");
	fileinput = fopen(gen_string, "w");
	
	j = 0;
	while(fgets(string, STRING_SIZE, filetemp)!=NULL){
		string[strlen(string) - 1] ='\0';

		token = (char*)malloc(TOKEN_SIZE*sizeof(char));
		token1 = (char*)malloc(TOKEN_SIZE*sizeof(char));

		token = strtok(string, ";");
		sprintf(output, "%s;", token);

		for(i=0; (token = strtok(NULL, ";")); i++){

			token[strlen(token)]='\0';

			token1 = Model_matching(token);//main detecting function
			
			strcat(output, token1);
			strcat(output, ";");
		}

		fprintf(fileinput, "%s;;;\n", output); // la valeur J pourra etre rajouté si besoin
		j++;
		free(string),string = NULL;
		string = (char*)malloc(STRING_SIZE*sizeof(char));
	}

	fclose(filetemp);
	fclose(fileinput);

/*****
*** In this section , parsing Configuration file containing all parameters
****/

	//filehelp = fopen("ConfigGen_64.csv", "r");
	filehelp = fopen(config_string, "r");
	if(!filehelp){
		printf("check names of yours files\n");
		exit(EXIT_FAILURE);
	}
	
	string = (char*)malloc(STRING_SIZE*sizeof(char));
	if(!string){
		printf("string marche pas\n");
		exit(EXIT_FAILURE);
	}
	while(fgets(string, STRING_SIZE, filehelp)!=NULL){
		
		string[strlen(string) - 1] = '\0';

		my_operandLine.tab = str_split(string, ";", &my_operandLine.sum);//define

		List_operandLine = mylib_add_operandLine(List_operandLine, my_operandLine);//define
		
		free(string), string = NULL;
		string = (char*)malloc(STRING_SIZE*sizeof(char));
	}
	fclose(filehelp);
	//end of ConfigGen_64 parsing (will be done once)
	
	/*********
	**** At this part include the function mylib_arrgt(n, p, output_correct.tmp)
	*******/
	printf("j = %d\n", j);

	//strcpy(string, "output_correct.tmp");
	strcpy(string, gen_string);

	mylib_arrgt(j, j , string);
	
	token1 = strrchr(string, '.');
	strncpy(help_string, string, strlen(string) - strlen(token1));
	strcat(help_string, "_dir");//to fit help_string with the name of the direc.

	/**********************Scanning an arrangement file to extract operand************************************/

	lister = opendir(help_string);

	if(lister == NULL){
		printf("Unable to open this directory!!!\n");
		exit(EXIT_FAILURE);
	}
	j=0;
	free(output), output = NULL;
	Malloc_InsnLine(output)
	Malloc_InsnLine(this_file)
	Malloc_InsnLine(new_file)

	while((results = readdir(lister))){
		if(strcmp(results->d_name,".") && strcmp(results->d_name,"..") && strstr(results->d_name, "_Lp")==NULL){
			strcpy(this_file, help_string);
			strcat(this_file, "/");
			strcat(this_file, results->d_name);
			fileinput = fopen(this_file, "r");
			sprintf(new_file, "%s/Launcher.csv", help_string);
			filetemp = fopen(new_file, "a");
			if(fileinput == NULL){
				printf("unable to open the file asked!!!\n");
				exit(EXIT_FAILURE);
			}
			sprintf(output, "%s/%s_Lp.csv", help_string, results->d_name);
			fprintf(filetemp,"%s/%s;%s\n", help_string, results->d_name, output);
			filehelp = fopen(output, "w");
			extract_operand(fileinput, filehelp);//(will be done for every file of ordering)
			fclose(fileinput);
			fclose(filehelp);
			fclose(filetemp);
			j++;

	/*****
	**** Fetching The Parameter List for each Lp_file and 
	**** after that store the results of fetch_list in Lp_file corresponding to 
	**** the output Lp_file was extracted
	******/

			fileinput = fopen(output, "r");
			if(!fileinput){
				printf("check names of your input files\n");
				exit(EXIT_FAILURE);
			}
	
	/****
	**The following lines will be done for every file generated by arrgt_new
	***/

			i = 0;

			Malloc_type(fetching_list, 1, instructionLine)

			while(fgets(string, STRING_SIZE, fileinput)!=NULL){

				i++;
		
				string[strlen(string) - 1] = '\0';

				fetching_list = (instructionLine*)realloc(fetching_list, sizeof(instructionLine)*i);

				if(!fetching_list){
					printf("realloc error\n");
					exit(EXIT_FAILURE);
				}
				fetching_list[i-1].InstLine = (char*)malloc(STRING_SIZE*sizeof(char));
				strcpy(fetching_list[i-1].InstLine, string);

				fetching_list[i - 1].rank = i ;

			}// end of Lp_File parsing (will be done for every file of arrangement)

			fclose(fileinput);

			//mylib_fetch_register(List_operandLine, fetching_list, 3, i);//Can include generating one or more files from an unique arrgt based on a structure
																															// struct each_file{int nbr_file, int *nbr_fetching;} each_file
																															//with nbr_fetching Malloc_int(nbr_file) and nbr_fecthing[i] = "nbr of fetching for requested file"

			mylib_fetch_register(List_operandLine, fetching_list, k, i);

			string = str_replace(output, strlen(output)-4, 1, "_out.");
			fileinput = fopen(string, "w");
			mylib_print_param_list(fetching_list, i, fileinput);

			fclose(fileinput);
			remove(output);
			rename(string, output);
			free(fetching_list),fetching_list = NULL;
			//free(this_file), this_file = NULL;
		}

	}
	printf("End of dir treatment!!\n");
	closedir(lister);

	/***Test(not concerned by the reverse function)***/

	strcpy(string, "RAX;RBX;RAX;RDX;R9;R10;RBX;R9;RAX;RDX;");

	test_list = mylib_unique_list(string, &i);

 return 0; 
}
