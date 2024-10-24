#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvores.h"

noArvore *busca(noArvore *raiz, int k)
{
    if (raiz == NULL || raiz->valor == k) // Verifica se a raiz é nula ou se já é o valor que procura.
        return raiz;
    if (raiz->valor > k)            // Verifica se ele é maior que o valor procurado.
        return busca(raiz->esq, k); // faz o uso da recursividade no nó da esq.
    else
        return busca(raiz->dir, k); // faz o uso da recursividade no nó da esq.
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
    if (p != raiz)
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
    noArvore *n = busca(raiz, valor); // Verifica se o nó existe.
    if (n)
    {
        noArvore *pai = buscaPai(raiz, n); // Descobre qual é o nó pai.
        if (pai)                           // caso tenha no pai.
        {
            if (pai->dir == n)
                pai->dir = removeRaiz(n); // no a ser removido é filho a direita.
            else
                pai->esq = removeRaiz(n); // no a ser removido e filho a esquerda.
        }
        else
        {
            raiz = removeRaiz(n); // não possui pai, logo, é o próprio no raiz.
        }
    }
    return raiz;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Função utilizada para obter a altura.
int altura(noArvore *N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}

// Função para obter no máximo dois inteiros.
int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

/* Função que aloca um novo nó com a chave dada e
fazendo a esquerda/direita apontar NULL*/
noArvore *newNode(int valor)
{
    noArvore *node = (noArvore *)
        malloc(sizeof(noArvore));
    node->valor = valor;
    node->esq = NULL;
    node->dir = NULL;
    node->altura = 1; // novo nó é adicionado inicialmente na folha.
    return (node);
}

// Uma função para fazer uma rotação de sub arvore a direita enraizada com y.
noArvore *dirRotate(noArvore *y)
{
    noArvore *x = y->esq;
    noArvore *T2 = x->dir;

    // Rotação de performace.
    x->dir = y;
    y->esq = T2;

    // Atualizando as alturas.
    y->altura = max(altura(y->esq),
                    altura(y->dir)) +
                1;
    x->altura = max(altura(x->esq),
                    altura(x->dir)) +
                1;

    // Retorna nova raíz.
    return x;
}

// Uma função para fazer uma rotação de sub arvore a esquerda enraizada com x.
noArvore *esqRotate(noArvore *x)
{
    noArvore *y = x->dir;
    noArvore *T2 = y->esq;

    // Rotação de performace.
    y->esq = x;
    x->dir = T2;

    // Atualizando as alturas.
    x->altura = max(altura(x->esq),
                    altura(x->dir)) +
                1;
    y->altura = max(altura(y->esq),
                    altura(y->dir)) +
                1;

    // Retorna nova raíz.
    return y;
}

// Obtem o fator de baleaceamento do nó N.
int fbalanco(noArvore *N)
{
    if (N == NULL)
        return 0;
    return altura(N->esq) - altura(N->dir);
}

// Função recursiva para inserir a chave  na subarvore enraízada
// com nó e retorna a nova raiz da subarvore.
noArvore *insert(noArvore *node, int valor)
{
    /* 1. Executa a inserção normal na árvore binaria de busca. */
    if (node == NULL)
        return (newNode(valor));

    if (valor < node->valor)
        node->esq = insert(node->esq, valor);
    else if (valor > node->valor)
        node->dir = insert(node->dir, valor);
    else // Chaves igual não permitidas na arvore binaria de busca.
        return node;

    /* 2. Atualização da altura do no ancestral. */
    node->altura = 1 + max(altura(node->esq),
                           altura(node->dir));

    /* 3. Obtem o fator de baleaceamento do nó ancestral checando se este nó esta desbalanceado
          checando se este nó esta desbalanceado*/

    int balanco = fbalanco(node);

    // Se este nó se tornar desbalaceado
    // então possuem 4 casos

    // esq esq Caso
    if (balanco > 1 && valor < node->esq->valor)
        return dirRotate(node);

    // dir dir Caso
    if (balanco < -1 && valor > node->dir->valor)
        return esqRotate(node);

    // esq dir Caso
    if (balanco > 1 && valor > node->esq->valor)
    {
        node->esq = esqRotate(node->esq);
        return dirRotate(node);
    }

    // dir esq Caso
    if (balanco < -1 && valor < node->dir->valor)
    {
        node->dir = dirRotate(node->dir);
        return esqRotate(node);
    }

    /*  retorna o ponteiro nó não modificado */
    return node;
}

/* Dada uma arvore binaria de busca não vazia,retorna o nó
   com o valor minimo de chave encontrado naquela arvore.
   Todo o resto da arvore não necessita ser buscado.
 */
noArvore *minValueNode(noArvore *node)
{
    noArvore *current = node;

    // Loop para se encontrar a folha mais a esquerda
    while (current->esq != NULL)
        current = current->esq;

    return current;
}

// Função recursiva para deletar um nó com o valor
// fornecido da subárvore com raiz dada.
// Ela retorna a raiz da subárvore modificada.
noArvore *deleteNode(noArvore *raiz, int valor)
{
    // EXCLUI BST PADRÃO

    if (raiz == NULL)
        return raiz;

    // Se o valor do nó a ser deletado é menor que o valor
    // da raiz,então ele fica na subarvore a esquerda.
    if (valor < raiz->valor)
        raiz->esq = deleteNode(raiz->esq, valor);

    // Se o valor do nó a ser deletado for maior que o
    // valor da raiz,então ele fica na subarvore a direita
    else if (valor > raiz->valor)
        raiz->dir = deleteNode(raiz->dir, valor);

    // Se esse é o mesmo valor da raiz,
    // então esse será o nó a ser deletado.
    else
    {
        // Nó com apenas um filho ou sem nenhum filho
        if ((raiz->esq == NULL) || (raiz->dir == NULL))
        {
            noArvore *temp = raiz->esq ? raiz->esq : raiz->dir;

            // Caso de nenhum filho
            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else               // No caso de apenas um filho.
                *raiz = *temp; // Copia o conteudo do
                               // filho não vazio.
            free(temp);
        }
        else
        {
            // Nó com dois filhos : fica em ordem.
            // Sucessor ( o nó mais a direita possivel)
            noArvore *temp = minValueNode(raiz->dir);

            // Copia os dados do sucessor em ordem para este nó.
            raiz->valor = temp->valor;

            // Deleta o sucessor em ordem
            raiz->dir = deleteNode(raiz->dir, temp->valor);
        }
    }

    // Se a árvore só possui um único nó então retorna.
    if (raiz == NULL)
        return raiz;

    // Atualiza a altura do nó atual
    raiz->altura = 1 + max(altura(raiz->esq),
                           altura(raiz->dir));

    // Obtém se o fator de balanceamento deste nó(para
    // checar se este nó se tornou desbalanceado.)
    int balanco = fbalanco(raiz);

    // Se o nó se tornar desbalanceado, tem-se 4 casos.

    // esq esq Case
    if (balanco > 1 && fbalanco(raiz->esq) >= 0)
        return dirRotate(raiz);

    // esq dir Case
    if (balanco > 1 && fbalanco(raiz->esq) < 0)
    {
        raiz->esq = esqRotate(raiz->esq);
        return dirRotate(raiz);
    }

    // dir dir Case
    if (balanco < -1 && fbalanco(raiz->dir) <= 0)
        return esqRotate(raiz);

    // dir esq Case
    if (balanco < -1 && fbalanco(raiz->dir) > 0)
    {
        raiz->dir = dirRotate(raiz->dir);
        return esqRotate(raiz);
    }

    return raiz;
}