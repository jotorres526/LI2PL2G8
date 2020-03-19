#ifndef ___CONTROLLER_H___
#define ___CONTROLLER_H___

#include "data.h"
int jogar(ESTADO *estado, COORDENADA c);

// Função que determina o fim do jogo
int endGame (ESTADO *e);
// Função que verifica se uma jogada é válida, isto é, se a proxima jogada a ser realizada é vizinha da posição anterior
int jogada_valida (ESTADO *e, COORDENADA c);
#endif