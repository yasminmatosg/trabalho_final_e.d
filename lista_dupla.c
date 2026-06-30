#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cores.h"

/*=======================================================
   LISTA DUPLAMENTE ENCADEADA - SISTEMA DE HISTÓRICO WEB
========================================================*/

/*
 * ESTRUTURA DO NÓ DA LISTA DUPLA
 * Diferente da lista simples, aqui nós guardamos DOIS endereços de memória.
 * Isso permite a navegação bidirecional. Em um histórico web, isso simula
 * perfeitamente os botões "Voltar" (anterior) e "Avançar" (proxima).
 */
typedef struct PaginaWeb
{

    char url[100];
    struct PaginaWeb *anterior;
    struct PaginaWeb *proxima;

} PaginaWeb;

void limparBuffer()
{

    while (getchar() != '\n' && !feof(stdin))
        ;
}

// Acessa uma nova página
void acessarPagina(PaginaWeb **atual, char url[])
{

    PaginaWeb *nova = (PaginaWeb *)malloc(sizeof(PaginaWeb));
    if (nova == NULL)
    {

        printf(COR_VERMELHA "\nErro de memoria!\n" COR_RESET);
        return;
    }

    strcpy(nova->url, url);
    nova->proxima = NULL;
    nova->anterior = *atual;

    if (*atual != NULL)
    {

        // Se havia páginas à frente, libera esse "futuro"
        PaginaWeb *aux = (*atual)->proxima;
        while (aux != NULL)
        {

            PaginaWeb *tmp = aux;
            aux = aux->proxima;
            free(tmp);
        }

        (*atual)->proxima = nova;
    }

    *atual = nova;
    printf(COR_VERDE "\nPagina acessada com sucesso!\n" COR_RESET);
}

void voltarPagina(PaginaWeb **atual)
{

    if (*atual == NULL)
    {

        printf(COR_AMARELA "\nHistorico vazio!\n" COR_RESET);
        return;
    }

    if ((*atual)->anterior == NULL)
    {

        printf(COR_AMARELA "\nNao existe pagina anterior.\n" COR_RESET);
        return;
    }

    *atual = (*atual)->anterior;
    printf(COR_VERDE "\nVoce voltou uma pagina.\n" COR_RESET);
}

void avancarPagina(PaginaWeb **atual)
{

    if (*atual == NULL)
    {

        printf(COR_AMARELA "\nHistorico vazio!\n" COR_RESET);
        return;
    }

    if ((*atual)->proxima == NULL)
    {

        printf(COR_AMARELA "\nNao existe proxima pagina.\n" COR_RESET);
        return;
    }

    *atual = (*atual)->proxima;
    printf(COR_VERDE "\nVoce avancou uma pagina.\n" COR_RESET);
}

// Exibe o histórico de navegação
void exibirHistorico(PaginaWeb *atual)
{

    if (atual == NULL)
    {

        printf(COR_AMARELA "\nHistorico vazio!\n" COR_RESET);
        return;
    }

    while (atual->anterior != NULL)
        atual = atual->anterior;

    printf(COR_CIANO "\n=========== HISTORICO ===========\n" COR_RESET);

    while (atual != NULL)
    {

        printf("URL: %s\n", atual->url);
        atual = atual->proxima;
    }
}

// Mostra página atual
void mostrarPaginaAtual(PaginaWeb *atual)
{

    if (atual == NULL)
        printf(COR_AMARELA "\nNenhuma pagina acessada.\n" COR_RESET);

    else
        printf(COR_VERDE "\nPagina atual: %s\n" COR_RESET, atual->url);
}

void liberarHistorico(PaginaWeb *atual)
{

    if (atual == NULL)
        return;

    while (atual->anterior != NULL)
        atual = atual->anterior;

    while (atual != NULL)
    {

        PaginaWeb *tmp = atual;
        atual = atual->proxima;
        free(tmp);
    }
}

int main()
{

    PaginaWeb *paginaAtual = NULL;
    int op;
    char url[100];

    do
    {

        printf(COR_AZUL);
        printf("\n=====================================================\n");
        printf("              HISTORICO DE NAVEGACAO                 \n");
        printf("=====================================================\n");
        printf("| 1 - Acessar nova pagina                          |\n");
        printf("| 2 - Voltar pagina                                |\n");
        printf("| 3 - Avancar pagina                               |\n");
        printf("| 4 - Exibir historico                             |\n");
        printf("| 5 - Mostrar pagina atual                         |\n");
        printf("| 0 - Sair                                         |\n");
        printf("=====================================================\n");
        printf("Escolha: ");
        printf(COR_RESET);

        if (scanf("%d", &op) != 1)
        {

            printf(COR_VERMELHA "\nDigite um numero valido!\n" COR_RESET);
            limparBuffer();
            continue;
        }
        limparBuffer();

        switch (op)
        {

        case 1:
            printf("Digite a URL: ");
            fgets(url, sizeof(url), stdin);
            url[strcspn(url, "\n")] = '\0';

            if (strlen(url) == 0){

                printf(COR_VERMELHA "\nURL nao pode ficar vazia!\n" COR_RESET);
            }
            else if (strchr(url, '.') == NULL) {

                printf(COR_VERMELHA "\nURL invalida! Exemplo: google.com\n" COR_RESET);
            }
            else {
                
                acessarPagina(&paginaAtual, url);
            }
            break;

        case 2:
            voltarPagina(&paginaAtual);
            break;

        case 3:
            avancarPagina(&paginaAtual);
            break;

        case 4:
            exibirHistorico(paginaAtual);
            break;

        case 5:
            mostrarPaginaAtual(paginaAtual);
            break;

        case 0:
            printf(COR_VERDE "\nFechando navegador...\n" COR_RESET);
            break;

        default:
            printf(COR_VERMELHA "\nOpcao invalida!\n" COR_RESET);
        }

    } while (op != 0);

    liberarHistorico(paginaAtual);
    return 0;
}