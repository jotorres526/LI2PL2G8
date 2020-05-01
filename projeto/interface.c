#include "interface.h"
#define BUF_SIZE 1024

void mostraJogada(JOGADA j) {
    COORDENADA c1 = getCoordenada(j, 1);
    COORDENADA c2 = getCoordenada(j, 2);
    int linJ1, linJ2;
    char colJ1, colJ2;
    colJ1 = getColuna(c1) + 'a';
    linJ1 = getLinha(c1) + 1;
    if(!isNullCoord(c2)) {
        linJ2 = getLinha(getCoordenada(j, 2)) + 1;
        colJ2 = getColuna(getCoordenada(j, 2)) + 'a';
        printf("%c%d %c%d\n", colJ1, linJ1, colJ2, linJ2);
    } else { 
        printf("%c%d\n", colJ1, linJ1);
    }
}

void mostrar_tabuleiro(ESTADO *e) {
    COORDENADA c;
    REVERSE_FORI(8) {
        printf("%d ", i + 1);
        FORJ(8) {
            c = setCoordenada(i, j);
            putchar(getCasa(e, c));
        }
        putchar('\n');
    }
    printf("  abcdefgh\n");
}

void logJogadas(ESTADO *e) {
    JOGADA j;
    FORI(getPointerJogada(e)) {
        j = getJogada(e, i);
        printf("Jog %02d: ", i + 1);
        mostraJogada(j);
    }
    if(getPointerJogada(e) == getNumJogadas(e)) {
        j = getJogada(e, getPointerJogada(e));
        if(!isNullCoord(getCoordenada(j, 1))) {
            printf("Jog %02d: ", getPointerJogada(e) + 1);
            mostraJogada(j);
        }
    }
}

int interpretador(ESTADO *e) {
    Boolean over = False;
    char linha[BUF_SIZE], filename[BUF_SIZE];
    char col[2], lin[2];
    int pos;
    printf("Bem vindo ao Rastros!\nInstruções: Q - Sair | | gr *ficheiro* - Grava jogo | | ler *ficheiro* - Lê savefile \n");
    mostrar_tabuleiro(e);
    for(int i = 0; !over; i++) {
        printf("(#%d Jogada %d Player %d)> ", i, getPointerJogada(e) + 1, getjogador(e));
        if(fgets(linha, BUF_SIZE, stdin) == NULL) return 0; //le o comando e retorna 0 caso nao seja escrito nada
        if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) { //If que executa a jogada
            COORDENADA coord = {*col - 'a', *lin - '1'};
            if(jogar(e, coord) == OK) {
                mostrar_tabuleiro(e);
                if((over = isTerminado(e))) printf("Game over!\nParabéns jogador %d!\n",winner(e));
            } else printf("Jogada inválida... Jogue novamente\n");
        } else if(strcmp(linha, "Q\n") == 0) { //Comando para sair do jogo
            printf("Saindo do jogo...\n");
            return 0;
        } else if(sscanf(linha, "gr %s", filename) == 1) { //Comando que guarda o tabuleiro atual (cria um "savefile")
            if(gravar(e, filename) == OK) printf("Guardado com sucesso\n");
        } else if(sscanf(linha, "ler %s", filename) == 1) { //Comando que le um "savefile"
            if(ler(e, filename) == OK) {
                printf("A ler tabuleiro...\n");
                mostrar_tabuleiro(e);
            }
        } else if(strcmp(linha, "movs\n") == 0) {
            logJogadas(e);
        } else if(sscanf(linha, "pos %d", &pos) == 1) {
            if(goToPos(e, pos)) mostrar_tabuleiro(e);
            else printf("Introduza uma jogada válida!\n");
        } else if(strcmp(linha, "jog\n") == 0) {
            if(jog(e, 1) == OK) {
                mostrar_tabuleiro(e);
                if((over = isTerminado(e))) printf("Game over!\nParabéns jogador %d!\n",winner(e));
            } else printf("erro\n");
        } else if(strcmp(linha, "jog2\n") == 0) {
            if(jog(e, 2) == OK) {
                mostrar_tabuleiro(e);
                if((over = isTerminado(e))) printf("Game over!\nParabéns jogador %d!\n", winner(e));
            } else printf("erro\n");
        }
    }
    return 1;
}
