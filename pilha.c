#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cores.h"

/*====================================================
      PILHA (STACK)- SiISTEMA QUE DESFAZ O CONTROL Z
======================================================*/

/*
 * ESTRUTURA DO NÓ DA PILHA (STACK)
 * A pilha funciona no modelo LIFO (Último a Entrar, Primeiro a Sair).
 * Cada ação realizada no editor de texto aponta para a ação que aconteceu
 * imediatamente ANTES dela (por isso chamamos o ponteiro de *abaixo).
 */
typedef struct Acao {

    char descricao[50];
    struct Acao *abaixo;

} Acao;

void limparBuffer() {
    while(getchar() != '\n');
}

/* Trava para garantir que a descrição não seja apenas um número ou uma letra.
 * Exige pelo menos dois caracteres válidos (letras ou números).
 */
int acaoValida(char *descricao) {
    int contagem = 0;
    for(int i = 0; descricao[i] != '\0'; i++) {
        if(isalnum(descricao[i])) {
            contagem++;
        }
    }
    return (contagem >= 2); 
}

// Adiciona uma nova ação no topo da pilha.
void realizarAcao(Acao **topo, char descricao[]) {

    Acao *nova;

    nova = (Acao*) malloc(sizeof(Acao));

    if(nova == NULL){

        printf(COR_VERMELHA "\nErro de memoria!\n" COR_RESET);
        return;

    }

    strcpy(nova->descricao, descricao);

    nova->abaixo = *topo;

    *topo = nova;

    printf(COR_VERDE "\nAcao registrada com sucesso!\n" COR_RESET);

}

// Remove a ação que está no topo da pilha.
void desfazerAcao(Acao **topo) {

    Acao *aux;

    if(*topo == NULL) {

        printf(COR_AMARELA "\nHistorico vazio.\n" COR_RESET);
        return;
    }

    aux = *topo;

    *topo = (*topo)->abaixo;

    printf(COR_CIANO "\nAcao desfeita: %s\n" COR_RESET, aux->descricao);

    free(aux);
}

void mostrarUltimaAcao(Acao *topo) {

    if(topo == NULL) {

        printf(COR_AMARELA "\nHistorico vazio.\n" COR_RESET);

    }

    else{

        printf(COR_VERDE "\nUltima acao:\n");
        printf("%s\n" COR_RESET, topo->descricao);
    }
}

void mostrarHistorico(Acao *topo) {

    int i = 1;

    if(topo == NULL) {

        printf(COR_AMARELA "\nHistorico vazio.\n" COR_RESET);

        return;
    }

    printf(COR_CIANO);
    printf("\n=========================================\n");
    printf("           HISTORICO DE ACOES\n");
    printf("=========================================\n");

    while(topo != NULL) {

        printf("%d - %s\n", i, topo->descricao);

        topo = topo->abaixo;

        i++;
    }

    printf("=========================================\n");

    printf(COR_RESET);
}

void limparHistorico(Acao **topo) {

    Acao *aux;

    if(*topo == NULL){

        printf(COR_AMARELA "\nHistorico vazio.\n" COR_RESET);

        return;
    }

    while(*topo != NULL){

        aux = *topo;

        *topo = (*topo)->abaixo;

        free(aux);        
    }

    printf(COR_VERDE "\nHistorico apagado com sucesso!\n" COR_RESET);

}

int main() {

    Acao *historico = NULL;

    int opcao;

    char descricao[50];

    do {

        printf(COR_AZUL);
        printf("\n===================================================\n");
        printf("                   EDITOR DE TEXTO                \n");
        printf("===================================================\n");
        printf("| 1 - Realizar acao                               |\n");
        printf("| 2 - Desfazer ultima acao                        |\n");
        printf("| 3 - Mostrar ultima acao                         |\n");
        printf("| 4 - Exibir historico                            |\n");
        printf("| 5 - Limpar historico                            |\n");
        printf("| 0 - Sair                                        |\n");
        printf("===================================================\n");
        printf("Escolha uma opcao: ");
        printf(COR_RESET);

        if(scanf("%d", &opcao) != 1){

            printf(COR_VERMELHA "\nOpcao invalida!\n" COR_RESET);

            limparBuffer();

            continue;
        }

        limparBuffer();

        switch(opcao) {

            case 1:

                printf("\nDigite a descricao da acao: ");

                fgets(descricao, sizeof(descricao), stdin);

                descricao[strcspn(descricao, "\n")] = '\0';

                if(!acaoValida(descricao)) {

                    printf(COR_VERMELHA "\nA descricao e muito curta. Evite usar apenas uma letra ou numero.\n" COR_RESET);
                }
                else{

                    realizarAcao(&historico, descricao);
                }

                break;

            case 2:

                desfazerAcao(&historico);

                break;

            case 3:

                mostrarUltimaAcao(historico);

                break;

            case 4:

                mostrarHistorico(historico);

                break;

            case 5:

                limparHistorico(&historico);

                break;

            case 0:

                printf(COR_VERDE "\nEncerrando o editor...\n" COR_RESET);

                break;

            default:

                printf(COR_VERMELHA "\nOpcao invalida!\n" COR_RESET);
        }

    } while(opcao != 0);

    limparHistorico(&historico);

    return 0;
}