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
    free(l);
    return temp;
}

// Devolve verdareiro se a lista é vazia
int isEmpty(LISTA l) {
    return (l == NULL);
}

// coloca o valor do nodo
LISTA setValorNodo(LISTA l, int x) {
    l->valorNodo = x;
    return l;
}

int getValorNodo(LISTA l) {
    return l->valorNodo;
}

// insere o apontador no primeiro nodo da lista
LISTA setHead(LISTA l, void *valor) {
    l->valor = valor;
    return l;
}