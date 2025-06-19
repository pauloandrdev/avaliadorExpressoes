#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _USE_MATH_DEFINES 
#include <math.h>
#include <ctype.h>
#include "expressao.h"  

#define MAX 512

typedef struct { // estrutura de pilha para numeros float
    float items[MAX];
    int top;
} PilhaFloat;

typedef struct {
    char items[MAX][MAX];
    int top;
} PilhaStr;

void push(PilhaFloat *p, float v) { p->items[++(p->top)] = v; }
float pop(PilhaFloat *p) { return p->items[(p->top)--]; }
float topo(PilhaFloat *p) { return p->items[p->top]; }
int vazio(PilhaFloat *p) { return p->top == -1; }

void pushStr(PilhaStr *p, const char *v) { strcpy(p->items[++(p->top)], v); }
char *popStr(PilhaStr *p) { return p->items[(p->top)--]; }
char *topoStr(PilhaStr *p) { return p->items[p->top]; }

int precedencia(char op) {
    switch(op) {
        case '^': return 4;
        case '*': case '/': case '%': return 3;
        case '+': case '-': return 2;
        case '(': return 1;
    }
    return 0;
}

int ehOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

int ehFuncao(const char *tok) {
    return strcmp(tok,"sen") == 0 || strcmp(tok,"cos") == 0 || strcmp(tok,"tg") == 0 || strcmp(tok,"log") == 0 || strcmp(tok,"raiz") == 0;
}

float aplicaOperadorUnario(const char *op, float a) {
    if (strcmp(op, "sen") == 0) return sin(a * M_PI / 180);
    if (strcmp(op, "cos") == 0) return cos(a * M_PI / 180);
    if (strcmp(op, "tg") == 0) return tan(a * M_PI / 180);
    if (strcmp(op, "log") == 0) return log10(a);
    if (strcmp(op, "raiz") == 0) return sqrt(a);
    return 0;
}

float aplicaOperadorBinario(char op, float a, float b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '%': return fmod(a, b);
        case '^': return pow(a, b);
    }
    return 0;
}

float getValorPosFixa(char *StrPosFixa) {
    PilhaFloat p; p.top = -1;
    char *tok = strtok(StrPosFixa, " ");
    while (tok) {
        if (isdigit(tok[0]) || (tok[0] == '-' && isdigit(tok[1]))) {
            push(&p, atof(tok));
        } else if (ehFuncao(tok)) {
            if (!vazio(&p)) {
                float a = pop(&p);
                push(&p, aplicaOperadorUnario(tok, a));
            }
        } else if (ehOperador(tok[0])) {
            if (!vazio(&p)) {
                float b = pop(&p);
                if (!vazio(&p)) {
                    float a = pop(&p);
                    push(&p, aplicaOperadorBinario(tok[0], a, b));
                } else {
                    push(&p, b); // Devolve o valor se não há operandos suficientes
                }
            }
        }
        tok = strtok(NULL, " ");
    }
    return vazio(&p) ? 0 : pop(&p);
}

char *getFormaInFixa(char *Str) {
    static char res[512]; res[0] = '\0';
    PilhaStr p; p.top = -1;
    char copia[512]; strcpy(copia, Str);
    char *tok = strtok(copia, " ");
    while (tok) {
        if (isdigit(tok[0]) || (tok[0] == '-' && isdigit(tok[1]))) {
            pushStr(&p, tok);
        } else if (ehFuncao(tok)) {
            char *a = popStr(&p);
            char temp[512];
            sprintf(temp, "%s(%s)", tok, a);
            pushStr(&p, temp);
        } else if (ehOperador(tok[0])) {
            char *b = popStr(&p);
            char *a = popStr(&p);
            char temp[512];
            sprintf(temp, "(%s %s %s)", a, tok, b);
            pushStr(&p, temp);
        }
        tok = strtok(NULL, " "); // proximo token
    }
    strcpy(res, topoStr(&p));
    return res;
}

char *getFormaPosFixa(char *Str) {
    static char res[512];
    memset(res, 0, sizeof(res)); // Limpa o buffer
    PilhaStr ops; ops.top = -1;
    char copia[512]; strcpy(copia, Str);
    char *tok = strtok(copia, " ");
    while (tok) {
        if (isdigit(tok[0]) || (tok[0] == '-' && isdigit(tok[1]))) {
            strcat(res, tok); strcat(res, " ");
        } else if (ehFuncao(tok)) {
            pushStr(&ops, tok);
        } else if (strcmp(tok, "(") == 0) {
            pushStr(&ops, tok);
        } else if (strcmp(tok, ")") == 0) {
            while (ops.top >= 0 && strcmp(topoStr(&ops), "(") != 0) {
                strcat(res, popStr(&ops)); strcat(res, " ");
            }
            if (ops.top >= 0 && strcmp(topoStr(&ops), "(") == 0) {
                popStr(&ops); // Remove o parêntese
            }
            if (ops.top >= 0 && ehFuncao(topoStr(&ops))) {
                strcat(res, popStr(&ops)); strcat(res, " ");
            }
        } else if (ehOperador(tok[0])) {
            while (ops.top >= 0 && strcmp(topoStr(&ops), "(") != 0 && 
                   ehOperador(topoStr(&ops)[0]) &&
                   precedencia(topoStr(&ops)[0]) >= precedencia(tok[0])) {
                strcat(res, popStr(&ops)); strcat(res, " ");
            }
            pushStr(&ops, tok);
        }
        tok = strtok(NULL, " ");
    }
    while (ops.top >= 0) {
        strcat(res, popStr(&ops)); strcat(res, " ");
    }
    return res;
}

float getValorInFixa(char *StrInFixa) {
    char *pos = getFormaPosFixa(StrInFixa);
    char copia[512]; strcpy(copia, pos);
    return getValorPosFixa(copia);
}
