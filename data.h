/**
@file dados.h
Definição do estado e das funções que o manipulam
*/
#ifndef ___DATA_H___
#define ___DATA_H___
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macros/cycle.h"
#include "macros/boolean.h"

/**
\brief Tipo de dados para os erros
*/
typedef enum {
  OK, 
  COORDENADA_INVALIDA, 
  JOGADA_INVALIDA, 
  ERRO_LER_TAB,
  ERRO_ABRIR_FICHEIRO,
} ERROS;

/**
\brief Tipo de dados para a casa
*/
typedef enum {
  UM = '1',
  DOIS = '2',
  VAZIO = '.',
  BRANCA = '*',
  PRETA = '#'
} CASA;

/**
\brief Tipo de dados para as coordenadas
*/
typedef struct {
    int coluna;
    int linha;
} COORDENADA;

/**
\brief Tipo de dados para a jogada
*/
typedef struct {
    COORDENADA jogador1;
    COORDENADA jogador2;
} JOGADA;

/**
\brief Tipo de dados para as jogadas
*/
typedef JOGADA JOGADAS[32];

/**
\brief Tipo de dados para o estado
*/

typedef struct {
  /** O tabuleiro */
    CASA tab[8][8];
  /** As jogadas */
    JOGADAS jogadas;
  /** O número das jogadas, usado no prompt */
    int num_jogadas;
  /** O jogador atual */
    int jogador_atual;
  /** O nº de comando, usado no prompt */
  int num_comando;
  /** A coordenada da última jogada */
  COORDENADA ultima_jogada;
} ESTADO;

/*******************Manipulação de COORDENADA******************/
/**
 * Função que cria uma coordenada recebendo as coordenadas respetivas para a coluna e linha.
*/
COORDENADA setCoordenada(int line, int col);
/**
 * Função que dada um coordenada devolve o parâmetro da coluna.
*/
int getColuna(COORDENADA c);
/** 
 * Funçao que dada uma coordenada devolve o parâmetro da linha.
 */
int getLinha(COORDENADA c);
/** 
 * Função que devolve a casa onde a ultima casa foi realizada.
*/
CASA getCasa_ultimaJogada(ESTADO *e);

/*******************Manipulação de JOGADA******************/

/**
 * Função que recebe uma jogada num determinado indice
*/
JOGADA getJogada(ESTADO *e, int idx);

/** 
 * Função que dada duas coordenadas cria uma JOGADA e retorna a respetiva jogada.
*/
JOGADA setJogada(COORDENADA c1, COORDENADA c2);

/**
 * Função que obtém a ultima jogada realizada.
*/
COORDENADA getUltimaJogada (ESTADO *e);

/** 
 * Função que coloca a ultima jogada no estado.
*/
void setUltimaJogada(ESTADO *e, COORDENADA c1);

/**
 * Função que adiciona um JOGADA j ao estado.
*/
void addToJogadas(ESTADO *e, JOGADA j);

/** 
 * Função que retorna o numero de jogadas realizadas até um determinado momento.
*/
int getNumJogadas(ESTADO *e);


/*******************Manipulação de CASA******************/

/**
 * Função que acede ao estado e ve qual a casa que se encontra numa determinada coordenada c.
*/
CASA getCasa(ESTADO *e, COORDENADA c);

/** 
 * Função que coloca uma casa numa determinada coordenada no estado.
*/
void setCasa(ESTADO *e, COORDENADA c, CASA casa);

/** 
 * Função que recebe coordenadas de dois inteiros e encontra a respetiva casa no estado.
*/
CASA getCasa_parametro(ESTADO *e, int x,int y);

/*******************Manipulação de jogador******************/
/** 
 * Função que acede ao estado e muda o jogador, caso seja 1 muda para 2 e vice-versa.
*/
void swapJogador(ESTADO *e);

/** 
 * Função que retorna qual é o jogador que está a jogar atual
*/
int getjogador(ESTADO *e);

/*******************Inicializacao******************/
/**
* Inicializa o estado do jogo
* A peça branca começa na coluna 4 da linha 4 e considera se essa a ultima jogada
* Todo o resto do tabuleiro é inicializado a VAZIO
* O tabuleiro é representado por um array bidimensional do tipo tab[linha][coluna]
*/
ESTADO *inicializar_estado();
#endif