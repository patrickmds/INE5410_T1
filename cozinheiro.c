#include "cozinheiro.h"

void create_cozinheiro(Cozinheiro *cozinheiro, int id)
{
    cozinheiro->id = id;
    cozinheiro->estado = LIVRE;
}


void destroy_cozinheiro(Cozinheiro* cozinheiro) {
	free(cozinheiro);
}

void cozinheiro_livre(Cozinheiro *cozinheiro)
{
    cozinheiro->estado = LIVRE;
}
void cozinheiro_esperando(Cozinheiro *cozinheiro)
{
    cozinheiro->estado = ESPERANDO;
}
void cozinheiro_ocupado(Cozinheiro *cozinheiro)
{
    cozinheiro->estado = OCUPADO;
}
