/*
 * Autor: Eduardo Alves Calza
 * GitHub: https://github.com/educalza
 * Data: 28 de setembro de 2024

 * Descrição: Este projeto simula uma eleição para o cargo de prefeito utilizando a linguagem C.
 * O programa permite o cadastro de chapas com candidatos e seus vices, além de realizar a votação,
 * contabilizando votos válidos, brancos e nulos. 
 * Ele também implementa a lógica de dois turnos de acordo com as regras eleitorais,
 * incluindo o critério de desempate pela idade dos candidatos. 
 * O boletim de urna é salvo em um arquivo após cada turno, apresentando as estatísticas detalhadas da eleição. 
 * O foco do projeto está no uso adequado de estruturas de dados, com análise da complexidade temporal de cada função no relatório final.
 * A estrutura de dados escolhida para realizar o projeto foi a Lista dinâmica, por ser mais fácil e rápida de usar.
 */


#include <stdio.h>
#include "eleicoes.h"

int main(){
    simulaUrnaVotacao();
    return 0;
}