#ifndef __COZINHA_H__
#define __COZINHA_H__

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "cozinheiro.h"
#include "pedido.h"
#include "semaphore.h"
#include "tarefas.h"

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

extern Cozinha* cozinha_init(int num_cozinheiros, int bocas, int frigideiras, int garcons, int tam_balcao);
extern void cozinha_destroy();
extern void processar_pedido(pedido_t p, Cozinha *cozinha);

void* preparar_bacon(void* arg);
void* preparar_spaghetti(void* arg);
void* preparar_molho(void* arg);
void* fazer_caldo(void* arg);

#endif /*__COZINHA_H__*/
