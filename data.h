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
COORDENADA setCoordenada(int line, int col);
int getColuna(COORDENADA c);
int getLinha(COORDENADA c);

/*******************Manipulação de JOGADA******************/
JOGADA getJogada(ESTADO *e, int idx);
JOGADA setJogada(COORDENADA c1, COORDENADA c2);
COORDENADA getUltimaJogada (ESTADO *e);
void setUltimaJogada(ESTADO *e, COORDENADA c1);
void addToJogadas(ESTADO *e, JOGADA j);
int getNumJogadas(ESTADO *e);


/*******************Manipulação de CASA******************/
CASA getCasa(ESTADO *e, COORDENADA c);
void setCasa(ESTADO *e, COORDENADA c, CASA casa);
CASA getCasa_parametro(ESTADO *e, int x,int y);

/*******************Manipulação de jogador******************/
void swapJogador(ESTADO *e);
int getjogador(ESTADO *e);
/*******************Inicializacao******************/
ESTADO *inicializar_estado();
#endif