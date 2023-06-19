#include <stdio.h>
#include <string.h>
#include "ASI.h"
#include "criaArq.h"
#include "arvoreb.h"


int main(int argc, char **argv)
{
    int opcode;
    Item itemProcurado;
    opcode = atoi(argv[1]);
    itemProcurado.chave = atoi(argv[3]);
    arquivo();
    /*  argv[0] = método - acesso sequencial, binario, arvore b, arvore b estrela
        argv[1] = quantidade de registros
        argv[2] = situação (ordenado descententemente, ascendentemente ou desordenado aleatoriamente)
        argv[3] = chave a ser pesquisada
        argv[4](opcional) = [-P] colocado caso deseja que as chaves de pesquisa dos registros do arquivo considerado sejam apresentadas na tela
    */
    FILE *arq;
    if((arq = fopen("arquivo.bin", "rb")) == NULL){
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }
    //Número de argumentos inválido
    if (argc!=5 && argc!=6) 
        printf("Número de argumentos inválido. As entradas são: <método> <quantidade> <situação> <chave> [-P](opcional)\n");
    // PESQUISA DE ACESSO INDEXADO:
    else if (opcode == 1)  { 
        if(acessoSequencialIndexado(&itemProcurado, arq))
            printf("Item: %d \nDado1: %ld\n", itemProcurado.chave, itemProcurado.dado1);
        else printf("O livro não está no arquivo\n");
        return 0;
    }

    else if (opcode == 3)  {
        // TipoApontador* arvoreb = (TipoApontador*) malloc (sizeof(TipoApontador*));
        // TipoRegistro* registro = (TipoRegistro*) malloc (sizeof(TipoRegistro*));
        // FILE* arquivo;

        // arquivo = fopen("arquivo.bin", "rb");

        // //Inicialização
        // InicializaArvore(arvoreb);

        // //Inserção
        // for (int i=0; i<argv[1]; i++){
        //     fscanf("%d %ld %s %s")

        //     Insere(arvoreb)
        // }

        // //tipo de ordenação

        // //pesquisa
        // Pesquisa(registro, arvoreb);

        // if (argc==5){ //Usuario digitou -P
        //     printf("")
        // }

        // free(arvoreb);
        // free(registro);   
    }
}