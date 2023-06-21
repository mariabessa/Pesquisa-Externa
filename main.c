#include <stdio.h>
#include <string.h>
#include "ASI.h"
#include "criaArq.h"
#include "arvoreb.h"


int main(int argc, char **argv)
{
    int opcode, quantReg;
    Item itemProcurado;
    opcode = atoi(argv[1]);
    quantReg = atoi(argv[2]);
    itemProcurado.chave = atoi(argv[4]);
    arquivo();
    /*  argv[1] = método - acesso sequencial, binario, arvore b, arvore b estrela
        argv[2] = quantidade de registros
        argv[3] = situação (ordenado descententemente, ascendentemente ou desordenado aleatoriamente)
        argv[4] = chave a ser pesquisada
        argv[5](opcional) = [-P] colocado caso deseja que as chaves de pesquisa dos registros do arquivo considerado sejam apresentadas na tela
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
        TipoApontador* Ap = (TipoApontador*) malloc (sizeof(TipoApontador*));
        TipoRegistro* Reg = (TipoRegistro*) malloc (sizeof(TipoRegistro*));
        FILE* arquivo;

        arquivo = fopen("arquivo.bin", "rb");

        printf("1\n\n");

        //Inicialização
        Inicializa(*Ap);

        printf("2\n\n");
        
        //Inserção
        for (int i = 0; i < quantReg; i++){
            fread(Reg, sizeof(Reg), 1, arquivo);
            printf("1");
            Insere(*Reg, Ap);
        }

        printf("3\n\n");

        //Tipo de ordenação

        //Pesquisa
        Pesquisa(Reg, *Ap);
        
        printf("4\n\n");

        if (argc==5){ //Usuario digitou -P
             printf(" ");
        }

        free(Ap);
    }
}