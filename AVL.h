#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

#include <stdbool.h>
typedef int TIPOCHAVE;

typedef struct aux {
    TIPOCHAVE chave;
    struct aux *esq;
    struct aux *dir;
    int altura;
} NO, *PONT;


PONT inicializa();
PONT criaNovoNo(TIPOCHAVE ch);
PONT contem(TIPOCHAVE ch, PONT raiz);
int numeroNos(PONT raiz);
void exibirArvore(PONT raiz);


int obterAltura(PONT no);
int obterFatorBalanceamento(PONT no);
int max(int a, int b);
PONT rotacaoDireta(PONT r);
PONT rotacaoEsquerda(PONT r);
PONT adiciona(PONT raiz, TIPOCHAVE ch);
PONT noComMenorValor(PONT no);
PONT removeNo(PONT raiz, TIPOCHAVE ch);

#endif