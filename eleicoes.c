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

    chapaAux = (Chapa*)malloc(sizeof(Chapa));
    if(chapaAux==NULL) exit(1);

    FILE *fp_boletimPrimeiroTurno = fopen("boletim.txt", "w");
    if(fp_boletimPrimeiroTurno == NULL) exit(1);

    int qntChapas, qntEleitores;
    printf("------------- URNA -------------\n\n\n");
    printf("| Numero de chapas a ser cadastradas:  ");
    scanf("%d", &qntChapas); printf("|");
    printf("\n| Numero de eleitores da cidade: ");
    scanf("%d", &qntEleitores); printf("|");
    system("pause");
    system("cls");

    int i=0;
    while(i<qntChapas){
        i++;
        printf("------------- URNA -------------\n\n\n");
        printf(" [1] CADASTRAR CHAPA\n [2] SAIR\n");
        int opcao = 0;
        scanf("%d", &opcao);
        switch (opcao){
        case 1:
            system("cls");
            printf("------------- CADASTRO DE CHAPA -------------\n\n\n");
            printf("Nome Prefeito: ");
            fflush(stdin);
            fgets(chapaAux->nomePrefeito, NOME, stdin);

            printf("Numero: ");
            scanf("%d", &chapaAux->numero);

            printf("\nData de nascimento dia/mes/ano: ");
            for(int i=0; i<3; i++){
                scanf("%d", &chapaAux->DataDeNascimento[i]);
            }

            printf("Nome Vice-Prefeito: ");
            fflush(stdin);
            fgets(chapaAux->nomeVice, NOME, stdin);
            C = cadastrarChapas(chapaAux->nomePrefeito, chapaAux->numero, chapaAux->DataDeNascimento, chapaAux->nomeVice);
            lst = insereChapaLista(C, lst);
            system("pause");
            system("cls");
            break;
        
        case 2:
            printf("Saindo...\n");
            system("pause");
            system("cls");
            break;
        default:
            printf("Digite uma opcao.\n");
            system("pause");
            system("cls");
            break;
        }
        if(i<=qntChapas){
            printf("Limite de chapas alcancado.\n");
            system("cls");
        }
    }

    printf("\n");
    i=1;
    while(i<=qntEleitores){
        printf("------------- VOTACAO -------------\n\n\n");
        printf("Escolha seu candidato.\n\n");
        imprimeCandidatosLista(lst);
        int opcao=0;
        scanf("%d", &opcao);
        lst = votarCandidatoDaChapa(lst, opcao);
        system("pause");
        system("cls");
        i++;
    }
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
    return novo;
}


void imprimeCandidatosLista(Lista* lst){
    for(Lista *p = lst; p != NULL; p = p->prox){
        p->C->nomePrefeito[strcspn(p->C->nomePrefeito, "\n")] = '\0';
        p->C->nomeVice[strcspn(p->C->nomeVice, "\n")] = '\0';
        printf("Prefeito %s %d\nVice %s\n\n", p->C->nomePrefeito, p->C->numero, p->C->nomeVice);
    }
}

Lista *votarCandidatoDaChapa(Lista *lst, int votacao){

    Lista *p;
    for(p=lst; p!=NULL; p=p->prox){
        if(p->C->numero == votacao){
            p->C->votacao += 1;
            break;
        }
    }
    return p;
}

void gerarBoletim(Lista *lst, FILE *boletimPrimeiroTurno){
    for(Lista *p=lst; p!=NULL; p=p->prox){
        fprintf(boletimPrimeiroTurno, "Prefeito: %s   %d\nVice: %s\nVOTOS: %d", p->C->nomePrefeito, p->C->numero, p->C->nomeVice, p->C->votacao);
    }
}