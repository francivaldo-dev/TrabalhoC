#ifndef ABP_H
#define ABP_H

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct aux {
    TIPOCHAVE chave;
    struct aux *esq, *dir;
} NO;

typedef NO* PONT;

PONT inicializa();
PONT criaNovoNo(TIPOCHAVE ch);
PONT adiciona(PONT raiz, PONT no);
PONT contem(TIPOCHAVE ch, PONT raiz);
int numeroNos(PONT raiz);
void exibirArvore(PONT raiz);
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai);
PONT removeNo(PONT raiz, TIPOCHAVE ch);

#endif