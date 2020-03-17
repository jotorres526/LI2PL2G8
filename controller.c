#include "controller.h"

/* Função deverá receber o estado atual e uma coordenada e  modificaro estado ao jogar na casa correta
se a jogada for válida. 
A função devolve verdadeiro (valor diferente de zero) se for possível jogar e falso (zero) caso
não seja possível.*/

int jogar(ESTADO *e, COORDENADA c) {
    COORDENADA lstJogada = obter_ultima_jogada(e);
    if ( obter_estado_casa(e,c) == VAZIO 
         && c.coluna < 8 && c.coluna >= 0 && c.linha < 8 && c.linha >= 0
         && jogada_valida(e,c)) {
        setPosicao(e, lstJogada, PRETA);
        if(obter_jogador_atual(e) == 1) {
            setUltimaJogada (e, c);
            swapJogador(e);
        } else {
            addToJogadas(e, setJogada(lstJogada, c));
            setUltimaJogada (e, c); 
            swapJogador(e);
        }
        setPosicao(e, c, BRANCA);
        return 1;
    } else {
        printf("Jogada Inválida.\n");
        return 0;
    }
}
