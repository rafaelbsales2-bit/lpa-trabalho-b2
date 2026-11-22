#include "estacionamento.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool ler_linha(const char *pergunta, char linha[], size_t capacidade)
{
    fputs(pergunta, stdout);
    fflush(stdout);

    size_t usados = 0;
    bool invalida = false;
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
        if (caractere == '\0' || usados == capacidade - 1) {
            invalida = true;
        } else {
            linha[usados++] = (char)caractere;
        }
    }

    if (caractere == '\n' && usados > 0 && linha[usados - 1] == '\r') {
        --usados;
    }
    linha[usados] = '\0';
    return !invalida && (caractere != EOF || usados > 0);
}

static bool ler_inteiro(const char *pergunta, int *numero)
{
    char linha[64];
    if (!ler_linha(pergunta, linha, sizeof linha)) {
        return false;
    }

    char *fim;
    errno = 0;
    long valor = strtol(linha, &fim, 10);
    if (fim == linha || errno == ERANGE || valor < INT_MIN || valor > INT_MAX) {
        return false;
    }
    while (isspace((unsigned char)*fim)) {
        ++fim;
    }
    if (*fim != '\0') {
        return false;
    }

    *numero = (int)valor;
    return true;
}

static void exibir_menu(void)
{
    puts("\nSistema de Gestão de Estacionamento");
    puts("7 - Exibir mapa de vagas");
    puts("0 - Encerrar");
}

int main(void)
{
    Estacionamento estacionamento;
    if (!iniciar_estacionamento(&estacionamento)) {
        fputs("Erro ao reservar memória para os veículos.\n", stderr);
        return EXIT_FAILURE;
    }

    bool executando = true;
    while (executando && !feof(stdin) && !ferror(stdin)) {
        int opcao;
        exibir_menu();
        if (!ler_inteiro("Opção: ", &opcao)) {
            if (!feof(stdin) && !ferror(stdin)) {
                puts("Opção inválida.");
            }
            continue;
        }

        switch (opcao) {
        case 7:
            exibir_mapa(&estacionamento);
            break;
        case 0:
            executando = false;
            break;
        default:
            puts("Opção inválida.");
            break;
        }
    }

    encerrar_estacionamento(&estacionamento);
    puts("Sessão encerrada.");
    return 0;
}
