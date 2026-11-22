#ifndef ESTACIONAMENTO_H
#define ESTACIONAMENTO_H

enum { FILEIRAS = 4, COLUNAS = 5, TOTAL_VAGAS = FILEIRAS * COLUNAS };

typedef struct {
    int mapa[FILEIRAS][COLUNAS];
} Estacionamento;

void exibir_mapa(const Estacionamento *estacionamento);

#endif
