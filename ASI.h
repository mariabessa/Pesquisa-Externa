# ifndef ASI_h
# define ASI_h
#define ITENSPORPAGINA 2

typedef struct{
    int chave;
    long dado1;
    char dado2[1000];
    char dado3[5000];
}item;

int tabelaDeIndices(FILE *);
int pesquisa(int*, int, int, item *, FILE *);

# endif