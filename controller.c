#include "controller.h"

/* Função deverá receber o estado atual e uma coordenada e  modificaro estado ao jogar na casa correta
se a jogada for válida. 
A função devolve verdadeiro (valor diferente de zero) se for possível jogar e falso (zero) caso
não seja possível.*/

// Função que verifica se uma jogada é válida, isto é, se a proxima jogada a ser realizada é vizinha da posição anterior
int jogada_vizinha (ESTADO *e, COORDENADA c) {
    COORDENADA posAnt = getUltimaJogada  (e);
    if ( getLinha(posAnt)  - 1 <= getLinha(c)  &&  getLinha(c)  <= getLinha(posAnt)  + 1 &&
         getColuna(posAnt) - 1 <= getColuna(c) &&  getColuna(c) <= getColuna(posAnt) + 1)
         return 1;
    else return 0;
}

// Função que ve se não é possivel jogar mais e se a peça branca se encontra presa
int is_traped (ESTADO *e, COORDENADA c) {
    int coluna,linha,ultimaColuna,ultimaLinha;
    if(getColuna(c) == 7 ) { 
        coluna = 6;
        ultimaColuna = 7;
    } else {
        coluna = getColuna(c) - 1;
        ultimaColuna = coluna + 2;
    } 
    if(getLinha(c)== 7) {
        linha = 6;
        ultimaLinha = 7;
    } else {
        linha  = getLinha(c) - 1 ;
        ultimaLinha = linha + 2;
    }
    for( int i = linha ; i < ultimaLinha; i++) {
        for(int j = coluna; j < ultimaColuna;j++) {
            if(getCasa_parametro(e ,i, j) == VAZIO) return 0;
        }
    }
    return 1;
}


// Função que determina o fim do jogo
int endGame (ESTADO *e) {
    COORDENADA posAnt = getUltimaJogada  (e);
    if(getLinha(posAnt) == 7 && getColuna(posAnt) == 7 ) {
        printf("Parabéns Jogador 2!!\n\nFim do jogo.\n");
        return 0;
    }
    else if(getLinha(posAnt) == 0 && getColuna(posAnt) == 0 ) {
        printf("Parabéns Jogador 1!!\n\nFim do jogo.\n");
        return 0;   
    }
    else if(is_traped(e,posAnt)) {
        printf("Parabéns Jogador %d!!\n\nFim do jogo.\n",getjogador(e));
        return 0;
    }  
    else return 1;
}

int jogar(ESTADO *e, COORDENADA c) {
    COORDENADA lstJogada = getUltimaJogada (e);
    if ( (getCasa(e,c) == VAZIO || getCasa(e,c) == DOIS || getCasa(e,c) == UM)
         && c.coluna < 8 && c.coluna >= 0 && c.linha < 8 && c.linha >= 0
         && jogada_vizinha(e,c)) {
        setCasa(e, lstJogada, PRETA);
        if(getjogador(e) == 1) {
            setUltimaJogada (e, c);
            swapJogador(e);
        } else {
            addToJogadas(e, setJogada(lstJogada, c));
            setUltimaJogada (e, c); 
            swapJogador(e);
        }
        setCasa(e, c, BRANCA);
        return 1;
    } else {
        printf("Jogada Inválida.\n");
        return 0;
    }
}

char revelar_casa(ESTADO *e, int linha, int coluna) {
    COORDENADA c = setCoordenada(linha, coluna); 
    CASA c1 = getCasa(e, c);
    return c1;
}

//Retorna o tamanho do array de strings
int tab_to_string(char **str, ESTADO *e) {
    char buff[10];
    int size = 0;
    REVERSE_FORI(8) {
        FORJ(8) buff[j] = revelar_casa(e, size, j); 
        buff[8] = '\n';
        buff[9] = '\0';
        str[i] = strdup(buff);
        size++;
    }
    return size;
}


int string_to_tab (char **str,ESTADO *e) {
    int size = 0;
    COORDENADA c;
    REVERSE_FORI(8) {
        FORJ(8) {
           c = setCoordenada(i,j);
           setCasa(e,c,str[i][j]);
        } 
        size++;
    }
return size;
}


int tab_to_string(char **str, ESTADO *e) {
    char buff[10];
    int size = 0;
    REVERSE_FORI(8) {
        FORJ(8) buff[j] = revelar_casa(e, size, j); 
        buff[8] = '\n';
        buff[9] = '\0';
        str[i] = strdup(buff);
        size++;
    }
    return size;
}


ERROS gravar(FILE *fp, ESTADO *e, char *filename) {
    char **tabuleiro = malloc(8 * sizeof(char *));
    int size = tab_to_string(tabuleiro, e);
    fp = fopen(filename, "w");
    if(fp == NULL) return ERRO_ABRIR_FICHEIRO;
    FORI(size) {
        fprintf(fp, "%s", tabuleiro[i]);
        free(tabuleiro[i]);
    }
    fclose(fp);
    free(tabuleiro);
    return OK;
}




