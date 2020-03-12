#include "data.h"
#include "macros/cycle.h"

//Funções que retornam valores já definidos
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
    return e -> tab[c.coluna][c.linha];
}

//Função obter a ultima jogada 
COORDENADA obter_ultima_jogada (ESTADO *e) {
    return e -> ultima_jogada;
}

////////////////////////////////////////////////////////////////////////
// Funções que retornam novos valores 
// Recebe uma coluna e uma linha e retorna uma coordenada
COORDENADA setCoordenada(int col, int line) {
    COORDENADA c;
    c.linha = col;
    c.coluna = line;
    return c;
}

//Recebe as coordenadas do jogador1 e do jogador2 respetivamente
//Retorna uma jogada 
JOGADA setJogada(COORDENADA c1, COORDENADA c2) {
    JOGADA jog; 
    jog.jogador1.coluna = c1.coluna;
    jog.jogador1.linha = c1.linha;
    jog.jogador2.coluna = c2.coluna;
    jog.jogador2.linha = c2.linha;
    return jog;
}

// Função que coloca ultima jogada
void setUltimaJogada(ESTADO *e, COORDENADA c1) {
    e -> ultima_jogada = setCoordenada(c1.coluna, c1.linha);
    if(e -> jogador_atual) e -> jogador_atual = 2;
    else e -> jogador_atual = 1;
}

//Função que adiciona uma jogada ao estado
void addToJogadas(ESTADO *e, JOGADA j) {
    if(e->num_jogadas < 32) e->jogadas[e->num_jogadas++] = j;
}

// Função que coloca a o peça numa posição
void setPosicao(ESTADO *e, COORDENADA cord,  CASA casa) {
    e->tab[cord.coluna][cord.linha] = casa;
}

//Cria um estado vazio com o tabuleiro inicializado
ESTADO *inicializar_estado() {
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    e -> jogador_atual = 1;
    e -> num_jogadas = 0;
    e -> ultima_jogada.coluna = -1;
    e -> ultima_jogada.linha  = -1;
    FORI(8) FORJ(8) e -> tab[i][j] = VAZIO;
    e -> tab[4][4] = BRANCA ;
    return e;
}