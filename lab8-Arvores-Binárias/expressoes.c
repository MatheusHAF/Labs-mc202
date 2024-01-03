// Matheus H. Aliberto de Francisco RA:239930
// Lab 08 - expressões

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define MAX 120

//estrutura de um nó da arvore binária
typedef struct no{
    char caractere;
    struct no *esq,*dir;
}no;

typedef no* p_noh;


int verifica_letra(char caractere){
    if((caractere >='a' && caractere<='z') || (caractere =='T') || (caractere=='F'))
        return 1;
    return 0;
}
int verifica_num(char caractere){
    if((caractere >= '0' && caractere <='9'))
        return 1;
    return 0;
}


int verifica_caractere(char caractere){
    if((caractere >= 'A' && caractere <='Z')||(caractere >='a' && caractere<='z')||
    (caractere >='0' && caractere <='9'))
        return 1;
    return 0;
}

//função que cria cada nó na árvore
p_noh criar_no(char caractere){
    p_noh novo = (p_noh)malloc(sizeof(no));
    novo->caractere = caractere;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

//função que destrói o nós filhos do nó pai
void destruir_noh(p_noh pai){
    if (pai != NULL){
        destruir_noh(pai->esq);
        destruir_noh(pai->dir);
        free(pai->esq);
        free(pai->dir);
        pai->esq = NULL;
        pai->dir = NULL;
    }
}

//função que cria uma arvore binária
p_noh criar_arvore(char exp[MAX]){

    p_noh string_exp_pilha[MAX]; //uma string que funciona igual uma pilha que assume que não será maior que o tamanho da expressao
    char caractere;
    int topo = -1;

    for (int i = 0; i < strlen(exp); i++){
        caractere = exp[i];
        if (verifica_caractere(caractere)){
            p_noh novo_no = criar_no(caractere);
            string_exp_pilha[topo+=1]=novo_no;
        }
        else{
            p_noh operador_2 = string_exp_pilha[topo--];
            p_noh operador_1 = string_exp_pilha[topo--];
            p_noh novo_no = criar_no(caractere);

            novo_no->dir = operador_2;
            novo_no->esq = operador_1;
            string_exp_pilha[topo+=1] = novo_no;
        }
    }
    
    return string_exp_pilha[topo];

}

//função que imprime a árvore binária de forma infixa
void imprime_arvore(p_noh raiz){
    if(raiz) {
        if(raiz->esq) {
            printf("(");
            imprime_arvore(raiz->esq);
        }

        if(verifica_caractere(raiz->caractere)){
            printf("%c", raiz->caractere);
        }
        else{
            printf(" %c ", raiz->caractere);
        } 
        if (raiz->dir) {
            imprime_arvore(raiz->dir);
            printf(")");
        }
    }
    
}

//função que auxilia a função de comparação
char comparador(char operador, char char_esq, char char_dir){
    if (operador == '='){
        if(char_esq == char_dir)
            return 'T';
        return 'F';
    }
    else{
        if(char_esq != char_dir)
            return 'T';
        return 'F';
    }
    return operador;
}

//função de comparação (! ou =)
char op_comparacao(char operador, char char_esq, char char_dir){
    if (verifica_letra(char_esq) && verifica_letra(char_dir)){
        if (char_esq != char_dir)
            return operador;
        return comparador(operador,char_esq,char_dir);
    }
    else if (verifica_num(char_esq) && verifica_num(char_dir)){
        return comparador(operador,char_esq,char_dir);
    }
    return operador;
}

//função que verifica a operação logica (& ou |)
char op_logico(char operador, char char_esq, char char_dir){
    if (operador == '|'){
        if (char_esq == 'T' || char_dir == 'T')
            return 'T';
    }
    else if(operador == '&'){
        if (char_esq == 'F' || char_dir == 'F')
            return 'F';
    }
    return operador;
}

//função que verifica a operação relacional (>,<,{ ou })
char op_relacional(char operador, char char_esq, char char_dir){
    
    //caso os caracteres forem iguais
    if(char_dir == char_esq){
        if(operador == '>' || operador == '<')
            return 'F';
        return 'T'; 
    }

    //caso ambo os caracteres forem numeros
    else if((verifica_num(char_esq) && verifica_num(char_dir))){
        if (operador == '>'){
            if (char_esq > char_dir)
                return 'T';
            return 'F';
        }
        else if (operador == '<'){
            if (char_esq < char_dir)
                return 'T';
            return 'F';
        }
        else if (operador == '}'){
            if (char_esq >= char_dir)
                return 'T';
            return 'F';
        }
        else if (operador == '{'){
            if (char_esq <= char_dir)
                return 'T';
            return 'F';
        }
        return operador;
            
    }

    //caso for entre numero e letra
    if (char_dir == '9' || char_esq == '9'){
        if(char_dir == '9' && operador == '{')
            return 'T';
        else if(char_dir == '9' && operador == '>')
            return 'F';
        else if(char_esq == '9' && operador == '<')
            return 'F';
        else if(char_esq == '9' && operador == '}')
            return 'T';
    }
    else if(char_dir == '0' || char_esq =='0'){
        if(char_dir == '0' && operador == '}')
            return 'T';
        else if(char_dir == '0' && operador == '<')
            return 'F'; 
        else if(char_esq == '0' && operador == '>')
            return 'F';       
    }
    return operador;
}

void ret(p_noh pai,char retorno){
    if (retorno == 'T' || retorno == 'F'){
        pai->caractere = retorno;
        destruir_noh(pai);
    }
}

//Função que otimiza o nó
void otimiza_noh(p_noh pai){
    char retorno;
    if (pai != NULL){  
        if(pai->caractere == '&' || pai->caractere == '|'){
            retorno = op_logico(pai->caractere, pai->esq->caractere,pai->dir->caractere);
            ret(pai,retorno);
        }
        if (pai->esq->esq == NULL && pai->dir->esq == NULL){
            //verifica se será uma operação relacional
            if(pai->caractere == '>' || pai->caractere == '<' || pai->caractere == '{' || pai->caractere == '}'){
                retorno = op_relacional(pai->caractere, pai->esq->caractere, pai->dir->caractere); 
                ret(pai,retorno); 
            }
            //verifica se é uma operação de comparação
            else if(pai->caractere == '=' || pai->caractere == '!'){
                retorno = op_comparacao(pai->caractere,pai->esq->caractere,pai->dir->caractere);
                ret(pai,retorno); 
            }
            
        }     
        else{
            otimiza_noh(pai->esq);
            otimiza_noh(pai->dir);
        }
        if(pai->caractere == '&' || pai->caractere == '|'){
            retorno = op_logico(pai->caractere, pai->esq->caractere,pai->dir->caractere);
            ret(pai,retorno);
        }
        if(pai->caractere == '!' || pai->caractere == '='){
            retorno = op_comparacao(pai->caractere, pai->esq->caractere,pai->dir->caractere);
            ret(pai,retorno);
        }
        
    }
}
// função que soma os nós da raiz
int soma_nohs(p_noh pai) {
    if (pai == NULL)
        return 0;
    return soma_nohs(pai->esq) + soma_nohs(pai->dir) + 1;
}

//função que começa a otimização da arvore
void otimizar_arvore(p_noh raiz){
    int esq, dir;
    char retorno;

    // compara a altura de cada lado da raiz para ver qual lado é menor 
    // e resolve-lo primeiro
    esq = soma_nohs(raiz->esq);
    dir = soma_nohs(raiz->dir);
    
    //caso o lado direito tiver mais nós
    if (esq<=dir){
        otimiza_noh(raiz->esq);
        retorno = op_logico(raiz->caractere,raiz->esq->caractere,raiz->dir->caractere);
        ret(raiz,retorno);
        
        if (raiz->caractere != 'T' || raiz->caractere != 'F'){
            otimiza_noh(raiz->dir);
        }
        
    }

    //caso o esquerdo tiver mais nós
    else{
        otimiza_noh(raiz->dir);
        retorno = op_logico(raiz->caractere,raiz->esq->caractere,raiz->dir->caractere);
        if (retorno == 'T' || retorno == 'F'){
            raiz->caractere = retorno;
            destruir_noh(raiz);
        }
        else{
            otimiza_noh(raiz->esq);
        }
    }
    if (raiz->caractere == '|'){
        if (raiz->esq->caractere == 'T' || raiz->dir->caractere == 'T'){
            raiz->caractere = 'T';
            destruir_noh(raiz);
        }  
    }
    else if (raiz->caractere == '&'){
        if (raiz->esq->caractere == 'F' || raiz->dir->caractere == 'F'){
            raiz->caractere = 'F';
            destruir_noh(raiz);
        }  
    }
    
}

int main(){
    int n;
    char expressao[MAX];

    //leitura de dados
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        scanf("%s",expressao);

        //criação da árvore binária
        p_noh raiz_arvore = criar_arvore(expressao);

        //imprime a expressao infixa
        imprime_arvore(raiz_arvore);

        //otimiza a arvore binária
        otimizar_arvore(raiz_arvore);
        
        //imprime a equação otimizada
        printf("\n");
        imprime_arvore(raiz_arvore); 
        if (i<n){
            printf("\n\n");
        }

        //destrói o que falta da arvore binária
        destruir_noh(raiz_arvore);
        free(raiz_arvore);
    }
    return 0;
}

