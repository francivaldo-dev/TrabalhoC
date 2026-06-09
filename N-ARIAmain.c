#include <stdio.h>
#include <stdlib.h>
#include "N-ARIA.h"

int main(int argc, char** argv) {
    PONT raizGlobal = NULL; // Variável corrigida para escopo global da main
    int v, p, b, n, h, modo;
    int continuar = 1;

    do {
        printf("\n\tMenu de Opcao\n\n");
        printf("1. Inicializa a arvore \n");
        printf("2. Insere na arvore\n");
        printf("3. Buscar um valor na arvore\n");
        printf("4. Conta o numero de nos da arvore\n");
        printf("5. Imprime a arvore\n");
        printf("6. Imprime a altura da arvore\n");
        printf("7. Remover um no da arvore\n"); // Nova opção adicionada
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
                printf("Digite o no raiz da arvore: ");
                scanf("%d", &v);
                raizGlobal = criarRaiz(v);
                printf("Arvore criada com sucesso!\n");
                break;

            case 2:
                if (raizGlobal == NULL) {
                    printf("Inicialize a arvore primeiro (Opcao 1).\n");
                    break;
                }
                printf("Digite um numero para inserir na arvore: ");
                scanf("%d", &v);
                printf("Digite o no pai: ");
                scanf("%d", &p);
                if (inserirFilho(raizGlobal, v, p)) {
                    printf("No inserido com sucesso!\n");
                } else {
                    printf("Erro: No pai %d nao encontrado.\n", p);
                }
                break;
                
            case 3:
                printf("Digite um valor para pesquisar na arvore: ");
                scanf("%d", &b);
                PONT r = buscarChave(raizGlobal, b);
                if (r == NULL)
                    printf("O valor %d nao foi localizado.\n", b);
                else
                    printf("O valor %d foi localizado na arvore.\n", b);
                break;
                
            case 4:
                n = numeroDeNos2(raizGlobal);
                printf("A arvore tem %d elementos.\n", n);
                break;
                
            case 5:
                printf("Estrutura da arvore: ");
                exibirArvore(raizGlobal);
                printf("\n");
                break;
            
            case 6:
                h = altura(raizGlobal);
                printf("A altura da arvore e %d.\n", h);
                break;

            case 7:
                if (raizGlobal == NULL) {
                    printf("Arvore vazia.\n");
                    break;
                }
                printf("Digite o valor do no que deseja remover: ");
                scanf("%d", &v);
                printf("Escolha o modo de remocao:\n");
                printf("1 - Deletar o no e TODOS os seus filhos (Cascata)\n");
                printf("2 - Deletar o no e PROMOVER os filhos para o avo\n");
                printf("Opcao: ");
                scanf("%d", &modo);
                
                if (modo == 1 || modo == 2) {
                    raizGlobal = removerNoNAria(raizGlobal, v, modo);
                    printf("Processo de remocao concluido.\n");
                } else {
                    printf("Modo invalido! Operacao cancelada.\n");
                }
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