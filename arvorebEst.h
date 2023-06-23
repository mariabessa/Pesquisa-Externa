#ifndef arvorebEst_h
#define arvorebEst_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TipoRegistro {
    int chave;   //valor inteiro 
    long int dado1;  //valor inteiro longo 
    char dado2[1000];    //cadeia de 1000 caracteres 
    char dado3[5000];    //cadeia de 5000 caractere 
} TipoRegistro;

typedef enum {Interna, Externa} TipoIntExt;

typedef struct TipoPagina {
    TipoIntExt Pt;
    union {
        struct {
            int ni; //qt de itens dentro da pagina interna
            int ri[MM]; //vetor de chaves
            TipoApontador pi[MM+1]; //vetor de apontadores
        } U0;

        struct{
            int ne; //qt de itens dentro da pagina externa
            TipoRegistro re[MM2]; //vetor de registros 
        }U1;
    }UU;
} TipoPagina;

typedef struct TipoPagina* TipoApontador;

void Pesquisa(TipoRegistro*, TipoApontador*);


#endif