#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_S 11
#define MAX_H 1511 //valor escolhido para servir no hash

//estrutura para uma criança que receberá doces
typedef struct crianca{
    char nome[MAX_S],sobrenome[MAX_S];
    int qtd_doces;
}crianca;
typedef struct crianca* p_crianca;

//estrutura para a familia que sera armazenada no vetor com hash
typedef struct familia{
    char nome[MAX_S];
    int qtd_doces;
    int condicao; // 0 para livre, 1 para ocupado e -1 para excluido
}familia;
typedef struct familia* p_familia;

//estrutura para a hash
typedef struct Hash{
    p_familia vetor[MAX_H];
}Hash;
typedef struct Hash* p_hash;

//função que define o hash
int define_hash(char chave[]){
    unsigned long int i;
    int n = 0;
    for (i = 0; i < strlen(chave); i++)
    n = (256 * n + chave[i]) % MAX_S;
    return n;
}

//verifica se a posição do hash esta ocupada, caso sim, i=+1;
int verifica_hash(p_hash hash, int i){
    if (hash->vetor[i]->condicao != 0 ){
        if (i == MAX_H-1){
            i=-1;
        }
        i = verifica_hash(hash,i+1);
    }     
    return i;
}

//função que insere uma familia no vetor com hash
void inserir_familia(p_hash hash){
    char nome[MAX_S];
    int qtd, indice;
    scanf("%s",nome);
    scanf("%d",&qtd);

    indice = define_hash(nome);
    indice = verifica_hash(hash,indice);

    strcpy(hash->vetor[indice]->nome,nome);
    hash->vetor[indice]->qtd_doces = qtd;
    hash->vetor[indice]->condicao = 1;
    
}

//função que remove a familia colocando sua condição em -1
void remover_familia(p_hash hash){
    char nome[MAX_S];
    int indice,cont=0;
    scanf("%s",nome);

    indice = define_hash(nome);

    while(cont<MAX_H){
        if (strcmp(hash->vetor[indice]->nome,nome) == 0){
            hash->vetor[indice]->condicao = -1;
            break;
        }
        else{
            indice+=1;
            cont+=1;
        }  
    }
    printf("\nA familia %s saiu com %d doce(s) sobrando.",hash->vetor[indice]->nome,hash->vetor[indice]->qtd_doces);
}

//função que adiciona a compra de mais doce pela familia
void adicionar_doces(p_hash hash){
    char nome[MAX_S];
    int qtd,indice,cont=0;
    scanf("%s",nome);
    scanf("%d",&qtd);

    indice = define_hash(nome);

    while(cont<MAX_H){
        if (strcmp(hash->vetor[indice]->nome,nome) == 0){
            hash->vetor[indice]->qtd_doces+=qtd;
            break;
        }
        else{
            indice+=1;
            cont+=1;
        }  
    }
    printf("\nA familia %s agora possui %d doces.",nome,hash->vetor[indice]->qtd_doces);
}

//função que busca a familia (comparando o nome dps de acessar com indice do hash) e retorna o seu indice
int busca_familia(p_hash hash, char nome[],int i){
    if (strcmp(hash->vetor[i]->nome,nome)==0)
        return i;
    i = busca_familia(hash,nome,i+1);
    return i;
}

//função que adiciona os doces comprados pelas familias
void altera_qtd_doces(p_hash hash,int i,p_crianca nova_crianca,int nota){
    if (hash->vetor[i]->qtd_doces-nota >= 0){
        hash->vetor[i]->qtd_doces -=nota;
        nova_crianca->qtd_doces +=nota;
    }
    else if(hash->vetor[i]->qtd_doces > 0){
        nova_crianca->qtd_doces += hash->vetor[i]->qtd_doces;
        hash->vetor[i]->qtd_doces = 0;
    }  
}

//função que cria a criança e adiciona seus doces
void trickortreat(p_hash hash){
    crianca nova_crianca;
    int n,i;
    char familia[MAX_S],nota[6];
    nova_crianca.qtd_doces = 0;

    scanf("%s",nova_crianca.nome);
    scanf("%s",nova_crianca.sobrenome);
    scanf("%d",&n);

    for (int j = 0; j < n; j++){
        scanf("%s",familia);
        scanf("%s",nota);
        i = define_hash(familia);
        i = busca_familia(hash,familia,i);
        if(strcmp(nota,"Boa") == 0){
            if (hash->vetor[i]->qtd_doces > 0){
                altera_qtd_doces(hash,i,&nova_crianca,3);
                if (hash->vetor[i]->qtd_doces == 0){
                    printf("\nA familia %s ficou sem doces.",hash->vetor[i]->nome);
                }
            }
        }
        else if(strcmp(nota,"Ruim") == 0){
            if (hash->vetor[i]->qtd_doces > 0){
                altera_qtd_doces(hash,i,&nova_crianca,1);
                if (hash->vetor[i]->qtd_doces == 0){
                    printf("\nA familia %s ficou sem doces.",hash->vetor[i]->nome);
                }
            }
        }
        if(strcmp(nota,"Media") == 0){
            if (hash->vetor[i]->qtd_doces > 0){
                altera_qtd_doces(hash,i,&nova_crianca,2);
                if (hash->vetor[i]->qtd_doces == 0){
                    printf("\nA familia %s ficou sem doces.",hash->vetor[i]->nome);
                }
            }
        }
    }
    //caso a criança não tiver nenhum doce;
    if (nova_crianca.qtd_doces == 0){
        nova_crianca.qtd_doces+=10;
        printf("\n%s %s recebeu %d doces da prefeitura.",nova_crianca.nome,nova_crianca.sobrenome,nova_crianca.qtd_doces);   
    }
    else{
        printf("\n%s %s recebeu %d doce(s) das familias.",nova_crianca.nome,nova_crianca.sobrenome,nova_crianca.qtd_doces);   
    }
}

//função para liberar a memoria alocada para o vetor
void liberar_memoria(p_hash hash){
    for (int i = 0; i < MAX_H; i++){
        free(hash->vetor[i]);
    }
}

int main(){
    char opc[13];
    Hash hash;

    for (int i = 0; i < MAX_H; i++) {
        hash.vetor[i] = malloc(sizeof(familia));
        hash.vetor[i]->condicao = 0;
        hash.vetor[i]->qtd_doces = 0;
    }

    scanf("%s",opc);
    while (1){
        if (strcmp(opc,"ENTRAR") == 0){
            inserir_familia(&hash);
        }
        else if (strcmp(opc,"SAIR") == 0){
            remover_familia(&hash);
        }
        else if (strcmp(opc,"COMPRAR") == 0){
            adicionar_doces(&hash);
        }
        else if (strcmp(opc,"TRICKORTREAT") == 0){
            trickortreat(&hash);
        }
        scanf("%s",opc);
        if (strcmp(opc,"FINALIZAR") == 0){
            liberar_memoria(&hash);
            break;
        }
    }
    
    return 0;
}
