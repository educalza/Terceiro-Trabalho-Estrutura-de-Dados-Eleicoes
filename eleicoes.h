#ifndef ELEICOES_H_INCLUDED
#define ELEICOES_H_INCLUDED

#include <stdio.h>

typedef struct chapa Chapa;

typedef struct lista Lista;

void simulaUrnaVotacao();

Chapa *cadastrarChapas(char *nomePrefeito, int numero, int *data_nascimento, char *nomeVice);

Lista *insereChapaLista(Chapa *C, Lista *lst);

void imprimeCandidatosLista(Lista* lst);

void votarCandidatoDaChapa(Lista *lst, int votacao, int *votosNulo, int *votosBranco);

void gerarBoletim(Lista *lst, FILE *boletimPrimeiroTurno, int votosNulos, int votosBrancos);

#endif // ESTOQUE_H_INCLUDED