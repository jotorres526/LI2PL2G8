#include "controller.h"
#include <string.h>

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

Boolean isJogadaValida(ESTADO *e, COORDENADA c) {
    Boolean r = False;
    if ((getCasa(e,c) == VAZIO || getCasa(e,c) == DOIS || getCasa(e,c) == UM) &&
        getColuna(c) < 8 && getColuna >= 0 && getLinha(c) < 8 && getLinha(c) >= 0 &&
        isCasaVizinha(e, c))
            r = True;
    return r;
}

void addMovJogador(ESTADO *e, COORDENADA c) {
    int position = getPointerJogada(e);
    int jogador = getjogador(e);
    JOGADA j = (jogador == 1) ? createJogada(c, createNullCoord()) : createJogada(getUltimaJogada(e), c);
    editJogadas(e, j, position);
    setUltimaJogada(e, c);
}

ERROS jogar(ESTADO *e, COORDENADA c) {
    ERROS r = JOGADA_INVALIDA;
    if (isJogadaValida(e, c)) {
        setCasa(e, getUltimaJogada(e), PRETA);
        setCasa(e, c, BRANCA);
        addMovJogador(e, c);
        if(getjogador(e) == 2) {
            incPointerJogada(e);
            editJogadas(e, createJogada(createNullCoord(),createNullCoord()),getPointerJogada(e));
        }
        setNumJogadas(e, getPointerJogada(e)); //Meter o numero de jogadas igual ao pointer previamente incrementado
        swapJogador(e);
        r = OK;
    }
    return r;
}

int winner(ESTADO *e) {
    int player = 0;
    COORDENADA posAnt = getUltimaJogada(e);
    if(getColuna(posAnt) == 0 && getLinha(posAnt) == 0) player = 1;
    if(getColuna(posAnt) == 7 && getLinha(posAnt) == 7) player = 2;
    if(isRodeado(e, posAnt)) {
        swapJogador(e);
        player = getjogador(e);
    }
    return player;
}

ERROS gravar(ESTADO *e, char *filename) {
    FILE *fp = fopen(filename, "w");
    JOGADA j;
    if(fp == NULL) return ERRO_ABRIR_FICHEIRO;
    //Ciclo que guarda o tabuleiro 
    REVERSE_FORI(8) {
        fprintf(fp, "%d ", i + 1);
        FORJ(8) {
            fputc(getCasa(e, setCoordenada(i, j)), fp);
        }
        fputc('\n', fp);
    }
    fprintf(fp, "  abcdefgh\n");
    fputc('\n', fp);
    //Guarda as jogadas no ficheiro
    FORI(getPointerJogada(e) + 1) {
        j = getJogada(e, i);
        if(isNullCoord(getCoordenada(j, 1))) break;
        int linJ1, linJ2;
        char colJ1, colJ2;
        linJ1 = getLinha(getCoordenada(j, 1)) + 1;
        colJ1 = getColuna(getCoordenada(j, 1)) + 'a';
        if (!isNullCoord(getCoordenada(j, 2))) {
            linJ2 = getLinha(getCoordenada(j, 2)) + 1;
            colJ2 = getColuna(getCoordenada(j, 2)) + 'a';
            fprintf(fp, "Jog %02d: %c%d %c%d\n", i + 1, colJ1, linJ1, colJ2, linJ2);
        }
        else fprintf(fp, "Jog %02d: %c%d\n", i + 1, colJ1, linJ1);
    }
    fclose(fp);
    return OK;
}

ERROS ler(ESTADO *e,  char *filename) {
    FILE *fp = fopen(filename, "r");
    char buffer[64];
    if(fp == NULL) return ERRO_ABRIR_FICHEIRO;
    //Passar o tabuleiro no ficheiro para o estado
    REVERSE_FORI(8){
        fgets(buffer, 64, fp);
        FROMJ_TO_N(2,10) setCasa(e, setCoordenada(i, j - 2), buffer[j]);
    }
    fgets(buffer, 64, fp);//consumir os caracteres de 'flavour' do tabuleiro
    fgetc(fp); //Consumir o new line
    //Passar as jogadas para o estado
    char jog1[32], jog2[32];
    int jogada;
    COORDENADA c1, c2;
    resetEstado(e);
    while(fgets(buffer, 64, fp)) {
        //Partir a linha de jogadas em pedaços 
        int scanned = sscanf(buffer, "Jog %02d: %s %s\n", &jogada, jog1, jog2);
        c1 = setCoordenada(jog1[1] - '1', jog1[0] - 'a');
        if(scanned == 3) c2 = setCoordenada(jog2[1] - '1', jog2[0] - 'a');
        else c2 = createNullCoord();
        addToJogadas(e, createJogada(c1, c2));
        incNumJogadas(e);
        incPointerJogada(e);
    }
    //Alterar a ultima jogada para refletir o 'reloading' da lista de jogadas
    if (isNullCoord(c2)) {
        setUltimaJogada(e, c1);
        setJogador(e, 2);
    } else {
        setUltimaJogada(e, c2);
        setJogador(e, 1);
    } 
    fclose(fp);
    return OK;
}


Boolean goToPos(ESTADO *e, int n) {
    JOGADA j = getJogada(e, n-1);
    Boolean r = False;
    if(n <= getNumJogadas(e) && n >= 0 && !isNullCoord(getCoordenada(j,2))) {
        setJogador(e,1);
        setPointerJogada(e, n);
        renicializaTab(e);
        if(n == getNumJogadas(e)) editJogadas(e, createJogada(createNullCoord(), createNullCoord()), n);
        if(n != 0) {
            setCasa(e,setCoordenada(4,4),PRETA);
            FORI(n) {       
                j = getJogada(e, i);
                setCasa(e, getCoordenada(j, 1), PRETA);
                setCasa(e, getCoordenada(j, 2), PRETA);
            }
            setCasa(e, getCoordenada(j, 2), BRANCA);
            setUltimaJogada(e, getCoordenada(j, 2));
        } else {
            setUltimaJogada(e, setCoordenada(4, 4));
        }
        r = True;
    }
    return r;
} 

Boolean over(ESTADO *e, COORDENADA c) {
    Boolean r = False;
    if ((getLinha(c) == 7 && getColuna(c) == 7) ||
        (getLinha(c) == 0 && getColuna(c) == 0) ||
        (isRodeado(e,c))) 
        r = True;
    return r;
}

LISTA getpositions (ESTADO *e, COORDENADA c2) {
    LISTA l1 = createList();
    for(int i = getLinha(c2) - 1; i <= getLinha(c2) + 1; i++)
        for(int j = getColuna(c2) - 1; j <= getColuna(c2) + 1; j++) {
            if(i >= 0 && i < 8 && j >= 0 && j < 8) {
                COORDENADA *c = malloc(sizeof(COORDENADA));
                *c = setCoordenada(i,j);
                if(getCasa(e,*c) == VAZIO || getCasa(e,*c) == UM || getCasa(e,*c) == DOIS) l1 = insertHead(l1,c); // inserir coordenadas livres à cabeça da lista vazia
            }
        }
    return l1;
}

int min(int x, int y) {
    if(x < y) return x;
    else return y;
}

int max(int x, int y) {
    if(x > y) return x;
    else return y;
}

double dist(COORDENADA c1, int jogador) {
    double dist; 
    COORDENADA c;
    if(jogador == 1) {
        c = setCoordenada(7,7);
        dist = sqrt(pow((c1.linha  - c.linha ), 2) + pow((c1.coluna - c.coluna), 2));
    } else {    
        c = setCoordenada(1,1);
        dist = sqrt(pow((c1.linha  - c.linha ), 2) + pow((c1.coluna - c.coluna), 2));
    }
    return dist;
}


int length(ESTADO *e, COORDENADA c) {
    int length = 0;
    for(LISTA pt = getpositions (e,c); pt; pt = pt->proximo) {
        length++;
    }
    return length;
}


int valor(ESTADO *e, COORDENADA c, int jogador) {
    if(over(e,c)&& jogador) return 100;
    if(dist(c,jogador) <= sqrt(8)) return -10;
    else if(length(e,c) % 2 == 0)return length(e,c);
    else if(length(e,c) % 2 != 0) return -9;
    return -10;
}


int minimax(ESTADO *e, LISTA nodo, int  profundidade, Boolean maximizingPlayer, int jogador) {
    COORDENADA *aux2= getHead(nodo), *aux3;
    CASA casa;
    if(over(e,*aux2) && !maximizingPlayer) return 100;
    else if(over(e,*aux2)) return -100;
    if(profundidade == 0) {
        COORDENADA *aux;
        aux = getHead(nodo);
        setCasa(e,*aux,BRANCA);
        int value;
        value = valor(e,*aux,maximizingPlayer);
        return value;
    }
    if(maximizingPlayer) {
        int valor1 = -200;
        for(LISTA pt = getpositions(e,*aux2); pt; pt = pt->proximo) {
            aux3 = getHead(pt);
            casa = getCasa(e,*aux3);
            setCasa(e,*aux3,BRANCA);
            int eval = minimax(e,pt,profundidade - 1, False,jogador);
            valor1 = max(valor1,eval);  
            setCasa(e,*aux3,casa);
        }
        return valor1;
    }
    else {
        int valor2 = 200;
        for(LISTA pt = getpositions(e,*aux2); pt; pt = pt->proximo) {
            aux3 = getHead(pt);
            casa = getCasa(e,*aux3);
            setCasa(e,*aux3,BRANCA);
            int eval = minimax(e,pt,profundidade - 1, True,jogador);
            valor2 = min(valor2,eval);
            setCasa(e,*aux3,casa);
        }
        return valor2;   
    }
}


COORDENADA jog(ESTADO *e, int jogador) {
    COORDENADA lastplay= getUltimaJogada(e),*aux;
    int value;
    LISTA nodo =  insertHead(createList(),&lastplay);
    COORDENADA c = setCoordenada(7,7);
    int x = minimax(e,nodo,2,True,jogador);
    for(LISTA pt = getpositions(e,lastplay); pt; pt = pt->proximo) {
        aux = getHead(pt);
        setCasa(e,*aux,BRANCA);
        value = valor(e,*aux,jogador);
        if(x == value) c = *aux;
        setCasa(e,*aux,VAZIO);
    }   
    return c;
}