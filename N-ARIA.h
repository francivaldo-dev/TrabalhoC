#ifndef N_ARIA_H
#define N_ARIA_H

#include <stdlib.h>
#include <stdio.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct auxNo {
    TIPOCHAVE chave;
    struct auxNo *ultimoFilho; 
    struct auxNo *proximoIrmao; 
} NO, *PONT;

PONT buscarChave(PONT raiz, TIPOCHAVE ch);
int numeroDeNos(PONT raiz);
int numeroDeNos2(PONT raiz);
int altura(PONT raiz);
PONT criarNovoNo(TIPOCHAVE ch);
bool inserirFilho(PONT raiz, TIPOCHAVE novaChave, TIPOCHAVE chavePai);
void exibirArvore(PONT raiz);
PONT criarRaiz(TIPOCHAVE novaChave);

//funções para a remoção
PONT buscarPai(PONT raiz, TIPOCHAVE ch);
void liberarSubarvore(PONT raiz);
PONT removerNoNAria(PONT raiz, TIPOCHAVE ch, int modo);

#endif