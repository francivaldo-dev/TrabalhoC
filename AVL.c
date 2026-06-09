#include <stdio.h>
#include <stdlib.h>

typedef struct NoAVL {
    int chave;
    struct NoAVL *esq;
    struct NoAVL *dir;
    int altura;
} NoAVL;

int altura(NoAVL *N) {
    if (N == NULL) return 0;
    return N->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

NoAVL* novoNoAVL(int chave) {
    NoAVL* no = (NoAVL*)malloc(sizeof(NoAVL));
    no->chave = chave;
    no->esq = NULL;
    no->dir = NULL;
    no->altura = 1;
    return no;
}

NoAVL *rotacaoDireita(NoAVL *y) {
    NoAVL *x = y->esq;
    NoAVL *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

NoAVL *rotacaoEsquerda(NoAVL *x) {
    NoAVL *y = x->dir;
    NoAVL *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

int getBalanceamento(NoAVL *N) {
    if (N == NULL) return 0;
    return altura(N->esq) - altura(N->dir);
}

NoAVL* inserirAVL(NoAVL* no, int chave) {
    if (no == NULL) return novoNoAVL(chave);

    if (chave < no->chave)
        no->esq = inserirAVL(no->esq, chave);
    else if (chave > no->chave)
        no->dir = inserirAVL(no->dir, chave);
    else 
        return no;

    no->altura = 1 + max(altura(no->esq), altura(no->dir));
    int balance = getBalanceamento(no);

    if (balance > 1 && chave < no->esq->chave)
        return rotacaoDireita(no);

    if (balance < -1 && chave > no->dir->chave)
        return rotacaoEsquerda(no);

    if (balance > 1 && chave > no->esq->chave) {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }

    if (balance < -1 && chave < no->dir->chave) {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }

    return no;
}

NoAVL * noComValorMinimo(NoAVL* no) {
    NoAVL* atual = no;
    while (atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

NoAVL* removerAVL(NoAVL* raiz, int chave) {
    if (raiz == NULL) return raiz;

    if (chave < raiz->chave)
        raiz->esq = removerAVL(raiz->esq, chave);
    else if(chave > raiz->chave)
        raiz->dir = removerAVL(raiz->dir, chave);
    else {
        if((raiz->esq == NULL) || (raiz->dir == NULL)) {
            NoAVL *temp = raiz->esq ? raiz->esq : raiz->dir;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else 
                *raiz = *temp; 
            free(temp);
        } else {
            NoAVL* temp = noComValorMinimo(raiz->dir);
            raiz->chave = temp->chave;
            raiz->dir = removerAVL(raiz->dir, temp->chave);
        }
    }

    if (raiz == NULL) return raiz;

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));
    int balance = getBalanceamento(raiz);

    if (balance > 1 && getBalanceamento(raiz->esq) >= 0)
        return rotacaoDireita(raiz);

    if (balance > 1 && getBalanceamento(raiz->esq) < 0) {
        raiz->esq =  rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    if (balance < -1 && getBalanceamento(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);

    if (balance < -1 && getBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

NoAVL* consultarAVL(NoAVL* raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave) return raiz;
    if (raiz->chave < chave) return consultarAVL(raiz->dir, chave);
    return consultarAVL(raiz->esq, chave);
}

int contarNosAVL(NoAVL* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNosAVL(raiz->esq) + contarNosAVL(raiz->dir);
}

void imprimirAVL(NoAVL* raiz) {
    if (raiz != NULL) {
        imprimirAVL(raiz->esq);
        printf("%d (H:%d) ", raiz->chave, raiz->altura);
        imprimirAVL(raiz->dir);
    }
}