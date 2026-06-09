#include <stdio.h>
#include <stdlib.h>
#include "ABP.h"

// Função que inicializa a arvore
PONT inicializa() {
    return (NULL);
}

// Função que cria um novo nó
PONT criaNovoNo(TIPOCHAVE ch) {
    PONT novoNo = (PONT) malloc(sizeof(NO));
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->chave = ch;
    return (novoNo);
}

// Função que adiciona um nó (valores iguais vão para a DIREITA)
PONT adiciona(PONT raiz, PONT no) {
    if (raiz == NULL)
        return (no);
    if (no->chave < raiz->chave)
        raiz->esq = adiciona(raiz->esq, no);
    else
        raiz->dir = adiciona(raiz->dir, no); // Aceita duplicados na direita
    return (raiz);
}

// Função que verifica se um nó consta da árvore
PONT contem(TIPOCHAVE ch, PONT raiz) {
    if (raiz == NULL) 
        return (NULL);
    if (raiz->chave == ch) 
        return (raiz);
    if (raiz->chave > ch)
        return (contem(ch, raiz->esq));
    return (contem(ch, raiz->dir));
}

// Função que conta o numero de nós da árvore
int numeroNos(PONT raiz) {
    if (!raiz) 
        return 0;
    return (numeroNos(raiz->esq) + 1 + numeroNos(raiz->dir));
}

// Função que imprime a árvore
void exibirArvore(PONT raiz) {
    if (raiz != NULL) {
        printf("%i", raiz->chave);
        printf("(");
        exibirArvore(raiz->esq);
        exibirArvore(raiz->dir);
        printf(")");
    }
}

// Função que busca um nó e identifica seu pai corretamente
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai) {
    PONT atual = raiz;
    *pai = NULL;
    while (atual) {
        if (atual->chave == ch) return (atual);
        *pai = atual;
        // Se for menor, vai para a esquerda. Se for maior OU IGUAL, vai para a direita.
        if (ch < atual->chave) atual = atual->esq;
        else atual = atual->dir;
    }
    return (NULL);
}

// Função que remove apenas UMA instância do nó da árvore
PONT removeNo(PONT raiz, TIPOCHAVE ch) {
    PONT pai, no, p, q;
    no = buscaNo(raiz, ch, &pai);
    if (no == NULL) return (raiz); // Não encontrou

    // Caso 1 e 2: Nó com 0 ou 1 filho
    if (!no->esq || !no->dir) {
        if (!no->esq) q = no->dir;
        else q = no->esq;
    } 
    // Caso 3: Nó com 2 filhos
    else {
        p = no;
        q = no->esq;
        while (q->dir) {
            p = q;
            q = q->dir;
        }
        if (p != no) {
            p->dir = q->esq;
            q->esq = no->esq;
        }
        q->dir = no->dir;
    }

    // Se o nó a ser removido é a própria raiz
    if (!pai) {
        free(no);
        return (q);
    }

    // Vincula o substituto (q) ao pai correto. 
    // Como há duplicados, checamos se o ponteiro do pai apontava para o 'no'
    if (pai->esq == no) pai->esq = q;
    else pai->dir = q;

    free(no);
    return (raiz);
}