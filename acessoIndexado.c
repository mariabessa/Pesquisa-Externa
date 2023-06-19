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

    for(int i = 0; i < quantItens; i++) {
        fread(&pagina[i], sizeof(Item), 1, arquivoBin);
        printf("%d\n", pagina[i].chave);
    }

    for (i = 0; i < quantItens; i++)
        if(pagina[i].chave == item->chave) {
            *item = pagina[i];
            return 1;
        }

    return 0;
}