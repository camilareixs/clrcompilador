#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "semantic.h"

char variaveis[100][50];

char tipos[100][50];

int totalVariaveis = 0;

void verificarDeclaracao(char *nome) {

    for(int i = 0; i < totalVariaveis; i++) {

        if(strcmp(variaveis[i], nome) == 0) {

            printf("\nERRO SEMANTICO!\n");

            printf("Variavel ja declarada: %s\n", nome);

            exit(1);
        }
    }
}

void adicionarVariavel(char *nome, char *tipo) {

    strcpy(variaveis[totalVariaveis], nome);

    strcpy(tipos[totalVariaveis], tipo);

    totalVariaveis++;
}

void verificarVariavelExiste(char *nome) {

    for(int i = 0; i < totalVariaveis; i++) {

        if(strcmp(variaveis[i], nome) == 0) {

            return;
        }
    }

    printf("\nERRO SEMANTICO!\n");

    printf("Variavel nao declarada: %s\n", nome);

    exit(1);
}