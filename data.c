#include "data.h"
#include "macros/cycle.h"

//Cria um estado vazio com o tabuleiro inicializado
ESTADO *inicializar_estado() {
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    e -> jogador_atual = 1;
    e -> num_jogadas = 0;
    e -> ultima_jogada.coluna = NULL;
    e -> ultima_jogada.linha = NULL;
    e -> tab[4][4] = BRANCA ;
    FORI(8) FORJ(8) e -> tab[i][j] = VAZIO;
    return e;
}

//Retorna qual o numero do jogador atual(1 ou 2)
int obter_jogador_atual(ESTADO *estado) {
    return estado ->  jogador_atual;
}

//Retorna o numero de jogadas efetuadas(Cada jogada tem o movimento dos dois jogadores)
int obter_numero_de_jogadas(ESTADO *estado) {
    return estado -> num_jogadas;
}

//Retorna o estado atual da casa na coordenada c (Branca, Preta ou Vazia)
int obter_estado_casa(ESTADO *e, COORDENADA c) {
    int x,y;
    x = e -> ultima_jogada.linha;
    y = e -> ultima_jogada.coluna;
    return e -> tab [x][y];
}

// Funções Auxiliares 
// Função que coloca uma coordenada no tabuleiro
void setCoordenada(COORDENADA cord, int col, int line) {
    cord.linha = col;
    cord.coluna = line;
}

// Função que cria uma jogada 
void setJogada(JOGADA jog, COORDENADA c1, COORDENADA c2) {
    jog.jogador1.coluna = c1.coluna;
    jog.jogador1.linha = c1.linha;
    jog.jogador2.coluna = c2.coluna;
    jog.jogador2.linha = c2.linha;
}

//Função que adiciona uma jogada ao estado
void addToJogadas(ESTADO *e, JOGADA j) {
    if(e->num_jogadas < 32) e->jogadas[e->num_jogadas++] = j;
}

// Função que coloca a o peça numa posição
void setPosicao(ESTADO *e, COORDENADA cord,  CASA casa) {
    e->tab[cord.coluna][cord.linha] = casa;
}

// Função que coloca ultima jogada
void setUltimaJogada(ESTADO *e, COORDENADA c1) {
    e->ultima_jogada.coluna = c1.coluna;
    e->ultima_jogada.linha = c1.linha;
}


