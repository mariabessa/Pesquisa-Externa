#include <stdio.h>
#include <string.h>
#include "acessoIndexado.h"

int main(int argc, char **argv)
{
    int opcode;
    opcode = atoi(argv[0]);

    /*  argv[0] = método
        argv[1] = quantidade de registros
        argv[2] = situação (ordenado descententemente, ascendentemente ou desordenado aleatoriamente)
        argv[3] = chave a ser pesquisada
        argv[4](opcional) = [-P] colocado caso deseja que as chaves de pesquisa dos registros do arquivo considerado sejam apresentadas na tela
    */
 
    //Número de argumentos inválido
    if (argc!=4 && argc!=5) 
        printf("Número de argumentos inválido. As entradas são: <método> <quantidade> <situação> <chave> [-P](opcional)");

    // PESQUISA DE ACESSO INDEXADO:
    if (argv[0] == 1) { 
        FILE *arquivo;

        Item item;
        Tabela tabela[MAXTABELA];

        char chave[5], dado1[10], dado2[1000], dado3[5000];
        int cont = 0, pos = 0;

        if((arquivo = fopen("arquivo.txt", "r")) == NULL) {
            printf("Erro na abertura do arquivo.\n");
            return 0;
        }
        
        while (fscanf(arquivo, "%s", chave) != -1)
        {
            strcpy(tabela[pos].chave, chave);
            tabela[pos].posicao = ++pos;
            
            fscanf(arquivo, "%s", dado1);
            fscanf(arquivo, "%s", dado2);
            fscanf(arquivo, "%s", dado3);
            
            fseek(arquivo, (sizeof(Item) + 2) * 3, SEEK_CUR);
        }

        // strcpy(item.chave, "00000");
        // strcpy(item.chave, "00007");
        // strcpy(item.chave, "00995");
        // strcpy(item.chave, "00996");
        strcpy(item.chave, "00999");
        // strcpy(item.chave, "03999");

        if(pesquisa(tabela, pos, &item, arquivo))
            printf("Codigo: %s; Dado 1: %s\n", item.chave, item.dado1);
        else
            printf("Chave não foi indentificada.\n");
        
        fclose(arquivo);
        return 0;
    }

    
}
