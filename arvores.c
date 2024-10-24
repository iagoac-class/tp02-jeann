#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvores.h"

double arvore_binaria(FILE *arq)
{
    double tempo = 0;
    clock_t begin = clock();

    char operacao;
    int valor;
    noArvore *raiz = NULL;
    noArvore *n;
    char line[16];

    while (fgets(line, sizeof(line), arq))
    {
        if (sscanf(line, "%c %d", &operacao, &valor) == 2)
        {
            n = malloc(sizeof(noArvore));
            n->valor = valor;
            n->esq = NULL;
            n->dir = NULL;

            if (operacao == 'I')
            {
                raiz = insere(raiz, n);
            }
            if (operacao == 'R')
            {
                raiz = removeNo(raiz, valor);
            }
        }
    }

    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}

double arvore_balanceada(FILE *arq)
{
    double tempo = 0;
    clock_t begin = clock();

    char operacao;
    int valor;
    noArvore *raiz = NULL;
    char line[16];

    while (fgets(line, sizeof(line), arq))
    {
        if (sscanf(line, "%c %d", &operacao, &valor) == 2)
        {
            if (operacao == 'I')
            {
                raiz = insert(raiz, valor);
            }
            if (operacao == 'R')
            {
                raiz = deleteNode(raiz, valor);
            }
        }
    }

    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}

int main(int argc, char *argv[])
{
    ///////////////////////////////////////////////////////////
    /////////////////// Leitor de instâncias //////////////////
    ///////////////// Não deve ser modificado /////////////////
    ///////////////////////////////////////////////////////////
    int instancia_num = -1;
    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 10)
    {
        printf("Para executar o código, digite ./arvores x\nonde x é um número entre 1 e 10 que simboliza a instância utilizada\n");
        exit(0);
    }

    if (argc != 2)
    { // garante que o número correto de argumentos foi passado
        printf("Número inválido de argumentos\n");
        return -1; // -1 é o erro de número de argumentos
    }
    else
        printf("Resolução da instancia %s\n", argv[1]);

    FILE *arq = fopen(argv[1], "r");

    if (arq == NULL)
    { // garante que o arquivo passado existe/foi encontrado
        printf("ERRO! Arquivo não foi encontrado!\n");
        return 1; // 1 é o erro de arquivo inválido
    }

    double tempo_n_balanceada = arvore_binaria(arq);
    fclose(arq);

    arq = fopen(argv[1], "r");

    if (arq == NULL)
    { // garante que o arquivo passado existe/foi encontrado
        printf("ERRO! Arquivo não foi encontrado!\n");
        return 1; // 1 é o erro de arquivo inválido
    }

    double tempo_balanceada = arvore_balanceada(arq);
    fclose(arq);

    printf("%f\n%f\n", tempo_n_balanceada, tempo_balanceada);

    return (1);
}