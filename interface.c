#include "interface.h"
#define BUF_SIZE 1024

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

void mostra_jogadas(ESTADO *e) {
    int dim = getNumJogadas(e) + 1;
    JOGADA j;
    int linJ1, linJ2;
    char colJ1, colJ2;
    FORI(dim) {
        j = getJogada(e, i);
        if(isNullCoord(getCoordenada(j, 1))) break;
        linJ1 = getLinha(getCoordenada(j, 1)) + 1;
        colJ1 = getColuna(getCoordenada(j, 1)) + 'a';
        if (!isNullCoord(getCoordenada(j, 2))) {
            linJ2 = getLinha(getCoordenada(j, 2)) + 1;
            colJ2 = getColuna(getCoordenada(j, 2)) + 'a';
            printf("Jog %02d: %c%d %c%d\n", i + 1 , colJ1, linJ1, colJ2, linJ2);
        }
        else printf("Jog %02d: %c%d\n", getNumJogadas(e), colJ1, linJ1);
    }
}

int interpretador(ESTADO *e) {
    Boolean over = False;
    char linha[BUF_SIZE], filename[BUF_SIZE];
    char col[2], lin[2];
    printf("Bem vindo ao Rastros!\nInstruções: Q - Sair | | gr *ficheiro* - Grava jogo | | ler *ficheiro* - Lê savefile \n");
    mostrar_tabuleiro(e);
    for(int i = 0; !over; i++) {
        printf("(#%d Jogada %d Player %d)> ", i, getNumJogadas(e), getjogador(e));
        if(fgets(linha, BUF_SIZE, stdin) == NULL) return 0; //le o comando e retorna 0 caso nao seja escrito nada
        if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) { //If que executa a jogada
            COORDENADA coord = {*col - 'a', *lin - '1'};
            if(jogar(e, coord)) {
                mostrar_tabuleiro(e);
                if((over = isTerminado(e))) printf("Game over!\nParabéns jogador %d!\n",winner(e));
            }
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
                mostra_jogadas(e);
        }
    }
    return 1;
}
