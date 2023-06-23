#include "arvorebEst.h"

//Pesquisa
void Pesquisa(TipoRegistro *x, TipoApontador* Ap){
    int i;
    TipoApontador Pag;
    Pag = *Ap;

    if((*Ap)->Pt == Interna){
        i = 1;
        
        while (i < Pag->UU.U0.ni && x->chave > Pag->UU.U0.ri[i-1]) i++;

        if (x->chave < Pag->UU.U0.ri[i-1]) 
            Pesquisa(x, &Pag->UU.U0.pi[i-1]);
        else 
            Pesquisa(x, &Pag->UU.U0.pi[i]);
        return;
    }
    i = 1;

    while (i < Pag->UU.U1.ne && x->chave > Pag->UU.U1.re[i-1].Chave) i++;

    if (x->chave == Pag-> UU.U1.re[i-1].chave) 
        *x = Pag->UU.U1.re[i-1];
    else 
        printf("TIpoRegistro não está presente na árvore\n");
}