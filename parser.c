#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"
#include "generator.h"
#include "semantic.h"
#include "tree.h"

Token tokenAtual;

void avancar() {
    tokenAtual = getNextToken();
    imprimirToken(tokenAtual);
}

void erroSintatico(char *esperado) {

    printf("\n========================\n");
    printf("ERRO SINTATICO\n");
    printf("========================\n");

    printf("Linha: %d\n", linha);

    printf("Esperado: %s\n", esperado);

    printf("Encontrado: %s\n", tokenAtual.lexema);

    exit(1);
}

void consumir(TokenType tipo, char *esperado) {

    if(tokenAtual.type == tipo) {
        avancar();
    }
    else {
        erroSintatico(esperado);
    }
}

void expressao(char *buffer);

void declaracao() {

    char tipo[50];
    char nome[50];

    strcpy(tipo, tokenAtual.lexema);

    adicionarNo("DECLARACAO", 1);

    adicionarNo(tipo, 2);

    avancar();

    if(tokenAtual.type != TOKEN_ID) {
        erroSintatico("identificador");
    }

    strcpy(nome, tokenAtual.lexema);

    adicionarNo(nome, 2);

    adicionarVariavel(nome, tipo);

    gerarDeclaracao(tipo, nome);

    avancar();

    consumir(TOKEN_PONTO_VIRGULA, ";");
}

void atribuicao() {

    char nome[50];
    char expr[200];

    adicionarNo("ATRIBUICAO", 1);

    strcpy(nome, tokenAtual.lexema);

    adicionarNo(nome, 2);

    verificarVariavelExiste(nome);

    avancar();

    consumir(TOKEN_IGUAL, "=");

    expressao(expr);

    adicionarNo(expr, 2);

    gerarAtribuicao(nome, expr);

    consumir(TOKEN_PONTO_VIRGULA, ";");
}

void escreva() {

    char valor[200];

    adicionarNo("ESCREVA", 1);

    consumir(TOKEN_ESCREVA, "escreva");

    consumir(TOKEN_ABRE_PAR, "(");

    if(tokenAtual.type == TOKEN_TEXTO) {

        strcpy(valor, tokenAtual.lexema);

        adicionarNo(valor, 2);

        gerarEscrevaTexto(valor);

        avancar();
    }
    else if(
        tokenAtual.type == TOKEN_ID ||
        tokenAtual.type == TOKEN_NUM_INT ||
        tokenAtual.type == TOKEN_NUM_DEC
    ) {

        strcpy(valor, tokenAtual.lexema);

        adicionarNo(valor, 2);

        gerarEscrevaVariavel(valor);

        avancar();
    }
    else {
        erroSintatico("texto ou valor");
    }

    consumir(TOKEN_FECHA_PAR, ")");

    consumir(TOKEN_PONTO_VIRGULA, ";");
}

void leia() {

    char nome[50];

    adicionarNo("LEIA", 1);

    consumir(TOKEN_LEIA, "leia");

    consumir(TOKEN_ABRE_PAR, "(");

    strcpy(nome, tokenAtual.lexema);

    adicionarNo(nome, 2);

    verificarVariavelExiste(nome);

    consumir(TOKEN_ID, "identificador");

    consumir(TOKEN_FECHA_PAR, ")");

    consumir(TOKEN_PONTO_VIRGULA, ";");

    gerarLeia(nome);
}

void cmdSe() {

    char esquerda[50];
    char operador[10];
    char direita[50];
    char condicao[200];

    adicionarNo("IF", 1);

    consumir(TOKEN_SE, "se");

    consumir(TOKEN_ABRE_PAR, "(");

    strcpy(esquerda, tokenAtual.lexema);

    avancar();

    strcpy(operador, tokenAtual.lexema);

    avancar();

    strcpy(direita, tokenAtual.lexema);

    avancar();

    consumir(TOKEN_FECHA_PAR, ")");

    sprintf(
        condicao,
        "%s %s %s",
        esquerda,
        operador,
        direita
    );

    adicionarNo(condicao, 2);

    gerarIf(condicao);

    consumir(TOKEN_ABRE_CHAVE, "{");

    while(
        tokenAtual.type != TOKEN_FECHA_CHAVE &&
        tokenAtual.type != TOKEN_EOF
    ) {
        comando();
    }

    consumir(TOKEN_FECHA_CHAVE, "}");

    if(tokenAtual.type == TOKEN_SENAO) {

        adicionarNo("SENAO", 2);

        gerarElse();

        avancar();

        consumir(TOKEN_ABRE_CHAVE, "{");

        while(
            tokenAtual.type != TOKEN_FECHA_CHAVE &&
            tokenAtual.type != TOKEN_EOF
        ) {
            comando();
        }

        consumir(TOKEN_FECHA_CHAVE, "}");

        fecharBloco();
    }
    else {
        fecharBloco();
    }
}

void cmdEnquanto() {

    char esquerda[50];
    char operador[10];
    char direita[50];
    char condicao[200];

    adicionarNo("WHILE", 1);

    consumir(TOKEN_ENQUANTO, "enquanto");

    consumir(TOKEN_ABRE_PAR, "(");

    strcpy(esquerda, tokenAtual.lexema);

    avancar();

    strcpy(operador, tokenAtual.lexema);

    avancar();

    strcpy(direita, tokenAtual.lexema);

    avancar();

    consumir(TOKEN_FECHA_PAR, ")");

    sprintf(
        condicao,
        "%s %s %s",
        esquerda,
        operador,
        direita
    );

    adicionarNo(condicao, 2);

    gerarWhile(condicao);

    consumir(TOKEN_ABRE_CHAVE, "{");

    while(
        tokenAtual.type != TOKEN_FECHA_CHAVE &&
        tokenAtual.type != TOKEN_EOF
    ) {
        comando();
    }

    consumir(TOKEN_FECHA_CHAVE, "}");

    fecharBloco();
}

void cmdPara() {

    char inicio[100];
    char condicao[100];
    char incremento[100];

    adicionarNo("FOR", 1);

    consumir(TOKEN_PARA, "para");

    consumir(TOKEN_ABRE_PAR, "(");

    strcpy(inicio, "");

    strcat(inicio, tokenAtual.lexema);

    avancar();

    strcat(inicio, " = ");

    consumir(TOKEN_IGUAL, "=");

    strcat(inicio, tokenAtual.lexema);

    avancar();

    consumir(TOKEN_PONTO_VIRGULA, ";");

    strcpy(condicao, "");

    strcat(condicao, tokenAtual.lexema);

    avancar();

    strcat(condicao, " ");

    strcat(condicao, tokenAtual.lexema);

    avancar();

    strcat(condicao, " ");

    strcat(condicao, tokenAtual.lexema);

    avancar();

    consumir(TOKEN_PONTO_VIRGULA, ";");

    strcpy(incremento, "");

    strcat(incremento, tokenAtual.lexema);

    avancar();

    strcat(incremento, " = ");

    consumir(TOKEN_IGUAL, "=");

    strcat(incremento, tokenAtual.lexema);

    avancar();

    strcat(incremento, " ");

    strcat(incremento, tokenAtual.lexema);

    avancar();

    strcat(incremento, " ");

    strcat(incremento, tokenAtual.lexema);

    avancar();

    consumir(TOKEN_FECHA_PAR, ")");

    adicionarNo(inicio, 2);

    adicionarNo(condicao, 2);

    adicionarNo(incremento, 2);

    gerarFor(
        inicio,
        condicao,
        incremento
    );

    consumir(TOKEN_ABRE_CHAVE, "{");

    while(
        tokenAtual.type != TOKEN_FECHA_CHAVE &&
        tokenAtual.type != TOKEN_EOF
    ) {
        comando();
    }

    consumir(TOKEN_FECHA_CHAVE, "}");

    fecharBloco();
}

void expressao(char *buffer) {

    strcpy(buffer, "");

    if(
        tokenAtual.type != TOKEN_ID &&
        tokenAtual.type != TOKEN_NUM_INT &&
        tokenAtual.type != TOKEN_NUM_DEC
    ) {
        erroSintatico("expressao");
    }

    strcat(buffer, tokenAtual.lexema);

    avancar();

    while(
        tokenAtual.type == TOKEN_MAIS ||
        tokenAtual.type == TOKEN_MENOS ||
        tokenAtual.type == TOKEN_MULT ||
        tokenAtual.type == TOKEN_DIV
    ) {

        strcat(buffer, " ");

        strcat(buffer, tokenAtual.lexema);

        avancar();

        strcat(buffer, " ");

        strcat(buffer, tokenAtual.lexema);

        avancar();
    }
}

void comando() {

    if(
        tokenAtual.type == TOKEN_INTEIRO ||
        tokenAtual.type == TOKEN_DECIMAL ||
        tokenAtual.type == TOKEN_TEXTO_TIPO ||
        tokenAtual.type == TOKEN_LOGICO
    ) {

        declaracao();
    }
    else if(tokenAtual.type == TOKEN_ID) {

        atribuicao();
    }
    else if(tokenAtual.type == TOKEN_ESCREVA) {

        escreva();
    }
    else if(tokenAtual.type == TOKEN_LEIA) {

        leia();
    }
    else if(tokenAtual.type == TOKEN_SE) {

        cmdSe();
    }
    else if(tokenAtual.type == TOKEN_ENQUANTO) {

        cmdEnquanto();
    }
    else if(tokenAtual.type == TOKEN_PARA) {

        cmdPara();
    }
    else {

        erroSintatico("comando valido");
    }
}

void parser() {

    iniciarArvore();

    adicionarNo("PROGRAMA", 0);

    avancar();

    while(tokenAtual.type != TOKEN_EOF) {

        comando();
    }

    finalizarArvore();

    printf("\nPrograma compilado com sucesso!\n");
}