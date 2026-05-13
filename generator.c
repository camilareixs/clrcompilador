#include <stdio.h>
#include <string.h>
#include "generator.h"

FILE *saida;

void iniciarGeracao() {
    saida = fopen("saida.c", "w");

    fprintf(saida, "#include <stdio.h>\n\n");
    fprintf(saida, "int main() {\n\n");
}

void finalizarGeracao() {
    fprintf(saida, "\nreturn 0;\n");
    fprintf(saida, "}\n");

    fclose(saida);
}

void gerarDeclaracao(char *tipo, char *nome) {

    if(strcmp(tipo, "inteiro") == 0) {
        fprintf(saida, "int %s;\n", nome);
    }
    else if(strcmp(tipo, "decimal") == 0) {
        fprintf(saida, "double %s;\n", nome);
    }
    else if(strcmp(tipo, "texto") == 0) {
        fprintf(saida, "char %s[256];\n", nome);
    }
    else if(strcmp(tipo, "logico") == 0) {
        fprintf(saida, "int %s;\n", nome);
    }
}

void gerarAtribuicao(char *nome, char *expr) {
    fprintf(saida, "%s = %s;\n", nome, expr);
}

void gerarEscrevaTexto(char *texto) {
    fprintf(saida, "printf(\"%%s\\n\", \"%s\");\n", texto);
}

void gerarEscrevaVariavel(char *nome) {
    fprintf(saida, "printf(\"%%d\\n\", %s);\n", nome);
}

void gerarLeia(char *nome) {
    fprintf(saida, "scanf(\"%%d\", &%s);\n", nome);
}

void gerarIf(char *condicao) {
    fprintf(saida, "if(%s) {\n", condicao);
}

void gerarElse() {
    fprintf(saida, "} else {\n");
}

void fecharBloco() {
    fprintf(saida, "}\n");
}

void gerarWhile(char *condicao) {
    fprintf(saida, "while(%s) {\n", condicao);
}

void gerarFor(char *inicio, char *condicao, char *incremento) {
    fprintf(saida, "for(%s; %s; %s) {\n",
        inicio,
        condicao,
        incremento
    );
}