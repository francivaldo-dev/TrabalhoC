#include <stdio.h>
#include <stdlib.h>
#include "N-ARIA.h"

PONT buscarChave(PONT raiz, TIPOCHAVE ch) {
    if (raiz == NULL) return NULL;
    if (raiz->chave == ch) return raiz;
    PONT aux = buscarChave(raiz->ultimoFilho, ch);
    if (aux) return aux;
    return buscarChave(raiz->proximoIrmao, ch);
}


int numeroDeNos(PONT raiz) {
    if (!raiz) return 0;
    int res = 1;
    PONT filhos = raiz->ultimoFilho;
    while (filhos != NULL) {
        res += numeroDeNos(filhos);
        filhos = filhos->proximoIrmao;
    }
    return res;
}


int numeroDeNos2(PONT raiz) {
    if (!raiz) return 0;
    return 1 + numeroDeNos2(raiz->ultimoFilho) + numeroDeNos2(raiz->proximoIrmao);
}

int altura(PONT raiz) {
    if (!raiz) return -1;
    int max = -1;
    int temp;
    PONT filhos = raiz->ultimoFilho;
    while (filhos != NULL) {
        temp = altura(filhos);
        if (temp > max) max = temp;
        filhos = filhos->proximoIrmao;
    }
    return max + 1;
}

PONT criarNovoNo(TIPOCHAVE ch) {
    PONT novoNo = (PONT) malloc(sizeof (NO));
    novoNo->ultimoFilho = NULL;
    novoNo->proximoIrmao = NULL;
    novoNo->chave = ch;
    return novoNo;
}

bool inserirFilho(PONT raiz, TIPOCHAVE novaChave, TIPOCHAVE chavePai) {
    PONT pai = buscarChave(raiz, chavePai);
    if (!pai) return false;
    PONT novo = criarNovoNo(novaChave);
    novo->ultimoFilho = NULL;
    novo->proximoIrmao = pai->ultimoFilho;
    pai->ultimoFilho = novo;
    return true;
}

void exibirArvore(PONT raiz) {
    if (raiz == NULL) return;
    printf("%d", raiz->chave);
    printf("(");                      
    PONT filhos = raiz->ultimoFilho;
    while (filhos != NULL) {
        exibirArvore(filhos);
        filhos = filhos->proximoIrmao;
    }
    printf(")");                       
}

PONT criarRaiz(TIPOCHAVE novaChave) {
    return criarNovoNo(novaChave);
}


/* Busca o nó pai de uma chave para poder refazer os ponteiros */
PONT buscarPai(PONT raiz, TIPOCHAVE ch) {
    if (raiz == NULL) return NULL;
    
    PONT filhos = raiz->ultimoFilho;
    while (filhos != NULL) {
        if (filhos->chave == ch) return raiz;
        PONT aux = buscarPai(filhos, ch);
        if (aux) return aux;
        filhos = filhos->proximoIrmao;
    }
    return NULL;
}

/* Libera recursivamente a memória de um nó e de todos os seus filhos */
void liberarSubarvore(PONT raiz) {
    if (raiz == NULL) return;
    PONT filhos = raiz->ultimoFilho;
    while (filhos != NULL) {
        PONT prox = filhos->proximoIrmao;
        liberarSubarvore(filhos);
        filhos = prox;
    }
    free(raiz);
}

/* Função principal de remoção com tratamento de filhos (Modo 1 ou 2) */
PONT removerNoNAria(PONT raiz, TIPOCHAVE ch, int modo) {
    if (raiz == NULL) return NULL;

    // Trata caso onde o nó a ser removido é a própria raiz da árvore
    if (raiz->chave == ch) {
        if (modo == 1) {
            liberarSubarvore(raiz);
            return NULL;
        } else {
            PONT novaRaiz = raiz->ultimoFilho;
            free(raiz);
            return novaRaiz; 
        }
    }

    PONT pai = buscarPai(raiz, ch);
    if (!pai) return raiz; 

    // Localiza o nó alvo e o irmão anterior a ele
    PONT anterior = NULL;
    PONT alvo = pai->ultimoFilho;
    while (alvo != NULL && alvo->chave != ch) {
        anterior = alvo;
        alvo = alvo->proximoIrmao;
    }

    if (alvo == NULL) return raiz; 

    // Desconecta o nó alvo da lista de irmãos do pai
    if (anterior == NULL) {
        pai->ultimoFilho = alvo->proximoIrmao;
    } else {
        anterior->proximoIrmao = alvo->proximoIrmao;
    }

    // Aplica a decisão escolhida sobre o destino dos filhos
    if (modo == 1) {
        liberarSubarvore(alvo); // Modo 1: Apaga o nó e todos os filhos em cascata
    } 
    else if (modo == 2) {
        PONT filhosDoAlvo = alvo->ultimoFilho; // Modo 2: Promove os filhos para o avô
        if (filhosDoAlvo != NULL) {
            PONT aux = filhosDoAlvo;
            while (aux->proximoIrmao != NULL) {
                aux = aux->proximoIrmao;
            }
            aux->proximoIrmao = pai->ultimoFilho;
            pai->ultimoFilho = filhosDoAlvo;
        }
        free(alvo);
    }

    return raiz;
}