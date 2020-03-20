#include "controller.h"

/* Função deverá receber o estado atual e uma coordenada e  modificaro estado ao jogar na casa correta
se a jogada for válida. 
A função devolve verdadeiro (valor diferente de zero) se for possível jogar e falso (zero) caso
não seja possível.*/

// Função que verifica se uma jogada é válida, isto é, se a proxima jogada a ser realizada é vizinha da posição anterior
Boolean isCasaVizinha(ESTADO *e, COORDENADA c) {
    COORDENADA posAnt = getUltimaJogada(e);
    Boolean r = False;
    if (getLinha(posAnt) - 1 <= getLinha(c)  && getColuna(posAnt) - 1 <= getColuna(c) &&
        getLinha(posAnt) + 1 >= getLinha(c)  && getColuna(posAnt) + 1 >= getColuna(c))
        r = True;
    return r;
}

// Função que ve se não é possivel jogar mais e se a peça branca se encontra presa
Boolean isRodeado(ESTADO *e, COORDENADA c) {
    Boolean r = True;
    for(int i = getLinha(c) - 1; i <= getLinha(c) + 1; i++)
        for(int j = getColuna(c) - 1; j <= getColuna(c) + 1; j++) {
            if(i >= 0 && i < 8 && j >= 0 && j < 8) {
                COORDENADA c = setCoordenada(i, j);
                if(getCasa(e, c) == VAZIO){
                    r = False;
                    break;
                } 
            }
        }
    return r;
}

// Função que determina o fim do jogo
Boolean isTerminado(ESTADO *e) {
    Boolean r = False;
    COORDENADA posAnt = getUltimaJogada(e);
    if ((getLinha(posAnt) == 7 && getColuna(posAnt) == 7) ||
        (getLinha(posAnt) == 0 && getColuna(posAnt) == 0) ||
        (isRodeado(e, posAnt))) 
        r = True;
    return r;
}

int jogar(ESTADO *e, COORDENADA c) {
    COORDENADA lstJogada = getUltimaJogada (e);
    if ( (getCasa(e,c) == VAZIO || getCasa(e,c) == DOIS || getCasa(e,c) == UM)
         && c.coluna < 8 && c.coluna >= 0 && c.linha < 8 && c.linha >= 0
         && isCasaVizinha(e, c)) {
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

char coordToChar(ESTADO *e, int linha, int coluna) {
    COORDENADA c = setCoordenada(linha, coluna); 
    CASA c1 = getCasa(e, c);
    return c1;
}

//Retorna o tamanho do array de strings
int tabuleiroToString(char **str, ESTADO *e) {
    char buff[10];
    int linha = 0;
    REVERSE_FORI(8) {
        FORJ(8) buff[j] = coordToChar(e, linha, j); 
        buff[8] = '\n';
        buff[9] = '\0';
        str[i] = strdup(buff);
        linha++;
    }
    return linha;
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
    int linha = 0;
    REVERSE_FORI(8) {
        FORJ(8) buff[j] = coordToChar(e, linha, j); 
        buff[8] = '\n';
        buff[9] = '\0';
        str[i] = strdup(buff);
        linha++;
    }
    return linha;
}


ERROS gravar(FILE *fp, ESTADO *e, char *filename) {
    char **tabuleiro = malloc(8 * sizeof(char *));
    int size = tabuleiroToString(tabuleiro, e);
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




