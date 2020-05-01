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
    int linha = getLinha(c);
    int coluna = getColuna(c);
    for(int i = linha - 1; r && i <= linha + 1; i++)
        for(int j = coluna - 1; r && j <= coluna + 1; j++)
            if(i >= 0 && i < 8 && j >= 0 && j < 8) {
                COORDENADA coord = setCoordenada(i, j);
                CASA casa = getCasa(e, coord);
                if((casa == VAZIO || casa == DOIS || casa == UM) && (linha != i || coluna != j)) r = False;
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
        getColuna(c) < 8 && getColuna(c) >= 0 && getLinha(c) < 8 && getLinha(c) >= 0 &&
        isCasaVizinha(e, c))
            r = True;
    return r;
}

void addMovJogador(ESTADO *e, COORDENADA c) {
    int position = getPointerJogada(e) - 1;
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
            editJogadas(e, createJogada(createNullCoord(), createNullCoord()), getPointerJogada(e));
        }
        setNumJogadas(e, getPointerJogada(e)); 
        swapJogador(e);
        r = OK;
    }
    return r;
}

int winner(ESTADO *e) {
    int player = 0;
    COORDENADA posAnt = getUltimaJogada(e);
    if(getColuna(posAnt) == 0 && getLinha(posAnt) == 0) player = 1;
    else if(getColuna(posAnt) == 7 && getLinha(posAnt) == 7) player = 2;
    else if(isRodeado(e, posAnt)) {
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

//Estado para verificar quais as jogadas acediveis a partir de uma coordenada
LISTA movsDisponiveis(ESTADO *e, LISTA l, COORDENADA c) {
    int linha = getLinha(c);
    int coluna = getColuna(c);
    for(int i = linha - 1; i <= linha + 1; i++)
        for(int j = coluna - 1; j <= coluna + 1; j++) {
            if(i >= 0 && i < 8 && j >= 0 && j < 8) {
                COORDENADA *coord = malloc(sizeof(COORDENADA));
                *coord = setCoordenada(i, j);
                CASA casa = getCasa(e, *coord);
                if((casa == VAZIO || casa == UM || casa == DOIS) && (linha != i || coluna != j)) {
                    l = insertHead(l, coord);
                } else free(coord);
            }
        }
    return l;
}


double dist(COORDENADA c1, int jogador) {
    double dist; 
    COORDENADA c;
    if(jogador == 1) {
        c = setCoordenada(7,7);
        dist = sqrt(pow((c1.linha  - c.linha), 2) + pow((c1.coluna - c.coluna), 2));
    } else {    
        c = setCoordenada(1,1);
        dist = sqrt(pow((c1.linha  - c.linha ), 2) + pow((c1.coluna - c.coluna), 2));
    }
    return dist;
}


int length(ESTADO *e, COORDENADA c) {
    int length = 0;
    LISTA pt = NULL, tmp;
    pt = movsDisponiveis(e, pt, c);
    tmp = pt;
    while(tmp) {
        length++;
        tmp = deleteHead(tmp);
    }
    return length;
}

int maxValue(ParMinMax fst, ParMinMax snd) {
    int r;
    int val1 = getValorPar(fst);
    int val2 = getValorPar(snd);
    if(val1 < val2) r = val2;
    else r = val1;
    return r; 
}

int minValue(ParMinMax fst, ParMinMax snd) {
    int r,
        val1 = getValorPar(fst),
        val2 = getValorPar(snd);
    if(val2 < val1) r = val2;
    else r = val1;
    return r; 
}

//Devia talvez ser um valor entre 0 e 100?
int calcValorCasa(ESTADO *e, COORDENADA c) {
    int jogador = getjogador(e);
    if(dist(c,jogador) <= sqrt(8)) return -10;
    else if(length(e, c) % 2 == 0)return -length(e, c);
    else if(length(e, c) % 2 != 0) return -9;
    return -10;
}

/*Retorna struct com um valor e uma coordenada*/
ParMinMax recAuxMinimax(ESTADO *e, COORDENADA c, int depth, Boolean isMax){
    ParMinMax aux, r;
    Boolean nxtLevel = isMax ? False : True;
    r = isMax ? setPar(-100, c) : setPar(100, c);
    int minMax;
    if(isRodeado(e, c)) r = setPar(101, c);
    else if(depth != 0) {
        LISTA proxCoords = createList();
        proxCoords = movsDisponiveis(e, proxCoords, c); 
        while (proxCoords) {
            COORDENADA *head = getHead(proxCoords);
            aux = recAuxMinimax(e, *head, depth - 1, nxtLevel);
            minMax = isMax ? maxValue(r, aux) : minValue(r, aux);
            if(isMax)
                r = minMax > getValorPar(r) ? setPar(minMax, c) : r;
            else 
                r = minMax < getValorPar(r) ? setPar(minMax, c) : r;
            proxCoords = deleteHead(proxCoords);
        }
    } else {
        int valor = calcValorCasa(e, c);
        r = setPar(valor, c);
    }
    return r; 
}

//Retorna a coordenada para a qual devemos jogar
COORDENADA minimax(ESTADO *e, int depth) {
    COORDENADA r = createNullCoord();
    if(depth > 0) {
        LISTA possiveisJogadas = createList();
        ParMinMax next, max = setPar(-101, createNullCoord()); //Estes valores tem de ser menor que na auxiliar pois precisa ser overwritten
        int minMax;
        possiveisJogadas = movsDisponiveis(e, possiveisJogadas, getUltimaJogada(e));
        //Para cada elemento aplicar recursivamente um auxiliar do minimax que retorna
        //um par com o valor e a coordenada
        while(possiveisJogadas) {
            COORDENADA *head = getHead(possiveisJogadas);
            next = recAuxMinimax(e, *head, depth - 1, True);
            minMax = maxValue(max, next);
            if(minMax > getValorPar(max))
                max = setPar(minMax, *head);
            possiveisJogadas = deleteHead(possiveisJogadas);
        }
        r = getCoordPar(max);
    }
    return r;
}

//Estado para verificar quais as jogadas acediveis a partir de uma coordenada
LISTA casasTabDistancia(int **tabDistancias, COORDENADA c) {
    int linha = getLinha(c), coluna = getColuna(c);
    LISTA l = createList();
    for(int i = linha - 1; i <= linha + 1; i++)
        for(int j = coluna - 1; j <= coluna + 1; j++) {
            if(i >= 0 && i < 8 && j >= 0 && j < 8) {
                int casa = tabDistancias[i][j];
                if((casa == -1 || casa == 99) && (linha != i || coluna != j)) {
                    COORDENADA *coord = malloc(sizeof(COORDENADA));
                    *coord = setCoordenada(i, j);
                    l = insertHead(l, coord);
                }
            }
        }
    return l;
}

int** preencheTabuleiro(COORDENADA c, int **tabDistancias, int dist) {
    LISTA proxCoordenadas = casasTabDistancia(tabDistancias, c);
    while(proxCoordenadas) {
        COORDENADA *h = getHead(proxCoordenadas);
        tabDistancias[getLinha(*h)][getColuna(*h)] = dist;
        tabDistancias = preencheTabuleiro(*h, tabDistancias, dist + 1);
        proxCoordenadas = deleteHead(proxCoordenadas);
    }
    return tabDistancias;
}

COORDENADA floodFill(ESTADO *e) {
    //Incializar um tabuleiro com as distancias ao objetivo do jogador atual
    int **tabDistancias = malloc(sizeof(int*) * 8), jogador = getjogador(e);
    COORDENADA casaAtual = getUltimaJogada(e), 
        objetivo = jogador == 1 ? setCoordenada(0, 0) : setCoordenada(7, 7),
        r;
    FORI(8) {
        tabDistancias[i] = malloc(sizeof(int) * 8);
        FORJ(8) {
            COORDENADA coordAux = setCoordenada(i, j);
            CASA casa = getCasa(e, coordAux);
            if(casa == UM || casa == DOIS) tabDistancias[i][j] = 0;
            else if(casa == PRETA) tabDistancias[i][j] = 100;
            else tabDistancias[i][j] = -1;
        }
    }
    if(jogador == 1) tabDistancias[7][7] = 99;
    else tabDistancias[0][0] = 99;

    tabDistancias = preencheTabuleiro(objetivo, tabDistancias, 1);

    int linha = getLinha(casaAtual), coluna = getColuna(casaAtual), min = 100;
    for(int i = linha - 1; i <= linha + 1; i++)
        for(int j = coluna - 1; j <= coluna + 1; j++) {
            if(i >= 0 && i < 8 && j >= 0 && j < 8 && tabDistancias[i][j] < min && (linha != i || coluna != j)) {
                min = tabDistancias[i][j];
                r = setCoordenada(i, j);
            }
        }
    FORI(8) free(tabDistancias[i]); 
    free(tabDistancias);
    return r;
}

ERROS jog(ESTADO *e, int heuristica) {
    COORDENADA nextMove;
    if(heuristica == 1) nextMove = minimax(e, 4); //a partir de 7 depth fica mto custoso
    if(heuristica == 2) nextMove = floodFill(e);
    return jogar(e, nextMove);
}