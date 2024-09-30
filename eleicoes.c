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
    int votosValidos;
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

    FILE *fp_boletimPrimeiroTurno = fopen("boletimPrimeiroTurno.txt", "w");
    FILE *fp_boletimSegundoTurno = fopen("boletimSegundoTurno.txt", "w");
    if(fp_boletimPrimeiroTurno == NULL) exit(1);
    if(fp_boletimSegundoTurno == NULL) exit(1);

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
            break;
        case 2:
            printf("Saindo...\n");
            system("pause");
            system("cls");
            break;
        default:
            printf("Digite uma opcao valida.\n");
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
    int votosNulo = 0, votosBranco = 0, votosValidos = 0;
    while(i<=qntEleitores){
        printf("------------- VOTACAO -------------\n\n\n");
        printf("Escolha seu candidato.\n\n");
        imprimeCandidatosLista(lst);
        int opcao=0;
        scanf("%d", &opcao);
        votarCandidatoDaChapa(lst, opcao, &votosNulo, &votosBranco, &votosValidos);
        system("pause");
        system("cls");
        i++;
    }

    int segundoTurno;
    segundoTurno = gerarBoletim(lst, fp_boletimPrimeiroTurno, votosNulo, votosBranco, votosValidos, qntEleitores);


    system("pause"); system("cls");
    printf("Segundo turno iniciando...\n");
    system("pause"); system("cls");
    limparListaSegundoTurno(&lst);
    if(segundoTurno){
        i=1;
        int votosNulo = 0, votosBranco = 0, votosValidos = 0;
        while(i<=qntEleitores){
            printf("------------- VOTACAO -------------\n\n\n");
            printf("Escolha seu candidato.\n\n");
            imprimeCandidatosLista(lst);
            int opcao=0;
            scanf("%d", &opcao);
            votarCandidatoDaChapa(lst, opcao, &votosNulo, &votosBranco, &votosValidos);
            system("pause");
            system("cls");
            i++;
        }
    }

    int boletimSegundoTurno;
    boletimSegundoTurno = gerarBoletim(lst, fp_boletimSegundoTurno, votosNulo, votosBranco, votosValidos, qntEleitores);

    fclose(fp_boletimPrimeiroTurno);
    fclose(fp_boletimSegundoTurno);
    free(chapaAux);
    liberarLista(lst);
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

    novo->votosValidos = 0;

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
        p->C->nomeVice[strcspn(p->C->nomeVice, "\n")]='\0';
        printf("Prefeito %s %d\nVice %s\n\n", p->C->nomePrefeito, p->C->numero, p->C->nomeVice);
    }
}

void votarCandidatoDaChapa(Lista *lst, int votacao, int *votosNulo, int *votosBranco, int *votosValidos){

    if(votacao == 0){
        (*votosNulo)++;
    }
    else{
        Lista *p;
        for(p=lst; p!=NULL; p=p->prox){
            if(p->C->numero == votacao){
                p->C->votosValidos += 1;
                (*votosValidos)++;
                p->C->nomePrefeito[strcspn(p->C->nomePrefeito, "\n")] = '\0';
                p->C->nomeVice[strcspn(p->C->nomeVice, "\n")] = '\0';
                printf("Voce votou no prefeito %s, com vice %s!!\n\n", p->C->nomePrefeito, p->C->nomeVice);
                break;
            }
        }
        if(p == NULL){
            (*votosBranco)++;
        }
    }
}

int gerarBoletim(Lista *lst, FILE *boletimPrimeiroTurno, int votosNulos, int votosBrancos, int votosValidos, int qntEleitores){
    for(Lista *p=lst; p!=NULL; p=p->prox){
        p->C->nomePrefeito[strcspn(p->C->nomePrefeito, "\n")] = '\0';
        p->C->nomeVice[strcspn(p->C->nomeVice,"\n")]='\0';
        float porcentagemVotosCadaChapa;
        porcentagemVotosCadaChapa = (p->C->votosValidos*100)/votosValidos;
        fprintf(boletimPrimeiroTurno, "Prefeito: %s  %d\nVice: %s\nVOTOS: %d\nPORCENTAGEM DE VOTOS: %.2f\n\n", p->C->nomePrefeito, p->C->numero, p->C->nomeVice, p->C->votosValidos, porcentagemVotosCadaChapa);
    }
    int votosTotais = votosBrancos+votosNulos+votosValidos;
    fprintf(boletimPrimeiroTurno, "VOTOS NULOS: %d\nVOTOS BRANCOS: %d\nVOTOS VALIDOS: %d\nVOTOS TOTAIS: %d\n\n", votosNulos, votosBrancos, votosValidos, votosTotais);
    
    float porcentagemVotosValidos = (votosValidos*100)/votosTotais;
    float porcentagemVotosNulos = (votosNulos*100)/votosTotais;
    float porcentagemVotosBrancos = (votosBrancos*100)/votosTotais;
    fprintf(boletimPrimeiroTurno, "PORCENTAGEM VOTOS VALIDOS: %.2f\nPORCENTAGEM VOTOS NULOS: %.2f\nPORCENTAGEM VOTOS BRANCOS: %.2f\n\n", porcentagemVotosValidos, porcentagemVotosNulos, porcentagemVotosBrancos);
    
    if (votosValidos > 0 && qntEleitores > 10) {
        Lista *candidatoGanho = NULL;
        for (Lista *p = lst; p != NULL; p = p->prox) {
            if (p->C->votosValidos > votosValidos / 2) {
                candidatoGanho = p;
                break;
            }
        }
        if(candidatoGanho){
            fprintf(boletimPrimeiroTurno, "\nSEM SEGUNDO TURNO\n");
            fprintf(boletimPrimeiroTurno, "Prefeito %s com Vice %s Eleito a prefeito da cidade!!\n\n", candidatoGanho->C->nomePrefeito, candidatoGanho->C->nomeVice);
            return 0;
        }else{
            fprintf(boletimPrimeiroTurno, "\nSEGUNDO TURNO NECESSARIO.\n");
            Lista *aux = lst->prox;
            for(Lista *p = lst; p!=NULL; p=p->prox){
                if(aux->C->votosValidos < p->C->votosValidos){
                    aux = p;
                }
            }
            return 1;
        }
    }
}

void limparListaSegundoTurno(Lista **lst) {
    if (*lst == NULL || (*lst)->prox == NULL) {
        return;
    }

    Lista *primeiro = NULL, *segundo = NULL;

    for (Lista *p = *lst; p != NULL; p = p->prox) {
        if (primeiro == NULL || p->C->votosValidos > primeiro->C->votosValidos) {
            segundo = primeiro;
            primeiro = p;
        } else if (segundo == NULL || p->C->votosValidos > segundo->C->votosValidos) {
            segundo = p;
        }
    }

    Lista *ant = NULL, *p = *lst;
    while (p != NULL) {
        Lista *prox = p->prox;
        if (p != primeiro && p != segundo) {
            if (ant == NULL) {
                *lst = prox;
            } else {
                ant->prox = prox;
            }
            free(p->C);
            free(p);
        } else {
            ant = p;
        }
        p = prox;
    }
}


void liberarLista(Lista *lst){
    Lista *p = lst, *aux = NULL;
    while(p!=NULL){
        aux = p->prox;
        free(p->C);
        free(p);
        p = aux;
    }
}