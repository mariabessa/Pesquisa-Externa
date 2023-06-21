#ifndef arvorebe_h
#define arvorebe_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MM 4
#define M 2

typedef struct TipoRegistro {
    //TipoChave Chave;

    int chave;   //valor inteiro 
    long int dado1;  //valor inteiro longo 
    char dado2[1000];    //cadeia de 1000 caracteres 
    char dado3[5000];    //cadeia de 5000 caractere 
} TipoRegistro;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina {
    short n;
    TipoRegistro r[MM];
    TipoApontador p[MM +1];
} TipoPagina;

//Inicializar
TipoApontador Inicializa (); 


//Pesquisa
void Pesquisa (TipoRegistro*, TipoApontador);

//Caminhamento
void Imprime (TipoApontador);

//Inserção
void InsereNaPagina (TipoApontador, TipoRegistro, TipoApontador);
void Ins(TipoRegistro, TipoApontador, short*, TipoRegistro*, TipoApontador*);
void Insere(TipoRegistro, TipoApontador*);


//Remoção
void Reconstitui (TipoApontador, TipoApontador, int, short*);
void Antecessor (TipoApontador, int, TipoApontador, short*);
void Ret(int, TipoApontador*, short*);
void Retira (int, TipoApontador*);

#endif 