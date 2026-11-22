#include "estacionamento.h"

#include <stdio.h>

#include <stdlib.h>

bool iniciar_estacionamento(Estacionamento *estacionamento)
{
    *estacionamento = (Estacionamento){0};
    const int capacidade_inicial = 2;
    estacionamento->veiculos = malloc(capacidade_inicial * sizeof *estacionamento->veiculos);
    if (estacionamento->veiculos == NULL) {
        return false;
    }

    estacionamento->capacidade = capacidade_inicial;
    return true;
}

void encerrar_estacionamento(Estacionamento *estacionamento)
{
    free(estacionamento->veiculos);
    *estacionamento = (Estacionamento){0};
}

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
