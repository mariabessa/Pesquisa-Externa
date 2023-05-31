# ifndef ASI_h
# define ASI_h
#define ITENSPORPAGINA 2

typedef struct{
    int chave;
    long dado1;
    char dado2[1000];
    char dado3[5000];
}item;

void ASI(FILE * arq, item itemProcurado);
int pesquisa(int*, int, int, item *, FILE *);

# endif