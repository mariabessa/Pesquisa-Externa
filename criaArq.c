#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "acessoIndexado.h"

#define TAMARQUIVO 1000

char* generateRandomString(int tam) {
    char *dado = (char*) malloc(tam * sizeof(char));
    char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t stringLen = strlen(string);

    for(int i = 0; i < tam - 1; i++)
        dado[i] = string[rand()%stringLen];
    
    return dado;
}

int main()
{
    FILE *arquivo;
    FILE *arquivoBin;
    Item item;
    int chave = 0;
    long int dado1 = 0;
    char *dado2, *dado3;

    // /*
    if((arquivo = fopen("arquivo.txt", "w")) == NULL) {
        puts("Arquivo nao pode ser aberto...");
        return 0;
    }
    // */

    if((arquivoBin = fopen("arquivo.bin", "wb+")) == NULL) {
        puts("Arquivo nao pode ser aberto...");
        return 0;
    }
    
    while (chave < TAMARQUIVO)
    {
        dado1 = rand();
        dado2 = generateRandomString(1000);
        dado3 = generateRandomString(5000);
        
        item.chave = chave++;
        item.dado1 = dado1;
        strcpy(item.dado2, dado2);
        strcpy(item.dado3, dado3);

        fprintf(arquivo, "%d %ld %s %s\n", item.chave, item.dado1, item.dado2, item.dado3);
        fwrite(&item, sizeof(item), 1, arquivoBin);
    }
    
    fclose(arquivo);
    fclose(arquivoBin);

    return 0;
}