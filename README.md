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

## Testes executados

Cada caso começa em uma nova sessão. Nas coordenadas abaixo, F indica
fileira e C indica coluna. Os identificadores são fictícios.

| Caso | Entrada ou operação | Resultado esperado | Resultado observado | Situação |
| --- | --- | --- | --- | --- |
| T01 · Vazio | Opções 6, 7 e 8 logo após abrir o programa | Lista vazia, 20 vagas livres e ocupação de 0,00% | Lista vazia, mapa livre e relatório com 0,00% | Aprovado |
| T02 · Cadastro | Cadastre ABC1D23, Carro azul, categoria 1, F1/C1. Consulte com abc1d23 e use 6 e 7 | Consulta e lista mostram o veículo, mapa marca F1/C1 | Registro exibido nas duas operações e F1/C1 ocupada | Aprovado |
| T03 · Duplicidade | Após T02, tente cadastrar abc1d23, Moto, categoria 2, F2/C1 | Cadastro recusado. F2/C1 segue livre | Aviso de ID duplicado e apenas F1/C1 ocupada | Aprovado |
| T04 · Vaga e limites | Após T02, tente cadastrar XYZ9K87 em F1/C1 e tente LPA2026 com F5 ou C6 | As três tentativas são recusadas e o mapa segue igual | Avisos de vaga ocupada, fileira inválida e coluna inválida. Uma vaga ocupada | Aprovado |
| T05 · Crescimento | Cadastre ABC1D23 em F1/C1, XYZ9K87 em F1/C2 e LPA2026 em F4/C5. Use 6, 7 e 8 | O terceiro cadastro amplia o vetor inicial de dois elementos, preservando os primeiros registros | Três registros, três vagas ocupadas e 15,00% | Aprovado |
| T06 · Atualização | Após T02, opção 3 para ABC1D23. Escolha alterar ambos, digite Moto de entrega e categoria 3. Repita com categoria 2 | A primeira tentativa preserva todos os campos. A segunda altera descrição e categoria | Primeira tentativa recusada sem mudança. Após a segunda, um registro em F1/C1, com a nova descrição e categoria Moto | Aprovado |
| T07 · Movimento | Cadastre ABC1D23 em F1/C1 e XYZ9K87 em F1/C2. Tente mover ABC1D23 para F1/C2, F1/C1 e F2/C3, nessa ordem | Destino ocupado recusado. Mesma vaga preservada. Última tentativa libera F1/C1 e ocupa F2/C3 | Avisos para as duas primeiras tentativas. F1/C2 e F2/C3 ocupadas, relatório de 10,00% | Aprovado |
| T08 · Remoção | Após T05, remova XYZ9K87 e tente consultá-lo. Use 6, 7 e 8 | ID ausente, F1/C2 livre e dois registros restantes | Consulta retornou não localizado. Mapa e relatório indicaram duas vagas ocupadas | Aprovado |
| T09 · Lotação | Cadastre CAR0001 até CAR0020 na ordem das vagas, alternando categorias 1 e 2. Tente cadastrar CAR0021 em F1/C1 | A 21ª tentativa é recusada por lotação. Relatório com 20 ocupadas e 0 livres | Lotação informada, 100,00% de ocupação, 10 carros e 10 motos | Aprovado |
| T10 · Encerramento | Execute a versão com sanitizadores, cadastre três veículos e escolha 0 | Sessão encerra e libera o vetor ampliado | Sessão encerrada sem diagnóstico de vazamento ou erro de memória | Aprovado |
| Extra · Descrição | Cadastre um veículo com descrição de 60 caracteres acentuados. Tente outro com 61 | Primeiro cadastro aceito com descrição inteira. Segundo recusado | O primeiro texto foi preservado e apenas uma vaga ficou ocupada | Aprovado |
| Extra · Falha de realocação | Simule `realloc` retornando `NULL` no terceiro cadastro | Terceiro cadastro cancelado. Dois registros e o mapa preservados | Erro de ampliação informado, dois registros e duas vagas ocupadas | Aprovado |

Para repetir T10 em Linux com GCC, compile com os sanitizadores habilitados:

```sh
gcc -std=c11 -Wall -Wextra -pedantic -g -fsanitize=address,undefined \
    -fno-omit-frame-pointer -no-pie src/main.c src/estacionamento.c -o estacionamento
ASAN_OPTIONS=detect_leaks=1 ./estacionamento
```

## Responsabilidades e integração

Rafael desenvolveu o menu e o mapa na branch `estrutura-e-menu`, o
cadastro e a coleção dinâmica na `cadastro-e-colecao` e a consulta,
listagem e edição na `consulta-e-atualizacao`.

Matheus desenvolveu a movimentação e a remoção na branch
`movimentacao-e-remocao`. Implementou o relatório de ocupação e as
correções de percentual e validação UTF-8 na `relatorio-e-correcoes`.
Registrou a documentação final, os testes e as evidências na
`documentacao-e-testes`.

Cada integrante fez os commits de suas tarefas nas branches indicadas
antes de integrá-los à `main` por fast-forward. Essa integração
preservou o histórico linear. No GitHub, as branches de cada integrante
foram publicadas no mesmo momento em que os respectivos commits
chegaram à `main` e continuam disponíveis para conferência.

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

Trabalhei na movimentação de vagas, na remoção de veículos, no relatório de ocupação, nas correções de formatação do percentual e de validação UTF-8 da descrição, na documentação do projeto e no registro dos testes da versão integrada. Usei o Gemini como apoio na correção de erros, organização do código e revisão dos arquivos README, e utilizei o Gemini para analisar os códigos em C em busca de eventuais erros de sintaxe ou de lógica, além de estudar melhorias de desempenho e boas práticas visando aprendizado e aperfeiçoamento para códigos futuros.

**Análise de desempenho e boas práticas.** Pedi uma avaliação do código em C com foco em desempenho, clareza e explicações sobre possíveis melhorias.

> irei mandar um codigo que fiz e quero que voce me auxilie visando o melhor desempenho e a melhor forma de escrever ele, caso aja alguma coisa que seria bom alterar, me explique como e por que

[Ver a conversa sobre desempenho e boas práticas](docs/evidencias/analise-desempenho-codigo.jpg).

**Revisão de sintaxe, lógica e desempenho.** Pedi que a IA analisasse o código em C para alertar sobre eventuais erros de sintaxe ou de lógica e indicar pontos de melhoria de desempenho para aprendizado em projetos futuros.

> analise esse codigo e caso possua algum erro de sintaxe ou logica me alerte. procure tambem como melhorar o desempenho dele e o que eu poderia ter feito melhor

[Ver a conversa sobre sintaxe, lógica e desempenho](docs/evidencias/revisao-sintaxe-logica-codigo.jpg). 
