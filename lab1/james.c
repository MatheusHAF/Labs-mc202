/*
Aluno: Matheus Henrique Aliberto de Francisco
RA: 239930
*/
#include <stdio.h>

void contador_vendas(int n, int lista_pix[],int lista_cont[]){//Função que conta o número de vendas de cada tipo saladas
    for (int i = 0; i < n; i++){
        if (lista_pix[i] == 5){
            lista_cont[0]+=1;
        }
        else if (lista_pix[i] == 7){
            lista_cont[1]+=1;
        }
        else{
            lista_cont[2]+=1;
        } 
    }
}

void contador_sequencias(int n, int lista_pix[], int sequencia[]){//função que conta as sequencias de vendas
    
    int cont;//variavel que auxilia na contagem do mesmo tipo de salada
    for (int i = 0; i < n; i++){
        // laço que pega cada valor da lista dos pix's
        cont = 0;

        for (int j = i; j < n; j++){
        // laço que pega o mesmo valor de pix do laço anterior
        // e compara com os seguintes da mesma lista
            if(lista_pix[i] != lista_pix[j]){
                break; // caso o valor da lista do laço 1 for diferente, se encerra a contagem
            }
            else{
                cont+=1;
            }
        }
        if (sequencia[1]<cont){ 
            sequencia[0] = lista_pix[i];
            sequencia[1] = cont;
        }  
    }
}

int main(){
    int n, lista_pix[1000],lista_cont[3]={0,0,0}, sequencia[2]={0,0};
    // a lista lista_pix armazena todos os valores de pix feito para o James
    // a lista lista_cont armazena a quatidade de vendas de cada salada, 
    // sendo o indicie [0] para as de 5 reais, o indice [1] para as de 7 reais e o indice [2] para as de 10 reais
    // a lista sequencia armazena 2 valores: o primeiro para guardar o valor da maior sequencia de vendas e o segundo com a quantidade da maior sequencia
    
    
    //entrada de valores
    scanf("%d",&n);

    for (int i = 0; i < n; i++){
        scanf("%d",&lista_pix[i]);
    }

    //chamada das funções sem retorno
    contador_vendas(n,lista_pix,lista_cont);
    contador_sequencias(n,lista_pix,sequencia);

    //saida de valores
    printf("James vendeu %d saladas de 5 reais, %d de 7 reais e %d de 10 reais",lista_cont[0],lista_cont[1],lista_cont[2]);
    printf("\nJames vendeu %d saladas de %d reais consecutivamente",sequencia[1],sequencia[0]);
    
    return 0;
}
