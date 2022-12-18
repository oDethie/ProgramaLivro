#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

typedef struct no{
    char nome[20];
    char tel[20];
    char senha[20];
    char condicao[20];
    char genero[20];
    char nomeLivro[20];
    char nomeDoador[20];
    int idRemove;
    struct no *proximo;
}No;

typedef struct{
    No *topo;
    int tam;
}Pilha;

Pilha cadastroPilha;

//Lista

typedef struct noLivro{
    char nome[20];
    char condicao[20];
    char genero[20];
    char tel[20];
    int idRemove;
    struct noLivro *proximo;
}NoLivro;

typedef struct noTroca{
    char nomeLivro[20];
    char nomeDoador[20];
    char tel[20];
    struct noTroca *proximo;
}NoTroca;

typedef struct {
    No *inicio;
    int tam;
}Lista;

Lista listaLivro;
Lista listaTroca;

//FILA --------------------------------------
typedef struct noBD{
    char nome[20];
    char condicao[20];
    char genero[20];
    char tel[20];
    int id;
    struct noBD *proximo;
}BancoDeDados;

typedef struct{
    char nome[20];
    char condicao[20];
    char genero[20];
    char tel[20];
    int id;
}guardaTemporario;

typedef struct{
    char nome[30];
    char senha[30];
    char tel[20];
}Cadastro;

typedef struct{
    char nomeLivro[20];
}ordenarNome;

void criaCadastro();
void inspecao(char cadastro[20], char cadastroTel[20], char cadastroSenha[20]);
int cadastroTelefone(No *no, char tel[20]);
void lerArquivo();
void resgataArquivo(char texto[100]);
int areaLogin(No* no, char nome[20], char telLogin[20]);
void criarPilha(Pilha *p);
void empilhar(Pilha *p, char nome[20], char tel[20], char senha[20]);
void imprimir(No *no);
int verificaLogin(No *no, char tel[20], char senha[20], char nome[20], char telLogin[20]);
void inserirFila(BancoDeDados **fila, guardaTemporario temp);
void imprimirFila(BancoDeDados *fila, int idTroca, char telefoneLogin[20], char nome[20]);
void verFila(Lista lista);
void areaCliente(char nome[20], char tel[20]);
void cadastroLivro(char tel[20]);
void salvarArquivo(char nome[20], char cond[20], char genero[20], char tel[20]);
void lerArquivoLivro();
void resgataArquivoLivro(char texto[100]);
void criarLista(Lista *lista);
void inserirInicio(Lista *lista, char nomeLivro[20], char condicao[20], char genero[20], char tel[20]);
void imprimirLivro(Lista lista, char tel[20], char nomeLogin[20]);
void areaTroca(BancoDeDados *sistemaLivros, int idTroca, char tel[20], char nome[20]);
int livrosCadastrado(char tel[20]);
void deletaLivro(char tel[20], int numeroId);
void trocaFeita(char nomeLivro[30], char nomeReceptor[20], char tel[20]);
void minhasTrocas(char tel[20]);
void lerTrocas();
void inserirInicioTroca(Lista *lista, char nomeLivro[20], char nomeReceptor[20], char tel[20]);
void resgataArquivoTroca(char texto[100]);
void livrosTrocado(char tel[20]);

