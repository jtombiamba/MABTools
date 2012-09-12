/* arrgt_new.c
 *
 * Recherche de tous les arrangements de p éléments de
 * l'ensemble {1, 2, 3, 4, 5, ..., n}
 * 
 *
 * compilation :  gcc -O2 -o arrgt arrgt.c
 * usage : arrgt  n p
 *
 * la structure contient après calcul tous les arrangements
 * dans le tableau arrgt_t->PageNumber
 *
 * arrgt_t->PageNumber[i] est l'arrangement i 0 <= i < Anp
 *
 * arrgt->PageNumber[i].strLine[k] pour 0<= k < p sont les termes de l'arrangement
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "arrgt_new.h"

void InsnLine_cpy(InsnLine A, InsnLine B){

	strcpy(A, B);
	return;

}

void mylib_parse_file(FILE* file, Page InsnT){
		
		int i = 0;
		InsnLine string;
		Malloc_InsnLine(string)

		while(fgets(string, STRING_SIZE, file)!=NULL){
			string[strlen(string)-1] = '\0';
			Malloc_InsnLine(InsnT.strLine[i])
			InsnLine_cpy(InsnT.strLine[i], string);
			i++;
			free(string), string =NULL;
			Malloc_InsnLine(string)
		}

}


void mylib_print_results(arrgt_t* arr, char* filename){
	
	int i, j, k;
	char* namefile;
	Malloc_InsnLine(namefile)
	char* namefile_1;
	Malloc_InsnLine(namefile_1)
	char *token1 = (char*)malloc(10*sizeof(char));
	FILE *file;

	token1 = strrchr(filename, '.');
	strncpy(namefile_1, filename, strlen(filename) - strlen(token1));
	
	for(i=0; i<arr->anp; i++){

		sprintf(namefile, "%s_dir/out_arr_%d", namefile_1, i);
	
		char *dir_name = strdup(namefile);
		for(k=0; namefile[k]!='\0'; k++){
			if(namefile[k]=='/'){
				strncpy(dir_name, namefile, k+1);
				dir_name[k]='\0';
				if(access(dir_name, R_OK)){
					mkdir(dir_name, 0777);
				}
			}
		}
		free(dir_name);
	
		//printf("debug! %s\n", namefile);
		file = fopen(namefile, "w");
		if(file==NULL){
			printf("unable to open the f** file!!\n");
			exit(EXIT_FAILURE);
		}
		for(j=0;j<arr->p; j++){

			fprintf(file, "%s\n", arr->PageNumber[i].strLine[j]);
		}
		fclose(file);
	}
}

	
void mylib_arrgt(int n, int p, char *filename) {
	int  i, j, anp;
	
	Page InsnL;
	Page InsnT;

	FILE* filein;
	//FILE* fileout;

	arrgt_t* Insn_arr = malloc(sizeof(arrgt_t));

	if(!Insn_arr) {
		printf("unsufficient memory\n");
		exit(EXIT_FAILURE);
	}
	/*
	if(argc<3) {
		printf("usage : %s n p\n",argv[0]);
		exit(1);
	}
	n = atoi(argv[1]); // lecture des paramètres
	p = atoi(argv[2]);
	*/
        if(n<0 || p<0 || p>n) {
					printf("n must be greater or equal to p\n");
					//exit(EXIT_FAILURE);
					return ;
				}
	
	/* -----------------------------------------------------------------
	 * initialisations de 'arr' , 
	 * on pourrait le mettre dans une fonction
	 * -----------------------------------------------------------------
	 */
	for(i=n,j=1, anp=1;i>n-p;i--,j++) {   // calcul de Cnp
          anp *= i;
	}
	Insn_arr->n = n;
	Insn_arr->p = p;
	Insn_arr->anp = anp;
	Insn_arr->pos = 0;
	
	Malloc_type(Insn_arr->PageNumber, anp, Page) 
	
	filein = fopen(filename, "r");
	/* -----------------------------------------------------------------
	 *  préparation des paramètres L et t avant de lancer 
	 *  la fonction 'combinaisons'
	 *  -----------------------------------------------------------------
	 */


	Malloc_type(InsnL.strLine, p, InsnLine)
	Malloc_type(InsnT.strLine, n, InsnLine)
	mylib_parse_file(filein, InsnT);

	/* c'est parti */
	
	Insn_arrangements(Insn_arr, 0, InsnL, InsnT);

	/* -----------------------------------------------------------------
	 * faire ici ce qu'on veut de comb
	 * par exemple l'afficher comme on le fait ci-dessous
	 * -----------------------------------------------------------------
	 */

	mylib_print_results(Insn_arr, filename);

	/* -----------------------------------------------------------------
	 * pour faire bien on désalloue la mémoire
	 * -----------------------------------------------------------------
	 */
	 free(Insn_arr);
	
	/* -----------------------------------------------------------------
	 * plus rien à faire ici, on peut d'en aller
	 * -----------------------------------------------------------------
	 */
	//printf("Chance\n");

}


void Insn_arrangements(arrgt_t *arr, int k, Page L, Page t) {
	int n = arr->n, p = arr->p, i, j, j1;
	Page t2;
	Malloc_type(t2.strLine, n, InsnLine)
	
	if(k==p) {

		Malloc_type(arr->PageNumber[arr->pos].strLine, p, InsnLine)

		for(i=0;i<p;i++) {
				Malloc_InsnLine(arr->PageNumber[arr->pos].strLine[i])
				InsnLine_cpy(arr->PageNumber[arr->pos].strLine[i], L.strLine[i]);
		}
		arr->pos++;
		return;
	}
	for(i=0;i<n-k;i++) {

		Malloc_InsnLine(L.strLine[k])
		InsnLine_cpy(L.strLine[k], t.strLine[i]);

		for(j=0, j1=0;j<n-k;j++) {
			if(j != i) {
				Malloc_InsnLine(t2.strLine[j1])
				InsnLine_cpy(t2.strLine[j1], t.strLine[j]);
				j1++;
			}
		}
		Insn_arrangements(arr, k+1, L, t2);
	}
}

