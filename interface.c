#include "interface.h"
#define BUF_SIZE 1024
void mostra_casa(CASA c) {
    switch(c) {
    case BRANCA:
        putchar('#');
        break;
    case PRETA:
        putchar('*');
        break;
    default:
        putchar('.');
    }
}

void mostrar_tabuleiro(ESTADO *e) {
    COORDENADA c;
    FORI(8) {
        FORJ(8) {
            c = setCoordenada(i, j);
            mostra_casa(obter_estado_casa(e, c));
        }
        putchar('\n');
    }
}

int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    if(fgets(linha, BUF_SIZE, stdin) == NULL) return 0;
    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col - 'a', *lin - '1'};
        jogar(e, coord);
        mostrar_tabuleiro(e);
    }
    return 1;
}