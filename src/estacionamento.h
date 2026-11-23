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

typedef enum {
    OPERACAO_OK,
    ID_DUPLICADO,
    POSICAO_INVALIDA,
    VAGA_OCUPADA,
    ESTACIONAMENTO_LOTADO,
    SEM_MEMORIA
} Resultado;

typedef enum {
    MOVIMENTO_OK,
    DESTINO_INVALIDO,
    MESMA_VAGA,
    DESTINO_OCUPADO
} ResultadoMovimentacao;

ResultadoMovimentacao mover_veiculo(Estacionamento *estacionamento, int indice,
                                    int fileira, int coluna);
void remover_veiculo(Estacionamento *estacionamento, int indice);
int buscar_veiculo(const Estacionamento *estacionamento, const char *id);
Resultado cadastrar_veiculo(Estacionamento *estacionamento, const Veiculo *veiculo);
bool iniciar_estacionamento(Estacionamento *estacionamento);
void encerrar_estacionamento(Estacionamento *estacionamento);
void exibir_mapa(const Estacionamento *estacionamento);
void exibir_relatorio(const Estacionamento *estacionamento);

#endif
