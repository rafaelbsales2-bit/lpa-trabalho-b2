#include "estacionamento.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

static bool posicao_valida(int fileira, int coluna)
{
    return fileira >= 0 && fileira < FILEIRAS && coluna >= 0 && coluna < COLUNAS;
}

int buscar_veiculo(const Estacionamento *estacionamento, const char *id)
{
    for (int indice = 0; indice < estacionamento->quantidade; ++indice) {
        if (strcmp(estacionamento->veiculos[indice].id, id) == 0) {
            return indice;
        }
    }
    return -1;
}

Resultado cadastrar_veiculo(Estacionamento *estacionamento, const Veiculo *veiculo)
{
    if (estacionamento->quantidade == TOTAL_VAGAS) {
        return ESTACIONAMENTO_LOTADO;
    }
    if (buscar_veiculo(estacionamento, veiculo->id) >= 0) {
        return ID_DUPLICADO;
    }
    if (!posicao_valida(veiculo->fileira, veiculo->coluna)) {
        return POSICAO_INVALIDA;
    }
    int *vaga = &estacionamento->mapa[veiculo->fileira][veiculo->coluna];
    if (*vaga) {
        return VAGA_OCUPADA;
    }
    if (estacionamento->quantidade == estacionamento->capacidade) {
        return SEM_ESPACO_NO_VETOR;
    }

    estacionamento->veiculos[estacionamento->quantidade++] = *veiculo;
    *vaga = 1;
    return OPERACAO_OK;
}

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
