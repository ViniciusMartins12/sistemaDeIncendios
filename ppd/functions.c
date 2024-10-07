#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "functions.h"

extern char forest[SIZE][SIZE];
extern pthread_mutex_t mutex;
extern pthread_cond_t cond;

void init_forest(char forest[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            forest[i][j] = 'T';  // Todos os nós sensores estão ativos
        }
    }
}

void *fire_generator(void *arg) {
    while (1) {
        sleep(3);  // Gera incêndio a cada 3 segundos
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        pthread_mutex_lock(&mutex);
        if (forest[x][y] == 'T') {
            forest[x][y] = '@';  // Marca como fogo
            printf("Incêndio gerado em: (%d, %d)\n", x, y);
            pthread_cond_broadcast(&cond);  // Notifica todos os sensores
        }
        pthread_mutex_unlock(&mutex);
    }
}

void *sensor_node(void *arg) {
    char *cell = (char *)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        while (*cell != '@') {
            pthread_cond_wait(&cond, &mutex);  // Espera notificação
        }
        // Detectou incêndio
        printf("Sensor detectou incêndio na célula: %c\n", *cell);
        // Comunica com vizinhos, se for borda, avisa a central
        *cell = '/';  // Célula queimada
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *control_center(void *arg) {
    while (1) {
        // Lógica para receber mensagens dos sensores e combater incêndios
        sleep(5);  // Tempo entre ações da central
        printf("Central de controle monitorando...\n");
        // Aqui você pode implementar mais lógica para o combate ao fogo
    }
}

void print_forest() {
    // Função para imprimir a floresta
}
