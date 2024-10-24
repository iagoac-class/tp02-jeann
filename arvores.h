#ifndef _H_ARVORES
#define _H_ARVORES

// Implementar qualquer struct que for necessária aqui

double arvore_binaria(FILE *arq);
double arvore_balanceada(FILE *arq);
typedef struct noArvore_ noArvore;
struct noArvore_
{
    int valor;
    noArvore *esq;
    noArvore *dir;
    int altura;
};

// Funções para árvore binária de busca
noArvore *busca(noArvore *raiz, int k);
noArvore *insere(noArvore *raiz, noArvore *n);
noArvore *buscaPai(noArvore *raiz, noArvore *n);
noArvore *removeRaiz(noArvore *raiz);
noArvore *removeNo(noArvore *raiz, int valor);

// Funções AVL
int max(int a, int b);
int altura(noArvore *N);
int fbalanco(noArvore *N);
noArvore *newNode(int valor);
noArvore *dirRotate(noArvore *y);
noArvore *esqRotate(noArvore *x);
noArvore *insert(noArvore *node, int valor);
noArvore *minValueNode(noArvore *node);
noArvore *deleteNode(noArvore *raiz, int valor);

#endif // _H_ARVORES