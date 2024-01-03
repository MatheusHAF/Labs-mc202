#include <stdio.h>
#include "partida.h"

void le_partida(Partidas *partida,int id_p) {
    int X, C, E;
    scanf("%d %d %d", &X, &C, &E);

    partida->V = 10 * C + 17.5 * E;
    partida->id_p = id_p;
    partida->n_participantes = X;
    partida->n_circuitos = C;
    partida->n_equipamentos = E;
    partida->circuito = cria_circuitos(C, X);
    le_circuitos(partida->circuito, C, X);
}

void imprime_info_partidas(Partidas *partida) {
    printf("Partida %d", partida->id_p);
    printf("\nNum. de Jogadores: %d - Num. de Circuitos: %d - Num. de Equipamentos: %d",
           partida->n_participantes, partida->n_circuitos, partida->n_equipamentos);
    printf("\nValor do Aluguel: R$ %.2f", partida->V);
}

void imprime_info_participantes(Partidas *partida) {
    int soma_jogadas;

    for (int i = 0; i < partida->n_participantes; i++) {
        soma_jogadas = 0;
        for (int j = 0; j < partida->n_circuitos; j++) {
            soma_jogadas += partida->circuito[j].jogadas_participantes[i];
        }

        printf("\nJogador %d: %d", i + 1, soma_jogadas);
    }
}

void imprime_circuito_dificil(Partidas *partida) {
    int id_circuito_dificil, maior_soma_jogadas = 0, soma_parcial = 0;

    id_circuito_dificil = partida->circuito[0].id_c;

    for (int i = 0; i < partida->n_circuitos; i++) {
        soma_parcial = 0;
        for (int j = 0; j < partida->circuito[i].n_participantes; j++) {
            soma_parcial += partida->circuito[i].jogadas_participantes[j];
        }
        if (soma_parcial > maior_soma_jogadas) {
            id_circuito_dificil = partida->circuito[i].id_c;
            maior_soma_jogadas = soma_parcial;
        }
    }

    printf("\nCircuito mais dificil: %d", id_circuito_dificil);
}

void cria_partidas(int qtd) {
    for (int i = 1; i <= qtd; i++) {
        Partidas partida;
        le_partida(&partida,i);

        /*Saida de dados*/
        imprime_info_partidas(&partida);
        imprime_info_participantes(&partida);
        imprime_circuito_dificil(&partida);

        libera_circuitos(partida.circuito, partida.n_circuitos);
        
        printf("\n##########\n");
    }
}
