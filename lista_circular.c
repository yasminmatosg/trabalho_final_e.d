#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cores.h"

/*=======================================================
   LISTA CIRCULAR - TURNOS DE JOGO DE TABULEIRO
========================================================*/

/*
 * ESTRUTURA DA LISTA CIRCULAR
 * É idêntica à de uma lista simples encadeada (apenas um ponteiro para o próximo).
 * O "pulo do gato" dessa estrutura não está no nó, mas sim na lógica de amarração:
 * nós garantimos que NUNCA exista um ponteiro apontando para NULL no fim da lista.
 */
typedef struct Jogador {
    char nome[30];
    struct Jogador *proximo;
} Jogador;

//Remove caracteres restantes do teclado.
void limparBuffer() {
    while(getchar() != '\n');
}

// Trava para exigir letras ou números no nome
int nomeValido(char *nome) {
    for(int i = 0; nome[i] != '\0'; i++) {
        if(isalnum(nome[i])) { 
            return 1; // Retorna 1 se achar pelo menos um caractere alfanumérico
        }
    }
    return 0;
}

void adicionarJogador(Jogador **inicio, char nome[]) {
    Jogador *novo;
    Jogador *ultimo;

    novo = (Jogador*) malloc(sizeof(Jogador));

    if(novo == NULL) {
        printf(COR_VERMELHA "\nErro de memoria!\n" COR_RESET);
        return;
    }

    strcpy(novo->nome, nome);

    if(*inicio == NULL) {
        *inicio = novo;
        novo->proximo = novo;
    }
    else{
        ultimo = *inicio;
        while(ultimo->proximo != *inicio) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = novo;
        novo->proximo = *inicio;
    }
    printf(COR_VERDE "\nJogador adicionado com sucesso!\n" COR_RESET);
}

void removerJogador(Jogador **inicio, char nome[]) {
    Jogador *atual;
    Jogador *anterior;
    Jogador *ultimo;

    if(*inicio == NULL) {
        printf(COR_AMARELA "\nNao ha jogadores.\n" COR_RESET);
        return;
    }

    atual = *inicio;
    anterior = NULL;

    do {
        if(strcmp(atual->nome, nome) == 0) {
            if(atual == *inicio){
                if(atual->proximo == *inicio) {
                    free(atual);
                    *inicio = NULL;
                }
                else{
                    ultimo = *inicio;
                    while(ultimo->proximo != *inicio) {
                        ultimo = ultimo->proximo;
                    }
                    *inicio = atual->proximo;
                    ultimo->proximo = *inicio;
                    free(atual);
                }
            }
            else{
                anterior->proximo = atual->proximo;
                free(atual);
            }
            printf(COR_VERDE "\nJogador removido com sucesso!\n" COR_RESET);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    } while(atual != *inicio);

    printf(COR_VERMELHA "\nJogador nao encontrado.\n" COR_RESET);
}

void mostrarJogadores(Jogador *inicio) {
    Jogador *aux;
    int i = 1;

    if(inicio == NULL) {
        printf(COR_AMARELA "\nNenhum jogador cadastrado.\n" COR_RESET);
        return;
    }

    aux = inicio;
    printf(COR_CIANO);
    printf("\n=========================================\n");
    printf("            JOGADORES DA MESA\n");
    printf("=========================================\n");
    do {
        printf("%d - %s\n", i, aux->nome);
        aux = aux->proximo;
        i++;
    } while(aux != inicio);
    printf("=========================================\n");
    printf(COR_RESET);
}

// Percorre a lista circular durante a quantidade de rodadas informada.
void simularTurnos(Jogador *inicio, int rodadas) {
    Jogador *atual;
    int i;

    if(inicio == NULL) {
        printf(COR_AMARELA "\nNao existem jogadores.\n" COR_RESET);
        return;
    }
    if(rodadas <= 0) {
        printf(COR_VERMELHA "\nNumero de rodadas invalido.\n" COR_RESET);
        return;
    }

    atual = inicio;
    printf(COR_MAGENTA);
    printf("\n=========================================\n");
    printf("          SIMULACAO DE TURNOS\n");
    printf("=========================================\n");
    for(i = 1; i <= rodadas; i++){
        printf("Rodada %d -> %s\n", i, atual->nome);
        atual = atual->proximo;
    }
    printf("=========================================\n");
    printf(COR_RESET);
}

// Mostra quem inicia a rodada.
void passarTurno(Jogador **inicio) {
    if(*inicio == NULL) {
        printf(COR_AMARELA "\nNao ha jogadores na mesa.\n" COR_RESET);
    }
    else {
        *inicio = (*inicio)->proximo; // Avança o ponteiro principal
        printf(COR_VERDE "\nTurno passado! Agora e a vez de: %s\n" COR_RESET, (*inicio)->nome);
    }
}

// Remove todos os jogadores da lista.
void liberarLista(Jogador **inicio) {
    Jogador *aux;
    Jogador *ultimo;

    if(*inicio == NULL)
        return;

    ultimo = *inicio;
    while(ultimo->proximo != *inicio) {
        ultimo = ultimo->proximo;
    }
    ultimo->proximo = NULL;

    while(*inicio != NULL) {
        aux = *inicio;
        *inicio = (*inicio)->proximo;
        free(aux);
    }
}

int main() {
    Jogador *mesa = NULL;
    int opcao;
    int rodadas;
    char nome[30];

    do {
        printf(COR_AZUL);
        printf("\n===================================================\n");
        printf("                JOGO DE TABULEIRO                 \n");
        printf("===================================================\n");
        printf("| 1 - Adicionar jogador                           |\n");
        printf("| 2 - Remover jogador                             |\n");
        printf("| 3 - Mostrar jogadores                           |\n");
        printf("| 4 - Simular turnos                              |\n");
        printf("| 5 - Passar a vez (Proximo jogador)              |\n");
        printf("| 0 - Sair                                        |\n");
        printf("===================================================\n");
        printf("Escolha uma opcao: ");
        printf(COR_RESET);

        if(scanf("%d", &opcao) != 1) {
            printf(COR_VERMELHA "\nOpcao invalida!\n" COR_RESET);
            limparBuffer();
            continue;
        }
        limparBuffer();

        switch(opcao) {
            case 1:
                printf("\nNome do jogador: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                if(!nomeValido(nome)) {
                    printf(COR_VERMELHA "\nNome invalido! Utilize letras ou numeros.\n" COR_RESET);
                } else {
                    adicionarJogador(&mesa, nome);
                }
                break;

            case 2:
                if(mesa == NULL) {
                    printf(COR_AMARELA "\nNao existem jogadores.\n" COR_RESET);
                } else {
                    printf("\nNome do jogador: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    removerJogador(&mesa, nome);
                }
                break;

            case 3:
                mostrarJogadores(mesa);
                break;

            case 4:
                printf("\nQuantidade de rodadas: ");
                if(scanf("%d", &rodadas) != 1) {
                    printf(COR_VERMELHA "\nDigite um numero valido!\n" COR_RESET);
                    limparBuffer();
                } else {
                    limparBuffer();
                    simularTurnos(mesa, rodadas);
                }
                break;

            case 5:
                passarTurno(&mesa);
                break;

            case 0:
                printf(COR_VERDE "\nEncerrando o jogo...\n" COR_RESET);
                break;

            default:
                printf(COR_VERMELHA "\nOpcao invalida!\n" COR_RESET);
        }
    } while(opcao != 0);

    liberarLista(&mesa);
    return 0;
}