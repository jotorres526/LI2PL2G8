/**
@file list.h
Definição do modulo de listas ligadas
*/

#ifndef ___LIST_H___
#define ___LIST_H___
#include <stdio.h>
#include <stdlib.h>
#include "macros/boolean.h"

typedef struct nodo {
   void *valor;
   int valorNodo;
   struct nodo *proximo;
} NODO, *LISTA;


/**
\brief Função que cria uma lista vazia.
@returns Uma lista vazia
 */
LISTA createList();

/**
\brief Função que insere uma cabeça numa lista. 
@param l - lista para inserir
@param *valor - valor a ser inserido
@returns novo inicio da lista
*/
LISTA insertHead(LISTA l, void *valor);

/**
\brief Função que insere uma cabeça numa lista. 
@param l - lista para inserir
@returns devolve o valor da cabeça da lista
*/
void *getHead(LISTA l);

/**
\brief Função que retira a cabeça numa lista. 
@param l - lista para inserir
@returns devolve a cauda da lista
*/
LISTA tail(LISTA l);

/**
\brief Função que remove a cabeça numa lista e liberta o espaço. 
@param l - lista para inserir
@returns novo inicio da lista
*/
LISTA deleteHead(LISTA l);

/**
\brief Função que ve se uma lista é vazia. 
@param l - lista para inserir
@returns 1 se for vazio, 0 caso contrário
*/ 
int isEmpty(LISTA l);

/**
\brief Função que insere uma cabeça numa lista. 
@param l - lista para inserir
@param x - valor a ser inserido no campo de valornodo
@returns inicio da lista
*/ 
LISTA setValorNodo(LISTA l, int x);

/**
\brief Função que devolde o valorNodo da lista. 
@param l - lista para verificar
@returns novo inicio da lista
*/ 
int getValorNodo(LISTA l);
/**
\brief Função que coloca um apontador no campo valor. 
@param l - lista para inserir
@param *valor - valor a ser inserido
@returns novo inicio da lista
*/ 
LISTA setHead(LISTA l, void *valor);
#endif