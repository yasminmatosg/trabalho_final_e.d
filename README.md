# Trabalho Final - Estrutura de Dados

![C](https://img.shields.io/badge/c-%23E01B8C.svg?style=for-the-badge&logo=c&logoColor=white)
![GCC](https://img.shields.io/badge/gcc-%236A1B9A.svg?style=for-the-badge&logo=gnu&logoColor=white)

<img width="1000" height="370" alt="images estrutura de dados github" src="https://github.com/user-attachments/assets/184b97f1-3e5b-4508-941a-9a830e720911" />

> 🎓 **Projeto acadêmico** desenvolvido para a disciplina de Estrutura de Dados (3º semestre) do curso de Análise e Desenvolvimento de Sistemas do Centro Universitário Unieuro.
> 
> O sistema apresenta a implementação prática de seis estruturas de dados fundamentais em **Linguagem C pura** (programação estruturada), focando em alocação dinâmica de memória, tratamento de erros rigoroso e eficiência de algoritmos.

## 🗁 Estruturas Implementadas

Cada estrutura de dados foi aplicada a um problema prático, justificando sua escolha técnica:

* **Árvore Binária de Busca:** Sistema de índice de biblioteca, utilizando ISBN como chave de pesquisa para inserção, remoção e busca eficiente O(log n).
* **Pilha (Stack):** Histórico de ações de um editor de texto, operando no conceito LIFO (*Last In, First Out*).
* **Fila (Queue):** Sistema de fila de impressão de documentos, garantindo o processamento FIFO (*First In, First Out*).
* **Lista Simplesmente Encadeada:** Gerenciamento de uma *playlist* de músicas com alocação dinâmica.
* **Lista Duplamente Encadeada:** Simulação de histórico de navegação Web, permitindo navegação bidirecional ("Voltar" e "Avançar").
* **Lista Circular:** Gerenciamento de turnos em um jogo de tabuleiro, formando um ciclo contínuo de execução entre jogadores.

## 🛠️ Tecnologias e Técnicas
* **Linguagem:** C (Padrão ANSI)
* **Compilador:** GCC
* **Técnicas de Segurança:** Validação de entradas com `ctype.h` (`isalnum`), limpeza de *buffer*, verificação de integridade de memória (`malloc`/`free`) e tratamento de erros em tempo de execução.

## ⚙️ Como Compilar e Executar

Como o projeto é modular, você pode compilar cada estrutura individualmente. Exemplo:

  1. Clone este repositório:
   ```bash
   git clone [https://github.com/yasminmatosg/trabalho_final_e.d.git]
   ```
2. Navegue até a pasta do projeto:

   ```bash
   cd trabalho_final_e.d
   ```
4. Compile um dos módulos (exemplo da Árvore):
   ```bash
   gcc arvore.c -o arvore
   ```
5. Execute:
   ```bash
   ./arvore
   ```
   ## 𐀪𐀪 Autoras
>[Maria Luiza Vicente da Silva Lacerda](https://github.com/Ma-Luh)
>
>[Yasmin Gomes de Matos](https://github.com/yasminmatosg)
>
   Projeto desenvolvido para a disciplina de Estrutura de Dados - UNIEURO 2026/1.
