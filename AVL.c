#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

PONT inicializa() {
    return NULL;
}

PONT criaNovoNo(TIPOCHAVE ch) {
    PONT novoNo = (PONT) malloc(sizeof(NO));
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->chave = ch;
    novoNo->altura = 0; // Todo nó novo começa como folha (altura 0)
    return novoNo;
}

/* Retorna a altura de um nó de forma segura (lidando com ponteiros NULL) */
int obterAltura(PONT no) {
    if (no == NULL) return -1;
    return no->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

/* Calcula o Fator de Balanceamento: FB = Altura_Esq - Altura_Dir */
int obterFatorBalanceamento(PONT no) {
    if (no == NULL) return 0;
    return obterAltura(no->esq) - obterAltura(no->dir);
}

/* Rotação à Direita (Usada para corrigir desbalanceamento Esquerda-Esquerda) */
PONT  rotacaoDireta(PONT r) {
    PONT p = r->esq;
    r->esq = p->dir;
    p->dir = r;

    // Atualiza as alturas dos nós modificados
    r->altura = max(obterAltura(r->esq), obterAltura(r->dir)) + 1;
    p->altura = max(obterAltura(p->esq), obterAltura(p->dir)) + 1;

    return p; // Nova raiz da subárvore
}

/* Rotação à Esquerda (Usada para corrigir desbalanceamento Direita-Direita) */
PONT rotacaoEsquerda(PONT r) {
    PONT p = r->dir;
    r->dir = p->esq;
    p->esq = r;

    // Atualiza as alturas dos nós modificados
    r->altura = max(obterAltura(r->esq), obterAltura(r->dir)) + 1;
    p->altura = max(obterAltura(p->esq), obterAltura(p->dir)) + 1;

    return p; // Nova raiz da subárvore
}

/* Inserção AVL: Insere recursivamente e rebalanceia na volta da recursão */
PONT adiciona(PONT raiz, TIPOCHAVE ch) {
    if (raiz == NULL) return criaNovoNo(ch);

    if (ch < raiz->chave)
        raiz->esq = adiciona(raiz->esq, ch);
    else if (ch > raiz->chave)
        raiz->dir = adiciona(raiz->dir, ch);
    else
        return raiz; // Chaves iguais não são permitidas na AVL padrão

    // Atualiza a altura do nó atual
    raiz->altura = max(obterAltura(raiz->esq), obterAltura(raiz->dir)) + 1;

    // Checa o fator de balanceamento deste nó ancestral
    int fb = obterFatorBalanceamento(raiz);

    // Caso Esquerda-Esquerda (Sinal do FB do nó e do filho são iguais -> Rotação Simples)
    if (fb > 1 && ch < raiz->esq->chave)
        return  rotacaoDireta(raiz);

    // Caso Direita-Direita
    if (fb < -1 && ch > raiz->dir->chave)
        return  rotacaoEsquerda(raiz);

    // Caso Esquerda-Direita (Sinais opostos -> Rotação Dupla: Esquerda no filho, Direita no pai)
    if (fb > 1 && ch > raiz->esq->chave) {
        raiz->esq =  rotacaoEsquerda(raiz->esq);
        return  rotacaoDireta(raiz);
    }

    // Caso Direita-Esquerda (Sinais opostos -> Rotação Dupla: Direita no filho, Esquerda no pai)
    if (fb < -1 && ch < raiz->dir->chave) {
        raiz->dir =  rotacaoDireta(raiz->dir);
        return  rotacaoEsquerda(raiz);
    }

    return raiz;
}

PONT contem(TIPOCHAVE ch, PONT raiz) {
    if (raiz == NULL) return NULL;
    if (raiz->chave == ch) return raiz;
    if (raiz->chave > ch) return contem(ch, raiz->esq);
    return contem(ch, raiz->dir);
}

int numeroNos(PONT raiz) {
    if (!raiz) return 0;
    return numeroNos(raiz->esq) + 1 + numeroNos(raiz->dir);
}

void exibirArvore(PONT raiz) {
    if (raiz != NULL) {
        printf("%i", raiz->chave);
        printf("(");
        exibirArvore(raiz->esq);
        exibirArvore(raiz->dir);
        printf(")");
    }
}

/* Auxiliar da remoção: encontra o nó com a menor chave em uma subárvore */
PONT noComMenorValor(PONT no) {
    PONT atual = no;
    while (atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

/* Remoção AVL: Remove o nó e rebalanceia a árvore de baixo para cima */
PONT removeNo(PONT raiz, TIPOCHAVE ch) {
    if (raiz == NULL) return raiz;

    if (ch < raiz->chave)
        raiz->esq = removeNo(raiz->esq, ch);
    else if (ch > raiz->chave)
        raiz->dir = removeNo(raiz->dir, ch);
    else {
        // Encontrou o nó a ser removido

        // Nós com apenas um filho ou nenhum
        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
            PONT temp = raiz->esq ? raiz->esq : raiz->dir;

            if (temp == NULL) { // Caso sem filhos
                temp = raiz;
                raiz = NULL;
            } else { // Caso com um filho
                *raiz = *temp; // Copia o conteúdo do filho para o nó atual
            }
            free(temp);
        } else {
            // Nó com dois filhos: pega o sucessor (menor da subárvore direita)
            PONT temp = noComMenorValor(raiz->dir);
            raiz->chave = temp->chave; // Copia a chave do sucessor para cá
            raiz->dir = removeNo(raiz->dir, temp->chave); // Deleta o sucessor original
        }
    }

    // Se a árvore tinha apenas um nó e ele foi deletado
    if (raiz == NULL) return raiz;

    // Atualiza a altura do nó atual
    raiz->altura = max(obterAltura(raiz->esq), obterAltura(raiz->dir)) + 1;

    // Verifica o balanceamento
    int fb = obterFatorBalanceamento(raiz);

    // Caso Esquerda-Esquerda
    if (fb > 1 && obterFatorBalanceamento(raiz->esq) >= 0)
        return  rotacaoDireta(raiz);

    // Caso Esquerda-Direita
    if (fb > 1 && obterFatorBalanceamento(raiz->esq) < 0) {
        raiz->esq =  rotacaoEsquerda(raiz->esq);
        return  rotacaoDireta(raiz);
    }

    // Caso Direita-Direita
    if (fb < -1 && obterFatorBalanceamento(raiz->dir) <= 0)
        return  rotacaoEsquerda(raiz);

    // Caso Direita-Esquerda
    if (fb < -1 && obterFatorBalanceamento(raiz->dir) > 0) {
        raiz->dir =  rotacaoDireta(raiz->dir);
        return  rotacaoEsquerda(raiz);
    }

    return raiz;
}