#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define SIZE 30

// Funções declaradas
void init_forest(char forest[SIZE][SIZE]);
void *fire_generator(void *arg);
void *sensor_node(void *arg);
void *control_center(void *arg);
void print_forest();

#endif // FUNCTIONS_H
