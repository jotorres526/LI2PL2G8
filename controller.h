/**
@file controller.h
Definição da lógica e controlo do estado
*/
#ifndef ___CONTROLLER_H___
#define ___CONTROLLER_H___
#include "data.h"

/**
\brief Definição da função que realiza as jogadas. 
Nesta função são realizadas as seguintes tarefas:
Verifica se a coordenada introduzida é vizinha, se está vazia e se está dentro do tabuleiro.
Visto isto caso seja o jogador 1 a jogar , coloca a jogada no parametro ultima jogada e troca para o jogador 2.
Caso seja o jogador 2 coloca também a nova jogada na ultima jogada, troca o jogador e ainda coloca no array de jogadas.
Caso a jogada não seja possível retorna 1. 
@param estado Apontador para o estado
@param c A coordenada
@returns 1 no caso de a jogada ser válida e 0 no caso contrário
*/
ERROS jogar(ESTADO *e, COORDENADA c);

/**
\brief Função que determina se o Jogo está terminado.
Neste sentido verifica se o algum jogador chegou a casa UM ou DOIS.
Caso chegue retorna True caso contrário falso.
@param e Apontador para o estado
@returns True no caso de o jogo ter terminado, False caso contrário
 */
Boolean isTerminado(ESTADO *e);

/**
\brief Função que verifica se a jogada a ser realizada é vizinha da casa anterior. 
Retorna True caso seja, False caso contrário.
@param e Apontador para o estado
@param c Coordanada da casa atual
@returns True no caso de c ser vizinha da posição atual, False caso contrário
*/
Boolean isCasaVizinha(ESTADO *e, COORDENADA c);

/**
\brief Função que grava o tabuleiro no seu estado atual para um ficheiro de texto.
@param e Apontador para o estado
@param filename Nome do ficheiro que sera gravado
@returns OK no caso de ter gravado com sucesso, ERRO_ABRIR_FICHEIRO caso contrário
*/
ERROS gravar(ESTADO *e, char *filename);

/**
\brief Função que lê um ficheiro e converte cada linha do mesmo para uma linha de tabuleiro do Estado do jogo.
@param e Apontador para o estado
@param filename Nome do ficheiro para ler
@returns OK no caso de ter gravado com sucesso, ERRO_ABRIR_FICHEIRO caso contrário
*/
ERROS ler(ESTADO *e,  char *filename);

/**
\brief Função que determina qual foi o jogador que venceu o jogo. 
Avalia portanto se o jogador se encontra na casa UM ou casa DOIS ou se está rodeado.
@param estado Apontador para o estado
@returns O jogador vencedor
*/
int winner (ESTADO *e) ;

Boolean goToPos(ESTADO *e, int n);
#endif