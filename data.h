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

//Cria um estado vazio com o tabuleiro inicializado
ESTADO *inicializar_estado();
//Retorna qual o numero do jogador atual(1 ou 2)
int obter_jogador_atual(ESTADO *estado);
//Retorna o numero de jogadas efetuadas(Cada jogada tem o movimento dos dois jogadores)
int obter_numero_de_jogadas(ESTADO *estado);
//Retorna o estado atual da casa na coordenada c (Branca, Preta ou Vazia)
CASA obter_estado_casa(ESTADO *e, COORDENADA c);
//Retorna uma coordenada
COORDENADA setCoordenada(int line, int col);
//Função obter a ultima jogada 
COORDENADA obter_ultima_jogada (ESTADO *e);
//Retorna uma jogada 
JOGADA setJogada(COORDENADA c1, COORDENADA c2);
//Função que adiciona uma jogada ao estado
void addToJogadas(ESTADO *e, JOGADA j);
// Função que coloca a o peça numa posição
void setPosicao(ESTADO *e, COORDENADA cord,  CASA casa);
// Função que coloca ultima jogada
void setUltimaJogada(ESTADO *e, COORDENADA c1);
//Altera o jogador atual
void swapJogador(ESTADO *e);
// Função que verifica se uma jogada é válida, isto é, se a proxima jogada a ser realizada é vizinha da posição anterior
int jogada_valida (ESTADO *e, COORDENADA c) ;
// Função que determina o fim do jogo acaba
int endGame (ESTADO *e) ;
#endif