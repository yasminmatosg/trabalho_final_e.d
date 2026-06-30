#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cores.h"

/*==============================================================
    LISTA SIMPLISMENTE ENCADEADA - SISTEMA DE PLAYLIST DE MÚSICA
================================================================*/

/*
 * ESTRUTURA DO NÓ DA LISTA SIMPLES:
 * Cada música aponta apenas para a *próxima* música.
 */
typedef struct Musica {

    char nome[50];
    struct Musica *proxima;

} Musica;

void limparBuffer() {

    int c;

    while((c = getchar()) != '\n' && c != EOF);
}

/* Trava para garantir que a música tenha pelo menos uma letra ou número,
 * impedindo cadastros com apenas espaços em branco ou símbolos.
 */
int nomeMusicaValido(char *nome) {
    for(int i = 0; nome[i] != '\0'; i++) {
        if(isalnum(nome[i])) { 
            return 1;
        }
    }
    return 0;
}

//Insere uma música no final da playlist.
void adicionarMusica(Musica **inicio, char nome[]) {

    Musica *nova;
    Musica *aux;

    nova = (Musica*)malloc(sizeof(Musica));

    if(nova == NULL){

        printf(COR_VERMELHA "\nErro de memoria.\n" COR_RESET);
        return;
    }

    strcpy(nova->nome, nome);

    nova->proxima = NULL;

    if(*inicio == NULL) {

        *inicio = nova;
    }

    else{

        aux = *inicio;

        while(aux->proxima != NULL) {

            aux = aux->proxima;
        }

        aux->proxima = nova;
    }

    printf(COR_VERDE "\nMusica adicionada com sucesso!\n" COR_RESET);
}

void removerMusica(Musica **inicio, char nome[]) {

    Musica *atual;
    Musica *anterior;

    if(*inicio == NULL) {

        printf(COR_AMARELA "\nPlaylist vazia.\n" COR_RESET);

        return;
    }

    atual = *inicio;
    anterior = NULL;

    while(atual != NULL && strcmp(atual->nome, nome) != 0) {

        anterior = atual;
        atual = atual -> proxima;
    }

    if(atual == NULL){

        printf(COR_VERMELHA "\nMusica nao encontrada.\n" COR_RESET);

        return;
    }

    if(anterior == NULL) {

        *inicio = atual -> proxima;
    }

    else {

        anterior -> proxima = atual -> proxima;
    }

    free(atual);

    printf(COR_VERDE "\nMusica removida com sucesso!\n" COR_RESET);

}

void buscarMusica(Musica *inicio, char nome[]) {

    while(inicio != NULL) {

        if(strcmp(inicio -> nome, nome) == 0) {

            printf(COR_VERDE "\nMusica encontrada!\n" COR_RESET);

            return;
        }

        inicio = inicio -> proxima;
    }

    printf(COR_VERMELHA "\nMusica nao encontrada.\n" COR_RESET);
}

// Mostra todas as músicas cadastradas.
void exibirPlaylist(Musica *inicio) {

    int i = 1;

    if(inicio == NULL){

        printf(COR_AMARELA "\nPlaylist vazia.\n" COR_RESET);

        return;

    }

    printf(COR_CIANO);

    printf("\n=========================================\n");
    printf("            PLAYLIST\n");
    printf("=========================================\n");

    while(inicio != NULL){

        printf("%d - %s\n", i, inicio -> nome);

        inicio = inicio -> proxima;

        i++;
    }

    printf("=========================================\n");

    printf(COR_RESET);
}

// Conta quantas músicas existem na playlist.
void contarMusicas(Musica *inicio) {

    int contador = 0;

    while(inicio != NULL) {

        contador++;

        inicio = inicio -> proxima;
    }

    printf(COR_VERDE "\nQuantidade de musicas: %d\n" COR_RESET, contador);
}

// Libera toda a memória utilizada.
void limparPlaylist(Musica **inicio) {

    Musica *aux;

    while(*inicio != NULL) {

        aux = *inicio;

        *inicio = (*inicio) -> proxima;

        free(aux);
    }

    printf(COR_VERDE "\nPlaylist limpa com sucesso!\n" COR_RESET);
}

int main() {

    Musica *playlist = NULL;

    int opcao;

    char nome[50];

    do {

        printf(COR_AZUL);
        printf("\n===================================================\n");
        printf("            PLAYLIST DE MUSICAS                    \n");
        printf("===================================================\n");
        printf("| 1 - Adicionar musica                            |\n");
        printf("| 2 - Remover musica                              |\n");
        printf("| 3 - Buscar musica                               |\n");
        printf("| 4 - Exibir playlist                             |\n");
        printf("| 5 - Contar musicas                              |\n");
        printf("| 6 - Limpar playlist                             |\n");
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

        switch(opcao){

            case 1:

                printf("\nNome da musica: ");

                fgets(nome, sizeof(nome), stdin);

                nome[strcspn(nome, "\n")] = '\0';

                if(!nomeMusicaValido(nome)) {

                    printf(COR_VERMELHA "\nNome invalido! Evite usar apenas espacos em branco ou simbolos.\n" COR_RESET);
                }

                else{

                    adicionarMusica(&playlist, nome);
                }

                break;

            case 2:

                if(playlist == NULL) {

                    printf(COR_AMARELA "\nPlaylist vazia.\n" COR_RESET);

                    break;
                }

                printf("\nNome da musica para remover: ");

                fgets(nome, sizeof(nome), stdin);

                nome[strcspn(nome, "\n")] = '\0';

                removerMusica(&playlist, nome);

                break;

            case 3:

                if(playlist == NULL) {

                    printf(COR_AMARELA "\nPlaylist vazia.\n" COR_RESET);

                    break;
                }

                printf("\nNome da musica para buscar: ");

                fgets(nome, sizeof(nome), stdin);

                nome[strcspn(nome, "\n")] = '\0';

                buscarMusica(playlist, nome);

                break;

            case 4:

                exibirPlaylist(playlist);

                break;

            case 5:

                contarMusicas(playlist);

                break;

            case 6:

                limparPlaylist(&playlist);

                break;

            case 0:

                printf(COR_VERDE "\nEncerrando o programa...\n" COR_RESET);

                break;

            default:

                printf(COR_VERMELHA "\nOpcao invalida!\n" COR_RESET);
        }

    } while(opcao != 0);

    limparPlaylist(&playlist);

    return 0;
}