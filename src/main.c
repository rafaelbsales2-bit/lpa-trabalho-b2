#include "estacionamento.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static bool ler_id(char id[ID_TAMANHO + 1])
{
    char linha[ID_TAMANHO + 3];
    if (!ler_linha("Identificador: ", linha, sizeof linha) || strlen(linha) != ID_TAMANHO) {
        puts("Identificador inválido. Digite 7 letras ou dígitos.");
        return false;
    }

    for (int i = 0; i < ID_TAMANHO; ++i) {
        char caractere = linha[i];
        if (caractere >= 'a' && caractere <= 'z') {
            caractere = (char)toupper((unsigned char)caractere);
        }
        if ((caractere < 'A' || caractere > 'Z') && (caractere < '0' || caractere > '9')) {
            puts("Identificador inválido. Use apenas letras de A a Z e dígitos.");
            return false;
        }
        id[i] = caractere;
    }
    id[ID_TAMANHO] = '\0';
    return true;
}

static bool ler_descricao(char descricao[DESCRICAO_MAXIMA + 1])
{
    char linha[DESCRICAO_MAXIMA + 3];
    if (!ler_linha("Descrição: ", linha, sizeof linha)
        || linha[0] == '\0' || strlen(linha) > DESCRICAO_MAXIMA) {
        puts("Descrição inválida. Digite de 1 a 60 caracteres.");
        return false;
    }
    strcpy(descricao, linha);
    return true;
}

static bool ler_categoria(int *categoria)
{
    if (!ler_inteiro("Categoria (1 = carro, 2 = moto): ", categoria)
        || (*categoria != CARRO && *categoria != MOTO)) {
        puts("Categoria inválida.");
        return false;
    }
    return true;
}

static bool ler_posicao(int *fileira, int *coluna)
{
    int numero_fileira;
    int numero_coluna;
    if (!ler_inteiro("Fileira (1 a 4): ", &numero_fileira)
        || numero_fileira < 1 || numero_fileira > FILEIRAS) {
        puts("Fileira inválida.");
        return false;
    }
    if (!ler_inteiro("Coluna (1 a 5): ", &numero_coluna)
        || numero_coluna < 1 || numero_coluna > COLUNAS) {
        puts("Coluna inválida.");
        return false;
    }
    *fileira = numero_fileira - 1;
    *coluna = numero_coluna - 1;
    return true;
}

static void cadastrar(Estacionamento *estacionamento)
{
    Veiculo veiculo = {0};
    if (!ler_id(veiculo.id) || !ler_descricao(veiculo.descricao)
        || !ler_categoria(&veiculo.categoria) || !ler_posicao(&veiculo.fileira, &veiculo.coluna)) {
        return;
    }

    switch (cadastrar_veiculo(estacionamento, &veiculo)) {
    case OPERACAO_OK:
        printf("Veículo %s cadastrado em F%d/C%d.\n",
               veiculo.id, veiculo.fileira + 1, veiculo.coluna + 1);
        break;
    case ID_DUPLICADO:
        puts("Identificador já cadastrado.");
        break;
    case VAGA_OCUPADA:
        puts("Vaga ocupada.");
        break;
    case POSICAO_INVALIDA:
        puts("Posição inválida.");
        break;
    case ESTACIONAMENTO_LOTADO:
        puts("Estacionamento lotado.");
        break;
    case SEM_MEMORIA:
        puts("Erro ao ampliar a coleção. Cadastro cancelado.");
        break;
    }
}

static const char *nome_categoria(int categoria)
{
    return categoria == CARRO ? "Carro" : "Moto";
}

static void exibir_veiculo(const Veiculo *veiculo)
{
    printf("%s | %s | %s | F%d/C%d\n", veiculo->id, veiculo->descricao,
           nome_categoria(veiculo->categoria), veiculo->fileira + 1, veiculo->coluna + 1);
}

static int selecionar_veiculo(const Estacionamento *estacionamento)
{
    char id[ID_TAMANHO + 1];
    if (!ler_id(id)) {
        return -1;
    }

    int indice = buscar_veiculo(estacionamento, id);
    if (indice < 0) {
        puts("Veículo não localizado.");
    }
    return indice;
}

static void consultar(const Estacionamento *estacionamento)
{
    int indice = selecionar_veiculo(estacionamento);
    if (indice >= 0) {
        exibir_veiculo(&estacionamento->veiculos[indice]);
    }
}

static void atualizar(Estacionamento *estacionamento)
{
    int indice = selecionar_veiculo(estacionamento);
    if (indice < 0) {
        return;
    }

    int escolha;
    if (!ler_inteiro("Alterar 1 = descrição, 2 = categoria, 3 = ambas: ", &escolha)
        || escolha < 1 || escolha > 3) {
        puts("Opção de atualização inválida.");
        return;
    }

    Veiculo revisado = estacionamento->veiculos[indice];
    if ((escolha == 1 || escolha == 3) && !ler_descricao(revisado.descricao)) {
        return;
    }
    if ((escolha == 2 || escolha == 3) && !ler_categoria(&revisado.categoria)) {
        return;
    }
    estacionamento->veiculos[indice] = revisado;
    printf("Veículo %s atualizado.\n", revisado.id);
}

static void listar(const Estacionamento *estacionamento)
{
    if (estacionamento->quantidade == 0) {
        puts("Nenhum veículo cadastrado.");
        return;
    }

    for (int indice = 0; indice < estacionamento->quantidade; ++indice) {
        exibir_veiculo(&estacionamento->veiculos[indice]);
    }
}

static void exibir_menu(void)
{
    puts("\nSistema de Gestão de Estacionamento");
    puts("1 - Cadastrar veículo");
    puts("2 - Consultar veículo por identificador");
    puts("3 - Atualizar descrição ou categoria");
    puts("6 - Listar veículos cadastrados");
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
        case 1:
            cadastrar(&estacionamento);
            break;
        case 2:
            consultar(&estacionamento);
            break;
        case 3:
            atualizar(&estacionamento);
            break;
        case 6:
            listar(&estacionamento);
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
