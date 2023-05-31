#include "ASI.h"
#include <stdio.h>
//joao esteve aqui

void ASI(FILE * arq, item itemProcurado){
    int contador = 0;
    float tamanhoTabela;
    // verificar o número total de itens do arquivo
    fseek(arq, 0, SEEK_END);
    int totalItens = ftell(arq)/ sizeof(item);
    tamanhoTabela = totalItens / ITENSPORPAGINA;
    if (totalItens % ITENSPORPAGINA != 0){
        tamanhoTabela++;
    }
    int tabela[(int)tamanhoTabela];
    item x[ITENSPORPAGINA];
    rewind(arq);
    // cria o vetor de indices
    while(fread(x, sizeof(item), ITENSPORPAGINA, arq) > 0){
        tabela[contador] = x[0].chave;
        contador++;
    }
    pesquisa(tabela, totalItens, tamanhoTabela, &itemProcurado, arq); 
    return;
}

int pesquisa(int tabela[], int totalItens, int tamanhoTabela, item *itemProcurado, FILE * arq){
    int desloc, quantidade, i = 0;
    item pagina[ITENSPORPAGINA];
    // verifica a pagina que o item procurado pode estar
    while(i <= tamanhoTabela && itemProcurado->chave >= tabela[i]) i++;
    if(i==0) return  0;
    // verifica se esta na ultima pag e ve a qntd de itens nela 
    if(i < tamanhoTabela || totalItens % ITENSPORPAGINA == 0) quantidade = ITENSPORPAGINA;
    else{
        quantidade = totalItens % ITENSPORPAGINA;
    }
    // desloca o ponteiro para a página
    desloc = (i-1) * ITENSPORPAGINA * sizeof(item);
    fseek(arq, desloc, 0);
    fread(&pagina, sizeof(item), quantidade, arq);
    // procura o item na página
    for(i = 0; i < quantidade; i++){
        if (pagina[i].chave == itemProcurado->chave){
            *itemProcurado = pagina[i];
            return 1;
        }
    }
    return 0;
}