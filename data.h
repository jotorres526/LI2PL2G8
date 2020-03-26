/**
@file data.h
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


// funcões por documentar:::
COORDENADA getCoordenada (JOGADA j, int jogador);





/*******************Manipulação de COORDENADA******************/
/**
\brief Função que cria uma coordenada as coordenadas respetivas para a coluna e linha.
@param col  - coordenada respetiva para a coluna
@param line - coordenada respetiva para a linha
@returns Coordenada criada
*/
COORDENADA setCoordenada(int line, int col);

/**
\brief Função que dada um coordenada devolve o parâmetro da coluna.
@param c -coordenada necessária
@returns Parâmetro da coluna
*/
int getColuna(COORDENADA c);

/**
\brief Função que dada um coordenada devolve o parâmetro da linha.
@param c - coordenada necessária
@returns Parâmetro da linha
*/
int getLinha(COORDENADA c);

/**
\brief Funcao que cria uma coordenada Nula
Serve maioritariamente para o caso de criar uma jogada mas sem o jogador 2 ter ainda jogado
@returns Uma coordenada onde a coluna e a linha são -1
*/
COORDENADA createNullCoord();

/**
\brief Verifica se uma coordenada é null
@param c Coordenada a verificar
@returns True no caso de a coordenada ser null e False caso contrário
*/
Boolean isNullCoord(COORDENADA c);

/** 
\brief Função que devolve a casa onde a ultima casa foi realizada.
@param e - Estado do jogo.
@returns Casa
*/
CASA getCasa_ultimaJogada(ESTADO *e);

/*******************Manipulação de JOGADA******************/
/**
\brief Função que recebe uma jogada num determinado indice
@param e - Estado do jogo
@param idx - Indice da jogada no array de jogadas
@returns Jogada obtida
*/
JOGADA getJogada(ESTADO *e, int idx);

/** 
\brief Função que dada duas coordenadas cria uma JOGADA e retorna a respetiva jogada.
@param c1 - Primeira coordenada 
@param c2 - Segunda coordenada
@returns JOGADA adicionada
*/
JOGADA setJogada(COORDENADA c1, COORDENADA c2);

/**
\brief Função que obtém a ultima jogada realizada.
@param e - Estado do jogo.
@returns Coordenada da ultima jogada
*/
COORDENADA getUltimaJogada (ESTADO *e);

/** 
\brief Função que coloca a ultima jogada no estado.
@param e - Estado do jogo
@param c1 - Coordenada da ultima jogada
*/
void setUltimaJogada(ESTADO *e, COORDENADA c1);

/**
\brief Função que adiciona um JOGADA j ao estado.
@param e - Estado do jogo
@param j - Jogada a ser adicionada
*/
void addToJogadas(ESTADO *e, JOGADA j);

/** 
\brief Função que retorna o numero de jogadas.
@param e - Estado do jogo
@returns numero de jogadas realizadas até ao momento
*/
int getNumJogadas(ESTADO *e);

/**
\brief Troca a jogada num dado indice por outra
@param e Estado do jogo
@param j Nova jogada que irá tomar o lugar da antiga
@param idx Indice da jogada que sera para trocar
*/
void editJogadas(ESTADO* e, JOGADA j, int idx);

/*******************Manipulação de CASA******************/

/**
\brief Função que acede ao estado e ve qual a casa que se encontra numa determinada coordenada c.
@param e - Estado do jogo 
@param c - Coordenada a procurar
@returns Casa que está na respetiva coordenada
*/
CASA getCasa(ESTADO *e, COORDENADA c);

/** 
\brief Função que coloca uma casa numa determinada coordenada no estado.
@param e - Estado do jogo
@param c - coordenada 
@param casa - Tipo de casa a ser colocado em c
*/
void setCasa(ESTADO *e, COORDENADA c, CASA casa);

/** 
\brief Função que recebe coordenadas de dois inteiros e encontra a respetiva casa no estado.
@param e - Estado inicial do jogo
@param x - Parametro da linha
@param y - Parâmetro da coluna
@returns Casa que se encontra em x e y
*/
CASA getCasa_parametro(ESTADO *e, int x,int y);

/*******************Manipulação de jogador******************/
/** 
\brief Função que acede ao estado e muda o jogador, caso seja 1 muda para 2 e vice-versa.
@param e - Estado do jogo
*/
void swapJogador(ESTADO *e);

/** 
\brief Função que retorna qual é o jogador que está a jogar atual
@param e - Estado inicial
@returns Jogador atual
*/
int getjogador(ESTADO *e);

/*******************Inicializacao******************/
/**
\brief Inicializa o estado do jogo
A peça branca começa na coluna 4 da linha 4 e considera se essa a ultima jogada
Todo o resto do tabuleiro é inicializado a VAZIO
O tabuleiro é representado por um array bidimensional do tipo tab[linha][coluna]
@returns Novo estado do jogo
*/
ESTADO *inicializar_estado();
#endif