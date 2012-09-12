#ifndef MYLIB_H
#define MYLIB_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STRING_SIZE 50
#define TOKEN_SIZE 15


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

char** str_split(char *s, const char *ct, int *sum);

void mylib_print_all(operandLine* List_operandLine);

operandLine* mylib_operandLine_i(operandLine* List_operandLine, int index);

operandLine* mylib_operandLine_find(operandLine* List_operandLine, char* index);

void mylib_copy_instructionLine(instructionLine InstrLineA, instructionLine* InstrLineB);

void mylib_copy_operandLine(operandLine operandLineA, operandLine* operandLineB);

operandLine* mylib_add_operandLine(operandLine *list_operandLine, operandLine operandLineA);

int mylib_nbr_Listoperand(operandLine* List_operandList);

int call_register(char **tab, int sum, int *previous, char *output);

char *str_replace(const char *s, long unsigned int start, long unsigned int lenght, const char *ct);

int str_istr(const char* cs, const char *ct);

char* mylib_find_and_replace(const char *string1, FILE* file1, char* change);

void mylib_fetch_register(operandLine* List_operandLine, instructionLine* List_of_fetch, int number, int rank);

void mylib_print_param_list(instructionLine* List_of_param, int all,  FILE *file);

instructionLine * mylib_unique_list(char * string, int *total);

void mylib_clear_copy(instructionLine *instrLineA, int allA,  instructionLine *instrLineB, int allB);

#endif
