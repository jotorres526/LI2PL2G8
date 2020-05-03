/**
@file main.c
Starting point do programa
*/
#include "interface.h"

/**
\brief Starting point do programa, também liberta o estado de memória
@returns 0 que significa que o programa terminou por chegar ao fim da função
*/
int main(){
    ESTADO *e = inicializar_estado();
    interpretador(e);
    free(e);
    return 0;
}