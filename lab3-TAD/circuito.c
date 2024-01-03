#include <stdio.h>
#include <stdlib.h>
#include "circuito.h"

Circuitos *cria_circuitos(int C, int qtd_participantes) {
    Circuitos *circuito = malloc(C * sizeof(Circuitos));
    if (circuito == NULL) {
        // Tratamento de erro, se necessário
        return NULL;
    }

    for (int i = 0; i < C; i++) {
        circuito[i].n_participantes = qtd_participantes;
        circuito[i].jogadas_participantes = malloc(qtd_participantes * sizeof(int));
        if (circuito[i].jogadas_participantes == NULL) {
            // Tratamento de erro, liberar memória alocada anteriormente, se necessário
            return NULL;
        }
    }

    return circuito;
}

void libera_circuitos(Circuitos *circuito, int C) {
    if (circuito != NULL) {
        for (int i = 0; i < C; i++) {
            free(circuito[i].jogadas_participantes);
        }
        free(circuito);
    }
}

void le_circuitos(Circuitos *circuito, int C, int qtd_participantes) {
    int jogada;
    for (int i = 0; i < C; i++) {
        scanf("%d", &circuito[i].id_c);

        for (int j = 0; j < qtd_participantes; j++) {
            scanf("%d", &jogada);
            circuito[i].jogadas_participantes[j] = jogada;
        }
    }
}
