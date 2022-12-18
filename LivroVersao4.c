// Trabalho final AED II
// Sistema para realizacao de troca de livros
// Integrantes :
// Ana Beatriz, Bianca Krauss, Joao Victor, Thiago Bento e Thiago Dias

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include "teste.h"

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

//FUNÇÂO feita para criar um novo usuario

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
                        inspecao(cadastro.nome, cadastro.tel, cadastro.senha); //Preparar strings para salvar no arquivo
                        break;
                    }
                }

                printf("\x1B[36m\nCadastro foi concluído com sucesso!\n"); // Para mudar a cor para azul claro
                fprintf(file, "%s-%s-%s,", cadastro.nome, cadastro.tel, cadastro.senha); // Para escrever no arquivo as informações dadas no cadastro

                empilhar(&cadastroPilha, cadastro.nome, cadastro.tel, cadastro.senha);

                fclose(file); // Fecha o arquivo criado

                main();
}

//Aqui ira realizar uma vistoria na string, caso tiver espaço em branco será trocado por _, e no tel e senha sera retirado os espaços em branco

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

//Aqui será feito uma inpeção no tel, para não cadastrar mais de um mesmo numero

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

//FUNÇÂO feita para realizar a leitura do bloco de notas

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

//FUNÇÂO responsável em separar o nome, tel e senha da=o bloco de notas e armazenar em um cadastro

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

//FUNÇÂO que pedirá ao usuário as suas credenciais

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

//FUNÇÔES para gerencionamento da pilha

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

//FUNÇÂO responsável em verificar as credenciais digitas e cadastradas e retornar um login bem sucedido OU NÂO, caso estiverem erradas

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

void inserirFila(BancoDeDados **fila, guardaTemporario temp){
    BancoDeDados *aux, *novo = (BancoDeDados*) malloc(sizeof(BancoDeDados));
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

//FUNÇÂO responsavel em confirmar a troca ou n do livro

void imprimirFila(BancoDeDados *fila, int idTroca, char telefoneLogin[20], char nome[20]){
    int decisao, flag=0;
    char nomeLivro[30]={};
    int idRemover;
    printf("\n\t------- TROCA ID: %d --------\n", idTroca);

    //VERIFICA se aquele livro desejado já é do seu próprio DONO
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
                printf("\n- ID: %d\n", fila->id);
                printf("------------------------\n");
                flag++;
                idRemover = fila->id;
                strcpy(nomeLivro, fila->nome);
                break;
            }
        fila = fila->proximo;
    }
    if(flag>0){
        printf("\nDeseja realizar a confirmação do pedido: ");
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

//------------------------------------------- FUNCÂO que o usuario logado irá ver, ou seja o SISTEMA em si

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
        printf("2 - Acessar seus cadastros\n");
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
                printf("Livros Cadastrados");

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

//FUNÇÂO responsável em criar um novo cadastro de um livro

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

// FUNÇÂO responsável em salvar um cadastro d livro em um bloco de notas

void salvarArquivo(char nome[20], char cond[20], char genero[20], char tel[20]){

    FILE *fileLivro;

    fileLivro = fopen("livros.txt", "a+");
    if(fileLivro == NULL) printf("\nErro ao executar arquivo\n");

    fprintf(fileLivro, "%s-%s-%s-%s,", nome, cond, genero, tel);

    fclose(fileLivro);
}

//LER livros cadastrados para posteriormente efetuar alguma troca ou deletá-lo

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

//FUNÇÂO feita para separar o nome do livro e suas informções para um cadastro

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
    NoLivro *novo = (NoLivro*) malloc(sizeof(NoLivro));
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

//FUNÇÂO que mostrará ao usuario os livros disponiveis para troca

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

//FUNÇÂO q entrará no sistema de troca/interesse naquele livro

void areaTroca(BancoDeDados *sistemaLivros, int idTroca, char tel[20], char nome[20]){
    int verificaID = 0, i=0;
    printf("\033[H\033[J");
    printf("Área de troca\n");

    imprimirFila(sistemaLivros, idTroca, tel, nome);

}

//FUNÇÂO q exibirá na tela os livros cadastrado pelo seu dono

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

//FUNÇÂO feita para o dono do livro excluir um cadastro

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

//ÙLTIMA função do sistema, um resumo mostrando as informções de contato do dono para o Receptor

void trocaFeita(char nomeLivro[30], char nomeReceptor[20], char tel[20]){

    printf("\033[H\033[J");
    printf("Interesse realizado com sucesso!");
    printf("\n\nAnote as informações do Resumo do pedido:\n");

    NoLivro *noLista = listaLivro.inicio;

    while(noLista){
            if(strcmp(noLista->nome, nomeLivro)==0)
            {
                printf("\nNome: %s", noLista->nome);
                printf("\nCondição: %s", noLista->condicao);
                printf("\nTelefone do proprietário do livro: %s\n", noLista->tel);
                getchar();
            }
            noLista = noLista->proximo;
    }
}
