/**
@file controller.h
Definição da lógica e das funções que o manipulam
*/
#ifndef ___INTERFACE_H___
#define ___INTERFACE_H___

#include "controller.h"

/** 
 * Função que precorre o tabuleiro do estado e utiliza a função putchar para imprimir o respetivo caracter da casa.
*/
void mostrar_tabuleiro(ESTADO *e);

/**
 * Interpertador de comandos pede ao utilizador para introduzir um comando
 *   No caso de o comando ser:
 *      - Q, o jogo fecha;
 *      - Coordenada, o jogador faz uma jogada;
 *      - gr nome do ficheiro, o estado atual será gravado num ficheiro de texto;
 *      - ler nome do ficheiro, irá ser carregado o estado previamente guardado.
 */
int interpretador(ESTADO *e);

#endif