#ifndef ARRGT_NEW_H_
#define ARRGT_NEW_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


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


void InsnLine_cpy(InsnLine A, InsnLine B);

void mylib_parse_file(FILE* file, Page InsnT);

void mylib_print_results(arrgt_t* arr, char* filename);

void Insn_arrangements(arrgt_t *arr, int k, Page L, Page t);

void mylib_arrgt(int n, int p, char *filename);

#endif
