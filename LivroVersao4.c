#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

typedef struct no{
    char nome[20];
    char tel[20];
    char senha[20];
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
    struct no *proximo;
}NoLivro;

typedef struct noTroca{
    char nomeLivro[20];
    char nomeDoador[20];
    char tel[20];
    struct no *proximo;
}NoTroca;

typedef struct{
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
void inserirFila(No **fila, guardaTemporario temp);
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


int main()
{
    setlocale(LC_ALL,""); // Para conseguir escrever corretamente

    int op; // Para você conseguir mudar a opção
    char telLogin[20]; // Para armazenar o telefone de contato
    char senhaLogin[20]; // Para criar uma senha para o login
    int opLogin; // Para o menu de login
    char nome[20]={' '};
    char telefone[20]={' '};

    lerArquivo();


    do
    {
        printf("\033[H\033[J"); // Para limpar a saída padrão
        printf("\x1B[31mBem Vindos a troca de livros online\n"); // Para alterar a cor para vermelho
        printf("\x1B[36m\nNesta plataforma você poderá procurar os livros que\ntenha interesse, e verificar se há a possibilidade de\ntroca com aquele que você tenha cadastrado\n"); // Para alterar a cor para azul claro
        printf("\x1B[00m\n1 - Criar um cadastro\n"); // Para voltar a cor padrão Opção para criar um cadastro
        printf("2 - Efetuar Login\n"); // Opção para fazer o login
        printf("3 - Sair\n"); // Opção para sair da tela padrão


        //Apagar
        printf("\n\n");
        imprimir(cadastroPilha.topo);
        //Apagar

        printf("\nDigite sua opção: ");
        scanf("%d", &op); // Para que você coloque qual opção deseja

        switch(op){
            case 1: // Caso escolha fazer o cadastro
                criaCadastro(); // Para você ser direcionado a fazer o cadastro
            break;

            case 2: // Caso escolha fazer o login

                printf("\033[H\033[J"); // Para limpar a saída padrão
                printf("\x1B[36mÁrea de login\n\n"); // Para mudar a cor para azul claro

                printf("\x1B[00m1 - Acessar área de login\n2 - Voltar\n"); // Para voltar a cor padrão
                printf("\nDigite sua opção: ");
                scanf("%d", &opLogin); // Para verificar a opção que deseja

                if(opLogin == 1){
                    int flagLogin = 1;
                    flagLogin=areaLogin(cadastroPilha.topo, nome, telefone);
                    if(flagLogin == -1){
                        main();
                    }
                    while(flagLogin == 1){
                        printf("\033[H\033[J");
                        printf("\x1B[31mDigito(0) incorreto(os)\n");
                        printf("\x1B[31mDigite novamente...\n");
                        flagLogin = areaLogin(cadastroPilha.topo, nome, telefone);
                    }
                    areaCliente(nome, telefone);
                } else if(opLogin != 1){
                    op = 5;
                }
            break;

            case 3: // Caso deseja sair
                printf("\033[H\033[J"); // Limpa a saida padrão
                printf("\x1B[33m\n\tObrigado por usar nossa plataforma. Até mais!\n\x1B[00m"); // Para mudar a cor para amarelo
            break;
        }
    }while(op != 1 && op != 2 && op != 3); // Sai do do while caso o numero não seja 1, 2 ou 3
}

void criaCadastro(){ // Para ser possível criar o cadastro

                int conf=2;
                int flag=0; // Para confirmar se está correto
                FILE *file; // Cria um arquivo
                file = fopen("cadastros.txt", "a+"); // Abre o arquivo que você chamou de cadastro e permite ler e escrever sem perder os dados anteriores
                if(file == NULL) printf("\nErro ao executar o arquivo\n"); // Para evitar problemas ao criar o arquivo

                Cadastro cadastro;

                printf("\033[H\033[J"); // Limpa a tela de saida

                while(conf == 2)
                {
                    printf("\033[H\033[J");
                    printf("\x1B[36mPágina de cadastro\n"); // Muda o texto para amarelo
                    printf("\x1B[00m\n\tDigite seu nome: "); // Retorna o texto para a cor original
                    getchar(); // Para ler o enter e esperar o usuário digitar a informação pedida
                    scanf("%29[^\n]", cadastro.nome); // Ele leu o que voce escreveu na tela e armazena na primeira variavel
                    do{
                        printf("\x1B[00m\tDigite seu telefone (com DDD): ");
                        getchar();
                        scanf("%19[^\n]", cadastro.tel); // Ele leu o que voce escreveu na tela e armazena na segunda variavel

                        flag = cadastroTelefone(cadastroPilha.topo, cadastro.tel);
                        if(flag == 1){
                            printf("\n\t\x1B[31mEste telefone já foi cadastrado!\n\tDigite outro número...\n\n");
                        }
                    }while(flag == 1);

                    printf("\tDigite sua senha: ");
                    getchar();
                    scanf("%29[^\n]", cadastro.senha); // Ele leu o que voce escreveu na tela e armazena na terceira variavel

                    printf("\x1B[36m\nInformações cadastradas: \n"); // Para mudar a cor para azul claro
                    printf("\x1B[00m\n\t- Nome digitado foi: %s\n", cadastro.nome); // Para voltar a cor padrão Mostra as informações digitadas no ato do cadastro
                    printf("\t- Telefone digitado foi: %s\n", cadastro.tel);
                    printf("\t- Senha digitada foi: %s\n", cadastro.senha);

                    printf("\x1B[36m\nOs dados armazenados estão corretos?\n"); // Para mudar a cor para azul claro
                    printf("\x1B[00m\n\t1 - Sim\n\t2 - Não\n\n");
                    printf("Digite sua opção: ");
                    scanf("%d", &conf); // Para colocar se confirma ou não

                    if(conf == 2) printf("\033[H\033[J");
                    else if(conf == 1) { // Para salvar o cadastro no arquivo
                        inspecao(cadastro.nome, cadastro.tel, cadastro.senha);
                        break;
                    }
                }

                printf("\x1B[36m\nCadastro foi concluído com sucesso!\n"); // Para mudar a cor para azul claro
                fprintf(file, "%s-%s-%s,", cadastro.nome, cadastro.tel, cadastro.senha); // Para escrever no arquivo as informações dadas no cadastro

                empilhar(&cadastroPilha, cadastro.nome, cadastro.tel, cadastro.senha);

                fclose(file); // Fecha o arquivo criado

                main();
}

void inspecao(char cadastro[20], char cadastroTel[20], char cadastroSenha[20]){
    int lengthNome = strlen(cadastro);
    char check[lengthNome];
    int i=0;
    strcpy(check, cadastro);

    while(i < lengthNome){
        if(check[i] == ' '){
            check[i] = '_';
        }
        i++;
    }

    int j=0, x;
    int lengthTel = strlen(cadastroTel);
    char checkTel[lengthTel];
    strcpy(checkTel, cadastroTel);

    while(j < lengthTel){
        if(checkTel[j] == ' '){
            for(x=j; x<lengthTel; x++){
                checkTel[x] = checkTel[x+1];
            }
        }
        j++;
    }

    int p=0, k;
    int lengthSenha = strlen(cadastroSenha);
    char checkSenha[lengthSenha];
    strcpy(checkSenha, cadastroSenha);

    while(p < lengthSenha){
        if(checkSenha[p] == ' '){
            for(k=p; k<lengthSenha; k++){
                checkSenha[k] = checkSenha[k+1];
            }
        }
        p++;
    }

    strcpy(cadastro, check);
    strcpy(cadastroTel, checkTel);
    strcpy(cadastroSenha, checkSenha);
}

int cadastroTelefone(No *no, char tel[20]){
    if(no){
        if(strcmp(no->tel, tel)==0){
            return 1;
        }
    } else if(no == NULL){
        return 0;
    }
    cadastroTelefone(no->proximo, tel);
}

void lerArquivo(){
    FILE *file = fopen("cadastros.txt", "r");
    char letra;
    char texto[100]={};
    int i=0;

    if(file){
        criarPilha(&cadastroPilha);
        while((letra=fgetc(file))!= EOF){
            if(letra != ','){
                texto[i] = letra;
                i++;
            } else if(letra == ','){
                resgataArquivo(texto);
                i=0;
            }
        }
        fclose(file);
    }
    else{
        printf("\nErro ao executar o arquivo\n");
    }
}

void resgataArquivo(char texto[100]){
    int i=0;
    int aux=0, j=0;
    char nome[20]={};
    char tel[20]={};
    char senha[20]={};

    while(i<strlen(texto)){
        if(texto[i] == '-'){
            texto[i] = ' ';
            aux++;
            j=0;
        }else if(aux==0){
            if(texto[i] != ' '){
                nome[j] = texto[i];
                texto[i] = ' ';
                j++;
            }
        }else if(aux==1){
            if(texto[i] != ' '){
                tel[j] = texto[i];
                texto[i] = ' ';
                j++;
            }
        }else if(aux==2){
            if(texto[i] != ' '){
                senha[j] = texto[i];
                texto[i] = ' ';
                j++;
            }
        }
        i++;
    }

    empilhar(&cadastroPilha, nome, tel, senha);
}

int areaLogin(No* no, char nome[20], char telLogin[20]){
    char tel[20], senha[20], flag;

    if(no){
        printf("\x1B[36m\nÁrea de login\n\n");

        printf("\x1B[00mPara efetuar o seu login, você deve inserir seu telefone e senha\n\n");

        printf("\tDigite seu telefone: ");
        getchar();
        scanf("%19[^\n]", tel);

        printf("\tDigite sua senha: ");
        getchar();
        scanf("%19[^\n]", senha);

        flag = verificaLogin(cadastroPilha.topo, tel, senha, nome, telLogin);

        if(flag != 0){
            return 1;
        }
        else return 0;
    } else if(no == NULL){
        return -1;
    }
}

void criarPilha(Pilha *p){
    p->topo = NULL;
    p->tam = 0;
}

void empilhar(Pilha *p, char nome[20], char tel[20], char senha[20]){
    No *novo = malloc(sizeof(No));
    if(novo){
        strcpy(novo->nome, nome);
        strcpy(novo->tel, tel);
        strcpy(novo->senha, senha);
        novo->proximo = p->topo;
        p->topo = novo;
        p->tam++;
    } else {
        printf("\n\tErro ao alocar memória!!");
    }
}

void imprimir(No *no){

    if(no){
        printf("%s\n", no->nome);
        printf("%s\n", no->tel);
        printf("%s\n", no->senha);
        imprimir(no->proximo);
    }
}

int verificaLogin(No *no, char tel[20], char senha[20], char nome[20], char telLogin[20]){

    if(no){
        if(((strcmp(no->tel, tel)==0) && (strcmp(no->senha, senha)==0)))
        {
            strcpy(nome, no->nome);
            strcpy(telLogin, no->tel);
            return 0;
        }
    }
    else if(no == NULL){
        return 1;
    }
    verificaLogin(no->proximo, tel, senha, nome,telLogin);
}

//-------------------------------------------------------AMBIENTE LOGADO PARA O USUARIO-----------------------------------------------------------------------

void inserirFila(No **fila, guardaTemporario temp){
    BancoDeDados *aux, *novo = malloc(sizeof(BancoDeDados));
    if(novo){
        strcpy(novo->nome,temp.nome);
        strcpy(novo->condicao, temp.condicao);
        strcpy(novo->genero, temp.genero);
        strcpy(novo->tel, temp.tel);
        novo->id = temp.id;

        novo->proximo = NULL;

        if(*fila == NULL)
            *fila = novo;
        else{
            aux = *fila;
            while(aux->proximo)
                aux = aux->proximo;
            aux->proximo = novo;
        }
    }
    else
        printf("\nErro ao alocar memoria.\n");
}

void imprimirFila(BancoDeDados *fila, int idTroca, char telefoneLogin[20], char nome[20]){
    int decisao, flag=0;
    char nomeLivro[30]={};
    int idRemover;
    printf("\n\t------- TROCA ID: %d --------\n", idTroca);
    while(fila){
        if(idTroca == fila->id && strcmp(fila->tel, telefoneLogin)==0){
            printf("\nDeculpe, mas esse livro já é seu");
            getchar();
            break;
        }else if(idTroca == fila->id && strcmp(fila->tel, telefoneLogin)!=0){
                printf("\n------------------------");
                printf("\n- Nome: %s\n", fila->nome);
                printf("- Condição: %s\n", fila->condicao);
                printf("- Gênero: %s", fila->genero);
                printf("\n- %ID: %d\n", fila->id);
                printf("------------------------\n");
                flag++;
                idRemover = fila->id;
                strcpy(nomeLivro, fila->nome);
                break;
            }
        fila = fila->proximo;
    }
    if(flag>0){
        printf("\nDeseja realizar o pedido: ");
        printf("\n\n1 - Sim\n2 - Não");
        printf("\n\nDigite sua opção: ");
        scanf("%d", &decisao);

        if(decisao == 1){
            trocaFeita(nomeLivro, nome, telefoneLogin);
        } else {
            printf("\n\n\tOK, voltando...");
            getchar();
        }
    }
}

void verFila(Lista lista){
    lerArquivo();
    int i=0;
    BancoDeDados *sistemaLivros = NULL;
    guardaTemporario temp;
    NoLivro *noLista = lista.inicio;
    if(lista.tam > 0){
        while(noLista){

            strcpy(temp.nome, noLista->nome);
            strcpy(temp.condicao, noLista->condicao);
            strcpy(temp.genero, noLista->genero);
            strcpy(temp.tel, noLista->tel);
            temp.id = ++i;

            inserirFila(&sistemaLivros, temp);

            noLista = noLista->proximo;
        }
    } else {
        printf("\nAinda não temos nenhum livro cadastrado em nosso sistema\n");
        getchar();
    }
}

//-------------------------------------------

void areaCliente(char nome[20], char tel[20]){
    int opCliente;
    int opInfo;
    int opLiCad=0;
    int numId=0;

    lerArquivoLivro();

    do{
        printf("\033[H\033[J");
        printf("Seja bem vindo(a) %s!", nome);

        printf("\n\n\tO que deseja fazer?\n\n");
        printf("1 - Cadastrar um livro\n");
        printf("2 - Acessar seus dados\n");
        printf("3 - Ver livros disponíveis para troca\n");
        printf("4 - LogOut");

        printf("\n\nDigite sua opção: ");
        scanf("%d", &opCliente);

        switch(opCliente){
            case 1:
                cadastroLivro(tel);
                opCliente = 0;
            break;

            case 2:
                printf("\033[H\033[J");
                printf("Informações pessoais");

                printf("\n\n1 - Seus livros cadastrados");
                printf("\n2 - Seus pedidos");

                printf("\n\nDigite sua opção: ");
                scanf("%d", &opInfo);

                if(opInfo == 1)
                {
                    lerArquivoLivro();
                    numId = livrosCadastrado(tel);
                    if(numId == 0) {
                        getchar();
                        opCliente = 0;
                    }
                    else{
                        printf("\n\nOpções:");
                        printf("\n\n1 - Excluir um cadastro");
                        printf("\n2 - Voltar");
                        printf("\n\nDigite sua opção: ");
                        scanf("%d", &opLiCad);

                        if(opLiCad == 1) {
                            deletaLivro(tel, numId);
                            opCliente=0;
                        }
                        else opCliente=0;
                    }

                } else if(opInfo == 2)
                    {
                        minhasTrocas(tel);
                        getchar();
                        opCliente=0;

                    }else {
                        opCliente = 0;
                    }
            break;

            case 3:
                lerArquivoLivro();
                imprimirLivro(listaLivro, tel, nome);
                opCliente = 0;
            break;

            case 4:
                main();
            break;
        }
    }while(opCliente != 1 && opCliente != 2 && opCliente != 3 && opCliente != 4);
}

void cadastroLivro(char tel[20]){

    char infoLivro[3][20];

    printf("\033[H\033[J");
    printf("\x1B[36mÁrea de cadastro para livros");

    printf("\n\n\x1B[00mDigite o nome do seu livro: ");
    getchar();
    scanf("%19[^\n]", infoLivro[0]);
    printf("Digite a condição do seu livro (Ótimo, bom ou ruim): ");
    getchar();
    scanf("%19[^\n]", infoLivro[1]);
    printf("Digite o gênero do seu livro: ");
    getchar();
    scanf("%19[^\n]", infoLivro[2]);

    inspecao(infoLivro[0], infoLivro[1], infoLivro[2]);

    salvarArquivo(infoLivro[0], infoLivro[1], infoLivro[2], tel);

    inserirInicio(&listaLivro, infoLivro[0], infoLivro[1], infoLivro[2], tel);
}

void salvarArquivo(char nome[20], char cond[20], char genero[20], char tel[20]){

    FILE *fileLivro;

    fileLivro = fopen("livros.txt", "a+");
    if(fileLivro == NULL) printf("\nErro ao executar arquivo\n");

    fprintf(fileLivro, "%s-%s-%s-%s,", nome, cond, genero, tel);

    fclose(fileLivro);
}

void lerArquivoLivro(){
    FILE *fileLivro = fopen("livros.txt", "r");
    char texto[100]={' '};
    char letra;
    int i=0;

    if(fileLivro){
        criarLista(&listaLivro);
        while((letra=fgetc(fileLivro))!= EOF){
            if(letra != ','){
                texto[i] = letra;
                i++;
            } else if(letra == ','){
                resgataArquivoLivro(texto);
                i=0;
            }
        }
        fclose(fileLivro);
    }
    else{
        printf("\nErro ao executar o arquivo\n");
    }
}

void resgataArquivoLivro(char texto[100]){
    int i=0;
    int aux=0, j=0;
    char nome[20]={};
    char condicao[20]={};
    char genero[20]={};
    char tel[20]={};

    while(i<strlen(texto)){
        if(texto[i] == '-'){
            texto[i] = ' ';
            aux++;
            j=0;
        }else if(aux==0){
            if(texto[i] != ' '){
                nome[j] = texto[i];
                texto[i] = ' ';
                j++;
            }
        }else if(aux==1){
            if(texto[i] != ' '){
                condicao[j] = texto[i];
                texto[i] = ' ';
                j++;
            }
        }else if(aux==2){
            if(texto[i] != ' '){
                genero[j] = texto[i];
                texto[i] = ' ';
                j++;
            }
        }else if(aux==3){
            if(texto[i] != ' '){
                tel[j] = texto[i];
                texto[i] = ' ';
                j++;
            }
        }
        i++;
    }
    inserirInicio(&listaLivro, nome, condicao, genero, tel);
}

void criarLista(Lista *lista){
    lista->inicio = NULL;
    lista->tam = 0;
}

void inserirInicio(Lista *lista, char nomeLivro[20], char condicao[20], char genero[20], char tel[20]){
    NoLivro *novo = malloc(sizeof(NoLivro));
    if(novo){
        strcpy(novo->nome, nomeLivro);
        strcpy(novo->condicao, condicao);
        strcpy(novo->genero, genero);
        strcpy(novo->tel, tel);
        novo->proximo = lista->inicio;
        lista->inicio = novo;
        lista->tam++;
    }
    else
        printf("Erro ao alocar memoria!\n");
}

void imprimirLivro(Lista lista, char tel[20], char nomeLogin[20]){
    lerArquivo();
    int i=0, idTroca, id=1;
    BancoDeDados *sistemaLivros = NULL;
    guardaTemporario temp;
    NoLivro *noLista = lista.inicio;
    printf("\033[H\033[J");
    printf("Lista - Livros Disponíveis\n");
    printf("-----------------------------------");
    if(lista.tam > 0){
        while(noLista){

            printf("\nNome: %s", noLista->nome);
            printf("\nCondição: %s", noLista->condicao);
            printf("\nGênero: %s", noLista->genero);
            printf("\nID: %d", id++);
            printf("\n-----------------------------------");

            strcpy(temp.nome, noLista->nome);
            strcpy(temp.condicao, noLista->condicao);
            strcpy(temp.genero, noLista->genero);
            strcpy(temp.tel, noLista->tel);
            temp.id = ++i;

            inserirFila(&sistemaLivros, temp);

            noLista = noLista->proximo;
        }
        printf("\n\n");
        printf("Qual livro você deseja realizar uma troca?\nDigite o ID do livro, ou '0' para voltar: ");
        scanf("%d", &idTroca);

        if(idTroca > 0 && idTroca < id){
            areaTroca(sistemaLivros, idTroca, tel, nomeLogin);
        } else if(idTroca < 0 || idTroca > (id-1)){
            imprimirLivro(lista, tel, nomeLogin);
        } else {
            printf("\n\tVoltando...");
            getchar();
        }
    } else {
        printf("\n\n\tAinda não temos nenhum livro cadastrado em nosso sistema\n");
        getchar();
    }
    getchar();
}

void areaTroca(BancoDeDados *sistemaLivros, int idTroca, char tel[20], char nome[20]){
    int verificaID = 0, i=0;
    printf("\033[H\033[J");
    printf("Área de troca\n");

    imprimirFila(sistemaLivros, idTroca, tel, nome);

}

int livrosCadastrado(char tel[20]){
    int i=1;
    int flag=0;
    NoLivro *noLista = listaLivro.inicio;
    printf("\033[H\033[J");
    printf("Livro(s) cadastrados(s) por você\n");
    printf("-----------------------------------");
    if(listaLivro.tam > 0){
        while(noLista){
            if(strcmp(noLista->tel, tel)==0)
            {
                noLista->idRemove=i++;
                printf("\nNome: %s", noLista->nome);
                printf("\nCondição: %s", noLista->condicao);
                printf("\nGênero: %s", noLista->genero);
                printf("\nID: %d", noLista->idRemove);
                printf("\n-----------------------------------");
                flag++;
            }
            noLista = noLista->proximo;
        }
    }

    getchar();

    if(flag>0) return --i;

    else {
        printf("\n\nAinda não temos nenhum livro seu cadastrado em nosso sistema\n");
        return 0;
    }
}

void deletaLivro(char tel[20], int numeroId){
    FILE *fileLivro;
    if(fileLivro == NULL) printf("\nErro ao executar o arquivo\n");
    fileLivro = fopen("livros.txt", "w");
    fclose(fileLivro);

    int idRemover;
    while(idRemover < 1 || idRemover > numeroId){
        printf("\nDigite o ID do livro que quer excluir: ");
        scanf("%d", &idRemover);
    }

    NoLivro *noLista = listaLivro.inicio;

    while(noLista){
            if(noLista->idRemove == idRemover)
            {
                printf("\nNome: %s", noLista->nome);
                printf("\nCondição: %s", noLista->condicao);
                printf("\nGênero: %s", noLista->genero);
                printf("\nID: %d", noLista->idRemove);
                printf("\n-----------------------------------");
                getchar();
            }
            else {
                fileLivro = fopen("livros.txt", "a+");
                if(fileLivro == NULL) printf("\nErro ao executar o arquivo\n");

                fprintf(fileLivro, "%s-%s-%s-%s,", noLista->nome, noLista->condicao, noLista->genero, noLista->tel);

                fclose(fileLivro);
            }
            noLista = noLista->proximo;
    }
}

void trocaFeita(char nomeLivro[30], char nomeReceptor[20], char tel[20]){

    FILE *fileLivro;
    if(fileLivro == NULL) printf("\nErro ao executar o arquivo\n");
    fileLivro = fopen("livros.txt", "w");
    fclose(fileLivro);

    FILE *fileTroca;
    if(fileTroca == NULL) printf("\nErro ao executar o arquivo\n");

    printf("\033[H\033[J");
    printf("Troca realizada com sucesso!");
    printf("\n\nResumo do pedido:\n");

    NoLivro *noLista = listaLivro.inicio;

    while(noLista){
            if(strcmp(noLista->nome, nomeLivro)==0)
            {
                fileTroca = fopen("troca.txt", "a+");
                printf("\nNome: %s", noLista->nome);
                printf("\nCondição: %s", noLista->condicao);
                printf("\nGênero: %s\n", noLista->genero);
                fprintf(fileTroca, "%s-%s-%s,", noLista->nome, nomeReceptor, tel);
                fclose(fileTroca);
                getchar();
            }
            else {
                fileLivro = fopen("livros.txt", "a+");
                if(fileLivro == NULL) printf("\nErro ao executar o arquivo\n");

                fprintf(fileLivro, "%s-%s-%s-%s,", noLista->nome, noLista->condicao, noLista->genero, noLista->tel);

                fclose(fileLivro);
            }
            noLista = noLista->proximo;
    }
}

//------------------------ Trocas feitas --------------------------

void minhasTrocas(char tel[20]){
    lerTrocas();
    livrosTrocado(tel);

}

void lerTrocas(){
    FILE *fileTroca = fopen("troca.txt", "r");
    char texto[100]={' '};
    char letra;
    int i=0;

    if(fileTroca){
        criarLista(&listaTroca);
        while((letra=fgetc(fileTroca))!= EOF){
            if(letra != ','){
                texto[i] = letra;
                i++;
            } else if(letra == ','){
                resgataArquivoTroca(texto);
                i=0;
            }
        }
        fclose(fileTroca);
    }
    else{
        printf("\nErro ao executar o arquivo\n");
    }
}

void inserirInicioTroca(Lista *lista, char nomeLivro[20], char nomeReceptor[20], char tel[20]){
    NoTroca *novo = malloc(sizeof(NoTroca));
    if(novo){
        strcpy(novo->nomeLivro, nomeLivro);
        strcpy(novo->nomeDoador, nomeReceptor);
        strcpy(novo->tel, tel);
        novo->proximo = lista->inicio;
        lista->inicio = novo;
        lista->tam++;
    }
    else
        printf("Erro ao alocar memoria!\n");
}

void resgataArquivoTroca(char texto[100]){
    int i=0;
    int aux=0, j=0;
    char nomeLivro[20]={};
    char nomeReceptor[20]={};
    char tel[20]={};

    while(i<strlen(texto)){
        if(texto[i] == '-'){
            texto[i] = ' ';
            aux++;
            j=0;
        }else if(aux==0){
            if(texto[i] != ' '){
                nomeLivro[j] = texto[i];
                texto[i] = ' ';
                j++;
            }
        }else if(aux==1){
            if(texto[i] != ' '){
                nomeReceptor[j] = texto[i];
                texto[i] = ' ';
                j++;
            }
        }else if(aux==2){
            if(texto[i] != ' '){
                tel[j] = texto[i];
                texto[i] = ' ';
                j++;
            }
        }
        i++;
    }
    inserirInicioTroca(&listaTroca, nomeLivro, nomeReceptor, tel);
}

void livrosTrocado(char tel[20]){

    NoTroca *noTroca = listaTroca.inicio;
    int flag=0;
    int i=0;
    char strings[10][20];
    int length=0;

    printf("\033[H\033[J");
    printf("Livro(s) trocado(s) por você\n\n- Ordenados Alfabéticamente\n\n");
    printf("------------------------------");
    if(listaTroca.tam > 0){
        while(noTroca){
            if(strcmp(noTroca->tel, tel)==0){
                //length = strlen(noTroca->nomeLivro);
                //strings[i] = malloc(length * sizeof(char));
                strcpy(strings[i], noTroca->nomeLivro);
                i++;
                flag++;
            }
            noTroca = noTroca->proximo;
        }
    }
    else {
        printf("\n\nTudo vazio por aqui!\n");
        getchar();
    }

    if(flag == 0){
        printf("\n\n\tVocê ainda não realizou nenhuma troca");
    } else {

        //ORDENANDO O VETOR
        int x,y, res;
        char aux[20];
        for(x=0; x<=flag; x++){
            for(y=x+1; y<=flag; y++){
                res = strcmp(strings[x], strings[y]);
                if(res>0){
                strcpy(aux, strings[x]);
                strcpy(strings[x], strings[y]);
                strcpy(strings[y], aux);
                }
            }
        }

        i=0;
        printf("\n");
        while(i<flag){
            printf("\n- %s", strings[i]);
            i++;
        }
    }
    getchar();
}
