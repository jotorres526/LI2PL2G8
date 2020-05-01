#include "interface.h"
int main(){
    ESTADO *e = inicializar_estado();
    interpretador(e);
    free(e);
    return 0;
}