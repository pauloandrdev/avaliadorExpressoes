#include <stdio.h>
#include <string.h>
#include "expressao.h"

int main() {
    Expressao exp;

    strcpy(exp.inFixa, "( 3 + 4 ) * 5");
    strcpy(exp.posFixa, getFormaPosFixa(exp.inFixa)); // calcula o valor da expressao pos-fixa
    exp.Valor = getValorPosFixa(exp.posFixa);

    printf("Expressao infixa: %s\n", exp.inFixa);
    printf("Expressao posfixa: %s\n", exp.posFixa);
    printf("Valor da expressao: %.2f\n", exp.Valor);

    return 0;
}
