/**
@file cycle.h
Definição de tipo de dados para true ou false
*/
#ifndef ___CYCLE_H___
#define ___CYCLE_H___
/**
\brief Faz um ciclo for com a inicialização de uma variavel int i = 0
@param n - numero ate qual o ciclo deve iterar
*/
#define FORI(n)             for(int i = 0; i < n; i++)

/**
\brief Faz um ciclo for com a inicialização de uma variavel int i = x ate um dado n
@param n - numero ate qual o ciclo deve iterar
@param x - numero no qual começa a iteração
*/
#define FROMI_TO_N(x, n)    for(int i = x; i < n; i++)

/**
\brief Faz um ciclo for com a inicialização de uma variavel int j = 0
@param n - numero ate qual o ciclo deve iterar
*/
#define FORJ(n)             for(int j = 0; j < n; j++)

/**
\brief Faz um ciclo for com a inicialização de uma variavel int j = x ate um dado n
@param n - numero ate qual o ciclo deve iterar
@param x - numero no qual começa a iteração
*/
#define FROMJ_TO_N(x, n)    for(int j = x; j < n; j++)

/**
\brief Faz um ciclo for desde uma dada quantidade n até 0 com a inicialização de uma variavel int i = n - 1
@param n - numero no qual o ciclo começa
*/
#define REVERSE_FORI(n)     for(int i = n - 1; i >= 0; i--)

#endif