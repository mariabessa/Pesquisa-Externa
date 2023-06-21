# ifndef ASI_h
# define ASI_h
#include <stdio.h>
#include <stdlib.h>
#define ITENSPORPAGINA 2

typedef struct{
    int chave;
    long int dado1;
    char dado2[1000];
    char dado3[5000];
}Item;

int acessoSequencialIndexado(Item *, FILE*);
int pesquisa(int*, int, int, Item *, FILE *);

# endif