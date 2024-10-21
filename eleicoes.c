#include "eleicoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

typedef struct votos{
    int votosNulo;
    int votosBranco;
    int votosValidos;
} Votos;

void simulaUrnaVotacao(){

    Chapa *C = NULL, *chapaAux;
    Lista *lst = NULL;

    chapaAux = (Chapa*)malloc(sizeof(Chapa));
    if(chapaAux==NULL) exit(1);

    int qntChapas, qntEleitores;
    printf("------------- URNA -------------\n\n\n");
    printf("| Numero de chapas a ser cadastradas:  ");
    for(int i=0; i<1; i++){
        scanf("%d", &qntChapas);
        if(qntChapas > 99 || qntChapas < 1){
            printf("O maximo de chapas eh 99, digite um numero entre 1 a 99");
            i=0;
        }
    }
    printf("\n| Numero de eleitores da cidade: ");
    scanf("%d", &qntEleitores); printf("|");
    system("pause");
    system("cls");

    int i=0;
    while(i<qntChapas){
        i++;
        printf("------------- URNA -------------\n\n\n");
        printf(" [1] CADASTRAR CHAPA\n [2] CANCELAR INSCRICAO DE UMA CHAPA\n [3] CANCELAR INSCRICOES\n [4] SAIR\n");
        int opcao = 0;
        scanf("%d", &opcao);
        switch (opcao){
        case 1:
            system("cls");
            printf("------------- CADASTRO DE CHAPA -------------\n\n\n");
            printf("Nome Prefeito: ");
            fflush(stdin);
            fgets(chapaAux->nomePrefeito, NOME, stdin);

            int numeroInvalido = 0;
            printf("Numero: ");
            scanf("%d", &chapaAux->numero);
            for(Lista *aux = lst; aux!=NULL; aux=aux->prox){
                if(aux->C->numero == chapaAux->numero){
                    printf("Por favor, digite um numero ainda nao utilizado.\n");
                    numeroInvalido = 1;
                }
            }
            if(chapaAux->numero < 1 || chapaAux->numero > 99){
                printf("Por favor, digite um numero entre 1 e 99.\n");
                numeroInvalido = 1;
            }

            if(!numeroInvalido){
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
            } else{
                i--;
                system("pause");
                break;
            }
        case 2:
            printf("Cancelando uma unica inscricao de chapa\n");
            system("pause");
            system("cls");
            break;
        case 3:
            printf("Cancelando inscricao chapas\n");
            i=qntChapas;
            system("pause");
            system("cls");
            break;
        case 4:
            printf("Saindo...\n");
            system("pause");
            system("cls");
            exit(0);
        default:
            printf("Digite uma opcao valida.\n");
            system("pause");
            system("cls");
            i--;
            break;
        }
        if(i<=qntChapas){
            printf("Limite de chapas alcancado.\n");
            system("cls");
        }
    }

    printf("\n");

    votarEmChapa(lst, qntEleitores);

    free(chapaAux);
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



void votarEmChapa(Lista *lst, int qntEleitores){

    FILE *fp_boletimPrimeiroTurno = fopen("boletimPrimeiroTurno.txt", "w");
    FILE *fp_boletimSegundoTurno = fopen("boletimSegundoTurno.txt", "w");
    if(fp_boletimPrimeiroTurno == NULL) exit(1);
    if(fp_boletimSegundoTurno == NULL) exit(1);

    Lista *p = lst;
    Votos *v = (Votos*) malloc(sizeof(Votos));
    if(v == NULL) exit(1);
    v->votosNulo = 0; v->votosBranco = 0; v->votosValidos = 0;

    int i=1;
    if(p->prox!=NULL){ // Verifica se há pelo menos 2 candidatos
        while(i<=qntEleitores){
            printf("------------- VOTACAO -------------\n\n\n");
            printf("Escolha seu candidato.\n\n");
            imprimeCandidatosLista(lst);
            int opcao=0;
            scanf("%d", &opcao);
            contarVotos(lst, opcao, v);
            system("pause");
            system("cls");
            i++;
        }
        gerarBoletim(lst, fp_boletimPrimeiroTurno, v, qntEleitores);

        if(qntEleitores<10){
            Lista *candidato1 = NULL, *candidato2 = NULL;
            for(Lista *p = lst; p != NULL; p = p->prox){
                if(candidato1 == NULL || p->C->votosValidos > candidato1->C->votosValidos){
                    candidato2 = candidato1;
                    candidato1 = p;
                } else if(candidato2 == NULL || p->C->votosValidos > candidato2->C->votosValidos){
                    candidato2 = p;
                }
            }
            if(candidato1->C->votosValidos > candidato2->C->votosValidos){
                fprintf(fp_boletimPrimeiroTurno, "Candidato a prefeito %s com vice %s ganhou a eleicao com %d votos\n", 
                candidato1->C->nomePrefeito, candidato1->C->nomeVice, candidato1->C->votosValidos);
                }
            else if(candidato1->C->votosValidos < candidato2->C->votosValidos){
                fprintf(fp_boletimPrimeiroTurno, "Candidato a prefeito %s com vice %s ganhou a eleicao com %d votos\n", 
                candidato2->C->nomePrefeito, candidato2->C->nomeVice, candidato2->C->votosValidos);
                } 
            else if(candidato1->C->votosValidos == candidato2->C->votosValidos){
                    candidatoMaisVelho(candidato1->C, candidato2->C, fp_boletimPrimeiroTurno);
                }
            }

        int turno = 2;
        Lista *candidato1 = NULL;
        for (Lista *p = lst; p != NULL; p = p->prox){
            if (p->C->votosValidos > v->votosValidos / 2){
                candidato1 = p;
                turno = 1;
                break;
            }
        }
        if(turno == 1){
            fprintf(fp_boletimPrimeiroTurno, "Candidato a prefeito %s com vice %s ganhou a eleicao com %d votos\n", 
                candidato1->C->nomePrefeito, candidato1->C->nomeVice, candidato1->C->votosValidos);
        }

        Lista *listaSegundoTurno = NULL;
        if(qntEleitores>10){
            if(turno == 2){
                fprintf(fp_boletimPrimeiroTurno, "SEGUNDO TURNO NECESSARIO.\n");
                printf("Iniciando segundo turno...\n");
                system("pause"); system("cls");

                listaSegundoTurno = limparListaSegundoTurno(lst);
                Votos *v = (Votos*) malloc(sizeof(Votos));
                v->votosBranco = 0; v->votosNulo = 0; v->votosValidos = 0;


                /*segundo turno*/
                i=1;
                while(i<=qntEleitores){
                    printf("------------- VOTACAO -------------\n\n\n");
                    printf("Escolha seu candidato.\n\n");
                    imprimeCandidatosLista(listaSegundoTurno);
                    int opcao=0;
                    scanf("%d", &opcao);
                    contarVotos(listaSegundoTurno, opcao, v);
                    system("pause");
                    system("cls");
                    i++;
                }
                
                gerarBoletim(listaSegundoTurno, fp_boletimSegundoTurno, v, qntEleitores);
                if(listaSegundoTurno->C->votosValidos == listaSegundoTurno->prox->C->votosValidos){
                    candidatoMaisVelho(listaSegundoTurno->C, listaSegundoTurno->prox->C, fp_boletimSegundoTurno);
                } else if(listaSegundoTurno->C->votosValidos > listaSegundoTurno->prox->C->votosValidos){
                    fprintf(fp_boletimSegundoTurno, "Candidato a prefeito %s com vice %s ganhou a eleicao com %d votos\n", 
                listaSegundoTurno->C->nomePrefeito, listaSegundoTurno->C->nomeVice, listaSegundoTurno->C->votosValidos);
                } else{
                    fprintf(fp_boletimSegundoTurno, "Candidato a prefeito %s com vice %s ganhou a eleicao com %d votos\n", 
                listaSegundoTurno->prox->C->nomePrefeito, listaSegundoTurno->prox->C->nomeVice, listaSegundoTurno->prox->C->votosValidos);
                }
                liberarLista(listaSegundoTurno);
            }
        } 
    }

    liberarLista(lst);
    fclose(fp_boletimPrimeiroTurno);
    fclose(fp_boletimSegundoTurno);
    }



void contarVotos(Lista *lst, int votacao, Votos *v){
    if(votacao == 0){
        v->votosNulo++;
    }
    else{
        Lista *p;
        for(p=lst; p!=NULL; p=p->prox){
            if(p->C->numero == votacao){
                p->C->votosValidos += 1;
                v->votosValidos++;
                p->C->nomePrefeito[strcspn(p->C->nomePrefeito, "\n")] = '\0';
                p->C->nomeVice[strcspn(p->C->nomeVice, "\n")] = '\0';
                printf("Voce votou no prefeito %s, com vice %s!!\n\n", p->C->nomePrefeito, p->C->nomeVice);
                break;
            }
        }
        if(p == NULL){
            v->votosBranco++;
        }
    }
}



Lista *limparListaSegundoTurno(Lista *lst){
    if(lst->prox == NULL){
        return NULL;
    }

    Lista *candidato1 = NULL, *candidato2 = NULL;
    
    // Encontrar os dois candidatos com mais votos
    for(Lista *p = lst; p != NULL; p = p->prox){
        if(candidato1 == NULL || p->C->votosValidos > candidato1->C->votosValidos){
            candidato2 = candidato1;
            candidato1 = p;
        } else if(candidato2 == NULL || p->C->votosValidos > candidato2->C->votosValidos){
            candidato2 = p;
        }
    }

    // Criar nova lista com cópias profundas dos candidatos
    Lista *novoSegundoTurno = NULL;

    Chapa *copiaChapa1 = (Chapa*)malloc(sizeof(Chapa));
    if(copiaChapa1 == NULL) exit(1);
    *copiaChapa1 = *candidato1->C; // Copia os dados da chapa

    Chapa *copiaChapa2 = (Chapa*)malloc(sizeof(Chapa));
    if(copiaChapa2 == NULL) exit(1);
    *copiaChapa2 = *candidato2->C; // Copia os dados da chapa

    copiaChapa1->votosValidos = 0;
    copiaChapa2->votosValidos = 0;
    novoSegundoTurno = insereChapaLista(copiaChapa2, novoSegundoTurno);
    novoSegundoTurno = insereChapaLista(copiaChapa1, novoSegundoTurno);

    return novoSegundoTurno;
}



void gerarBoletim(Lista *lst, FILE *boletimPrimeiroTurno, Votos *v, int qntEleitores){

    if(lst == NULL) return;

    for(Lista *p=lst; p!=NULL; p=p->prox){
        p->C->nomePrefeito[strcspn(p->C->nomePrefeito, "\n")] = '\0';
        p->C->nomeVice[strcspn(p->C->nomeVice,"\n")]='\0';
        float porcentagemVotosCadaChapa;
        porcentagemVotosCadaChapa = (p->C->votosValidos*100)/v->votosValidos;
        fprintf(boletimPrimeiroTurno, "Prefeito: %s  %d\nVice: %s\nVOTOS: %d\nPORCENTAGEM DE VOTOS: %.2f\n\n",
        p->C->nomePrefeito, p->C->numero, p->C->nomeVice, p->C->votosValidos, porcentagemVotosCadaChapa);
    }
    int votosTotais = v->votosBranco+v->votosNulo+v->votosValidos;
    fprintf(boletimPrimeiroTurno, "VOTOS NULOS: %d\nVOTOS BRANCOS: %d\nVOTOS VALIDOS: %d\nVOTOS TOTAIS: %d\n\n", 
    v->votosNulo, v->votosBranco, v->votosValidos, votosTotais);
    
    float porcentagemVotosValidos = (v->votosValidos*100)/votosTotais;
    float porcentagemVotosNulos = (v->votosNulo*100)/votosTotais;
    float porcentagemVotosBrancos = (v->votosBranco*100)/votosTotais;
    fprintf(boletimPrimeiroTurno, "PORCENTAGEM VOTOS VALIDOS: %.2f\nPORCENTAGEM VOTOS NULOS: %.2f\nPORCENTAGEM VOTOS BRANCOS: %.2f\n\n", 
    porcentagemVotosValidos, porcentagemVotosNulos, porcentagemVotosBrancos);
}



void imprimeCandidatosLista(Lista* lst){
    for(Lista *p = lst; p != NULL; p = p->prox){
        p->C->nomePrefeito[strcspn(p->C->nomePrefeito, "\n")] = '\0';
        p->C->nomeVice[strcspn(p->C->nomeVice, "\n")]='\0';
        printf("Prefeito %s %d\nVice %s\n\n", p->C->nomePrefeito, p->C->numero, p->C->nomeVice);
    }
}



void candidatoMaisVelho(Chapa *cand1, Chapa *cand2, FILE *fp_boletim){
    Chapa *maisVelho = cand1;

    if (cand2->DataDeNascimento[0] < cand1->DataDeNascimento[0]){
        maisVelho = cand2;
    } else if (cand2->DataDeNascimento[0] == cand1->DataDeNascimento[0]){
        if (cand2->DataDeNascimento[1] < cand1->DataDeNascimento[1]){
            maisVelho = cand2;
        } else if (cand2->DataDeNascimento[1] == cand1->DataDeNascimento[1]){
            if (cand2->DataDeNascimento[2] < cand1->DataDeNascimento[2]){
                maisVelho = cand2;
            }
        }
    }

    fprintf(fp_boletim, "Candidato a prefeito %s com vice %s ganhou a eleicao com %d votos por ser mais velho\n",
            maisVelho->nomePrefeito, maisVelho->nomeVice, maisVelho->votosValidos);
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