#ifndef CIRCUITO_H
#define CIRCUITO_H

typedef struct Circuitos {
    int id_c;
    int n_participantes;
    int *jogadas_participantes;
} Circuitos;

Circuitos *cria_circuitos(int C, int qtd_participantes);
void libera_circuitos(Circuitos *circuito, int C);
void le_circuitos(Circuitos *circuito, int C, int qtd_participantes);

#endif /* CIRCUITO_H */
