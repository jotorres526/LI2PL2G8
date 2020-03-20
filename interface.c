#include "interface.h"
#define BUF_SIZE 1024

void mostrar_tabuleiro(ESTADO *e) {
    char **tabuleiro = malloc(8 * sizeof(char *));
    int size = tab_to_string(tabuleiro, e);
    FORI(8) {
        printf("%d ", 8 - i);
        FORJ(9) putchar(tabuleiro[i][j]);
    }
    printf("  abcdefgh\n");
    FORI(size) free(tabuleiro[i]);
    free(tabuleiro);
}

int interpretador(ESTADO *e) {
    char linha[BUF_SIZE], filename[BUF_SIZE];
    char col[2], lin[2];
    FILE *fp;
    printf("Bem vindo ao Rastros!\nInstruções: Q - Sair; gr - Gravar,\n");
    mostrar_tabuleiro(e);
    for(int i = 0; endGame(e); i++) {
        printf("(#%d Jogada %d Player %d)> ", i, getNumJogadas(e), getjogador(e));
        if(fgets(linha, BUF_SIZE, stdin) == NULL) return 0; //le o comando e retorna 0 caso nao seja escrito nada
        if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) { //If que executa a jogada
            COORDENADA coord = {*col - 'a', *lin - '1'};
            if(jogar(e, coord)) mostrar_tabuleiro(e);
        } else if(strcmp(linha, "Q\n") == 0) { //Comando para sair do jogo
            printf("Saindo do jogo...\n");
            return 0;
        } else if(sscanf(linha, "gr %s", filename) == 1) { //Comando que guarda o tabuleiro atual (cria um "savefile")
            if(gravar(fp, e, filename) == OK) printf("Guardado com sucesso\n");
        } else if(sscanf(linha, "ler %s", filename) == 1) { //Comando que le um "savefile"
            fp = fopen(filename, "r");
            fclose(fp);
        }
    }
    return 1;
}