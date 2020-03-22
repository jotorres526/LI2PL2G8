/**
@file interface.h
Definição da interface e da maneira como o utilizador interage com o programa
*/
#ifndef ___INTERFACE_H___
#define ___INTERFACE_H___

#include "controller.h"

/** 
\brief Função que precorre o tabuleiro do estado e utiliza a função putchar para imprimir o respetivo caracter da casa.
@param e Apontador para o estado
*/
void mostrar_tabuleiro(ESTADO *e);

/**
\brief Interpertador de comandos pede ao utilizador para introduzir um comando
No caso de o comando ser:
   - Q, o jogo fecha;
   - Coordenada, o jogador faz uma jogada;
   - gr nome do ficheiro, o estado atual será gravado num ficheiro de texto;
   - ler nome do ficheiro, irá ser carregado o estado previamente guardado.
@param e Apontador para o estado
@returns 0 para parar o jogo ou 1 para continuar 
 */
int interpretador(ESTADO *e);

#endif