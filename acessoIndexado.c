#include <stdio.h>
#include <string.h>
#include "acessoIndexado.h"

int pesquisa(Tabela tabela[], int tam, Item* item, FILE *arquivo) {
    
    Item pagina[ITENSPAGINA];

    int i = 0, quantItens = ITENSPAGINA;
    long desloc;

    while (i < tam && strcmp(tabela[i].chave, item->chave) <= 0) i++;

    if(i == 0) return 0;

    if(i == tam) {
        fseek (arquivo, 0, SEEK_END);
        quantItens = (ftell(arquivo)/(sizeof(Item) + 2))%ITENSPAGINA;

        if(quantItens == 0) quantItens = 4;
    }
    
    desloc = (tabela[i].posicao-1)*ITENSPAGINA*(sizeof(Item) + 2);
    fseek (arquivo, desloc, SEEK_SET);

    for(int i = 0; i <= quantItens; i++) {
        char chave[5], dado1[10], dado2[1000], dado3[5000];
        
        fscanf(arquivo, "%s", chave);
        strcpy(pagina[i].chave, chave);

        fscanf(arquivo, "%s", dado1);
        // strcpy(pagina[i].dado1, dado1);
        
        fscanf(arquivo, "%s", dado2);
        // strcpy(pagina[i].dado2, dado2);
        
        fscanf(arquivo, "%s", dado3);
        // strcpy(pagina[i].dado3, dado3);
    }

    for (i = 0; i < quantItens; i++)
        if(strcmp(pagina[i].chave, item->chave) == 0) {
            *item = pagina[i];
            return 1;
        }

    return 0;
}