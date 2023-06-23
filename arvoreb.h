#ifndef arvoreb_h
#define arvoreb_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MM 4
#define M 2

<<<<<<< Updated upstream:arvoreb.h
typedef long TipoChave;

typedef struct TipoRegistro {
    TipoChave Chave;

//     chave (valor inteiro), dado1 (valor inteiro longo), dado2 (cadeia de 1000
// caracteres), dado3 (cadeia de 5000 caracteres). N
=======
typedef struct TipoRegistro {
    int chave;   //valor inteiro 
    long int dado1;  //valor inteiro longo 
    char dado2[1000];    //cadeia de 1000 caracteres 
    char dado3[5000];    //cadeia de 5000 caractere 
>>>>>>> Stashed changes:Pesquisa-Externa-version-1.0.5/arvoreb.h
} TipoRegistro;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina {
    short n;
    TipoRegistro r[MM];
    TipoApontador p[MM +1];
} TipoPagina;

//Inicializar
void InicializaArvore(TipoApontador* arvore){
    arvore = NULL;
}

//Pesquisa
void Pesquisa (TipoRegistro*, TipoApontador);

//Caminhamento
void Imprime (TipoApontador);

//Inserção
void InsereNaPagina (TipoApontador, TipoRegistro, TipoApontador);
void Ins(TipoRegistro, TipoApontador, short*, TipoRegistro, TipoApontador);
void Insere(TipoRegistro, TipoApontador*);


//Remoção
void Reconstitui (TipoApontador, TipoApontador, int, short*);
void Antecessor (TipoApontador, int, TipoApontador, short*);
void Ret(TipoChave, TipoApontador*, short*);
void Retira (TipoChave, TipoApontador*);

#endif 