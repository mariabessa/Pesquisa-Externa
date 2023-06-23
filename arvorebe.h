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



typedef enum {Interna, Externa} TipoIntExt;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina {
   TipoIntExt Pt;
   union{
        struct {
            int ni;
            int ri[M];
            TipoApontador pi[M + 1];
        } Interna;
        struct{
            int ne;
            TipoRegistro re[MM];
        } Externa;
   } Pagina;
} TipoPagina;

//Inicializar
TipoApontador InicializaBE (); 


//Pesquisa
void PesquisaBE (TipoRegistro*, TipoApontador*);

//Inserção
void InsereNaPaginaBE (TipoApontador, TipoRegistro, TipoApontador);
void InsBE(TipoRegistro, TipoApontador, short*, TipoRegistro*, TipoApontador*);
void InsereBE(TipoRegistro, TipoApontador*);

#endif 