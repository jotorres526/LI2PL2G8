
#include "bot.h"
int main(int argc, char **argv) {
    ESTADO *e = inicializar_estado();
    if(argc == 3) {
        ler(e,argv[1]);
        COORDENADA c = minimax(e,6);
        jogar(e,c); 
        gravar(e,argv[2]);  
    }
    return 0;
}
