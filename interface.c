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
    int dim = getNumJogadas(e), i = 0;
    while(i < dim) {
        JOGADA j = getJogada(e,i); 
        if(getLinha(getCoordenada(j,2)) == 0 && getColuna(getCoordenada(j,2)) == 0) { 
            int x1 = getLinha(getCoordenada(j,1))+ 1;
            int y1 = getColuna(getCoordenada(j,1)) + 'a';
            int x2 = getLinha(getCoordenada(j,2))+ 1;
            int y2 = getColuna(getCoordenada(j,2)) + 'a';
            printf("(Jogada %d): ",i);
            printf("%c%d %c%d\n",y1,x1,y2,x2);
            i++;
        } else {
            int x1 = getLinha(getCoordenada(j,1))+ 1;
            int y1 = getColuna(getCoordenada(j,1)) + 'a';
            printf("(Jogada %d): ",i);
            printf("%c%d\n",y1,x1);
            i++;
        }
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
