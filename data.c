#include "data.h"
#include "macros/cycle.h"

void setUltimaJogada(ESTADO *e, int col, int line) {
    e -> ultima_jogada.coluna = col;
    e ->ultima_jogada.linha = line;
}

//Cria um estado vazio com o tabuleiro inicializado
ESTADO *inicializar_estado() {
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    e -> jogador_atual = 1;
    e -> num_jogadas = 0;
    setUltimaJogada (e,0,0);
    FORI(8) FORJ(8) e -> tab[i][j] = VAZIO;
    FORI(32) e -> jogadas [i] = NULL;
    return e;
}



int main () {
    return 0;
}
