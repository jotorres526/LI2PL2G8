
#include "bot.h"
int main(int argc, char **argv) {
    ESTADO *e = inicializar_estado();
    COORDENADA c;
    if(argc == 3) {
        ler(e,argv[1]);
        int jogadas = getNumJogadas(e);
        if(jogadas < 5) c = floodFill(e);
        else if(jogadas < 12) c = minimax(e, 6);
        else c = minimax(e, 8);
        jogar(e, c);
        gravar(e,argv[2]);  
    }
    return 0;
}
