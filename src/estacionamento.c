#include "estacionamento.h"

#include <stdio.h>

void exibir_mapa(const Estacionamento *estacionamento)
{
    printf("\n    ");
    for (int coluna = 0; coluna < COLUNAS; ++coluna) {
        printf("C%d ", coluna + 1);
    }
    putchar('\n');

    for (int fileira = 0; fileira < FILEIRAS; ++fileira) {
        printf("F%d  ", fileira + 1);
        for (int coluna = 0; coluna < COLUNAS; ++coluna) {
            printf(" %c ", estacionamento->mapa[fileira][coluna] ? 'X' : '.');
        }
        putchar('\n');
    }
    puts("Legenda: X = ocupada, . = livre");
}
