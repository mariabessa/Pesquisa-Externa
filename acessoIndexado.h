#ifndef BF708B95_4323_4FD5_BC37_A84F959F0479
#define BF708B95_4323_4FD5_BC37_A84F959F0479
#ifndef acessoIndexado_h
#define acessoIndexado_h

#define ITENSPAGINA 4
#define MAXTABELA 250

typedef struct {
    int posicao;
    char chave[5];
} Tabela;

typedef struct {
    char chave[5];
    char dado1[10];
    char dado2[1000];
    char dado3[5000];
} Item;

int pesquisa(Tabela*, int, Item*, FILE*);

# endif


#endif /* BF708B95_4323_4FD5_BC37_A84F959F0479 */
