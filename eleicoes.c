#include "eleicoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 99
#define NOME 50

typedef struct chapa{
    char nomePrefeito[NOME];
    int numero;
    int DataDeNascimento[3];

    char nomeVice[NOME];

    int votacao;
} Chapa;

typedef struct lista{
    Chapa *C;
    struct lista *prox;
} Lista;

void simulaUrnaVotacao(){

    Chapa *C = NULL, *chapaAux;
    Lista *lst = NULL;

    FILE *fp_boletimPrimeiroTurno = fopen("boletim.txt", "w");
    if(fp_boletimPrimeiroTurno == NULL) exit(1);
    

    int *nEleitores, *nChapas;
    printf("Numero de eleitores da cidade: ");
    scanf("%d", &nEleitores);
    system("pause"); system("cls");

    printf("Numero de Chapas da cidade: ");
    scanf("%d", &nChapas);
    system("pause"); system("cls");



    printf("---------- Cadastro de chapas ----------\n");
    printf("Sistema de parada = 0\n\n");
    int count = 0;
    while(count < nChapas){
        printf("Prefeito\n");

        printf("Numero: ");
        scanf("%d", &chapaAux->numero);
        if(chapaAux->numero == 0){
            printf("Cadastro de chapa cancelado.\n");
            exit(0);
        }

        printf("Nome: ");
        fflush(stdin);
        fgets(chapaAux->nomePrefeito, NOME, stdin);

        printf("\nData de nascimento dia/mes/ano");
        for(int i=0; i<3; i++){
            scanf("%d%%d%d", chapaAux->DataDeNascimento[0], chapaAux->DataDeNascimento[1], chapaAux->DataDeNascimento[2]);
        }
        system("pause");
        system("cls");
        C = cadastrarChapas(chapaAux->nomePrefeito, chapaAux->numero, chapaAux->DataDeNascimento, chapaAux->nomeVice);
        lst = insereChapaLista(C, lst);
    }
    printf("\n-----------------------------------------\n");

    printf("---------- Votacao das Chapas ----------\n");
    printf("Candidatos... \n\n");
    imprimeCandidatosLista(lst);
    printf("\nDigite sua votacao: ");
    int *votacao;
    scanf("%d", &votacao);

}

Chapa *cadastrarChapas(char *nomePrefeito, int numero, int *data_nascimento, char *nomeVice){

    Chapa *novo = (Chapa*)malloc(sizeof(Chapa));
    if(novo == NULL) exit(1);

    strncpy(novo->nomePrefeito, nomePrefeito, NOME - 1);
    novo->nomePrefeito[NOME-1] = '\0';

    novo->numero = numero;
    for(int i=0; i<3; i++){
        novo->DataDeNascimento[i] = data_nascimento[i];
    }
    strncpy(novo->nomeVice, nomeVice, NOME - 1);
    novo->nomeVice[NOME - 1] = '\0';

    novo->votacao = 0;

    return novo;
}

Lista *insereChapaLista(Chapa *C, Lista *lst){

    Lista *novo = (Lista*)malloc(sizeof(Lista));
    if(novo == NULL) exit(1);

    novo->C = C;
    novo->prox = lst;
    fprinf("%s %d\n%s\n\n", novo->C->nomePrefeito, novo->C->numero, novo->C->nomeVice);
    return novo;
}


void imprimeCandidatosLista(Lista* lst){
    for(Lista *p = lst; p != NULL; p = p->prox){
        printf("Prefeito %s %d\nVice %s\n\n", lst->C->nomePrefeito, lst->C->numero, lst->C->nomeVice);
    }
}

Lista *votarCandidatoDaChapa(int *votacao, Lista *lst, int *qntChapa){

    Lista *aux = NULL;
    for(int i = 0; i<qntChapa; i++){
        int count = 0;
        for(Lista *p = lst; p=!NULL; p=p->prox){
            if(votacao == p->C->numero){
                aux = p;
                break;
            }
        }
    }
    return aux->C->votacao;
}