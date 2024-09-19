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
} Chapa;

typedef struct lista{
    Chapa *C;
    struct lista *prox;
} Lista;

void simulaUrnaVotacao(){

    Chapa *C = (Chapa*)malloc(sizeof(Chapa));
    if(C == NULL){
        printf("Erro de alocacao.\n");
        exit(1);
    }

    Lista *lst = (Lista*)malloc(sizeof(Lista));
    if(lst == NULL){
        printf("Erro de alocacao.\n");
        exit(1);
    }

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
    C = cadastrarChapas(nChapas);
    lst = insereChapaLista(C, lst);


}

Chapa *cadastrarChapas(int *nChapas){
    Chapa *novo = (Chapa*)malloc(sizeof(Chapa));
    if(novo == NULL) exit(1);

    int count = 0;
    while(count < nChapas){

        printf("Prefeito\n");

        printf("Numero: ");
        scanf("%d", &novo->numero);
        if(novo->numero == 0){
            printf("Cadastro de chapa cancelado.\n");
            exit(0);
        }
        
        printf("Nome: ");
        fflush(stdin);
        fgets(novo->nomePrefeito, NOME, stdin);

        printf("\nData de nascimento dia/mes/ano");
        for(int i=0; i<3; i++){
            scanf("%d%%d%d", novo->DataDeNascimento[0], novo->DataDeNascimento[1], novo->DataDeNascimento[2]);
        }
        return novo;
        system("cls");
    }
    return 0;
}

Lista *insereChapaLista(Chapa *C, Lista *lst){

    Lista *novo = (Lista*)malloc(sizeof(Lista));
    if(novo == NULL) exit(1);

    novo->C = C;
    novo->prox = lst;
    fprinf("%s %d\n%s\n\n", novo->C->nomePrefeito, novo->C->numero, novo->C->nomeVice);
    return novo;
}