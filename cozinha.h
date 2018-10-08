#ifndef __COZINHA_H__
#define __COZINHA_H__

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "cozinheiro.h"
#include "pedido.h"
#include "semaphore.h"
#include "tarefas.h"

#define CARNE_C 3
#define SPAGHETTI_C 1
#define SOPA_C 2
#define LIVRE 0
#define ESPERANDO 1
#define OCUPADO 2

typedef struct {
    int num_cozinheiros;
    int bocas;
    int frigideiras;
    int garcons;
    int tam_balcao;

    sem_t sem_cozinheiros;
    sem_t sem_bocas;
    sem_t sem_frigideiras;
    sem_t sem_garcons;
    sem_t sem_tam_balcao;

    Cozinheiro *cozinheiros;
} Cozinha;

typedef struct {
    pedido_t pedido;
    Cozinha *cozinha;
    int id_coz;
} Params;


extern Cozinha* cozinha_init(int num_cozinheiros, int bocas, int frigideiras, int garcons, int tam_balcao);
extern void cozinha_destroy();
extern void* processar_pedido(void* arg);

void* preparar_bacon(void* arg);
void* preparar_spaghetti(void* arg);
void* preparar_molho(void* arg);
void* fazer_caldo(void* arg);

int pegar_cozinheiro_livre();

#endif /*__COZINHA_H__*/
