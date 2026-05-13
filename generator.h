#ifndef GENERATOR_H
#define GENERATOR_H

void iniciarGeracao();
void finalizarGeracao();

void gerarDeclaracao(char *tipo, char *nome);

void gerarAtribuicao(char *nome, char *expr);

void gerarEscrevaTexto(char *texto);
void gerarEscrevaVariavel(char *nome);

void gerarLeia(char *nome);

void gerarIf(char *condicao);

void gerarElse();

void fecharBloco();

void gerarWhile(char *condicao);

void gerarFor(
    char *inicio,
    char *condicao,
    char *incremento
);

#endif