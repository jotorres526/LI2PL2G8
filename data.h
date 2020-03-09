#ifndef ___DATA_H___
#define ___DATA_H___

typedef enum {VAZIO, BRANCA, PRETA} CASA;

typedef struct {
    int coluna;
    int linha;
} COORDENADA;

typedef struct {
    COORDENADA jogador1;
    COORDENADA jogador2;
} JOGADA;
typedef JOGADA JOGADAS[32];

typedef struct {
    CASA tab[8][8];
    COORDENADA ultima_jogada;
    JOGADAS jogadas;
    int num_jogadas;
    int jogador_atual;
} ESTADO;

//Cria um estado vazio com o tabuleiro inicializado
ESTADO *inicializar_estado();
//Retorna qual o numero do jogador atual(1 ou 2)
int obter_jogador_atual(ESTADO *estado);
//Retorna o numero de jogadas efetuadas(Cada jogada tem o movimento dos dois jogadores)
int obter_numero_de_jogadas(ESTADO *estado);
//Retorna o estado atual da casa na coordenada c (Branca, Preta ou Vazia)
int obter_estado_casa(ESTADO *e, COORDENADA c);

#endif