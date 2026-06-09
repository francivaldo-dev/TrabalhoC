#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

int main(int argc, char** argv) {
    PONT r = NULL; 
    int v, b, n;
    int continuar = 1;
    PONT p_aux;

    do {
        printf("\n\tMenu AVL\n\n");
        printf("1. Inicializa/Limpa a arvore \n");
        printf("2. Insere na arvore (Com Auto-Balanceamento)\n");
        printf("3. Buscar um valor na arvore\n");
        printf("4. Conta o numero de nos da arvore\n");
        printf("5. Imprime a arvore\n");
        printf("6. Remove um no da arvore (Com Auto-Balanceamento)\n");
        printf("0. Sair\n");
        printf("\nEscolha uma opcao: ");

        scanf("%d", &continuar);
        
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        switch (continuar) {
            case 1:
                r = inicializa();
                printf("Arvore AVL pronta para uso!\n");
                break;

            case 2:
                printf("Digite um numero para inserir na arvore: ");
                scanf("%d", &v);
                r = adiciona(r, v);
                printf("Operacao de insercao concluida.\n");
                break;
                
            case 3:
                printf("Digite um valor para pesquisar: ");
                scanf("%d", &b);
                p_aux = contem(b, r);
                if (p_aux == NULL)
                    printf("O valor %d NAO foi localizado.\n", b);
                else
                    printf("O valor %d foi localizado (Altura do no: %d).\n", b, p_aux->altura);
                break;
                
            case 4:
                n = numeroNos(r);
                printf("A arvore possui: %d nos.\n", n);
                break;
                
            case 5:
                printf("Estrutura AVL: ");
                exibirArvore(r);
                printf("\n");
                break;
            
            case 6:
                printf("Digite o valor para remover: ");
                scanf("%d", &v);
                r = removeNo(r, v);
                printf("Operacao de remocao concluida.\n");
                break;

            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (continuar);

    return 0;
}