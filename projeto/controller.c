/**
@file controller.c
Definição da lógica e controlo do estado
*/
#include "controller.h"
#include <string.h>

/**
\brief Verifica se uma dada COORDENADA é acedível a partir da ultima jogada verificando se
o valor da linha/coluna pertence é "vizinho" dos valores da ultima jogada
@param e Estado do jogo
@param c Coordenada a analizar
@returns True se for vizinha e False se não for vizinha
*/  
Boolean isCasaVizinha(ESTADO *e, COORDENADA c) {
    COORDENADA posAnt = getUltimaJogada(e);
    Boolean r = False;
    if (getLinha(posAnt) - 1 <= getLinha(c)  && getColuna(posAnt) - 1 <= getColuna(c) &&
        getLinha(posAnt) + 1 >= getLinha(c)  && getColuna(posAnt) + 1 >= getColuna(c))
        r = True;
    return r;
}

/**
\brief Verifica se uma coordenada é vizinha da ultima jogada, está a mover-se para uma casa onde nao haja peças brancas ou pretas e se está dentro
dos boundries do tabuleiro, efetivamente verificando se é um movimento válido
@param e Estado do jogo
@param c Coordenada a verificar
@returns True se for uma jogada válida e False caso contrário
*/ 
Boolean isJogadaValida(ESTADO *e, COORDENADA c) {
    Boolean r = False;
    if ((getCasa(e,c) == VAZIO || getCasa(e,c) == DOIS || getCasa(e,c) == UM) &&
        getColuna(c) < 8 && getColuna(c) >= 0 && getLinha(c) < 8 && getLinha(c) >= 0 &&
        isCasaVizinha(e, c))
            r = True;
    return r;
}


/**
\brief Partindo do pressuposto que uma peça está rodeada faz um "quadrado" de coordenadas em volta da COORDENADA c e percorre todas as 8 coordenadas.
Se encontrar uma casa VAZIO; UM ou DOIS é verificado que nessa coordenada a peça não está rodeada
@param e Estado do jogo
@param c Coordenada que se quer verificar se está rodeada
@returns True caso a peça se encontre rodeada e False caso contrário 
*/
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

/**
\brief Verifica se o jogo está terminado vendo a posição da ultima jogada, isto é, caso esteja numa das casas objetivo ou se estiver rodeado
@param e Estado do jogo
@returns True se o jogo estiver terminado e False caso contrário
*/
Boolean isTerminado(ESTADO *e) {
    Boolean r = False;
    COORDENADA posAnt = getUltimaJogada(e);
    if ((getLinha(posAnt) == 7 && getColuna(posAnt) == 7) ||
        (getLinha(posAnt) == 0 && getColuna(posAnt) == 0) ||
        (isRodeado(e, posAnt))) 
        r = True;
    return r;
}

/**
\brief Cálcula qual é o jogador atual e dependendo disso adiciona/altera uma jogada no array de jogadas e altera o valor da ultima jogada para a dada COORDENADA
@param e Estado do jogo
@param c Coordenada a adicionar ao array
*/ 
void addMovJogador(ESTADO *e, COORDENADA c) {
    int position = getPointerJogada(e);
    int jogador = getjogador(e);
    JOGADA j = (jogador == 1) ? createJogada(c, createNullCoord()) : createJogada(getUltimaJogada(e), c);
    editJogadas(e, j, position);
    setUltimaJogada(e, c);
}

/**
\brief Recebe uma dada coordenada e após validar se é um movimento possível altera o estado do jogo, reposicionando a peça branca;
altera o array de jogadas para refletir o novo movimento;
incrementa o numero de jogadas total;
dá swap no jogador
@param e Estado do jogo que irá ser alterado
@param c Coordenada recebida para um jogador se movimentar para lá
@returns JOGADA_INVALIDA caso a coordenada não passe na validação ou OK caso o estado tenha sido corretamente alterado
*/
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

/**
\brief Calcula qual o vencedor do jogo, analizando em que situação a ultima jogada se encontrava
caso esteja numa das coordenadas objetivo ganha o jogador que tinha de jogar para lá
caso esteja rodeada ganha o jogador que encurralou o adversário
@param e Estado do jogo
@returns Inteiro representante do jogador vencedor (1 ou 2)
*/
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

/**
\brief Cria um ficheiro com um dado nome onde é escrito lá o tabuleiro no seu formato adequado e também a lista de movimentos efetuados
@param e Estado a ser gravado
@param filename Nome que se quer dar ao ficheiro
@returns ERRO_ABRIR_FICHEIRO caso nao tenha sido possível criar o ficheiro ou OK caso o jogo tenha sido gravado com sucesso
*/
ERROS gravar(ESTADO *e, char *filename) {
    FILE *fp = fopen(filename, "w");
    JOGADA j;
    if(fp == NULL) return ERRO_ABRIR_FICHEIRO;
    REVERSE_FORI(8) {   //Ciclo que guarda o tabuleiro 
        FORJ(8) {
            fputc(getCasa(e, setCoordenada(i, j)), fp);
        }
        fputc('\n', fp);
    }
    fputc('\n', fp);
    FORI(getPointerJogada(e) + 1) {  //Guarda as jogadas no ficheiro
        j = getJogada(e, i);
        if(isNullCoord(getCoordenada(j, 1))) break;
        int linJ1, linJ2;
        char colJ1, colJ2;
        linJ1 = getLinha(getCoordenada(j, 1)) + 1;
        colJ1 = getColuna(getCoordenada(j, 1)) + 'a';
        if (!isNullCoord(getCoordenada(j, 2))) {
            linJ2 = getLinha(getCoordenada(j, 2)) + 1;
            colJ2 = getColuna(getCoordenada(j, 2)) + 'a';
            fprintf(fp, "%02d: %c%d %c%d\n", i + 1, colJ1, linJ1, colJ2, linJ2);
        }
        else fprintf(fp, "%02d: %c%d\n", i + 1, colJ1, linJ1);
    }
    fclose(fp);
    return OK;
}

ERROS ler(ESTADO *e,  char *filename) {
    FILE *fp = fopen(filename, "r");
    COORDENADA c1, c2;
    char buffer[64], jog1[32], jog2[32];
    int jogada;
    if(fp == NULL) return ERRO_ABRIR_FICHEIRO;
    //Passar o tabuleiro no ficheiro para o estado
    REVERSE_FORI(8){
        if(fgets(buffer, 64, fp))
            FORJ(8) setCasa(e, setCoordenada(i, j), buffer[j]);
    }
    fgetc(fp);
    resetEstado(e);
    while(fgets(buffer, 64, fp)) {
        //Partir a linha de jogadas em pedaços 
        int scanned = sscanf(buffer, "%02d: %s %s", &jogada, jog1, jog2);
        c1 = setCoordenada(jog1[1] - '1', jog1[0] - 'a');
        c2 = (scanned == 3) ? setCoordenada(jog2[1] - '1', jog2[0] - 'a') : createNullCoord();
        addToJogadas(e, createJogada(c1, c2));
        if(!isNullCoord(c2)) {
            incNumJogadas(e);
            incPointerJogada(e);
            setUltimaJogada(e, c2);
            setJogador(e, 1);
        }
        else {
            setUltimaJogada(e, c1);
            setJogador(e, 2);
        }   
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

int length(ESTADO *e, COORDENADA c) {
    int length = 0;
    LISTA pt = createList(), tmp;
    pt = movsDisponiveis(e, pt, c);
    tmp = pt;
    while(tmp) {
        length++;
        tmp = deleteHead(tmp);
    }
    return length;
}

Boolean isTerminadoCoordenada(ESTADO *e, COORDENADA c) {
    Boolean r = False;
    //int casasRodeadoras = length(e, c);
    if ((getLinha(c) == 7 && getColuna(c) == 7) ||
        (getLinha(c) == 0 && getColuna(c) == 0) ||
        (isRodeado(e,c))) 
        r = True;
    return r;
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

//Estado para verificar quais as jogadas acediveis a partir de uma coordenada
LISTA casasTabDistancia(int **tabDistancias, COORDENADA c) {
    int linha = getLinha(c), coluna = getColuna(c);
    LISTA l = createList();
    for(int i = linha - 1; i <= linha + 1; i++)
        for(int j = coluna - 1; j <= coluna + 1; j++) {
            if(i >= 0 && i < 8 && j >= 0 && j < 8 && (linha != i || coluna != j)) {
                int casa = tabDistancias[i][j];
                if(casa == -1 || casa == 99) {
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

int **initTabDistancias(ESTADO *e) {
    int **tabDistancias = malloc(sizeof(int*) * 8);
    int jogador = getjogador(e);
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
    return tabDistancias;
}

int verAproximacao(ESTADO *e, COORDENADA current, COORDENADA next) {
    int r = 0, **tabDist = initTabDistancias(e), jogador = getjogador(e);
    COORDENADA objetivo = jogador == 1 ? setCoordenada(0, 0) : setCoordenada(7, 7);
    COORDENADA objAdversario = jogador == 2 ? setCoordenada(0, 0) : setCoordenada(7, 7);
    tabDist = preencheTabuleiro(objetivo, tabDist, 1);
    int linhaCurr = getLinha(current), colunaCurr = getColuna(current), 
        linhaNxt = getLinha(next), colunaNxt = getColuna(next);
    int distCurr, distNxt;
    if(tabDist[linhaCurr][colunaCurr] != -1) {
        distCurr = tabDist[linhaCurr][colunaCurr];
        distNxt = tabDist[linhaNxt][colunaNxt];
        if(distCurr <  distNxt) r = -1;
        if(distCurr > distNxt) r = 1;
    } else {
        tabDist = preencheTabuleiro(objAdversario, tabDist, 1);
        distCurr = tabDist[linhaCurr][colunaCurr];
        distNxt = tabDist[linhaNxt][colunaNxt];
        if(distCurr >  distNxt) r = -1;
        if(distCurr < distNxt) r = 1;
    }
    FORI(8) free(tabDist[i]);
    free(tabDist);
    return r;
}

//aproximacao tem valores 1; 0 ou -1 dependo se se aproxima ou não do objetivo
int calcValorCasa(ESTADO *e, COORDENADA c, int aproximacao, Boolean isMax) {
    int r, isCasaParidade = 0;
    if((length(e, c) % 2) == 0) isCasaParidade = 1;
    Boolean terminado = isTerminadoCoordenada(e, c);
    if(terminado && isMax) r = 100;
    else if(terminado && !isMax) r = -100;
    else r = 30 * isCasaParidade + 60 * aproximacao;
    return r;
}

/*Retorna struct com um valor e uma coordenada*/
ParMinMax recAuxMinimax(ESTADO *e, COORDENADA c, int depth, Boolean isMax, int aproximacao){
    ParMinMax aux, r;
    Boolean nxtLevel = isMax ? False : True;
    r = isMax ? setPar(-101, c) : setPar(101, c);
    int minMax;
    Boolean terminado = isTerminadoCoordenada(e, c);
    if(terminado && isMax) r = setPar(100, c);
    else if(terminado && !isMax) r = setPar(-100, c);
    else if(depth != 0) {
        LISTA proxCoords = createList();
        proxCoords = movsDisponiveis(e, proxCoords, c); 
        while (proxCoords) {
            COORDENADA *head = getHead(proxCoords);
            aux = recAuxMinimax(e, *head, depth - 1, nxtLevel, aproximacao);
            minMax = isMax ? maxValue(r, aux) : minValue(r, aux);
            if(isMax)
                r = minMax > getValorPar(r) ? setPar(minMax, c) : r;
            else 
                r = minMax < getValorPar(r) ? setPar(minMax, c) : r;
            proxCoords = deleteHead(proxCoords);
        }
    } else {
        int valor = calcValorCasa(e, c, aproximacao, isMax);
        r = setPar(valor, c);
    }
    return r; 
}

//Retorna a coordenada para a qual devemos jogar
COORDENADA minimax(ESTADO *e, int depth) {
    COORDENADA r = createNullCoord();
    int aproximacao;
    if(depth > 0) {
        int minMax;
        LISTA possiveisJogadas = createList();
        ParMinMax next, max = setPar(-102, createNullCoord()); //Estes valores tem de ser menor que na auxiliar pois precisa ser overwritten
        COORDENADA casaAtual = getUltimaJogada(e);
        possiveisJogadas = movsDisponiveis(e, possiveisJogadas, getUltimaJogada(e));
        //Para cada elemento aplicar recursivamente um auxiliar do minimax que retorna
        //um par com o valor e a coordenada
        while(possiveisJogadas) {
            COORDENADA *head = getHead(possiveisJogadas);
            aproximacao = verAproximacao(e, casaAtual, *head);
            next = recAuxMinimax(e, *head, depth - 1, True, aproximacao);
            minMax = maxValue(max, next);
            if(minMax > getValorPar(max))
                max = setPar(minMax, *head);
            possiveisJogadas = deleteHead(possiveisJogadas);
        }
        r = getCoordPar(max);
    }
    return r;
}

COORDENADA floodFill(ESTADO *e) {
    //Incializar um tabuleiro com as distancias ao objetivo do jogador atual
    int **tabDistancias = initTabDistancias(e), jogador = getjogador(e);
    COORDENADA casaAtual = getUltimaJogada(e), 
        objetivo = jogador == 1 ? setCoordenada(0, 0) : setCoordenada(7, 7),
        r;

    tabDistancias = preencheTabuleiro(objetivo, tabDistancias, 1);

    int linha = getLinha(casaAtual), coluna = getColuna(casaAtual), min = 100;
    for(int i = linha - 1; i <= linha + 1; i++)
        for(int j = coluna - 1; j <= coluna + 1; j++) {
            if(i >= 0 && i < 8 && j >= 0 && j < 8 && (linha != i || coluna != j)) {
                if(jogador == 1 && tabDistancias[i][j] < min) {
                    min = tabDistancias[i][j];
                    r = setCoordenada(i, j);
                } else if (jogador == 2 && tabDistancias[i][j] <= min) {
                    min = tabDistancias[i][j];
                    r = setCoordenada(i, j);
                }
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
