#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int chave = 0;
    long int dado1 = 0;
    char *dado2, *dado3;

    if((arquivo = fopen("arquivo.txt", "w")) == NULL) {
        puts("Arquivo nao pode ser aberto...");
        return 0;
    }
    
    while (chave < TAMARQUIVO)
    {
        dado1 = rand();
        dado2 = generateRandomString(1000);
        dado3 = generateRandomString(5000);
        
        fprintf(arquivo, "%05d %010ld %s %s\n", chave++, dado1, dado2, dado3);
    }
    
    
    fclose(arquivo);

    return 0;
}