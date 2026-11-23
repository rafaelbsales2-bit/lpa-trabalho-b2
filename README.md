# Sistema de Gestão de Estacionamento

Lógica de Programação e Algoritmos, 2026/2, trabalho do 2º bimestre.

Programa C11 de terminal para um estacionamento fictício com quatro fileiras
e cinco colunas. Os veículos ficam em memória durante a sessão.

## Integrantes

- [Rafael Bastos Sales](https://github.com/rafaelbsales2-bit)
- [Matheus Campelo Teles](https://github.com/mcxmpxlxt)

## Compilação e execução

A partir da raiz do projeto, em um terminal com GCC:

```sh
gcc -std=c11 -Wall -Wextra -pedantic src/main.c src/estacionamento.c -o estacionamento
./estacionamento
```

O terminal deve usar UTF-8 para digitar e exibir descrições com acentos.

## Menu

| Opção | Operação |
| --- | --- |
| 1 | Cadastrar veículo em vaga livre |
| 2 | Consultar veículo por identificador |
| 3 | Atualizar descrição, categoria ou ambas |
| 4 | Mover veículo para outra vaga |
| 5 | Remover veículo e liberar sua vaga |
| 6 | Listar veículos cadastrados |
| 7 | Exibir mapa de vagas |
| 8 | Exibir relatório de ocupação |
| 0 | Encerrar e liberar memória |

Use sete letras ou dígitos para o identificador. Ele é convertido para
maiúsculas e permanece fixo depois do cadastro. A descrição aceita de 1 a 60
caracteres UTF-8. As categorias são 1 para carro e 2 para moto. Na tela,
fileiras vão de 1 a 4 e colunas de 1 a 5. Uma entrada inválida cancela a
operação em andamento e retorna ao menu.

## Estruturas e módulos

- `src/estacionamento.h` declara `Veiculo`, a struct `Estacionamento` e
  as operações. A matriz de inteiros 4 × 5 usa 0 para vaga livre e 1 para
  vaga ocupada. Cada veículo guarda identificador, descrição, categoria e
  posição com índices a partir de zero.
- `src/estacionamento.c` mantém o vetor dinâmico de veículos ativos e a
  matriz. O vetor começa com capacidade para dois veículos e duplica quando
  cheio. A quantidade indica quantos registros estão ativos. A capacidade
  indica quantos cabem no espaço reservado. Se `realloc` falhar, o
  cadastro é cancelado e o vetor anterior continua válido. O módulo também
  exibe o mapa e calcula o relatório.
- `src/main.c` controla o menu, valida entradas, normaliza identificadores,
  converte coordenadas e chama as operações. A atualização valida os campos
  em uma cópia antes de substituir o registro original.

## Responsabilidades e integração

Rafael - Trabalhei no menu e no mapa (`estrutura-e-menu`), no cadastro e
na coleção dinâmica (`cadastro-e-colecao`) e na consulta, listagem e edição
(`consulta-e-atualizacao`). As três branches foram integradas à `main`
por fast-forward.

Matheus - trabalhei na movimentação de vagas, na remoção de veículos, no
relatório de ocupação, na correção da formatação do percentual, na
validação UTF-8 da descrição, na documentação final e no registro dos
testes, integrando as etapas diretamente na `main`.

## Autoria, IA e referências

### Rafael Bastos Sales

Trabalhei no menu, no mapa de vagas, na coleção dinâmica, no cadastro, na consulta, na listagem e na atualização dos veículos. Usei o OpenAI Codex para revisar o código e o README. Revisei as sugestões e incorporei as correções com pequenas mudanças para manter a organização e o comportamento que eu queria para o programa. Não adaptei código de fontes externas.

**Revisão do código.** Pedi uma revisão de legibilidade e de possíveis erros nos arquivos C.

> Organize o meus códigos de maneira profissional para facilitar a leitura e indique erros caso existam. Não aplique as alterações diretamente aos arquivos originais.

A revisão apontou que a descrição era limitada a 60 bytes. Em UTF-8, isso fazia o cadastro rejeitar até uma descrição com 31 letras “á”. Matheus corrigiu essa validação. A descrição aceita até 60 caracteres UTF-8, inclusive quando há acentos. [Ver a conversa sobre o código](docs/evidencias/revisao-do-codigo.png).

**Revisão do README.** Pedi ajuda com a formatação e aproveitei as sugestões para organizar os comandos de compilação e execução e a identificação dos integrantes.

> Formate o README de maneira profissional.

[Ver a conversa sobre o README](docs/evidencias/formatacao-do-readme.png).

### Matheus Campelo Teles

Trabalhei na movimentação de vagas, na remoção de veículos, no relatório de ocupação, nas correções de formatação do percentual e de validação UTF-8 da descrição, na documentação do projeto e no registro dos testes da versão integrada. O OpenAI Codex auxiliou na correção de erros, na organização do código e na revisão dos arquivos README. Todo o conteúdo criado foi revisado por mim, Matheus Campelo Teles.
