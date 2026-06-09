#include <stdio.h>
#include <stdlib.h>

typedef struct NoABB {
    int chave;
    struct NoABB *esq;
    struct NoABB *dir;
} NoABB;

NoABB* novoNoABB(int chave) {
    NoABB* no = (NoABB*)malloc(sizeof(NoABB));
    no->chave = chave;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

NoABB* inserirABB(NoABB* no, int chave) {
    if (no == NULL) return novoNoABB(chave);

    if (chave <= no->chave)
        no->esq = inserirABB(no->esq, chave);
    else
        no->dir = inserirABB(no->dir, chave);

    return no;
}

NoABB* noMinimoABB(NoABB* no) {
    NoABB* atual = no;
    while (atual && atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

NoABB* removerABB(NoABB* raiz, int chave) {
    if (raiz == NULL) return raiz;

    if (chave < raiz->chave)
        raiz->esq = removerABB(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = removerABB(raiz->dir, chave);
    else {
        if (raiz->esq == NULL) {
            NoABB* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            NoABB* temp = raiz->esq;
            free(raiz);
            return temp;
        }

        NoABB* temp = noMinimoABB(raiz->dir);
        raiz->chave = temp->chave;
        raiz->dir = removerABB(raiz->dir, temp->chave);
    }
    return raiz;
}

void imprimirABB(NoABB* raiz) {
    if (raiz != NULL) {
        imprimirABB(raiz->esq);
        printf("%d ", raiz->chave);
        imprimirABB(raiz->dir);
    }
}