// Aluno: Matheus Henrique Aliberto de Francisco RA: 239930
// lab-12 - Grafos

#include <stdio.h>
#include <stdlib.h>
#define MAX 21

//estrutura para um grafo (como os ids = valores dos vertices eram na ordem de criação)
typedef struct grafo{
    int **adj;
    int num_vertices;
} grafo;
typedef grafo* p_grafo;

//estrutura para a fila
typedef struct Fila{
    int vertices[MAX];
    int primeiro, ultimo;
}Fila;
typedef struct Fila * p_fila;

//Função para criar um grafo e uma matriz inicializar todos os valores em 0;
p_grafo cria_grafo(p_grafo Grafo){
    Grafo = malloc(sizeof(grafo));
    Grafo->num_vertices = 0;
    Grafo->adj = malloc((MAX-1) * sizeof(int *));
    for (int i = 0; i < (MAX-1); i++)
        Grafo->adj[i] = malloc((MAX-1) * sizeof(int));
    for (int i = 0; i < (MAX-1); i++)
        for (int j = 0; j < (MAX-1); j++)
            Grafo->adj[i][j] = 0;

    return Grafo;
}

//função para destruir o grafo
void destruir_grafo(p_grafo Grafo) {
    for (int i = 0; i < MAX-1; i++)
            free(Grafo->adj[i]);
    free(Grafo->adj);
    free(Grafo);
} 

// Função que cria uma fila
Fila* criar_fila() {
    p_fila f = (p_fila)malloc(sizeof(Fila));
    f->primeiro = -1;
    f->ultimo = -1;
    return f;
}
// função para destruir uma fila
void destruir_fila(p_fila f) {
    free(f); 
}

// Função que verifica a fila
int fila_vazia(p_fila f){
    if(f->primeiro == -1)
        return 1;
    return 0;
}

// Função para enfileirar uma vertixe na matriz
void enfileira(p_fila f, int vertice) {
    if (f->ultimo == MAX - 2){
        printf("\nNão existe caminho");
    }
    else {
        if (f->primeiro == -1)
            f->primeiro = 0;
        f->ultimo++;
        f->vertices[f->ultimo] = vertice;
    }
}

// Função para desenfileirar um elemento
int desenfileira(p_fila f) {
    int vertice;
    if (fila_vazia(f))
       return -1;

    vertice = f->vertices[f->primeiro];
    f->primeiro+=1;
    if (f->primeiro > f->ultimo) {
        f->primeiro = f->ultimo = -1;
    }
    return vertice;
}


//função para adicionar um vertice no grafo
void adiciona_vertice(p_grafo Grafo){
    Grafo->num_vertices+=1;
}

//função para adicionar uma aresta no grafo
void adiciona_aresta(p_grafo Grafo, int u,int v){
    if(Grafo->adj[u-1][v-1]==1)
        return;
    Grafo->adj[u-1][v-1]=1;
    Grafo->adj[v-1][u-1]=1;
}

//função para remover uma aresta no grafo
void remove_aresta(p_grafo Grafo, int u,int v){
    if(Grafo->adj[u-1][v-1]==0)
        return;
    Grafo->adj[u-1][v-1]=0;
    Grafo->adj[v-1][u-1]=0;
}

//função para buscar todos os vertices conectados apartir de um ponto
void busca_conexos(p_grafo Grafo,int vet_conexos[],int vet_visitados[],int i,int *cont){
    vet_visitados[i]=1;
    vet_conexos[(*cont)]= i+1;
    (*cont)+=1;
    for (int j = 0; j < Grafo->num_vertices; j++){
        if (vet_visitados[j]==0 && Grafo->adj[i][j] == 1) {
            busca_conexos(Grafo,vet_conexos,vet_visitados,j,cont);
        }
    }
}

//função para zerar qualquer vetor fixo
void zera_vetor(int vetor[]){
    //deixar todos igual a 0 por nao terem sido acessados
    for (int i = 0; i < MAX; i++){
        vetor[i]=0;
    } 
}
//função para imprimir a passagens de cada vertice
void imprime_conexos(p_grafo Grafo){
    int ponto,vet_conexos[MAX], vet_visitados[MAX],cont;
    
    //deixar todos igual a 0 por nao terem sido acessados
    zera_vetor(vet_visitados);
    zera_vetor(vet_conexos);

    //verificando cada vertice no grafo
    for(int i = 0; i < Grafo->num_vertices; i++){
        cont=0;
        ponto = i+1;
        //verifica se o vertice foi visitado; 
        busca_conexos(Grafo,vet_conexos,vet_visitados,i,&cont);
        
        //laço para imprimir o vetor com as passagens
        printf("\nPonto %d (Pontos diretamente ou indiretamente conectados):",ponto);
        for (int j = 0; j < Grafo->num_vertices; j++){
            if (vet_conexos[j]==0 || j>=cont)
                break;
            printf(" %d",vet_conexos[j]);    
        }
        zera_vetor(vet_conexos);
        zera_vetor(vet_visitados);

    }
}

//função que verifica se há conexão entre u e v;
int verifica_conexao(p_grafo Grafo,int u,int v,int verificador){
    for (int i = u; i < Grafo->num_vertices; i++){
        if(Grafo->adj[u][i]==1){
            if(i==v){
                verificador = 1;
                return verificador;
            } 
            verificador = verifica_conexao(Grafo,i,v,verificador);
        }
    }
    return verificador;
    
}

int *busca_em_largura(p_grafo g, int u) {
    int w, v;
    int *pai = malloc(g->num_vertices * sizeof(int));
    int *vet_visitados = malloc(g->num_vertices * sizeof(int));
    Fila *f = criar_fila();

    for (v = 0; v < g->num_vertices; v++) {
        pai[v] = -1;
        vet_visitados[v] = 0;
    }

    enfileira(f, u+1);
    pai[u] = u+1;
    vet_visitados[u] = 1;

    while (!fila_vazia(f)) {
        v = desenfileira(f)-1;
        for (w = 0; w < g->num_vertices; w++) {
            if (g->adj[v][w] && !vet_visitados[w]) {
                vet_visitados[w] = 1;
                pai[w] = v+1;
                enfileira(f, w+1);
            }
        }
    }
    destruir_fila(f);
    free(vet_visitados);
    return pai;
}


//função que busca o melhor caminho entre dois vertices;
void busca_caminho(p_grafo Grafo, int u, int v, int melhor_caminho[]) {
    int *caminho = busca_em_largura(Grafo, u);

    if (caminho[v] == -1) {
        free(caminho);
        printf("\nNão existe conexão entre os nós.");
        return;
    }

    int i = v+1;
    int tam_caminho = 0;

    while (i != u+1) {
        melhor_caminho[tam_caminho] = i;
        i = caminho[i-1];
        tam_caminho+=1;
    }

    melhor_caminho[tam_caminho] = u+1;
    tam_caminho+=1;

    for (i = tam_caminho-1; i > -1; i--) {
        if (i == tam_caminho-1) {
            printf("\n%d", melhor_caminho[i]);   
        }
        else{
            printf(" -> %d",melhor_caminho[i]);
        }
    }
    free(caminho);
}

int main(){
    int operacao,u,v;
    p_grafo Grafo = NULL;

    scanf("%d",&operacao);
    while (operacao<=6){
        if (Grafo == NULL){
            Grafo = cria_grafo(Grafo);
        }
        
        switch (operacao){
            case 1:
                scanf("%d",&u);
                adiciona_vertice(Grafo);
                break;
            case 2:
                scanf("%d %d",&u,&v);
                adiciona_aresta(Grafo,u,v);
                break;
            case 3:
                scanf("%d %d",&u,&v);
                remove_aresta(Grafo,u,v);
                break;
            case 4:
                scanf("%d %d",&u,&v);
                if(verifica_conexao(Grafo,u-1,v-1,0)){
                    printf("\nExiste conexão entre os nós.");
                }
                else{
                    printf("\nNão existe conexão entre os nós.");
                }
                
                break;
            case 5:
                scanf("%d %d",&u,&v);
                int melhor_caminho[21];
                zera_vetor(melhor_caminho);
                busca_caminho(Grafo,u-1,v-1,melhor_caminho);
                break;
            case 6:
                imprime_conexos(Grafo);
                break;
            default:
                break;
        }
        scanf("%d",&operacao);
    }
    
    destruir_grafo(Grafo);

    return 0;
}
