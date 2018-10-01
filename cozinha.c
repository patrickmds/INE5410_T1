#include "cozinha.h"

#define CARNE 1
#define SPAGHETTI 2
#define SOPA 3


extern Cozinha* cozinha_init(int num_cozinheiros, int bocas, int frigideiras,
                             int garcons, int tam_balcao)
{
    Cozinha *cozinha = (Cozinha*)malloc(sizeof(Cozinha));

    cozinha->cozinheiros = (Cozinheiro*)malloc(num_cozinheiros * sizeof(Cozinheiro));

    cozinha->num_cozinheiros = num_cozinheiros;
    cozinha->bocas = bocas;
    cozinha->frigideiras = frigideiras;
    cozinha->garcons = garcons;
    cozinha->tam_balcao = tam_balcao;

    sem_init(&(cozinha->sem_cozinheiros), 0, num_cozinheiros);
    sem_init(&(cozinha->sem_bocas), 0, bocas);
    sem_init(&(cozinha->sem_frigideiras), 0, frigideiras);
    sem_init(&(cozinha->sem_garcons), 0, garcons);
    sem_init(&(cozinha->sem_tam_balcao), 0, tam_balcao);

    for(int i = 0; i < num_cozinheiros; i++) {
        create_cozinheiro(&(cozinha->cozinheiros[i]), i);
    }

    return cozinha;
}

extern void cozinha_destroy(Cozinha *cozinha)
{
    sem_destroy(&(cozinha->sem_cozinheiros));
    sem_destroy(&(cozinha->sem_bocas));
    sem_destroy(&(cozinha->sem_frigideiras));
    sem_destroy(&(cozinha->sem_garcons));
    sem_destroy(&(cozinha->sem_tam_balcao));
    free(cozinha);
}


extern void processar_pedido(pedido_t p, Cozinha *cozinha)
{
	pedido_prato_t pedido_prato = p.prato;  // nome do prato

    unsigned int tipo = p.id;
    prato_t* prato = create_prato(p);

    printf(" tipo %d\n", tipo);

    if (tipo == CARNE) {
        printf("PREPARANDO CARNE!\n");
        carne_t* carne = create_carne();
        cortar_carne(carne);
        temperar_carne(carne);

        sem_wait(&(cozinha->sem_frigideiras));
          grelhar_carne(carne);
        sem_post(&(cozinha->sem_frigideiras));

        empratar_carne(carne, prato);
        notificar_prato_no_balcao(prato);

        sem_wait(&(cozinha->sem_tam_balcao));
          printf("Prato no balcão\n");
        sem_wait(&(cozinha->sem_garcons));
        sem_post(&(cozinha->sem_tam_balcao));
          printf("Garçom entregando o prato\n");
          entregar_pedido(prato);
          printf("Prato entregue\n");
        sem_post(&(cozinha->sem_garcons));

    } else if (tipo == SPAGHETTI) {
        printf("PREPARANDO SPAGHETTI!\n");

        molho_t* molho_preparado;
        spaghetti_t* spaghetti_preparado;
        bacon_t* bacon_preparado;

        pthread_t threads[3];
        pthread_create(&threads[0], NULL, preparar_spaghetti, &cozinha);
        pthread_create(&threads[1], NULL, preparar_molho, &cozinha);
        pthread_create(&threads[2], NULL, preparar_bacon, &cozinha);

        pthread_join(threads[0], (void *)spaghetti_preparado);
        pthread_join(threads[1], (void *)molho_preparado);
        pthread_join(threads[2], (void *)bacon_preparado);

        empratar_spaghetti((spaghetti_t *)spaghetti_preparado, (molho_t *)molho_preparado, (bacon_t *)bacon_preparado, prato);
        notificar_prato_no_balcao(prato);

        sem_wait(&(cozinha->sem_tam_balcao));
          printf("Prato no balcão\n");
        sem_wait(&(cozinha->sem_garcons));
        sem_post(&(cozinha->sem_tam_balcao));
          printf("Garçom entregando o prato\n");
          entregar_pedido(prato);
          printf("Prato entregue\n");
        sem_post(&(cozinha->sem_garcons));

    } else if (tipo == SOPA) {
        printf("PREPARANDO SOPA!\n");
        legumes_t* legumes = create_legumes();
        caldo_t* caldo_pronto;
        pthread_t thread;
        pthread_create(&thread, NULL, fazer_caldo, &cozinha);

        cortar_legumes(legumes);

        pthread_join(thread, (void *)caldo_pronto);
        cozinhar_legumes(legumes, (caldo_t *)caldo_pronto);
        sem_post(&(cozinha->sem_bocas));

        empratar_sopa(legumes, (caldo_t *)caldo_pronto, prato);

        notificar_prato_no_balcao(prato);
        sem_wait(&(cozinha->sem_tam_balcao));
          printf("Prato no balcão\n");
        sem_wait(&(cozinha->sem_garcons));
        sem_post(&(cozinha->sem_tam_balcao));
          printf("Garçom entregando o prato\n");
          entregar_pedido(prato);
          printf("Prato entregue\n");
        sem_post(&(cozinha->sem_garcons));
    } else {
        printf("Prato não está no menu\n");
    }

    return;
}

void* preparar_molho(void* arg)
{
    Cozinha *cozinha = (Cozinha *)arg;

    molho_t* molho = create_molho();

    sem_wait(&(cozinha->sem_bocas));
      esquentar_molho(molho);
    sem_post(&(cozinha->sem_bocas));

    pthread_exit(&molho);
}

void* preparar_spaghetti(void* arg)
{
    Cozinha *cozinha = (Cozinha *)arg;
    spaghetti_t* spaghetti = create_spaghetti();
    agua_t* agua = create_agua();

    sem_wait(&(cozinha->sem_bocas));
      ferver_agua(agua);
      cozinhar_spaghetti(spaghetti, agua);
    sem_post(&(cozinha->sem_bocas));

    pthread_exit(&spaghetti);
}

void* preparar_bacon(void* arg)
{
    Cozinha *cozinha = (Cozinha *)arg;
    bacon_t* bacon = create_bacon();

    sem_wait(&(cozinha->sem_frigideiras));
    sem_wait(&(cozinha->sem_bocas));
      dourar_bacon(bacon);
    sem_wait(&(cozinha->sem_bocas));
    sem_wait(&(cozinha->sem_frigideiras));

    pthread_exit(&bacon);
}

void* fazer_caldo(void* arg)
{
    Cozinha *cozinha = (Cozinha *)arg;
    agua_t* agua = create_agua();
    sem_wait(&(cozinha->sem_bocas));
      ferver_agua(agua);
      caldo_t* caldo = preparar_caldo(agua);
    pthread_exit(&caldo);
}
