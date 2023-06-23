#include "arvorebe.h"

// Inicialização: Arvore B

TipoApontador InicializaBE (){
    TipoApontador raiz = (TipoApontador)malloc(sizeof(TipoPagina));
    raiz->n = 0;
    raiz->Pagina->ni = 0;
    
    for (int i = 0; i < MM; i++) {
        raiz->Pagina->ri[i].chave = -1;
        raiz->Pagina->ri[i].dado1 = -1;
        raiz->Pagina->ri[i].dado2[0] = '\0';
        raiz->Pagina->ri[i].dado3[0] = '\0';
    }
    
    for (int i = 0; i < MM + 1; i++) {
        raiz->p[i] = NULL;
    }
    
    return raiz;
}

// Pesquisa: Arvore B

void PesquisaBE(TipoRegistro *x, TipoApontador *Ap){
    int i;
    TipoApontador Pag;
    Pag = *Ap;

    if((*Ap)->Pt == Interna){
        i = 1;
        while(i < Pag->Pagina.Interna.ni && x->chave > Pag->Pagina.Interna.ri[i-1])
            i++;
        if(x->chave < Pag->Pagina.Interna.ri[i-1])
            Pesquisa(x, &Pag->Pagina.Interna.pi[i-1]);
            
            else
                Pesquisa(x, &Pag->Pagina.Interna.pi[i]);
        return;
    }
    i = 1;

    while(i < Pag->Pagina.Externa.ne && x->chave > Pag->Pagina.Externa.re[i-1].chave)
        i++;
    if(x->chave == Pag->Pagina.Externa.re[i-1].chave)
        *x = Pag->Pagina.Externa.re[i-1];

        else
            printf("TipoRegistro nao esta presente na arvore\n");
}

//Inserção: Arvore B*


void InsereNaPaginaExternaBE (TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir) {
    short NaoAchouPosicao;
    int k;

    k = Ap->n;      //ERROOOOOOOOOOOOOOOOOOOOOOOOOOO

    NaoAchouPosicao = (k>0);

    while (NaoAchouPosicao) {

        if (Reg.chave >= Ap->r[k-1].chave) {
            NaoAchouPosicao = false;
            break;
        }

        Ap->r[k] = Ap->r[k-1];
        Ap->p[k+1] = Ap->p[k];
        k--;

        if(k<1){ 
            NaoAchouPosicao = false;
        }

    }

    Ap->r[k] = Reg;
    Ap->p[k+1] = ApDir;
    Ap->n++;
}

void InsereNaPaginaInternaBE (TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir) {
    short NaoAchouPosicao;
    int k;

    k = Ap->n;      //ERROOOOOOOOOOOOOOOOOOOOOOOOOOO

    NaoAchouPosicao = (k>0);

    while (NaoAchouPosicao) {

        if (Reg.chave >= Ap->r[k-1].chave) {
            NaoAchouPosicao = false;
            break;
        }

        Ap->r[k] = Ap->r[k-1];
        Ap->p[k+1] = Ap->p[k];
        k--;

        if(k<1){ 
            NaoAchouPosicao = false;
        }

    }

    Ap->r[k] = Reg;
    Ap->p[k+1] = ApDir;
    Ap->n++;
}

void InsBE(TipoRegistro Reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno, TipoApontador *ApRetorno) {
    long i = 1; 
    long j;
    TipoApontador ApTemp;


    if(Ap == NULL) {

        *Cresceu = true;
        (*RegRetorno) = Reg; 
        (*ApRetorno) = NULL;
        return;
    }

    while (i<Ap->n && Reg.chave > Ap->r[i-1].chave) 
        i++;

    if(Reg.chave == Ap->r[i-1].chave){
        printf("Erro: Registro já está presente\n");
        *Cresceu = false;
        return;
    }

    if(Reg.chave < Ap->r[i-1].chave) 
        i--;
    
    Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);

    if(!*Cresceu) 
        return;

    if(Ap->n < MM) { //pagina tem espaço
        InsereNaPagina (Ap, *RegRetorno, *ApRetorno);
        *Cresceu = false;
        return;
    }

    //Overflow: Pagina tem que ser dividida
    ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;
    
    if(i<M+1){
        InsereNaPagina(ApTemp, Ap->r[MM-1], Ap->p[MM]);
        Ap->n--;
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    }

    else 
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
    
    for(j=M+2; j<= MM; j++) 
        InsereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j]);

    Ap->n = M; 
    ApTemp->p[0] = Ap->p[M+1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;
}

void InsereBE(TipoRegistro Reg, TipoApontador *Ap) {
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;

    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);
    
    if(Cresceu) { //Arvore cresce na altura pela raiz
        ApTemp = (TipoPagina*) malloc (sizeof(TipoPagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap;
        *Ap = ApTemp; 
    }
}
