#include "interface.h"
#define BUF_SIZE 1024
void mostra_casa(CASA c) {
    switch(c) {
    case BRANCA:
        putchar('*');
        break;
    case PRETA:
        putchar('#');
        break;
    default:
        putchar('.');
    }
}

void mostrar_tabuleiro(ESTADO *e) {
    COORDENADA c;
    
    REVERSE_FORI(8) { //Percorrer todas as linhas de forma inversa
        printf("%d ", i + 1);
        FORJ(8) { //Percorrer todas as colunas de uma linha
            if(i == 7 && j == 7) putchar('2');
            else if(i == 0 && j == 0) putchar('1');
            else {
                c = setCoordenada(i, j); 
                CASA c1 = obter_estado_casa(e, c);
                mostra_casa(c1);
            }
        }
        putchar('\n');
    }
    printf("  abcdefgh\n");
}

int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    int isValid;
    printf("Bem vindo ao Rastros!\n\n");
    mostrar_tabuleiro(e);
    while(isValid) {
        printf("Jogada %d -> Para qual casa se vai mover, jogador %d?:", obter_numero_de_jogadas(e), obter_jogador_atual(e));
        if(fgets(linha, BUF_SIZE, stdin) == NULL) return 0;
        if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
            COORDENADA coord = {*col - 'a', *lin - '1'};
            isValid = jogar(e, coord);
            mostrar_tabuleiro(e);
        }
    }
    return 1;
}