/**
@file boolean.h
Definição de tipo de dados para true ou false
*/
#ifndef ___BOOLEAN_H___
#define ___BOOLEAN_H___
/**
\brief tipo de dados de true e false para usar em if statements
*/ 
typedef enum {
    /**Para verificar quando algo é Falso*/
    False = 0, 
    /**Para verificar quando algo é Verdadeiro*/
    True = 1 
} Boolean;
#endif