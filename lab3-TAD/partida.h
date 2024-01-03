#ifndef PARTIDA_H
#define PARTIDA_H

#include "circuito.h"

typedef struct Partidas {
    float V;
    int id_p;
    int n_participantes;
    int n_circuitos;
    int n_equipamentos;
    Circuitos *circuito;
} Partidas;

void le_partida(Partidas *partida,int id_p);
void imprime_info_partidas(Partidas *partida);
void imprime_info_participantes(Partidas *partida);
void imprime_circuito_dificil(Partidas *partida);
void cria_partidas(int qtd);

#endif /* PARTIDA_H */
