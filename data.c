#include "data.h"
void setCoordenada(COORDENADA cord, int col, int line) {
    cord.linha = col;
    cord.coluna = line;
}

void setJogada(JOGADA jog, int col1, int line1, int col2, int line2) {
    jog.jogador1.coluna = col1;
    jog.jogador1.linha = line1;
    jog.jogador2.coluna = col2;
    jog.jogador2.linha = line2;
}

void setTabuleiro(ESTADO *e, COORDENADA cord,  CASA casa) {
    e->tab[cord.coluna][cord.linha] = casa;
}

void setUltimaJogada(ESTADO *e, int col, int line) {
    e->ultima_jogada.coluna = col;
    e->ultima_jogada.linha = line;
}

void addToJogadas(ESTADO *e, JOGADA j) {
    if(e->num_jogadas < 32) e->jogadas[e->num_jogadas++] = j;
}
