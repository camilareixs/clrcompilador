#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "tokens.h"

typedef struct {

    TokenType type;
    char lexema[100];

} Token;

extern FILE *arquivo;

Token getNextToken();

#endif