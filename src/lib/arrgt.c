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

#define Malloc(name, size, type) \
				\
				type* name = malloc(size*sizeof(type)); \
				if(!name) { \
				fprintf(stderr, "unsufficient memory\n"); exit(EXIT_FAILURE);}  
					

#define Malloc_type(name, size, type) \
				\
				name = (type*)malloc(size*sizeof(type)); \
				if(!name) { \
				fprintf(stderr, "unsufficient memory\n"); exit(EXIT_FAILURE);}  

				

/****************Début des fonctions et structures*******************/

/* la structure cb ci-dessous contient tous les résultats */
typedef struct arrgt {
	int n,    // le n de Anp
	    p,    // le p de Anp
	    anp,  // la valeur Anp du nombre de combinaisons
	    pos,  // varie de 0 au début à Cnp-1 à la fin
	    **tab; // tableau de Cnp lignes contenant chacune une combinaison
	           // sous la forme de p entiers (de 1 au moins à n au plus)
} arrgt;

typedef struct _InsnLine {
	char* strLine;		//La chaine de l instruction
	struct _InsnLine *next;		//La suite de la chaine

} InsnLine;


typedef struct arrgt_t {
	int n,    // le n de Anp
	    p,    // le p de Anp
	    anp,  // la valeur Anp du nombre de combinaisons
	    pos;  // varie de 0 au début à Cnp-1 à la fin

	InsnLine** InsnTab; // Tableau de Anp lignes contenant chacune un arrangement
										 // sous la forme de p éléments dans chaque liste chainée

} arrgt_t;

	
void mylib_copy_InsnLine(InsnLine InsnLineA, InsnLine* InsnLineB){

		//InsnLineB->strLine = (char*)malloc(STRING_SIZE*sizeof(char));
		Malloc_type(InsnLineB->strLine, STRING_SIZE, char)
		strcpy((*InsnLineB).strLine, InsnLineA.strLine);
		return;
}

InsnLine* mylib_add_InsnLine(InsnLine* List_InsnLine, InsnLine InsnLineA){

		//InsnLine* new_element = malloc(sizeof(InsnLine));
		Malloc(new_element, 1, InsnLine)
		//InsnLine* help = malloc(sizeof(InsnLine));
		Malloc(help, 1, InsnLine)
		Malloc_type(new_element->strLine, STRING_SIZE, char)
		//new_element->strLine = (char*)malloc(STRING_SIZE*sizeof(char));
		mylib_copy_InsnLine(InsnLineA, new_element);
		new_element->next = NULL;
		if(!List_InsnLine){
			printf("first\n");
			return new_element;
		}
		else{
			help = List_InsnLine;
			//printf("state\n");
			while(help->next!=NULL){
				help = help->next;
				//printf("rest\n");
			}
			//help->next = malloc(sizeof(InsnLine));
			Malloc_type(help->next, 1, InsnLine)
			help->next = new_element;
		}

		return List_InsnLine;
}

void mylib_parse_file(FILE* file, InsnLine* InsnT){
		
		int i;
		char* string = (char*)malloc(STRING_SIZE*sizeof(char));
		InsnLine help_InsnLine;// = malloc(sizeof(InsnLine));
		help_InsnLine.strLine = (char*)malloc(STRING_SIZE*sizeof(char));

		while(fgets(string, STRING_SIZE, file)!=NULL){
			string[strlen(string)-1] = '\0';
			strcpy(help_InsnLine.strLine, string);
			InsnT = mylib_add_InsnLine(InsnT, help_InsnLine);
			free(string), string =NULL;
		  string = (char*)malloc(STRING_SIZE*sizeof(char));
		}

}

InsnLine* mylib_Insn_i(InsnLine* InsnLineA, int index){

	int i;
	InsnLine* help_InsnLine = malloc (sizeof(InsnLine));
	help_InsnLine = InsnLineA;
	for(i=0; i<index && help_InsnLine->next !=NULL; i++){
		help_InsnLine = help_InsnLine->next;
	}
	if(help_InsnLine == NULL){
		return NULL;
	}
	else {
		return help_InsnLine;
	}
}

void mylib_print_results(arrgt_t* arr, FILE* file){
	
	int i, j;
	char* namefile = (char*)malloc(STRING_SIZE * sizeof(char));
	InsnLine* help_printLine = malloc(sizeof(InsnLine));
	
	for(i=0; i<arr->anp; i++){
		help_printLine = arr->InsnTab[i];
		sprintf(namefile, "Results/out_arr_%d", i);
		file = fopen(namefile, "w");
		while(help_printLine->next!=NULL){
			fprintf(file, "%s\n", help_printLine->next->strLine);
			help_printLine = help_printLine->next;
		}
		free(help_printLine), help_printLine = NULL;
		help_printLine = malloc(sizeof(InsnLine));
		fclose(file);
	}
}

/************Fin des fonctions et structures********************/

void arrangements(arrgt *arr, int k, int *L, int *t);

//void Insn_arrangements(arrgt_t *arr, int k, InsnLine* L, InsnLine* t);

/***************fonction Arrangement pour Lignes d Instructions***************************/

void Insn_arrangements(arrgt_t* arr, int k, InsnLine* L, InsnLine* t) {

	int n = arr->n, p = arr->p, i, j;
	int j1;
	InsnLine* t_second = NULL;
	t_second = malloc(sizeof(InsnLine));
	t_second->next = NULL;
	InsnLine t_third[n];
	//Malloc(t_second, n, InsnLine)

	InsnLine help_copy_InsnLine;// = malloc(sizeof(InsnLine));
	
	InsnLine* help_copy_InsnLine_2 = malloc(sizeof(InsnLine));
	
	printf("k = %d\n", k);
	
	if(k==p) {
	
		arr->InsnTab[arr->pos] = (InsnLine*)malloc(sizeof(InsnLine));

		Malloc_type(arr->InsnTab[arr->pos], p, InsnLine)
		
		help_copy_InsnLine.strLine = (char*)malloc(STRING_SIZE*sizeof(char));
		//help_copy_InsnLine_2.strLine = (char*)malloc(STRING_SIZE*sizeof(char));

		while(L->next!=NULL) {
			//mylib_copy_InsnLine(*(L->next), &(help_copy_InsnLine));
			strcpy(help_copy_InsnLine.strLine, L->next->strLine);
			
			printf("obstacle %s\n", help_copy_InsnLine.strLine);

			mylib_add_InsnLine(arr->InsnTab[arr->pos], help_copy_InsnLine);
			
			L = L->next;
		}

		arr->pos++;
		
		return;
	}
	printf("two\n");
	
	for(i=0;i<n-k;i++) {

		//mylib_add_InsnLine(L, &(mylib_Insn_i(t, i)->next));
		
		help_copy_InsnLine_2 = mylib_Insn_i(t, i);
		
		strcpy(help_copy_InsnLine.strLine, help_copy_InsnLine_2->next->strLine);
		
		mylib_add_InsnLine(L, help_copy_InsnLine);
		
		for(j=0;j<n-k;j++) {
			if(j != i) {
				
				help_copy_InsnLine_2 = mylib_Insn_i(t, j);

				strcpy(help_copy_InsnLine.strLine, help_copy_InsnLine_2->next->strLine);
				//strcpy(help_copy_InsnLine.strLine, mylib_Insn_i(t, j)->next->strLine);
				//printf("lool %d %s and %s\n", j,  help_copy_InsnLine.strLine, t_second->strLine);
				
				mylib_add_InsnLine(t_second, help_copy_InsnLine);
				
				printf("real\n");
				
			}
		}
		Insn_arrangements(arr, k+1, L, t_second);
	}
return;
}
	
int
main(int argc, char *argv[]) {  //functions or datatypes with Insn_ are for the instruction version of arrangements
	int n, p, i, j, anp, *L, *t;

	FILE* filein;
	FILE* fileout;

	InsnLine* InsnL;
	InsnLine* InsnT;

        arrgt * arr = (arrgt *)malloc(sizeof(arrgt));

        arrgt_t * Insn_arr = (arrgt_t *)malloc(sizeof(arrgt_t));


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
	for(i=n,j=1, anp=1;i>n-p;i--,j++) {   // calcul de Anp
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
	//Insn_arr->InsnTab = (InsnLine**)malloc(anp * sizeof(InsnLine*));
	Malloc_type(Insn_arr->InsnTab, anp, InsnLine*)
	filein = fopen("input.tmp", "r");
	/* -----------------------------------------------------------------
	 *  préparation des paramètres L et t avant de lancer 
	 *  la fonction 'arrangements'
	 *  -----------------------------------------------------------------
	 */
	L = (int *) malloc(p*sizeof(int));
	InsnL =  malloc(sizeof(InsnLine));
	t = (int *) malloc(n*sizeof(int));
	InsnT =  malloc(sizeof(InsnLine));
	for(i=0;i<n;i++) t[i] = i;
	printf("entree\n");
	mylib_parse_file(filein, InsnT);
	printf("sortie\n");
	fclose(filein);
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
	 * plus rien à faire ici, on peut commencer avec les lignes d instructions
	 * -----------------------------------------------------------------
	 */

	Insn_arrangements(Insn_arr, 0, InsnL, InsnT);

	mylib_print_results(Insn_arr, fileout);

	free(InsnL);
	free(InsnT);
	for(i=0;i<Insn_arr->anp;i++) {
		 free(Insn_arr->InsnTab[i]);
	}
	free(Insn_arr->InsnTab);
	free(Insn_arr);

	return 0;
}


void arrangements(arrgt *arr, int k, int *L, int *t) {
	int n = arr->n, p = arr->p, i, j, j1, t2[n];
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
