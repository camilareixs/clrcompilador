#include <stdio.h>
#include <stdlib.h>

int main() {

    int opcao;

    while(1) {

        system("cls");

        printf("=====================================\n");
        printf("         CLR MINI IDE\n");
        printf("=====================================\n\n");

        printf("1 - Compilar codigo CLR\n");
        printf("2 - Ver codigo gerado em C\n");
        printf("3 - Ver arvore de derivacao\n");
        printf("0 - Sair\n\n");

        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:

                system("compilador.exe");

                printf("\n\nCompilacao finalizada!\n");

                break;

            case 2:

                printf("\n======= CODIGO C GERADO =======\n\n");

                system("type saida.c");

                break;

            case 3:

                printf("\n======= ARVORE DE DERIVACAO =======\n\n");

                system("type arvore.txt");

                break;

            case 4:

                printf("\n======= EXECUTANDO =======\n\n");

                system("gcc saida.c -o programa");

                system("programa.exe");

                break;

            case 0:

                return 0;

            default:

                printf("Opcao invalida!\n");
        }

        printf("\n\nPressione ENTER para continuar...");
        getchar();
        getchar();
    }

    return 0;
}