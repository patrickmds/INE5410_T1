#ifndef __COZINHEIRO__
#define __COZINHEIRO__

#define LIVRE 0
#define ESPERANDO 1
#define OCUPADO 2

#include <stdlib.h>

typedef struct {
    int id;
    int estado;
} Cozinheiro;

void create_cozinheiro(Cozinheiro *cozinheiro, int id);

void destroy_cozinheiro(Cozinheiro *cozinheiro);

void cozinheiro_livre(Cozinheiro *cozinheiro);
void cozinheiro_esperando(Cozinheiro *cozinheiro);
void cozinheiro_ocupado(Cozinheiro *cozinheiro);

#endif
