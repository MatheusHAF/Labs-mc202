/*
Aluno: Matheus Henrique Aliberto de Francisco
RA: 239930
*/
#include <stdio.h>
#include <stdlib.h>

#define max 300
#define plv 21

//função que calcula o tamanho de cada palavra e armazena em um vetor paralelo cada tamanho
void calcula_tamanho(char palavra[plv], int tamanho[max],int j){
    tamanho[j] = 0;
    for (int i = 0; i < plv; i++){
        if (palavra[i] != '\0'){
            tamanho[j]+=1;
        }
        else{
            break;
        }      
    }  
}

//verifica se a palavra existe na vertical (de cima até baixo) e retorna 0 se não existe ou 1 se existe
int verifica_existencia_vertical(int L,int C,char texto[max][max],char palavra[plv],char tamanho_palavra){
    int verificador=0;
    for (int i = 0; i < L; i++){
        for (int j = 0; j < C; j++){
            verificador = 1;
            for (int k = 0; k < tamanho_palavra; k++){
                if (palavra[k] != texto[i+k][j]){
                    verificador = 0;
                    break;
                }  
            }
            if (verificador == 1){
                printf("A palavra %s está no texto!\n", palavra);
                return 1;
            }  
        }
    }
    return 0;   
}

//verifica se a palavra existe na vertical (de baixo até cima)
int verifica_existencia_vertical_inversa(int L,int C,char texto[max][max],char palavra[plv],char tamanho_palavra){
    int verificador=0;
    for (int i = L-1; i >= 0; i--){//percorrendo as linhas ao contrario
        for (int j = 0; j < C; j++){
            verificador = 1;
            for (int k = 0; k < tamanho_palavra; k++){
                if (palavra[k] != texto[i-k][j]){
                    verificador = 0;
                    break;
                }  
            }
            if (verificador == 1){
                printf("A palavra %s está no texto!\n", palavra);
                return 1;
            }  
        }
    }
    return 0;   
}
//verifica se a palavra existe na horinzontal (da esquerda até direita)
int verifica_existencia_horizontal(int L,int C,char texto[max][max],char palavra[plv],char tamanho_palavra){
    int verificador=0;
    for (int i = 0; i < L; i++){
        for (int j = 0; j < C; j++){
            verificador = 1;
            for (int k = 0; k < tamanho_palavra; k++){
                if (palavra[k] != texto[i][j+k]){
                    verificador = 0;
                    break;
                }  
            }
            if (verificador == 1){
                printf("A palavra %s está no texto!\n", palavra);
                return 1;
            }  
        }
    }
    return 0;
    
}
//verifica se a palavra existe na horinzontal (da direita até esquerda)
int verifica_existencia_horizontal_inversa(int L,int C,char texto[max][max],char palavra[plv],char tamanho_palavra){
    int verificador=0;
    for (int i = 0; i < L; i++){
        for (int j = C-1; j >=0; j--){// percorrendo as colunas ao contrario
            verificador = 1;
            for (int k = 0; k < tamanho_palavra; k++){
                if (palavra[k] != texto[i][j-k]){
                    verificador = 0;
                    break;
                }  
            }
            if (verificador == 1){
                printf("A palavra %s está no texto!\n", palavra);
                return 1;
            }  
        }
    }
    return 0;   
}

int main(){
    
    int L,C,P,tamanho_palavras[max];
    char texto[max][max],lista_palavras[max][plv];

    scanf("%d %d %d",&L,&C,&P);

    //leitura da matriz
    for (int i = 0; i < L; i++){
        for (int j = 0; j < C; j++){
            scanf(" %c",&texto[i][j]);
        }
    }

    //leitura da lista de palavras
    for (int k = 0; k < P; k++){
        scanf("%s",lista_palavras[k]);
        calcula_tamanho(lista_palavras[k],tamanho_palavras,k);
    }
    
    for (int k = 0; k < P; k++){
        if(
        verifica_existencia_horizontal(L,C,texto,lista_palavras[k],tamanho_palavras[k]) == 0
        && verifica_existencia_vertical(L,C,texto,lista_palavras[k],tamanho_palavras[k]) == 0
        && verifica_existencia_vertical_inversa(L,C,texto,lista_palavras[k],tamanho_palavras[k]) == 0
        && verifica_existencia_horizontal_inversa(L,C,texto,lista_palavras[k],tamanho_palavras[k]) == 0
        ){
            printf("A palavra %s não está no texto!\n", lista_palavras[k]);
        }
    }   
    return 0;
}