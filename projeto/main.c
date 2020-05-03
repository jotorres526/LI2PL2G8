/**
@file main.c
Starting point do programa
*/
#include "interface.h"
//Starting point do programa
int main(){
    ESTADO *e = inicializar_estado();
    interpretador(e);
    free(e);
    return 0;
}