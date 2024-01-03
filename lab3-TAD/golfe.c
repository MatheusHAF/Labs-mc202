#include <stdio.h>
#include "partida.h"

int main() {
    int qtd_partidas;

    /*Leitura dos dados*/
    scanf("%d", &qtd_partidas);
    cria_partidas(qtd_partidas);

    return 0;
}
