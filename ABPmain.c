#include <stdio.h>
#include <stdlib.h>
#include "ABP.h"

int main(int argc, char** argv) {
    PONT r = NULL; // Inicialize apontando para NULL
    int v, b, n;
    int continuar = 1;
    PONT p_aux; // Variável auxiliar para a busca

    do {
        printf("\n\tMenu de Opcao\n\n");
        printf("1. Inicializa a arvore \n");
        printf("2. Insere na arvore\n");
        printf("3. Buscar um valor na arvore\n");
        printf("4. Conta o numero de nos da arvore\n");
        printf("5. Imprime a arvore\n");
        printf("6. Remove um no da arvore\n");
        printf("0. Sair\n");

        scanf("%d", &continuar);
        // Ajustado para funcionar em múltiplos sistemas operacionais de forma limpa
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        switch (continuar) {
            case 1:
                r = inicializa();
                printf("Arvore criada com sucesso!\n");
                break;

            case 2:
                printf("Digite um numero para inserir na arvore: ");
                scanf("%d", &v);
                PONT no = criaNovoNo(v);
                r = adiciona(r, no);
                printf("No inserido com sucesso!\n");
                break;
                
            case 3:
                printf("Digite um valor para pesquisar na arvore: ");
                scanf("%d", &b);
                p_aux = contem(b, r); // CORRIGIDO: Usa p_aux para não perder a raiz 'r'
                if (p_aux == NULL)
                    printf("O valor %d nao foi localizado.\n", b);
                else
                    printf("O valor %d foi localizado na arvore.\n", b);
                break;
                
            case 4:
                n = numeroNos(r);
                printf("A arvore possui: %d nos.\n", n);
                break;
                
            case 5:
                printf("Estrutura da arvore: ");
                exibirArvore(r);
                printf("\n");
                break;
            
            case 6:
                printf("Digite um valor para remover da arvore: ");
                scanf("%d", &v);
                r = removeNo(r, v);
                printf("Tentativa de remocao concluida.\n");
                break;

            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Digite uma opcao valida\n");
        }
    } while (continuar);

    return 0;
}