#include <stdio.h>
#include <stdlib.h>
#include "macros/boolean.h"

typedef struct nodo {
   void *valor;
   struct nodo *proximo;
} NODO, *LISTA;


// Cria uma lista vazia
LISTA createList();
// Insere um valor na cabeça da lista
LISTA insertHead(LISTA l, void *valor);
// Devolve a cabeça da lista
void *getHead(LISTA l);
// Devolve a cauda da lista
LISTA tail(LISTA l);
// Remove a cabeça da lista (libertando o espaço ocupado) e devolve a cauda
LISTA deleteHead(LISTA l);
// Devolve verdareiro se a lista é vazia
int isEmpty(LISTA l);