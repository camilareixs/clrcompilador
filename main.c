#include <stdio.h>

#include "lexer.h"
#include "parser.h"
#include "generator.h"
#include "tree.h"

extern FILE *arquivo;

int main() {

    arquivo = fopen("entrada.clr", "r");

    if(arquivo == NULL) {

        printf("Erro ao abrir entrada.clr\n");

        return 1;
    }

    iniciarArvore();

    iniciarGeracao();

    parser();

    finalizarGeracao();

    fclose(arquivo);

    printf("\nPrograma compilado com sucesso!\n");

    printf("Arquivo C gerado: saida.c\n");

    printf("Arvore gerada: arvore.txt\n");

    return 0;
}