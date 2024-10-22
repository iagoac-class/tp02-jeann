#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvores.h"

typedef struct noArvore_ noArvore;
struct noArvore_
{
    int valor;
    noArvore *esq;
    noArvore *dir;
};

noArvore *busca(noArvore *raiz, int k)
{
    if (raiz == NULL || raiz->valor == k) // Verifica se a raiz é nula ou se já é o valor que procura.
        return raiz;
    if (raiz->valor > k)            // Verifica se ele é maior que o valor procurado.
        return busca(raiz->esq, k); // faz o uso da recursividade no nó da esq
    else
        return busca(raiz->dir, k); // faz o uso da recursividade no nó da esq
}

noArvore *insere(noArvore *raiz, noArvore *n)
{
    if (raiz == NULL) // Verifica se a raiz é nula.
    {
        return n; // O novo nó se torna a raiz.
    }
    if (raiz->valor > n->valor) // Caso o valor da raiz seja maior que o que se procura.
    {
        raiz->esq = insere(raiz->esq, n); // O novo nó é inserido a esquerda da raiz.
    }
    else
    {
        raiz->dir = insere(raiz->dir, n); // Senão ele é inserido a direita da raiz.
    }
    return raiz;
}
noArvore *buscaPai(noArvore *raiz, noArvore *n)
{

    if (raiz == NULL || raiz == n) // Verifica se a raiz é nula ou se é igual ao valor que deseja.
    {
        return NULL;
    }

    if (raiz->esq == n || raiz->dir == n) // Caso for igual a esquerda ou direita da raiz.
    {
        return raiz;
    }
    if (n->valor > raiz->valor) // Se o valor nó procurado for maior que o valor da raiz.
    {
        return buscaPai(raiz->dir, n); // A busca é feita na direita.
    }
    else
    {
        return buscaPai(raiz->esq, n); // A busca é feita na esquerda.
    }
}
noArvore *removeRaiz(noArvore *raiz)
{
    noArvore *p, *q;

    if (raiz->esq == NULL) // Se o nó da esquerda da raiz for nulo.
    {
        q = raiz->dir;
        free(raiz);
        return (q);
    }

    p = raiz;
    q = raiz->esq;

    while (q->dir != NULL) // Enquanto a direita do nó que se deseja adicionar for diferente de nulo.
    {
        p = q;
        q = q->dir;
    }
    if (p != raiz) // Se o
    {
        p->dir = q->esq;
        q->esq = raiz->esq;
    }
    q->dir = raiz->dir;
    free(raiz);
    return q;
}

noArvore *removeNo(noArvore *raiz, int valor)
{
    noArvore *n = busca(raiz, valor); // Verifica se o nó existe
    if (n)
    {
        noArvore *pai = buscaPai(raiz, n); // Descobre qual é o nó pai
        if (pai)                           // caso tenha no pai
        {
            if (pai->dir == n)
                pai->dir = removeRaiz(n); // no a ser removido é filho a direita
            else
                pai->esq = removeRaiz(n); // no a ser removido e filho a esquerda
        }
        else
        {
            raiz = removeRaiz(n); // não possui pai, logo, é o próprio no raiz
        }
    }
    return raiz;
}

double arvore_binaria(int instancia_num)
{
    double tempo = 0;
    clock_t begin = clock();

    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}

double arvore_balanceada(int instancia_num)
{
    double tempo = 0;
    clock_t begin = clock();

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

    double tempo_n_balanceada = arvore_binaria(instancia_num);
    double tempo_balanceada = arvore_balanceada(instancia_num);

    printf("%f\n%f\n", tempo_n_balanceada, tempo_balanceada);

    return (1);
}