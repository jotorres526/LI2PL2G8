#include "interface.h"
int main(){
    ESTADO *e = inicializar_estado();
    interpretador(e);
    return 0;
}