#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "arvoreBinaria.h"



bool binaryTree(FILE *arquivoRegistros, int archiveSize, Registros *itemProcurado, bool optionalFunction, int *compInserction, int *transferInserction, double *timeInserction, int *compSearch, int *transferSearch, double *timeSearch){
    if(arquivoRegistros == NULL){ //verificando se o arquivo pode ser aberto.
        return false;
    }
    FILE *arquivoArvore = fopen("arquivoArvorebinaria.bin", "wb+");

    if(arquivoArvore == NULL){
        return false;
    }


    Registros currentlyItem;
    RegArvore dadoArvore;

    //inserção da árvore no arquivo .bin.


    clock_t startI = clock();
    for(int i = 0; i < archiveSize; i++){
        if(fread(&currentlyItem, sizeof(Registros), 1, arquivoRegistros) > 0){
            fseek(arquivoArvore, 0, SEEK_SET);
            //inserindo...
            if(insereBinaria(arquivoArvore , currentlyItem, *transferInserction, dadoArvore, optionalFunction, compInserction))
                *transferInserction = *transferInserction + 1;
        }
    }
    clock_t endI = clock();
    *timeInserction = (endI - startI);

    fseek(arquivoArvore, 0, SEEK_SET);

    startI = clock();

    if (searchTree(arquivoArvore, itemProcurado->chave, itemProcurado, compSearch)){
        endI = clock();
        *timeSearch = (endI - startI);
        *transferSearch = 0;
        fclose(arquivoArvore);
        return true;
    }
    else {
        fclose(arquivoArvore);
        return false;
    }
    return false;
}

bool insereBinaria(FILE *arquivoArvore, Registros novoItem, int numeroItens, RegArvore dadoArvore, bool optionalFunction, int *comparacoes){
    
    if(numeroItens == 0){
        *comparacoes = *comparacoes + 1;
        dadoArvore.reg = novoItem;
        dadoArvore.direita = -1;
        dadoArvore.esquerda = -1;
        fwrite(&dadoArvore, sizeof(RegArvore), 1, arquivoArvore);
        if (optionalFunction == true)
            printf("Chave %d = %d\n\n", numeroItens, dadoArvore.reg.chave);
        return true;
    }
    else{
        while(fread(&dadoArvore, sizeof(RegArvore), 1, arquivoArvore) > 0){
            *comparacoes = *comparacoes + 1;
            if(novoItem.chave > dadoArvore.reg.chave){
                *comparacoes = *comparacoes + 1;
                if(dadoArvore.direita == -1){
                    *comparacoes = *comparacoes + 1;
                    //dado atual deve apontar para o final do arquivo, ou seja, o último item adicionado.
                    dadoArvore.direita = numeroItens;
                    fseek(arquivoArvore, -sizeof(RegArvore), SEEK_CUR);
                    fwrite(&dadoArvore, sizeof(RegArvore), 1, arquivoArvore);
                    //adiciondo novo item ao final do arquivo.
                    dadoArvore.reg = novoItem;
                    dadoArvore.direita = -1;
                    dadoArvore.esquerda = -1;
                    fseek(arquivoArvore, 0, SEEK_END);
                    fwrite(&dadoArvore, sizeof(RegArvore), 1, arquivoArvore);
                    if (optionalFunction == true)
                          printf("Chave %d = %d\n\n", numeroItens, dadoArvore.reg.chave);
                    return true;
                }
                else{
                    *comparacoes = *comparacoes + 1;
                    fseek(arquivoArvore, dadoArvore.direita*sizeof(RegArvore), SEEK_SET);
                }
            }
            else if(novoItem.chave < dadoArvore.reg.chave){
                *comparacoes = *comparacoes + 1;
                //vai pra esquerda
                if(dadoArvore.esquerda == -1){
                    *comparacoes = *comparacoes + 1;

                    //atualiza o pai para conter o apontador correto para o filho
                    dadoArvore.esquerda = numeroItens;
                    fseek(arquivoArvore, -sizeof(RegArvore), SEEK_CUR);
                    fwrite(&dadoArvore, sizeof(RegArvore), 1, arquivoArvore);

                    //coloca o item na arvore
                    dadoArvore.reg = novoItem;
                    dadoArvore.direita = -1;
                    dadoArvore.esquerda = -1;
                    fseek(arquivoArvore, 0, SEEK_END); //vai para o fim do arquivo onde deve ser inserido o item
                    fwrite(&dadoArvore, sizeof(RegArvore), 1, arquivoArvore);
                    if (optionalFunction == true)
                        printf("Chave %d = %d\n\n", numeroItens, dadoArvore.reg.chave);
                    return true;
                }
                else{
                    //caso nao possa ser inserido vai para o filho da esquerda
                    *comparacoes = *comparacoes + 1;
                    fseek(arquivoArvore, dadoArvore.esquerda*sizeof(RegArvore), SEEK_SET);
                }
            }
        }
    }
    printf("retornou falso\n\n");
    return false;
}

bool searchTree(FILE *arquivoArvore, int chave, Registros *reg, int *comparacoes){

    RegArvore no;

    while(fread(&no, sizeof(RegArvore), 1, arquivoArvore) == 1){ //lê enquanto ainda tiver elementos
        if(chave == no.reg.chave){ //elemento encontrado
            *reg = no.reg;
            *comparacoes = *comparacoes + 1;
            return true;
        }
        else if(chave < no.reg.chave){ //caminha para esquerda
            fseek(arquivoArvore, no.esquerda*sizeof(RegArvore), SEEK_SET);
            *comparacoes = *comparacoes + 1;
        }
        else if(chave > no.reg.chave){ //caminha para direita
            fseek(arquivoArvore, no.direita*sizeof(RegArvore), SEEK_SET);
            *comparacoes = *comparacoes + 1;
        }
    }
    return false;
}
