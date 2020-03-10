#include "controller.h"

/* Função deverá receber o estado atual e uma coordenada e  modificaro estado ao jogar na casa correta
se a jogada for válida. 
A função devolve verdadeiro (valor diferente de zero) se for possível jogar e falso (zero) caso
não seja possível.*/

int jogar(ESTADO *e, COORDENADA c) {
    if ( obter_estado_casa (e,c)== VAZIO && (c.coluna < 8 && c.coluna > 0) && (c.linha < 8 && c.linha > 0)) {
        printf("jogar %d %d\n", c.coluna, c.linha);
        return 1;
    } else {
        printf("Jogada Inválida.");
        return 0;
    }
}

int main () {
    return 0 ;
}