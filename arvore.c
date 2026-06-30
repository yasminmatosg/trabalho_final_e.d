#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cores.h"

/*=======================================================
       ÁRVORE - SISTEMA DE ÍNDICE DE BIBLIOTECA
========================================================*/

typedef struct Livro {
    char isbn[20];
    char titulo[50];
    struct Livro *esquerda, *direita;
} Livro;

int validarISBN(char *isbn) {
    int len = strlen(isbn);
    if (len < 13 || len > 17) return 0; 
    
    int digitos = 0;
    for (int i = 0; i < len; i++) {
        if (isbn[i] >= '0' && isbn[i] <= '9') {
            digitos++;
        } else if (isbn[i] != '-') {
            return 0; // Rejeita letras e outros caracteres
        }
    }
    return (digitos == 13); // Confirma se tem exatamente 13 números
}

/* BUSCA (Logarítmica - O(log n)):
 * A lógica aqui é a "Divisão e Conquista". Como a árvore está ordenada,
 * a cada passo nós descartamos metade da árvore. Se o ISBN buscado for menor que a raiz,
 * o ponteiro do nó atual é descartado e seguimos apenas pela esquerda.
 */
Livro *buscar(Livro *raiz, char isbn[]) {
    if (raiz == NULL)
        return NULL;

    int cmp = strcmp(isbn, raiz->isbn);
    if (cmp == 0)
        return raiz;

    if (cmp < 0)
        return buscar(raiz->esquerda, isbn);

    return buscar(raiz->direita, isbn);
}

/* INSERÇÃO (Recursiva):
 * O malloc solicita um bloco de memória no HEAP. A verificação if(!novo) é nossa
 * blindagem contra estouro de memória. A recursão percorre a árvore até encontrar
 * um ponteiro NULL (espaço vazio), que é onde o novo nó será "pendurado".
 */
Livro *inserir(Livro *raiz, char isbn[], char titulo[]) {
    if (raiz == NULL) {
        Livro *novo = (Livro *)malloc(sizeof(Livro));
        if (novo == NULL) {
            printf(COR_VERMELHA "\nErro de memoria!\n" COR_RESET);
            return NULL;
        }
        strcpy(novo->isbn, isbn);
        strcpy(novo->titulo, titulo);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    int cmp = strcmp(isbn, raiz->isbn);
    if (cmp < 0) {
        raiz->esquerda = inserir(raiz->esquerda, isbn, titulo);
    }
    else if (cmp > 0) {
        raiz->direita = inserir(raiz->direita, isbn, titulo);
    } 
    else {
        printf(COR_AMARELA "\nISBN ja cadastrado!\n" COR_RESET);
    }
    return raiz;
}

/* REMOÇÃO:
 * Se o nó tiver 2 filhos, não podemos simplesmente deletar. Precisamos achar o
 * sucessor (o menor valor da subárvore da direita) para ocupar o lugar do nó deletado,
 * mantendo a propriedade de ordenação da BST. O 'free' libera a memória ocupada pelo nó deletado.
 */
Livro *remover(Livro *raiz, char isbn[]) {
    if (raiz == NULL)
        return NULL;

    int cmp = strcmp(isbn, raiz->isbn);
    if (cmp < 0) {
        raiz->esquerda = remover(raiz->esquerda, isbn);
    }
    else if (cmp > 0) {
        raiz->direita = remover(raiz->direita, isbn);
    } 
    else {
        if (raiz->esquerda == NULL) {
            Livro *aux = raiz->direita;
            free(raiz);
            return aux;
        }
        if (raiz->direita == NULL) {
            Livro *aux = raiz->esquerda;
            free(raiz);
            return aux;
        }

        Livro *aux = raiz->direita;
        while (aux->esquerda != NULL) {
            aux = aux->esquerda;
        }

        strcpy(raiz->isbn, aux->isbn);
        strcpy(raiz->titulo, aux->titulo);
        raiz->direita = remover(raiz->direita, aux->isbn);
    }
    return raiz;
}

void exibir(Livro *raiz) {
    if (raiz != NULL) {
        exibir(raiz->esquerda);
        printf(COR_CIANO);
        printf("----------------------------------------\n");
        printf("ISBN   : %s\n", raiz->isbn);
        printf("Titulo : %s\n", raiz->titulo);
        printf("----------------------------------------\n");
        printf(COR_RESET);
        exibir(raiz->direita);
    }
}

// Libera memória
void liberar(Livro *raiz) {
    if(raiz != NULL){
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}

int main() {
    Livro *raiz = NULL;
    Livro *resultado;
    int opcao;
    char isbn[20];
    char titulo[50];

    do {
        printf(COR_AZUL);
        printf("\n===================================================\n");
        printf("|             SISTEMA DE BIBLIOTECA               |\n");
        printf("===================================================\n");
        printf("| 1 - Inserir Livro                               |\n");
        printf("| 2 - Remover Livro                               |\n");
        printf("| 3 - Buscar Livro                                |\n");
        printf("| 4 - Exibir Livros                               |\n");
        printf("| 0 - Sair                                        |\n");
        printf("===================================================\n");
        printf("Escolha uma opcao: ");
        printf(COR_RESET);

        if(scanf("%d", &opcao) != 1) {
            while(getchar() != '\n');
            printf(COR_VERMELHA "\nOpcao invalida!\n" COR_RESET);
            continue;
        }
        while(getchar() != '\n');

        switch(opcao) {
        case 1:
            printf("ISBN (Ex: 978-85-333-0227-3): ");
            fgets(isbn, sizeof(isbn), stdin);
            isbn[strcspn(isbn, "\n")] = '\0';

            if (!validarISBN(isbn)) {
                printf(COR_VERMELHA "\nFormato invalido! Use 13 digitos com hifens (sem letras).\n" COR_RESET);
                break;
            }

            printf("Titulo: ");
            fgets(titulo, sizeof(titulo), stdin);
            titulo[strcspn(titulo, "\n")] = '\0';

            raiz = inserir(raiz, isbn, titulo);
            printf(COR_VERDE "\nLivro inserido com sucesso!\n" COR_RESET);
            break;

        case 2:
            printf("ISBN para remover: ");
            fgets(isbn, sizeof(isbn), stdin);
            isbn[strcspn(isbn, "\n")] = '\0';

            if(buscar(raiz, isbn) == NULL)
                printf(COR_AMARELA "\nLivro não encontrado!\n" COR_RESET);
            else{
                raiz = remover(raiz, isbn);
                printf(COR_VERDE "\nLivro removido com sucesso!\n" COR_RESET);
            }
            break;

        case 3:
            printf("ISBN para buscar: ");
            fgets(isbn, sizeof(isbn), stdin);
            isbn[strcspn(isbn, "\n")] = '\0';

            resultado = buscar(raiz, isbn);
            if(resultado == NULL)
                printf(COR_AMARELA "\nLivro nao encontrado!\n" COR_RESET);
            else{
                printf(COR_VERDE "\nLivro encontrado!\n" COR_RESET);
                printf("ISBN   : %s\n", resultado->isbn);
                printf("Titulo : %s\n", resultado->titulo);
            }
            break;

        case 4:
            if(raiz == NULL)
                printf(COR_AMARELA "\nNenhum livro cadastrado.\n" COR_RESET);
            else
                exibir(raiz);
            break;

        case 0:
            printf(COR_VERDE "\nEncerrando...\n" COR_RESET);
            break;

        default:
            printf(COR_VERMELHA "\nOpcao invalida!\n" COR_RESET);
        }
    } while(opcao != 0);

    liberar(raiz);
    return 0;
}