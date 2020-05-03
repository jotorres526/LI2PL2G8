/**
@file controller.h
Definição da lógica e controlo do estado
*/
#ifndef ___CONTROLLER_H___
#define ___CONTROLLER_H___
#include "data.h"
#include "list.h"

/**
\brief Verifica se uma coordenada é vizinha da ultima jogada, está a mover-se para uma casa onde nao haja peças brancas ou pretas e se está dentro
dos boundries do tabuleiro, efetivamente verificando se é um movimento válido
@param e Estado do jogo
@param c Coordenada a verificar
@returns True se for uma jogada válida e False caso contrário
*/ 
Boolean isJogadaValida(ESTADO *e, COORDENADA c);

/**
\brief Partindo do pressuposto que uma peça está rodeada faz um "quadrado" de coordenadas em volta da COORDENADA c e percorre todas as 8 coordenadas.
Se encontrar uma casa VAZIO; UM ou DOIS é verificado que nessa coordenada a peça não está rodeada
@param e Estado do jogo
@param c Coordenada que se quer verificar se está rodeada
@returns True caso a peça se encontre rodeada e False caso contrário 
*/
Boolean isRodeado(ESTADO *e, COORDENADA c);

/**
\brief Cálcula qual é o jogador atual e dependendo disso adiciona/altera uma jogada no array de jogadas e altera o valor da ultima jogada para a dada COORDENADA
@param e Estado do jogo
@param c Coordenada a adicionar ao array
*/ 
void addMovJogador(ESTADO *e, COORDENADA c);

/**
\brief Definição da função que realiza as jogadas. 
Nesta função são realizadas as seguintes tarefas:
Verifica se a coordenada introduzida é vizinha, se está vazia e se está dentro do tabuleiro.
Visto isto caso seja o jogador 1 a jogar , coloca a jogada no parametro ultima jogada e troca para o jogador 2.
Caso seja o jogador 2 coloca também a nova jogada na ultima jogada, troca o jogador e ainda coloca no array de jogadas.
Caso a jogada não seja possível retorna 1. 
@param e Apontador para o estado
@param c A coordenada
@returns 1 no caso de a jogada ser válida e 0 no caso contrário
*/
ERROS jogar(ESTADO *e, COORDENADA c);

/**
\brief Função que determina se o Jogo está terminado.
Neste sentido verifica se o algum jogador chegou a casa UM ou DOIS.
Caso chegue retorna True caso contrário falso.
@param e Apontador para o estado
@returns True no caso de o jogo ter terminado, False caso contrário
*/
Boolean isTerminado(ESTADO *e);

/**
\brief Função que verifica se a jogada a ser realizada é vizinha da casa anterior. 
Retorna True caso seja, False caso contrário.
@param e Apontador para o estado
@param c Coordanada da casa atual
@returns True no caso de c ser vizinha da posição atual, False caso contrário
*/
Boolean isCasaVizinha(ESTADO *e, COORDENADA c);

/**
\brief Função que grava o tabuleiro no seu estado atual para um ficheiro de texto.
@param e Apontador para o estado
@param filename Nome do ficheiro que sera gravado
@returns OK no caso de ter gravado com sucesso, ERRO_ABRIR_FICHEIRO caso contrário
*/
ERROS gravar(ESTADO *e, char *filename);

/**
\brief Função que lê um ficheiro e converte cada linha do mesmo para uma linha de tabuleiro do Estado do jogo.
@param e Apontador para o estado
@param filename Nome do ficheiro para ler
@returns OK no caso de ter gravado com sucesso, ERRO_ABRIR_FICHEIRO caso contrário
*/
ERROS ler(ESTADO *e,  char *filename);

/**
\brief Função que determina qual foi o jogador que venceu o jogo. 
Avalia portanto se o jogador se encontra na casa UM ou casa DOIS ou se está rodeado.
@param e Apontador para o estado
@returns O jogador vencedor
*/
int winner (ESTADO *e) ;

/**
\brief Faz o jogo se movimentar entre jogadas podendo ir desde a jogada 0 até à ultima jogada
@param e - Estado do jogo
@param n - Jogada a partir de onde se vai continuar o jogo
@returns True caso seja possivel e False caso contrario
*/ 
Boolean goToPos(ESTADO *e, int n);

/**
\brief Função que faz uma jogada com base em heuristicas
@param e Apontador para o estado
@param heuristica que deve ser utilizada caso seja 1 é o floodfill caso 2 é o minimax
@returns Coordenada que aproxima o jogador da vitorias
*/
ERROS jog(ESTADO *e, int heuristica);

/**
\brief Função o melhor valor de uma casa a ser jogada através do algoritmo minimax
@param e Apontador para o estado
@param depth - profundidade de jogadas a ser analisadas
@returns coordenada com o melhor valor
*/
COORDENADA minimax(ESTADO *e, int depth) ;
/**
\brief Função o melhor valor de uma casa a ser jogada através do algoritmo floodfill
@param e Apontador para o estado
@returns coordenada com o melhor valor
*/
COORDENADA floodFill(ESTADO *e); 

/**
\brief Função que cria a lista com todos os movimentos disponíveis a volta de uma casa
@param e Apontador para o estado
@param l Lista a ser inserida as coordenadas
@param c coordenada onde sera feita a avaliação
@returns Lista com as coordenadas disponíveis
*/
LISTA movsDisponiveis(ESTADO *e, LISTA l, COORDENADA c);

/**
\brief Função que calcula o numero de coordenadas livres a volta de uma coordenada c. Neste modo calcular se é par as coordenadas a volta
@param e Apontador para o estado
@param c coordenada para ser avaliada
@returns numero de coordenadas possíveis
*/
int length(ESTADO *e, COORDENADA c);

/**
\brief Função que dada um coordenada ve se o jogo terminou nessa coordenada
@param e Apontador para o estado
@param c coordenada para ser avaliada
@returns True caso o jogo esteja acabado, False caso contrário
*/
Boolean isTerminadoCoordenada(ESTADO *e, COORDENADA c);

/**
\brief Função que dada dois pares minimax retorna o maior valor
@param fst primeiro parMinMax
@param snd segundo parMinMax
@returns retorna o maior valor dos pares
*/
int maxValue(ParMinMax fst, ParMinMax snd);

/**
\brief Função que dada dois pares minimax retorna o menor valor
@param fst primeiro parMinMax
@param snd segundo parMinMax
@returns retorna o menor valor dos pares
*/
int minValue(ParMinMax fst, ParMinMax snd);

/**
\brief Função que dada dois pares minimax retorna o menor valor
@param tabDistancias apontador para um tabuleiro de distancias
@param c coordenada onde se quer iniciar a contagem de distancias do tabuleiro
@returns a lista com as casas a volta vaziass
*/
LISTA casasTabDistancia(int **tabDistancias, COORDENADA c);

/**
\brief Função que preenche um tabuleiro de inteiros com a sua distancia a um dado objetivo
Neste sentido o tabuleiro de distancias e um tabuleiro criado desde uma casa objetivo ate preencher o tabuleiro todo. Cada casa
contem um inteiro com a distância ao respetivo objetivo. Ideia é o jogador mover se para a casa com menor valor.
@param c coordenada onde se quer iniciar a contagem de distancias do tabuleiro
@param tabDistancias apontador para um tabuleiro de distancias
@param dist numero a ser incrementado desde a casa objetivo até ao fim do tabuleiro, ou seja, as respetivas distâncias
@returns o tabuleiro de inteiros preenchido
*/
int** preencheTabuleiro(COORDENADA c, int **tabDistancias, int dist);

/**
\brief Função que inicializa um tabuleiro de distâncias
@param e apontador para o estado atual do jogo
@returns tabuleiro inicializado e pronto a ser mudado com as respetivas distâncias
*/
int **initTabDistancias(ESTADO *e);

/**
\brief Função que dado um estado e uma coordenada seguinte calcula se essa coordenada se aproxima da casa objetivo para vencer
@param e apontador para o estado atual do jogo
@param current que é a coordenada onde se encontra o jogador;
@param next coordenada futura
@returns 1 caso o jogador se aproxime da casa objetivo, 0 caso seja uma distancia igual e -1 caso seja uma casa mais distante.
*/
int verAproximacao(ESTADO *e, COORDENADA current, COORDENADA next);

/**
\brief Função que que calcula o valor de uma casa num estado
@param e apontador para o estado atual do jogo
@param c coordenada a ser avaliada
@param aproximacao resultado da função verAproximação
@param isMax booleano que diz se é o jogador maximizante ou não
@returns 1 caso o jogador se aproxime da casa objetivo, 0 caso seja uma distancia igual e -1 caso seja uma casa mais distante.
*/
int calcValorCasa(ESTADO *e, COORDENADA c, int aproximacao, Boolean isMax);

/**
\brief Função que faz a recursão do minimax
@param e apontador para o estado atual do jogo
@param c coordenada a ser avaliada
@param depth profundidade a ser utilizada pelo algoritmios
@param isMax booleano que diz se é o jogador maximizante ou não
@param aproximacao que diz se o jogador se encontra proximo da casa objetivo ou não
@returns um ParMinMax com a melhor jogada de acordo com o isMax
*/
ParMinMax recAuxMinimax(ESTADO *e, COORDENADA c, int depth, Boolean isMax, int aproximacao);
#endif