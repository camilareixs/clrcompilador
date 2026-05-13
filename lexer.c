#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"

FILE *arquivo;

char* categoriaToken(TokenType type) {

    switch(type) {

        case TOKEN_INTEIRO:
            return "TIPO_INTEIRO";

        case TOKEN_DECIMAL:
            return "TIPO_DECIMAL";

        case TOKEN_TEXTO:
            return "TIPO_TEXTO";

        case TOKEN_LOGICO:
            return "TIPO_LOGICO";

        case TOKEN_VERDADEIRO:
            return "VERDADEIRO";

        case TOKEN_FALSO:
            return "FALSO";

        case TOKEN_SE:
            return "SE";

        case TOKEN_SENAO:
            return "SENAO";

        case TOKEN_ENQUANTO:
            return "ENQUANTO";

        case TOKEN_PARA:
            return "PARA";

        case TOKEN_ESCREVA:
            return "ESCREVA";

        case TOKEN_LEIA:
            return "LEIA";

        case TOKEN_ID:
            return "ID";

        case TOKEN_NUM_INT:
            return "NUM_INT";

        case TOKEN_NUM_DEC:
            return "NUM_DEC";

        case TOKEN_STRING:
            return "TEXTO";

        case TOKEN_MAIS:
            return "SOMA";

        case TOKEN_MENOS:
            return "SUBTRACAO";

        case TOKEN_MULT:
            return "MULTIPLICACAO";

        case TOKEN_DIV:
            return "DIVISAO";

        case TOKEN_POT:
            return "POTENCIA";

        case TOKEN_IGUAL:
            return "ATRIBUICAO";

        case TOKEN_IGUAL_IGUAL:
            return "IGUAL";

        case TOKEN_DIFERENTE:
            return "DIFERENTE";

        case TOKEN_MAIOR:
            return "MAIOR";

        case TOKEN_MENOR:
            return "MENOR";

        case TOKEN_MAIOR_IGUAL:
            return "MAIOR_IGUAL";

        case TOKEN_MENOR_IGUAL:
            return "MENOR_IGUAL";

        case TOKEN_E:
            return "E";

        case TOKEN_OU:
            return "OU";

        case TOKEN_PONTO_VIRGULA:
            return "PONTO_VIRGULA";

        case TOKEN_VIRGULA:
            return "VIRGULA";

        case TOKEN_ABRE_PAR:
            return "ABRE_PAR";

        case TOKEN_FECHA_PAR:
            return "FECHA_PAR";

        case TOKEN_ABRE_CHAVE:
            return "ABRE_CHAVE";

        case TOKEN_FECHA_CHAVE:
            return "FECHA_CHAVE";

        case TOKEN_EOF:
            return "EOF";

        default:
            return "ERRO";
    }
}

void imprimirToken(Token token) {

    printf("<%s, %s>\n",
           categoriaToken(token.type),
           token.lexema);
}

Token getNextToken() {

    Token token;

    int c;

    do {
        c = fgetc(arquivo);
    }
    while(c == ' ' || c == '\n' || c == '\t' || c == '\r');

    // EOF
    if(c == EOF) {

        token.type = TOKEN_EOF;

        strcpy(token.lexema, "EOF");

        imprimirToken(token);

        return token;
    }

    // IDENTIFICADORES E PALAVRAS RESERVADAS
    if(isalpha(c)) {

        int i = 0;

        while(isalnum(c) || c == '_') {

            token.lexema[i++] = c;

            c = fgetc(arquivo);
        }

        token.lexema[i] = '\0';

        ungetc(c, arquivo);

        if(strcmp(token.lexema, "inteiro") == 0)
            token.type = TOKEN_INTEIRO;

        else if(strcmp(token.lexema, "decimal") == 0)
            token.type = TOKEN_DECIMAL;

        else if(strcmp(token.lexema, "texto") == 0)
            token.type = TOKEN_TEXTO;

        else if(strcmp(token.lexema, "logico") == 0)
            token.type = TOKEN_LOGICO;

        else if(strcmp(token.lexema, "verdadeiro") == 0)
            token.type = TOKEN_VERDADEIRO;

        else if(strcmp(token.lexema, "falso") == 0)
            token.type = TOKEN_FALSO;

        else if(strcmp(token.lexema, "se") == 0)
            token.type = TOKEN_SE;

        else if(strcmp(token.lexema, "senao") == 0)
            token.type = TOKEN_SENAO;

        else if(strcmp(token.lexema, "enquanto") == 0)
            token.type = TOKEN_ENQUANTO;

        else if(strcmp(token.lexema, "para") == 0)
            token.type = TOKEN_PARA;

        else if(strcmp(token.lexema, "escreva") == 0)
            token.type = TOKEN_ESCREVA;

        else if(strcmp(token.lexema, "leia") == 0)
            token.type = TOKEN_LEIA;

        else if(strcmp(token.lexema, "e") == 0)
            token.type = TOKEN_E;

        else if(strcmp(token.lexema, "ou") == 0)
            token.type = TOKEN_OU;

        else
            token.type = TOKEN_ID;

        imprimirToken(token);

        return token;
    }

    // NÚMEROS
    if(isdigit(c)) {

        int i = 0;

        int decimal = 0;

        while(isdigit(c) || c == '.') {

            if(c == '.')
                decimal = 1;

            token.lexema[i++] = c;

            c = fgetc(arquivo);
        }

        token.lexema[i] = '\0';

        ungetc(c, arquivo);

        if(decimal)
            token.type = TOKEN_NUM_DEC;

        else
            token.type = TOKEN_NUM_INT;

        imprimirToken(token);

        return token;
    }

    // STRINGS
    if(c == '"') {

        int i = 0;

        c = fgetc(arquivo);

        while(c != '"' && c != EOF) {

            token.lexema[i++] = c;

            c = fgetc(arquivo);
        }

        token.lexema[i] = '\0';

        token.type = TOKEN_STRING;

        imprimirToken(token);

        return token;
    }

    // OPERADORES E SÍMBOLOS
    switch(c) {

        case '+':

            token.type = TOKEN_MAIS;
            strcpy(token.lexema, "+");
            break;

        case '-':

            token.type = TOKEN_MENOS;
            strcpy(token.lexema, "-");
            break;

        case '*':

            token.type = TOKEN_MULT;
            strcpy(token.lexema, "*");
            break;

        case '/':

            token.type = TOKEN_DIV;
            strcpy(token.lexema, "/");
            break;

        case '^':

            token.type = TOKEN_POT;
            strcpy(token.lexema, "^");
            break;

        case ';':

            token.type = TOKEN_PONTO_VIRGULA;
            strcpy(token.lexema, ";");
            break;

        case ',':

            token.type = TOKEN_VIRGULA;
            strcpy(token.lexema, ",");
            break;

        case '(':

            token.type = TOKEN_ABRE_PAR;
            strcpy(token.lexema, "(");
            break;

        case ')':

            token.type = TOKEN_FECHA_PAR;
            strcpy(token.lexema, ")");
            break;

        case '{':

            token.type = TOKEN_ABRE_CHAVE;
            strcpy(token.lexema, "{");
            break;

        case '}':

            token.type = TOKEN_FECHA_CHAVE;
            strcpy(token.lexema, "}");
            break;

        case '=':

            c = fgetc(arquivo);

            if(c == '=') {

                token.type = TOKEN_IGUAL_IGUAL;
                strcpy(token.lexema, "==");
            }
            else {

                token.type = TOKEN_IGUAL;
                strcpy(token.lexema, "=");

                ungetc(c, arquivo);
            }

            break;

        case '!':

            c = fgetc(arquivo);

            if(c == '=') {

                token.type = TOKEN_DIFERENTE;
                strcpy(token.lexema, "!=");
            }
            else {

                token.type = TOKEN_ERRO;
                strcpy(token.lexema, "!");
            }

            break;

        case '>':

            c = fgetc(arquivo);

            if(c == '=') {

                token.type = TOKEN_MAIOR_IGUAL;
                strcpy(token.lexema, ">=");
            }
            else {

                token.type = TOKEN_MAIOR;
                strcpy(token.lexema, ">");

                ungetc(c, arquivo);
            }

            break;

        case '<':

            c = fgetc(arquivo);

            if(c == '=') {

                token.type = TOKEN_MENOR_IGUAL;
                strcpy(token.lexema, "<=");
            }
            else {

                token.type = TOKEN_MENOR;
                strcpy(token.lexema, "<");

                ungetc(c, arquivo);
            }

            break;

        default:

            token.type = TOKEN_ERRO;

            token.lexema[0] = c;
            token.lexema[1] = '\0';
    }

    imprimirToken(token);

    return token;
}