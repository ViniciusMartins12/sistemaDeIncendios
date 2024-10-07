#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "functions.h"

#define SIZE 30

char forest[SIZE][SIZE];
pthread_mutex_t mutex;
pthread_cond_t cond;

void *fire_generator(void *arg);
void *sensor_node(void *arg);
void *control_center(void *arg);
void print_forest();

int main() {
    pthread_t sensors[SIZE][SIZE];
    pthread_t fire_thread, control_thread;

    // Inicializa a matriz da floresta
    init_forest(forest);

    // Inicializa mutex e condição
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // Cria a thread da central de controle
    pthread_create(&control_thread, NULL, control_center, NULL);

    // Cria a threads geradoras de incêndio
    pthread_create(&fire_thread, NULL, fire_generator, NULL);

    // Cria os nós sensores
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            pthread_create(&sensors[i][j], NULL, sensor_node, (void*)&forest[i][j]);
        }
    }

    // Espera pelas threads
    pthread_join(fire_thread, NULL);
    pthread_join(control_thread, NULL);

    // Finaliza mutex e condição
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
