#ifndef ESTACIONAMENTO_H
#define ESTACIONAMENTO_H

#include <stdbool.h>

enum { FILEIRAS = 4, COLUNAS = 5, TOTAL_VAGAS = FILEIRAS * COLUNAS };

enum { ID_TAMANHO = 7, DESCRICAO_MAXIMA = 60 };
enum { CARRO = 1, MOTO = 2 };

typedef struct {
    char id[ID_TAMANHO + 1];
    char descricao[DESCRICAO_MAXIMA + 1];
    int categoria;
    int fileira;
    int coluna;
} Veiculo;

typedef struct {
    Veiculo *veiculos;
    int quantidade;
    int capacidade;
    int mapa[FILEIRAS][COLUNAS];
} Estacionamento;

bool iniciar_estacionamento(Estacionamento *estacionamento);
void encerrar_estacionamento(Estacionamento *estacionamento);
void exibir_mapa(const Estacionamento *estacionamento);

#endif
