#include "arvorebe.h"

// Inicialização: Arvore B

TipoApontador Inicializa (){
    TipoApontador raiz = (TipoApontador)malloc(sizeof(TipoPagina));
    raiz->n = 0;
    
    for (int i = 0; i < MM; i++) {
        raiz->r[i].chave = -1;
        raiz->r[i].dado1 = -1;
        raiz->r[i].dado2[0] = '\0';
        raiz->r[i].dado3[0] = '\0';
    }
    
    for (int i = 0; i < MM + 1; i++) {
        raiz->p[i] = NULL;
    }
    
    return raiz;
}

// Pesquisa: Arvore B

void Pesquisa(TipoRegistro *x, TipoApontador *Ap){
    int i;
    TipoApontador Pag;
    Pag = *Ap;

    if((*Ap)->Pt == Interna){
        i = 1;
        while(i < Pag->UU.U0.ni && x->chave > Pag->UU.U0.ri[i-1])
            i++;
        if(x->chave < Pag->UU.U0.ri[i-1])
            Pesquisa(x, &Pag->UU.U0.pi[i-1]);
            
            else
                Pesquisa(x, &Pag->UU.U0.pi[i]);
        return;
    }
    i = 1;

    while(i < Pag->UU.U1.ne && x->chave > Pag->UU.U1.re[i-1].chave)
        i++;
    if(x->chave == Pag->UU.U1.re[i-1].chave)
        *x = Pag->UU.U1.re[i-1];

        else
            printf("TipoRegistro nao esta presente na arvore\n");
}

// Caminhamento: Arvore B

void Imprime (TipoApontador arvore) {
    int i=0;

    if (arvore == NULL) 
        return;

    while (i<= arvore->n){
        Imprime(arvore->p[i]);
        
        if (i != arvore->n)
            printf("%d ", arvore->r[i].chave);
        
        i++;
    }
}

//Inserção: Arvore B

void InsereNaPagina (TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir) {
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

void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno, TipoApontador *ApRetorno) {
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

void Insere(TipoRegistro Reg, TipoApontador *Ap) {
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

//Remoção: Arvore B

void Reconstitui (TipoApontador ApPag, TipoApontador ApPai, int PosPai, short* Diminuiu) {
    TipoPagina *Aux; 
    long DispAux, j;

    if (PosPai < ApPai->n) {  //TipoPagina a direita de ApPag   
    Aux = ApPai->p[PosPai+1]; 
    DispAux = (Aux->n - M + 1)/2;
    ApPag->r[ApPag->n] = ApPai->r[PosPai];
    ApPag->p[ApPag->n + 1] = Aux->p[0];
    ApPag->n++;
    
        if (DispAux > 0) { //Existe folga: transfere de Aux para ApPag
            for (j=1; j<DispAux; j++){
                InsereNaPagina(ApPag, Aux -> r[j-1], Aux->p[j]);
                ApPai->r[PosPai] = Aux->r[DispAux-1];
                Aux->n -= DispAux;
                for (j=0; j<Aux->n;j++) Aux->r[j] = Aux->r[j+DispAux];
                for (j=0; j<=Aux->n; j++) Aux->p[j] = Aux->p[j+DispAux];
                *Diminuiu = false;
            }
        }

        else { //fusao: intercala Aux em  ApPag e libera Aux 
            for (j=1; j<=M; j++) InsereNaPagina(ApPag, Aux->r[j-1], Aux->p[j]);
            free (Aux);
            for (j = PosPai + 1; j < ApPai->n; j++){
                ApPai->r[j-1] = ApPai->r[j]; ApPai->p[j] = ApPai->p[j+1];
            }
            ApPai->n--;
            
            if (ApPai->n >= M) *Diminuiu = false;
        }

    }

    else { //Aux = TipoPagina a esquerda de ApPag  
        Aux = ApPai->p[PosPai-1];
        DispAux = (Aux->n - M + 1)/2;
        
        for (j = ApPag->n; j >= 1; j--) ApPag->r[j] = ApPag -> r[j-1];
        
        ApPag->r[0] = ApPai->r[PosPai-1];

        for (j = ApPag->n; j>= 0; j--) ApPag->p[j+1] = ApPag->p[j];

        ApPag->n++;

        if(DispAux > 0) {//Existe folga: transferencia de Aux para ApPag
            for (j=1; j< DispAux; j++) InsereNaPagina(ApPag, Aux->r[Aux->n-j], Aux->p[Aux->n - j + 1]);

            ApPag->p[0] = Aux->p[Aux->n - DispAux + 1];
            ApPai->r[PosPai-1] = Aux->r[Aux->n - DispAux];
            Aux->n -= DispAux;
            *Diminuiu = false;
        }

        else { //Fusão: intercala ApPag em Aux e libea ApPag 
            for (j=1; j<= M; j++) InsereNaPagina (Aux, ApPag->r[j-1], ApPag->p[j]);
            free(ApPag);
            ApPai->n--;
            
            if (ApPai->n >= M) *Diminuiu = false;
        }
    }
}

void Antecessor (TipoApontador Ap, int Ind, TipoApontador ApPai, short *Diminuiu) {
    if (ApPai->p[ApPai->n] != NULL){
        Antecessor (Ap, Ind, ApPai->p[ApPai->n], Diminuiu);
        
        if (*Diminuiu) 
            Reconstitui(ApPai->p[ApPai->n], ApPai, (long)ApPai->n, Diminuiu);
    
        return;
    }
    Ap->r[Ind-1] = ApPai->r[ApPai->n-1];
    ApPai->n--;
    *Diminuiu = (ApPai->n < M);
}

void Ret(int Ch, TipoApontador *Ap, short* Diminuiu) {
    long j, Ind = 1;
    TipoApontador Pag;
    
    if (*Ap == NULL) {
        printf("Erro: reistro não está na árvore\n");
        *Diminuiu = false;
        return;
    }

    Pag = *Ap;
    while (Ind < Pag->n && Ch > Pag->r[Ind-1].chave) Ind++;

    if(Ch==Pag->r[Ind-1].chave) {
        if(Pag->p[Ind-1] ==NULL) { //Tipo pagina folha
            Pag->n--;
            *Diminuiu = (Pag->n < M);
            
            for(j= Ind; j<= Pag->n; j++) {
                Pag->r[j-1] = Pag->r[j]; 
                Pag->p[j] = Pag->p[j+1];
            }

            return;
        }

        //TipoPagina não é folha: trocar com antecessor
        Antecessor (*Ap, Ind, Pag->p[Ind-1], Diminuiu);
        
        if (*Diminuiu) Reconstitui(Pag->p[Ind-1], *Ap, Ind - 1, Diminuiu);

        return;
    }

    if(Ch > Pag->r[Ind-1].chave) Ind ++;

    Ret(Ch, &Pag->p[Ind-1], Diminuiu);

    if(*Diminuiu) Reconstitui(Pag->p[Ind-1], *Ap, Ind-1, Diminuiu);
}

void Retira (int Ch, TipoApontador *Ap) {
    short Diminuiu;
    TipoApontador Aux;
    Ret(Ch, Ap, &Diminuiu);

    if (Diminuiu && (*Ap)->n ==0) { // Arvore diminui na altura
        Aux = *Ap;
        *Ap = Aux->p[0];
        free(Aux);
    }
}

