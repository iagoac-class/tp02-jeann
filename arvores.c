#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       
#include "arvores.h"

typedef struct noArvore_ noArvore;
struct noArvore_ {
    int valor;
    noArvore * esq;
    noArvore * dir;
};

noArvore * busca (noArvore * raiz, int k) {
if (raiz == NULL || raiz->valor == k)
    return raiz;
if (raiz->valor > k)
    return busca (raiz->esq, k);
else
    return busca (raiz->dir, k);
}

noArvore * insere (noArvore * raiz, noArvore * n) {
    if (raiz == NULL) return n;
    if (raiz->valor > n->valor)
        raiz->esq = insere(raiz->esq, n);
    else
        raiz->dir = insere (raiz->dir, n);
    return raiz;
}
noArvore *buscaPai(noArvore * raiz,noArvore * valor) {
       
}

noArvore * removeNo(noArvore * raiz, int valor) {
    noArvore * n = busca(raiz, valor); //checa se o noh existe
    if (n) {
        noArvore * pai = buscaPai(raiz, n); //descobre quem eh o noh pai
        if (pai) { //caso tenha noh pai
            if (pai->dir == n) //noh a ser removido eh filho a direita
                pai->dir = removeRaiz(n);
            else //noh a ser removido eh filho a esquerda
                pai->esq = removeRaiz(n);
        } else { //nao possui pai, logo, eh o proprio noh raiz
            raiz = removeRaiz(n);
        }
    }
    return raiz;
}



double arvore_binaria(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    
    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}

double arvore_balanceada(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    
    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}


int main(int argc, char* argv[]) {
    ///////////////////////////////////////////////////////////
    /////////////////// Leitor de instâncias //////////////////
    ///////////////// Não deve ser modificado /////////////////
    ///////////////////////////////////////////////////////////
    int instancia_num = -1;
    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 10) {
        printf("Para executar o código, digite ./arvores x\nonde x é um número entre 1 e 10 que simboliza a instância utilizada\n");
        exit(0);
    }
    
    double tempo_n_balanceada = arvore_binaria(instancia_num);
    double tempo_balanceada = arvore_balanceada(instancia_num);

    

    
    printf("%f\n%f\n", tempo_n_balanceada, tempo_balanceada);

    return (1);
}