#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 60
//estrutura para representar um livro
typedef struct livro{
    char nome[MAX];
    struct livro *proximo; 
    struct livro *anterior;
} livro;
typedef struct livro* p_livro;

//estrutura para representar uma lista de livros
typedef struct lista{
    p_livro inicio;
    p_livro final;
    p_livro atual;
    int direcao; //direciona onde sera colocado o novo livro, 1 para direita e 0 para esquerda;  
    int qtd; //qtd de livros
} lista;
typedef struct lista* p_lista;

//função para processar e tratar o nome de um livro
void tratamento(char *nome) {
    fgets(nome, 56, stdin); //leitura do nome do livro
    int len_nome = strlen(nome);

    if (len_nome > 0) {
        for (int i = 0; i < len_nome - 1; i++) { // laço para retirar o ' ' do começo
            nome[i] = nome[i + 1];
        }
        nome[len_nome - 2] = '\0'; // adiciona o '\0' para indicar o final de uma string
    }
}

//função para adicionar um livro na lista atual
void adiciona_livro(p_lista Lista) {
    char nome[MAX];
    p_livro novo = (p_livro)malloc(sizeof(livro));

    //criando um novo livro
    tratamento(nome);
    novo->proximo = NULL;
    novo->anterior = NULL;
    strcpy(novo->nome,nome);

    //lista vazia
    if(Lista->inicio == NULL) {
        Lista->inicio = novo;
        Lista->final = novo;
        Lista->atual = novo;
        Lista->direcao = 1;
    }
    else{
        if(Lista->direcao){
        novo->anterior = Lista->atual;
        if (Lista->atual == NULL && Lista->direcao == 1){
            Lista->atual = Lista->final;
        }
        Lista->atual->proximo = novo;
        Lista->atual = novo;
        Lista->final = novo;
        } 
        else{
            if(Lista->atual->anterior == NULL){
                Lista->atual->anterior = novo;
                novo->proximo = Lista->atual;
                Lista->inicio = novo;
            }
            else{
                novo->anterior = Lista->atual->anterior;
                Lista->atual->anterior->proximo = novo;
                Lista->atual->anterior = novo;
                novo->proximo = Lista->atual;
            }
            
        }
        if (Lista->atual == Lista->inicio){
            Lista->inicio = novo;
        }
    }

    Lista->qtd+=1;
}

//função para imprimir os livros da lista atual
void imprime_lista(p_lista Lista) {
    p_livro livro = Lista->inicio;
    int cont=0;

    while (livro != NULL){
        if (cont == 0){
            printf("%s",livro->nome);
        }
        else{
            printf(", %s",livro->nome);
        }
        cont+=1;
        livro = livro->proximo;
    } 
    printf("\n");
}

//função para remover um livro
void remove_livro(p_lista Lista){
    char nome[MAX];
    p_livro livro = Lista->inicio;
    p_livro prox,ant;
    tratamento(nome);

    // Percorre todas as listas
    while (livro != NULL) {
        if (strcmp(livro->nome, nome) == 0) {
            //se for o primeiro da lista    
            if (livro == Lista->inicio) {
                if (Lista->inicio == Lista->final){//lista apenas com 1 livro
                    Lista->inicio = NULL;
                    Lista->final = NULL;
                    Lista->atual = NULL;
                }
                else{
                    livro->proximo->anterior = NULL;
                    Lista->inicio = livro->proximo;
                }
            }
            // Se o livro a ser removido for o último da lista
            else if (livro == Lista->final) {
                ant = livro->anterior;
                ant->proximo = NULL;
                Lista->final = ant;
            }
            //se for no meio da lista
            else {
                if (livro->anterior == NULL){
                    prox = livro->proximo;
                    ant = livro->anterior;
                    prox->anterior = ant;
                }
                else{
                    prox = livro->proximo;
                    ant = livro->anterior;
                    ant->proximo = prox;
                    prox->anterior = ant;
                }
            }
            
            if (Lista->atual == livro){
                Lista->atual = livro->proximo;
            }
            free(livro);
            break;
        }
        livro = livro->proximo;
    }
}

//função para liberar memoria alocada para os livros
void libera_livros(p_lista Lista){
    p_livro livro = Lista->inicio;
    p_livro prox;

    while (livro != NULL ){
        prox = livro->proximo;
        free(livro);
        livro = prox;
    }
    
}

int main() {
    //inicializa as variaveis e estruturas
    char opcao[10];
    lista Lista;
    Lista.inicio = NULL;
    Lista.atual = NULL;
    Lista.final = NULL;
    Lista.qtd = 0;

    while (scanf("%s", opcao) != EOF) {
        if (strcmp(opcao, "adicionar") == 0) {
            adiciona_livro(&Lista);
        }
        else if (strcmp(opcao, "inicio") == 0) {
            Lista.direcao = 0;
            Lista.atual = Lista.inicio;
        }
        else if (strcmp(opcao, "final") == 0) {
            Lista.direcao = 1;
            Lista.atual = Lista.final;
        }
        else if (strcmp(opcao, "remover") == 0) {
            remove_livro(&Lista);
        }
        else if (strcmp(opcao, "imprimir") == 0) {
            imprime_lista(&Lista);
        }
    }

    libera_livros(&Lista);

    return 0;
}
