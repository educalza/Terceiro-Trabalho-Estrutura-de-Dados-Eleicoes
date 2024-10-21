# Simulador de Urna Eletrônica - Trabalho de Estruturas de Dados

Este repositório contém um sistema desenvolvido em C que simula uma urna eletrônica para eleições de prefeitos. O projeto foi criado como parte do 3º Trabalho Computacional da disciplina de **Estrutura de Dados** no curso de **Ciência da Computação** da **Universidade Estadual do Norte do Paraná (UENP)**.

## Objetivo

O objetivo deste trabalho é praticar a lógica de programação e a implementação de estruturas de dados dinâmicas. O sistema permite cadastrar chapas, realizar a votação, apurar os resultados, e gerar boletins de eleição para o primeiro e segundo turno, caso necessário.

## Funcionalidades

- **Cadastro de Chapas**: Insere os dados de candidatos a prefeito e vice.
- **Votação**: Simula a votação para cada eleitor da cidade, contabilizando votos válidos, nulos e em branco.
- **Apuração**: Conta os votos de todas as chapas e decide se haverá segundo turno.
- **Geração de Boletins**: Cria arquivos de texto com os resultados do primeiro e segundo turnos, se aplicável.
- **Desempate**: Em caso de empate, o candidato mais velho vence.

## Estrutura de Dados Utilizada

Foi utilizada uma **lista dinâmica** (lista encadeada) para armazenar as chapas e os votos. As operações principais, como cadastro, votação e apuração, são realizadas através da manipulação desta lista.

## Arquivos

- `eleicoes.h`: Cabeçalhos e definições das funções e estruturas de dados.
- `eleicoes.c`: Implementação das funções principais (cadastrar chapas, votação, apuração, geração de boletins, etc.).
- `main.c`: Função principal que inicializa a simulação da urna eletrônica.
- `boletimPrimeiroTurno.txt`: Arquivo gerado com os resultados do primeiro turno.
- `boletimSegundoTurno.txt`: Arquivo gerado com os resultados do segundo turno (se necessário).

## Como Executar

1. Clone o repositório:

    ```bash
    git clone https://github.com/educalza/Terceiro-Trabalho-Estrutura-de-Dados-Eleicoes.git
    ```

2. Compile o código:

    ```bash
    gcc main.c eleicoes.c -o eleicoes
    ```

3. Execute o programa:

    ```bash
    ./eleicoes
    ```

4. Insira o número de chapas e eleitores, e siga as instruções do programa para realizar a votação.

## Exemplos de Uso

### Cadastro de Chapas

Durante a execução do programa, o usuário deve cadastrar os candidatos informando:
- Nome do prefeito
- Número da chapa
- Data de nascimento
- Nome do vice-prefeito

### Votação

Cada eleitor pode escolher uma chapa para votar. Se o eleitor inserir:
- Número de uma chapa válida: o voto é computado para essa chapa.
- Zero: o voto é computado como **voto branco**.
- Número inválido: o voto é computado como **voto nulo**.

### Segundo Turno

Se nenhuma chapa obtiver mais de 50% + 1 dos votos válidos, o programa realizará um segundo turno entre as duas chapas mais votadas.

### Boletins de Votação

Após a apuração, o programa gera dois arquivos de texto:
- `boletimPrimeiroTurno.txt`: com o resultado do primeiro turno.
- `boletimSegundoTurno.txt`: com o resultado do segundo turno (se houver).

## Contribuição

Sinta-se à vontade para fazer um fork deste projeto, abrir issues ou pull requests para melhorias ou correções.

## Licença

Este projeto está sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.

---

Trabalho desenvolvido por **Eduardo Alves Calza** sob orientação do professor **Rafael de Lima Aguiar**.

Outubro, 2024.