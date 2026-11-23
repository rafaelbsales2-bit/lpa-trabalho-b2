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
        int nova_capacidade = estacionamento->capacidade * 2;
        Veiculo *ampliado = realloc(estacionamento->veiculos, nova_capacidade * sizeof *ampliado);
        if (ampliado == NULL) {
            return SEM_MEMORIA;
        }
        estacionamento->veiculos = ampliado;
        estacionamento->capacidade = nova_capacidade;
    }

    estacionamento->veiculos[estacionamento->quantidade++] = *veiculo;
    *vaga = 1;
    return OPERACAO_OK;
}

ResultadoMovimentacao mover_veiculo(Estacionamento *estacionamento, int indice,
                                    int fileira, int coluna)
{
    if (!posicao_valida(fileira, coluna)) {
        return DESTINO_INVALIDO;
    }

    Veiculo *veiculo = &estacionamento->veiculos[indice];
    if (fileira == veiculo->fileira && coluna == veiculo->coluna) {
        return MESMA_VAGA;
    }
    if (estacionamento->mapa[fileira][coluna]) {
        return DESTINO_OCUPADO;
    }

    estacionamento->mapa[veiculo->fileira][veiculo->coluna] = 0;
    estacionamento->mapa[fileira][coluna] = 1;
    veiculo->fileira = fileira;
    veiculo->coluna = coluna;
    return MOVIMENTO_OK;
}

void remover_veiculo(Estacionamento *estacionamento, int indice)
{
    Veiculo *veiculo = &estacionamento->veiculos[indice];
    estacionamento->mapa[veiculo->fileira][veiculo->coluna] = 0;

    for (int i = indice + 1; i < estacionamento->quantidade; ++i) {
        estacionamento->veiculos[i - 1] = estacionamento->veiculos[i];
    }
    --estacionamento->quantidade;
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

void exibir_relatorio(const Estacionamento *estacionamento)
{
    int ocupadas = 0;
    for (int fileira = 0; fileira < FILEIRAS; ++fileira) {
        for (int coluna = 0; coluna < COLUNAS; ++coluna) {
            ocupadas += estacionamento->mapa[fileira][coluna];
        }
    }

    int carros = 0;
    for (int indice = 0; indice < estacionamento->quantidade; ++indice) {
        if (estacionamento->veiculos[indice].categoria == CARRO) {
            ++carros;
        }
    }
    int motos = estacionamento->quantidade - carros;
    double percentual = 100.0 * ocupadas / TOTAL_VAGAS;

    printf("\nTotal de vagas: %d\n", TOTAL_VAGAS);
    printf("Vagas ocupadas: %d\n", ocupadas);
    printf("Vagas livres: %d\n", TOTAL_VAGAS - ocupadas);
    printf("Ocupação: %.2f%%\n", percentual);
    printf("Carros: %d\nMotos: %d\n", carros, motos);
}
