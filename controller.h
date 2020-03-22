#ifndef ___CONTROLLER_H___
#define ___CONTROLLER_H___

#include "data.h"
int jogar(ESTADO *estado, COORDENADA c);
// Função que determina o fim do jogo
Boolean isTerminado(ESTADO *e);
// Função que verifica se uma jogada é válida, isto é, se a proxima jogada a ser realizada é vizinha da posição anterior
Boolean isCasaVizinha(ESTADO *e, COORDENADA c);
// Funçao que ve qual o char de uma determinada casa.
char coordToChar(ESTADO *e, int linha, int coluna);
//Função que transforma um tabuleiro num array de strings
int tabuleiroToString(char **str, ESTADO *e);
ERROS gravar(FILE *fp, ESTADO *e, char *filename);
ERROS ler(ESTADO *e,  char *filename);
int winner (ESTADO *e) ;
#endif