// Aluno: Matheus H. A. de Francisco
//RA: 239930
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_S 35
#define MAX_P 35
#define MAX_OPC 10
#define PAI(p) ((p-1) /2) //macro para definir a posicao pai
#define F_ESQ(i) (2*i+1) //macro para definir a posicao do filho a esquerda
#define F_DIR(i) (2*i+2) //macro para definir a posicao do filho a pai

//estrutura para um sobrevivente
typedef struct sobrevivente{
    char nome[MAX_S];
    int prioridade,id;
    struct sobrevivente *proximo;
    
}sobrevivente;

typedef sobrevivente *p_sobrevivente;

//estrutura para saber o pedido 
typedef struct{
    char prato[MAX_P];
    p_sobrevivente sobrevivente;
    int prioridade;
}pedidos;

typedef pedidos *p_pedidos;

//função que cria um sobrevivente em forma de lista ligada
p_sobrevivente cria_sobreviventes(int S, p_sobrevivente lista){
    char nome[MAX_S],sobrenome[MAX_S];
    int tam,qtd;
    p_sobrevivente primeiro;

    for (int i = 0; i < S; i++){    
        p_sobrevivente novo = (p_sobrevivente)malloc(sizeof(sobrevivente));
        
        scanf("%s %s %d", nome, sobrenome,&qtd); // Lê até o segundo espaço vazio
        
        tam = strlen(nome);
        nome[tam+1] ='\0';//adicionar o final da string
        nome[tam] =' ';//adicionar o espaço vazio no nome
        tam = strlen(sobrenome);
        sobrenome[tam]='\0';

        strcat(nome,sobrenome);
        strcpy(novo->nome,nome);
        novo->prioridade = qtd;
        novo->id = i;
        novo->proximo = NULL;
        
        // Se a lista estiver vazia, o novo sobrevivente é o primeiro
        if (lista == NULL) {
            lista = novo; 
        }
        else {
            primeiro = lista;
            while (lista->proximo != NULL) {
                lista = lista->proximo;
            }
            lista->proximo = novo;//novo sobrevivente no final da lista
            lista = primeiro;// pegar o começo da lista novamente após adicionar o novo 
        }
    }
    return lista;  
}

//função que cria um pedido e vincula o sobrevivente pelo id
p_pedidos cria_pedido(p_pedidos novo_pedido,p_sobrevivente lista) {
    int len,id;
    char prato[MAX_P];

    scanf("%d",&id);
    while (lista->id != id){
        lista = lista->proximo;
    }
    
    fgets(prato,sizeof(prato),stdin);
    len = strlen(prato)-1;
    prato[len]='\0';
    //remover caractere vazio no começo da string
    for (int i = 0; prato[i] != '\0'; i++) {
        prato[i] = prato[i + 1];
    }

    strcpy(novo_pedido->prato,prato);
    novo_pedido->sobrevivente = lista;
    novo_pedido->prioridade = lista->prioridade;
    return novo_pedido;
}

//função que realiza a troca quando acontecer o a organização do vetor heap
void troca(p_pedidos *a, p_pedidos *b) {
    p_pedidos t =*a;
    *a =*b;
    *b = t;
}

//
void sobe_no_heap(pedidos **fila , int k) {
    if (k > 0 && fila[PAI(k)]->prioridade< fila[k]->prioridade) {
        troca (&fila[k], &fila[PAI(k)]);
        sobe_no_heap(fila , PAI(k));
    }
}

//Função que adiciona pedidos no vetor heap
void adiciona_pedido(pedidos **vet_pedidos,int *tam,p_sobrevivente lista){
    p_pedidos novo = malloc(sizeof(pedidos));
    vet_pedidos[(*tam)-1] = cria_pedido(novo,lista);
    sobe_no_heap(vet_pedidos , (*tam)-1);
}

//função que desce e organiza o heap novamente
void desce_no_heap(pedidos **fila , int k,int tam) {
    int maior_filho;
    if (F_ESQ(k) < tam) {
        maior_filho = F_ESQ(k);
        if (F_DIR(k) < tam &&
        fila[F_ESQ(k)]->prioridade < fila[F_DIR(k)]->prioridade)
            maior_filho = F_DIR(k);
        if (fila[k]->prioridade < fila[maior_filho]->prioridade) {
            troca (&fila[k], &fila[maior_filho]);
            desce_no_heap(fila , maior_filho,tam);
        }
    }
}

//função utilizada para extrair o pedido da raiz do heap
pedidos extrai_maximo(pedidos **fila,int *tam) {
    pedidos *pedido = fila[0];
    troca (&fila[0], &fila[(*tam)-1]);
    (*tam)--;
    desce_no_heap(fila , 0,*tam);
    return *pedido;
}
//libera posição do vetor
void libera_posicao(pedidos **vetor, int i){
    free(vetor[i]);
}

//liberar a memoria do vetor
void libera_vetor(pedidos **vetor, int tam){
    if (vetor == NULL)
        return;
    for (int i = 0; i < tam; i++)
        libera_posicao(vetor,i);
    free(vetor);
}
//imprime as informações da rodada
void imprime_rodada(pedidos **fila_pedidos,int panelas,int rodada,int *tam){
    pedidos extraido;
    printf("---- rodada %d ----\n",rodada);
    for (int i = 0; i < panelas; i++){
        if (i <= panelas && *tam > 0){
            extraido = extrai_maximo(fila_pedidos,tam);
            libera_posicao(fila_pedidos,(*tam));
            printf("%s",extraido.sobrevivente->nome);
            printf(" %s ",extraido.prato);
            printf("%d\n",extraido.prioridade);
        }
    }
}

//muda prioridade do pedido de acordo com a prioridade
void muda_prioridade(pedidos **fila , int k, int valor,int *tam) {
    if (fila[k]->prioridade < (fila[k]->prioridade + valor)){
        fila[k]->prioridade += valor;
        sobe_no_heap(fila , k);
    } 
    else {
        fila[k]->prioridade += valor;
        desce_no_heap(fila , k,*tam);
    }
}
//libera a memoria alocada para os sobreviventes
void libera_sobreviventes(p_sobrevivente lista){
    p_sobrevivente atual;
    atual = lista;
    while (atual != NULL){
        p_sobrevivente proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

int main(){

    int P,S,N, tam_vet=0,id_sobrev,valor_alt,rodada=1;
    char opcao[MAX_OPC]; 
    p_sobrevivente lista = NULL;
    p_sobrevivente copia_lista = NULL;
    pedidos **vet_pedidos = NULL;

    //entrada de dados
    scanf("%d %d",&P,&S);

    //cria a lista ligada de sobreviventes
    lista = cria_sobreviventes(S,lista);

    //primeira chamada de N para entrar no while
    scanf("%d",&N);
    while (N!=0){
        for (int i = 0; i < N; i++){
            scanf("%s",opcao);
            if (strcmp(opcao,"novo") == 0){
                tam_vet+=1;
                if (vet_pedidos == NULL){
                    vet_pedidos = (pedidos **)malloc(sizeof(pedidos));
                    adiciona_pedido(vet_pedidos,&tam_vet,lista);
                    
                }
                else{
                    //realocação e add de pedido no vetor
                    vet_pedidos = (pedidos **)realloc(vet_pedidos,tam_vet*sizeof(pedidos));
                    adiciona_pedido(vet_pedidos,&tam_vet,lista);
                }
            }
            else{
                int contador=0;
                copia_lista = lista;
                scanf("%d %d",&id_sobrev,&valor_alt);
                while (contador <= tam_vet-1 && vet_pedidos[contador]->sobrevivente->id != id_sobrev){
                    copia_lista = copia_lista->proximo;
                    contador++;
                }
                vet_pedidos[contador]->prioridade += valor_alt;
                if (vet_pedidos[contador]->prioridade + valor_alt > vet_pedidos[contador]->prioridade){
                    sobe_no_heap(vet_pedidos,contador);
                }
                else{
                    desce_no_heap(vet_pedidos,contador,tam_vet);
                }
                
                
                
            } 
        }
        imprime_rodada(vet_pedidos,P,rodada,&tam_vet);  
        rodada+=1;
        scanf("%d",&N);
    }
    //caso o vetor heap de pedidos não estiver vazio, 
    //realizar a impressão deles e liberar a memoria faltante de heap
    if (tam_vet != 0){
        while (tam_vet !=0){
            imprime_rodada(vet_pedidos,P,rodada,&tam_vet);
            rodada+=1;
        }
        libera_vetor(vet_pedidos,tam_vet);
        vet_pedidos = NULL;
        free(vet_pedidos);
    }
    libera_sobreviventes(lista);
    return 0;
}