/* arrgt.c
 *
 * Recherche de tous les arrangements de p éléments de
 * l'ensemble {1, 2, 3, 4, 5, ..., n}
 * 
 * 01/05/2005 Jean-Paul Davalan <jpdvl@wanadoo.fr>
 *
 * compilation :  gcc -O2 -o arrgt arrgt.c
 * usage : arrgt  n p
 *
 * la structure contient après calcul tous les arrangements
 * dans le tableau arrgt->tab
 *
 * arrgt->tab[i] est l'arrangement i 0 <= i < Anp
 *
 * arrgt->tab[i][k] pour 0<= k < p sont les termes de l'arrangement
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

	int n,
			p,
			anp,
			pos;

	Page* PageNumber; // contiendra toutes les anp pages 

	
} arrgt_t;


/* la structure cb ci-dessous contient tous les résultats */


typedef struct arrgt {
	int n,    // le n de Anp
	    p,    // le p de Anp
	    anp,  // la valeur Anp du nombre de combinaisons
	    pos,  // varie de 0 au début à Cnp-1 à la fin
	    **tab; // tableau de Cnp lignes contenant chacune une combinaison
	           // sous la forme de p entiers (de 1 au moins à n au plus)
} arrgt;

void InsnLine_cpy(InsnLine A, InsnLine B){

	strcpy(A, B);
	return;

}

void mylib_parse_file(FILE* file, Page InsnT){
		
		int i = 0;
		InsnLine string;
		Malloc_InsnLine(string)//= (char*)malloc(STRING_SIZE*sizeof(char));
		InsnLine help_InsnLine;
		Malloc_InsnLine(help_InsnLine)// = malloc(sizeof(InsnLine));

		while(fgets(string, STRING_SIZE, file)!=NULL){
			string[strlen(string)-1] = '\0';
			Malloc_InsnLine(InsnT.strLine[i])
			InsnLine_cpy(InsnT.strLine[i], string);
			i++;
			free(string), string =NULL;
			Malloc_InsnLine(string)//= (char*)malloc(STRING_SIZE*sizeof(char));
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

void arrangements(arrgt *arr, int k, int *L, int *t);

void Insn_arrangements(arrgt_t *arr, int k, Page L, Page t);
	
int
main(int argc, char *argv[]) {
	int n, p, i, j, anp, *L, *t;
        arrgt * arr = (arrgt *)malloc(sizeof(arrgt));
	
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
	arr->n = n;
	Insn_arr->n = n;
	arr->p = p;
	Insn_arr->p = p;
	arr->anp = anp;
	Insn_arr->anp = anp;
	arr->pos = 0;
	Insn_arr->pos = 0;

	arr->tab = (int **)malloc(anp * sizeof(int *));
	
	Malloc_type(Insn_arr->PageNumber, anp, Page) 
	
	filein = fopen("input.tmp", "r");
	/* -----------------------------------------------------------------
	 *  préparation des paramètres L et t avant de lancer 
	 *  la fonction 'combinaisons'
	 *  -----------------------------------------------------------------
	 */
	L = (int *) malloc(p*sizeof(int));
	t = (int *) malloc(n*sizeof(int));

	Malloc_type(InsnL.strLine, p, InsnLine)
	Malloc_type(InsnT.strLine, n, InsnLine)

	for(i=0;i<n;i++) t[i] = i;

	mylib_parse_file(filein, InsnT);

	/* c'est parti */
	
	arrangements(arr, 0, L, t);

	
	/* -----------------------------------------------------------------
	 * faire ici ce qu'on veut de comb
	 * par exemple l'afficher comme on le fait ci-dessous
	 * -----------------------------------------------------------------
	 */
	for(i=0;i<arr->anp;i++) {   // Cnp lignes
		printf("(");
		for(j=0;j<arr->p;j++) { // de p nombres entiers
			printf("%d",arr->tab[i][j]);
			if(j<arr->p-1) printf(", ");
		}
                printf(")\n");
	}
	printf("\n");
	/* -----------------------------------------------------------------
	 * pour faire bien on désalloue la mémoire
	 * -----------------------------------------------------------------
	 */
	free(L);
	free(t);
	for(i=0;i<arr->anp;i++) {
		 free(arr->tab[i]);
	}
	free(arr->tab);
	free(arr);
	
	/* -----------------------------------------------------------------
	 * plus rien à faire ici, on peut d'en aller
	 * -----------------------------------------------------------------
	 */
	Insn_arrangements(Insn_arr, 0, InsnL, InsnT);
	printf("chance\n");
	mylib_print_results(Insn_arr, fileout);

	return 0;
}


void arrangements(arrgt *arr, int k, int *L, int *t) {
	int n = arr->n, p = arr->p, i, j, j1, t2[n];
	
	printf("k = %d\n", k);
	if(k==p) {
		arr->tab[arr->pos] = (int *)malloc(p*sizeof(int));
		for(i=0;i<p;i++) arr->tab[arr->pos][i] = L[i] + 1;
		arr->pos++;
		return;
	}
	for(i=0;i<n-k;i++) {
		L[k] = t[i];
		for(j=0, j1=0;j<n-k;j++) {
			if(j != i) {
				t2[j1] = t[j];
				j1++;
			}
		}
		arrangements(arr, k+1, L, t2);
	}
}

void Insn_arrangements(arrgt_t *arr, int k, Page L, Page t) {
	int n = arr->n, p = arr->p, i, j, j1;
	Page t2;
	Malloc_type(t2.strLine, n, InsnLine)
	
	printf("k = %d\n", k);
	if(k==p) {
		//arr->PageNumber[arr->pos] = (InsnLine*)malloc(p*sizeof(int));
		Malloc_type(arr->PageNumber[arr->pos].strLine, p, InsnLine)

		for(i=0;i<p;i++) {
				Malloc_InsnLine(arr->PageNumber[arr->pos].strLine[i])
				InsnLine_cpy(arr->PageNumber[arr->pos].strLine[i], L.strLine[i]);//arr->tab[arr->pos][i] = L[i] + 1;
		}
		arr->pos++;
		return;
	}
	for(i=0;i<n-k;i++) {

		//printf("before\n");
		Malloc_InsnLine(L.strLine[k])
		InsnLine_cpy(L.strLine[k], t.strLine[i]);
		//printf("after\n");
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

