#include <stdio.h>
#include <stdlib.h>

#define MAX_FILHOS 5

typedef struct NoNario {
    int dado;
    struct NoNario* filhos[MAX_FILHOS];
    int qtd_filhos;
} NoNario;

NoNario* criarNoNario(int dado) {
    NoNario* novo = (NoNario*)malloc(sizeof(NoNario));
    novo->dado = dado;
    novo->qtd_filhos = 0;
    for(int i = 0; i < MAX_FILHOS; i++) novo->filhos[i] = NULL;
    return novo;
}

void destruirSubarvore(NoNario* no) {
    if (no == NULL) return;
    for(int i = 0; i < no->qtd_filhos; i++) {
        destruirSubarvore(no->filhos[i]);
    }
    free(no);
}

NoNario* removerNoNario(NoNario* raiz, int alvo, int modo) {
    if (raiz == NULL) return NULL;

    for (int i = 0; i < raiz->qtd_filhos; i++) {
        if (raiz->filhos[i]->dado == alvo) {
            NoNario* noDeletar = raiz->filhos[i];

            if (modo == 1) {
                destruirSubarvore(noDeletar);
            } 
            else if (modo == 2) {
                if (noDeletar->qtd_filhos > 0) {
                    NoNario* promovido = noDeletar->filhos[0];
                    
                    for (int j = 1; j < noDeletar->qtd_filhos; j++) {
                        if (promovido->qtd_filhos < MAX_FILHOS) {
                            promovido->filhos[promovido->qtd_filhos++] = noDeletar->filhos[j];
                        } else {
                            printf("Aviso: Limite MAX_FILHOS excedido.\n");
                        }
                    }
                    raiz->filhos[i] = promovido;
                } else {
                    raiz->filhos[i] = NULL;
                }
                free(noDeletar);
            }

            if (raiz->filhos[i] == NULL || modo == 1) {
                for (int k = i; k < raiz->qtd_filhos - 1; k++) {
                    raiz->filhos[k] = raiz->filhos[k + 1];
                }
                raiz->filhos[raiz->qtd_filhos - 1] = NULL;
                raiz->qtd_filhos--;
            }
            return raiz;
        } else {
            raiz->filhos[i] = removerNoNario(raiz->filhos[i], alvo, modo);
        }
    }
    return raiz;
}