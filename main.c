#include <stdio.h>
#include <string.h>
#include "ASI.h"
#include "criaArq.h"
#include "arvoreb.h"


int main(int argc, char **argv)
{
    int opcode;
    opcode = atoi(argv[0]);
    arquivo();
    /*  argv[0] = método - acesso sequencial, binario, arvore b, arvore b estrela
        argv[1] = quantidade de registros
        argv[2] = situação (ordenado descententemente, ascendentemente ou desordenado aleatoriamente)
        argv[3] = chave a ser pesquisada
        argv[4](opcional) = [-P] colocado caso deseja que as chaves de pesquisa dos registros do arquivo considerado sejam apresentadas na tela
    */
 
    //Número de argumentos inválido
    if (argc!=4 && argc!=5) 
        printf("Número de argumentos inválido. As entradas são: <método> <quantidade> <situação> <chave> [-P](opcional)");

    // PESQUISA DE ACESSO INDEXADO:
    if (opcode == 1)  { 
        Item itemProcurado;
        printf("Qual a chave do indice deseja buscar?\n");
        scanf("%d", &itemProcurado.chave);
        tabelaDeIndices(&itemProcurado);
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