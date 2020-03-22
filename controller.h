/**
@file controller.h
Definição da lógica e das funções que o manipulam
*/
#ifndef ___CONTROLLER_H___
#define ___CONTROLLER_H___
#include "data.h"

/**
 *  Definição da função que realiza as jogadas. 
 *  Nesta função são realizadas as seguintes tarefas:
 *      Verifica se a coordenada introduzida é vizinha, se está vazia e se está dentro do tabuleiro.
 *      Visto isto caso seja o jogador 1 a jogar , coloca a jogada no parametro ultima jogada e troca para o jogador 2.
 *      Caso seja o jogador 2 coloca também a nova jogada na ultima jogada, troca o jogador e ainda coloca no array de jogadas.
 *      Caso a jogada não seja possível retorna 1. 
*/
int jogar(ESTADO *estado, COORDENADA c);
/**
 *  Função que determina se o Jogo está terminado.
 *  Neste sentido verifica se o algum jogador chegou a casa UM ou DOIS.
 *  Caso chegue retorna True caso contrário falso.
 *  
 */
Boolean isTerminado(ESTADO *e);
/**
 *  Função que verifica se a jogada a ser realizada é vizinha da casa anterior. 
 *  Retorna True caso seja, False caso contrário.
*/
Boolean isCasaVizinha(ESTADO *e, COORDENADA c);
/*
    Funçao que ve qual o char de uma determinada casa.
*/
char coordToChar(ESTADO *e, int linha, int coluna);
/*

*/
//Função que transforma um tabuleiro num array de strings
int tabuleiroToString(char **str, ESTADO *e);
ERROS gravar(FILE *fp, ESTADO *e, char *filename);
ERROS ler(ESTADO *e,  char *filename);
int winner (ESTADO *e) ;
#endif