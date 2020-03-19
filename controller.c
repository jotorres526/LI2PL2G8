#include "controller.h"

/* Função deverá receber o estado atual e uma coordenada e  modificaro estado ao jogar na casa correta
se a jogada for válida. 
A função devolve verdadeiro (valor diferente de zero) se for possível jogar e falso (zero) caso
não seja possível.*/

// Função que verifica se uma jogada é válida, isto é, se a proxima jogada a ser realizada é vizinha da posição anterior
int jogada_valida (ESTADO *e, COORDENADA c) {
    COORDENADA posAnt = obter_ultima_jogada (e);
    if ( posAnt.linha  - 1 <= c.linha  &&  c.linha  <= posAnt.linha  + 1 &&
         posAnt.coluna - 1 <= c.coluna &&  c.coluna <= posAnt.coluna + 1)
         return 1;
    else return 0;
}

// Função que determina o fim do jogo
int endGame (ESTADO *e) {
    COORDENADA posAnt = obter_ultima_jogada (e);
    if((posAnt.linha == 7 && posAnt.coluna == 7 ) {
        printf("Parabéns Jogador 2!!\n\nFim do jogo.\n");
        return 0;
    }
    else if(posAnt.linha == 0 && posAnt.coluna == 0 ) {
        printf("Parabéns Jogador 1!!\n\nFim do jogo.\n");
        return 0;   
       }
    else return 1;
}

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
