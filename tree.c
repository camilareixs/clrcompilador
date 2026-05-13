#include <stdio.h>
#include "tree.h"

FILE *arvore;

void iniciarArvore() {

    arvore = fopen("arvore.txt", "w");

    fprintf(arvore, "PROGRAMA\n");
}

void adicionarNo(char *texto, int nivel) {

    for(int i = 0; i < nivel; i++) {

        fprintf(arvore, "|   ");
    }

    fprintf(arvore, "|-- %s\n", texto);
}

void finalizarArvore() {

    fclose(arvore);
}