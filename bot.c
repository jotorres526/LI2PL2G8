
#include "bot.h"
int main(int argc, char **argv) {
    ESTADO *e = inicializar_estado();
    ler(e,argv[1]);
    COORDENADA c = minimax(e,4);
    jogar(e,c);
    gravar(e,argv[2]);
    return 0;
}