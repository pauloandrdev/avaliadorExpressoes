#ifndef EXPRESSAO_H
#define EXPRESSAO_H

typedef struct {
    char posFixa[512];     // Expressão na forma pos-fixa
    char inFixa[512];      // Expressão na forma infixa
    float Valor;           // Valor numérico da expressão
} Expressao;

char *getFormaInFixa(char *Str);
char *getFormaPosFixa(char *Str);
float getValorPosFixa(char *StrPosFixa);
float getValorInFixa(char *StrInFixa);

#endif