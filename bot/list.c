/**
@file list.c
Implementação das funções manipuladoras de listas 
*/
#include "list.h"

LISTA createList() {
  LISTA l = NULL;
  return l;
}

LISTA insertHead(LISTA l, void *valor) {
    LISTA nodo = malloc(sizeof(NODO));
    nodo->valor = valor;
    nodo->proximo = l;
    l = nodo;
    return l;
}

void *getHead(LISTA l) {
    return l->valor;
}

// Devolve a cauda da lista
LISTA tail(LISTA l) {
    LISTA temp = l->proximo;
    return temp;
}

// Remove a cabeça da lista (libertando o espaço ocupado) e devolve a cauda
LISTA deleteHead(LISTA l) {
    LISTA temp = tail(l);
    free(l->valor);
    free(l);
    return temp;
}

// Devolve verdareiro se a lista é vazia
int isEmpty(LISTA l) {
    return (l == NULL);
}

// insere o apontador no primeiro nodo da lista
LISTA setHead(LISTA l, void *valor) {
    l->valor = valor;
    return l;
}

// insere um elemento no proximo de um dado nodo
LISTA setNext(LISTA l, LISTA x) {
    l->proximo = x;
    return l;
}

//
LISTA getNext(LISTA l) {
    return l->proximo;
}