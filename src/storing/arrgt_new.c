/* arrgt.c
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

#define STRING_SIZE 50

#define Malloc_InsnLine(name) \
				\
				name = (char*)malloc(STRING_SIZE*sizeof(char)); \
				if(!name) { \
				fprintf(stderr, "unsufficient memory\n"); exit(EXIT_FAILURE);}  

#define Malloc_type(name, size, type) \
				\
				name = (type*)malloc(size*sizeof(type)); \
				if(!name) { \
				fprintf(stderr, "unsufficient memory\n"); exit(EXIT_FAILURE);}  


typedef char* InsnLine; // redéfinition de char*

typedef struct {InsnLine* strLine;} Page; // tableau de InsnLine qui contiendra les lignes d' 1 fichier



typedef struct _Arrgt {

	int n,//le N de Anp
			p,//le P de Anp
			anp,// la valeur Anp
			pos;//la position du curseur sur tous les Anp

	Page* PageNumber; // contiendra toutes les anp pages 

	
} arrgt_t;


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


void mylib_print_results(arrgt_t* arr, FILE* file){
	
	int i, j;
	InsnLine namefile;
	Malloc_InsnLine(namefile)

	for(i=0; i<arr->anp; i++){

		sprintf(namefile, "Results/out_arr_%d", i);
		file = fopen(namefile, "w");
		for(j=0;j<arr->p; j++){

			fprintf(file, "%s\n", arr->PageNumber[i].strLine[j]);
		}
		fclose(file);
	}
}


void Insn_arrangements(arrgt_t *arr, int k, Page L, Page t);
	
int
main(int argc, char *argv[]) {
	int n, p, i, j, anp;
	
	Page InsnL;
	Page InsnT;

	FILE* filein;
	FILE* fileout;

	arrgt_t* Insn_arr = malloc(sizeof(arrgt_t));

	if(!Insn_arr) {
		printf("unsufficient memory\n");
		exit(EXIT_FAILURE);
	}

	if(argc<3) {
		printf("usage : %s n p\n",argv[0]);
		exit(1);
	}
	n = atoi(argv[1]); // lecture des paramètres
	p = atoi(argv[2]);
        if(n<0 || p<0 || p>n) return 0;
	
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
	
	filein = fopen("output_correct.tmp", "r");
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

	mylib_print_results(Insn_arr, fileout);

	/* -----------------------------------------------------------------
	 * pour faire bien on désalloue la mémoire
	 * -----------------------------------------------------------------
	 */
	 free(Insn_arr);
	
	/* -----------------------------------------------------------------
	 * plus rien à faire ici, on peut d'en aller
	 * -----------------------------------------------------------------
	 */
	printf("Chance\n");

	return 0;
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

