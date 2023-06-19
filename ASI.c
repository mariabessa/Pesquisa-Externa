#include "ASI.h"


int tabelaDeIndices( Item *itemProcurado){
    FILE *arq;
    int contador = 0;
    float tamanhoTabela;
    if((arq = fopen("arquivo.bin", "rb")) == NULL){
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }
    // verificar o número total de itens do arquivo
    fseek(arq, 0, SEEK_END);
    int totalItens = ftell(arq)/ sizeof(Item);
    tamanhoTabela = totalItens / ITENSPORPAGINA;
    if (totalItens % ITENSPORPAGINA != 0){
        tamanhoTabela++;
    }
    int *tabela = malloc(sizeof(int) * tamanhoTabela);
    Item x[ITENSPORPAGINA];
    rewind(arq);
    // cria o vetor de indices
    while(fread(x, sizeof(Item), ITENSPORPAGINA, arq) > 0){
        tabela[contador] = x[0].chave;
        contador++;
    }
    if (pesquisa(tabela, totalItens, tamanhoTabela, itemProcurado, arq)) 
        printf("Item: %d \nDado1: R$%ld\n", itemProcurado->chave, itemProcurado->dado1);
    else printf("O livro não está no arquivo\n");
    fclose(arq);
    return 0;
}

int pesquisa(int tabela[], int totalItens, int tamanhoTabela, Item *itemProcurado, FILE * arq){
    int desloc, quantidade, i = 0;
    Item pagina[ITENSPORPAGINA];
    // verifica a pagina que o item procurado pode estar
    while(i <= tamanhoTabela && itemProcurado->chave >= tabela[i]) i++;
    if(i==0) return  0;
    // verifica se esta na ultima pag e ve a qntd de itens nela 
    if(i < tamanhoTabela || totalItens % ITENSPORPAGINA == 0) quantidade = ITENSPORPAGINA;
    else{
        quantidade = totalItens % ITENSPORPAGINA;
    }
    // desloca o ponteiro para a página
    desloc = (i-1) * ITENSPORPAGINA * sizeof(Item);
    fseek(arq, desloc, 0);
    fread(&pagina, sizeof(Item), quantidade, arq);
    // procura o item na página
        for(i = 0; i < quantidade; i++){
        if (pagina[i].chave == itemProcurado->chave){
            *itemProcurado = pagina[i];
            return 1;
        }
    }
    return 0;
}