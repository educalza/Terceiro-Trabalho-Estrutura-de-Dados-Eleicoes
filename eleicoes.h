#ifndef ELEICOES_H_INCLUDED
#define ELEICOES_H_INCLUDED

#include <stdio.h>

typedef struct chapa Chapa;

typedef struct lista Lista;

typedef struct votos Votos;

void simulaUrnaVotacao();

Chapa *cadastrarChapas(char *nomePrefeito, int numero, int *data_nascimento, char *nomeVice);

Lista *insereChapaLista(Chapa *C, Lista *lst);

void imprimeCandidatosLista(Lista *lst);

void contarVotos(Lista *lst, int votacao, Votos *v);

void gerarBoletim(Lista *lst, FILE *boletimPrimeiroTurno, Votos *v, int qntEleitores);

Lista *limparListaSegundoTurno(Lista *lst);

void votarEmChapa(Lista *lst, int qntEleitores);

void liberarLista(Lista *lst);

#endif // ESTOQUE_H_INCLUDED