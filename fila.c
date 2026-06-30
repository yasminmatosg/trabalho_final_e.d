#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cores.h"

/*=======================================================
          FILA - FILA DE IMPRESSÃO DE DOCS
========================================================*/

/*
 * ESTRUTURA DO NÓ E DA FILA (QUEUE)
 * A Fila usa o conceito FIFO (Primeiro a Entrar, Primeiro a Sair).
 * Criamos o nó do 'Documento' e uma estrutura especial 'Impressora'.
 * A 'Impressora' guarda DOIS ponteiros: um para o início da fila (frente)
 * e outro para o final (tras). Isso deixa a inserção muito mais rápida.
 */
typedef struct Documento{

    char nomeArquivo[50];
    struct Documento *proximo;

}Documento;

/*
    Estrutura da fila.
    A fila possui um ponteiro para o primeiro
    documento (frente) e outro para o último
    documento (tras).
*/
typedef struct{

    Documento *frente;
    Documento *tras;

}Impressora;

void limparBuffer(){

    while(getchar() != '\n');
}

//Inicializa a fila vazia.
void inicializarImpressora(Impressora *imp){

    imp->frente = NULL;
    imp->tras = NULL;
}

// Adiciona um documento ao final da fila.
void enviarParaImpressao(Impressora *imp, char nome[]) {

    Documento *novo;

    novo = (Documento*) malloc(sizeof(Documento));

    if(novo == NULL){

        printf(COR_VERMELHA "\nErro de memoria!\n" COR_RESET);

        return;
    }

    strcpy(novo->nomeArquivo, nome);

    novo->proximo = NULL;

    if(imp->frente == NULL) {

        imp->frente = novo;
        imp->tras = novo;
    }

    else {

        imp -> tras -> proximo = novo;

        imp -> tras = novo;
    }

    printf(COR_VERDE "\nDocumento enviado para impressao!\n" COR_RESET);

}

void imprimirProximo(Impressora *imp) {

    Documento *aux;

    if(imp->frente == NULL) {

        printf(COR_AMARELA "\nFila vazia.\n" COR_RESET);

        return;
    }

    aux = imp -> frente;

    imp -> frente = imp -> frente -> proximo;

    if(imp->frente == NULL) {

        imp->tras = NULL;
    }

    printf(COR_CIANO "\nImprimindo: %s\n" COR_RESET, aux -> nomeArquivo);

    free(aux);
}

//Mostra o primeiro documento da fila./
void mostrarProximo(Impressora *imp) {

    if(imp -> frente == NULL){

        printf(COR_AMARELA "\nFila vazia.\n" COR_RESET);
    }

    else{

        printf(COR_VERDE "\nProximo documento:\n");

        printf("%s\n" COR_RESET, imp -> frente -> nomeArquivo);
    }
}

void mostrarFila(Impressora *imp){

    Documento *aux;

    int i = 1;

    if(imp->frente == NULL) {

        printf(COR_AMARELA "\nFila vazia.\n" COR_RESET);

        return;

    }

    aux = imp->frente;

    printf(COR_CIANO);

    printf("\n=========================================\n");
    printf("         FILA DE IMPRESSAO\n");
    printf("=========================================\n");

    while(aux != NULL) {

        printf("%d - %s\n", i, aux -> nomeArquivo);

        aux = aux->proximo;

        i++;
    }

    printf("=========================================\n");

    printf(COR_RESET);
}

void limparFila(Impressora *imp) {

    Documento *aux;

    if(imp -> frente == NULL) {

        printf(COR_AMARELA "\nFila vazia.\n" COR_RESET);

        return;
    }

    while(imp -> frente != NULL) {

        aux = imp -> frente;

        imp -> frente = imp -> frente->proximo;

        free(aux);
    }

    imp -> tras = NULL;

    printf(COR_VERDE "\nFila limpa com sucesso!\n" COR_RESET);

}

int main(){

    Impressora fila;

    inicializarImpressora(&fila);

    int opcao;

    char arquivo[50];

    do{

        printf(COR_AZUL);
        printf("\n===================================================\n");
        printf("             FILA DE IMPRESSAO\n");
        printf("===================================================\n");
        printf("| 1 - Enviar documento                            |\n");
        printf("| 2 - Imprimir proximo documento                  |\n");
        printf("| 3 - Mostrar proximo documento                   |\n");
        printf("| 4 - Exibir fila                                 |\n");
        printf("| 5 - Limpar fila                                 |\n");
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

                printf("\nNome do documento: ");

                fgets(arquivo, sizeof(arquivo), stdin);

                arquivo[strcspn(arquivo, "\n")] = '\0';

                if(strlen(arquivo) == 0){

                    printf(COR_VERMELHA "\nO nome do documento nao pode ficar vazio.\n" COR_RESET);
                }
                else{

                    enviarParaImpressao(&fila, arquivo);
                }

                break;

            case 2:

                imprimirProximo(&fila);

                break;

            case 3:

                mostrarProximo(&fila);

                break;

            case 4:

                mostrarFila(&fila);

                break;

            case 5:

                limparFila(&fila);

                break;

            case 0:

                printf(COR_VERDE "\nEncerrando a impressora...\n" COR_RESET);

                break;

            default:

                printf(COR_VERMELHA "\nOpcao invalida!\n" COR_RESET);
        }

    }while(opcao != 0);

    limparFila(&fila);

    return 0;
}