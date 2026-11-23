# Sistema de Gestão de Estacionamento

Lógica de Programação e Algoritmos, 2026/2, trabalho do 2º bimestre.

Projeto de terminal em C para controlar veículos e vagas de um estacionamento
fictício. Os dados pertencem à sessão em execução.

## Compilação e execução

```sh
gcc -std=c11 -Wall -Wextra -pedantic src/main.c src/estacionamento.c -o estacionamento
./estacionamento
```

## Integrantes

- [Rafael Bastos Sales](https://github.com/rafaelbsales2-bit)
- [Matheus Campelo Teles](https://github.com/mcxmpxlxt)

## Uso de IA

### Rafael Bastos Sales

Trabalhei no menu, no mapa de vagas, na coleção dinâmica, no cadastro, na consulta, na listagem e na atualização dos veículos. Usei o OpenAI Codex para revisar o código e o README. Revisei as sugestões e incorporei as correções com pequenas mudanças para manter a organização e o comportamento que eu queria para o programa. Não adaptei código de fontes externas.

**Revisão do código.** Pedi uma revisão de legibilidade e de possíveis erros nos arquivos C.

> Organize o meus códigos de maneira profissional para facilitar a leitura e indique erros caso existam. Não aplique as alterações diretamente aos arquivos originais.

A revisão apontou que a descrição era limitada a 60 bytes. Em UTF-8, isso fazia o cadastro rejeitar até uma descrição com 31 letras “á”. Matheus corrigiu a contagem de caracteres acentuados numa versão posterior do programa. [Ver a conversa sobre o código](docs/evidencias/revisao-do-codigo.png).

**Revisão do README.** Pedi ajuda com a formatação e aproveitei as sugestões para organizar os comandos de compilação e execução e a identificação dos integrantes.

> Formate o README de maneira profissional.

[Ver a conversa sobre o README](docs/evidencias/formatacao-do-readme.png).
