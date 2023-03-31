#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TAM_ARREGLO 5

int arreglo[TAM_ARREGLO] = {0};
int indice = 0;
int num_productores_terminados = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condicion_consumidor = PTHREAD_COND_INITIALIZER;

void* productor(void* arg) {
    int valor;
    while (indice < TAM_ARREGLO) {
        printf("Introduzca un valor para la casilla %d: ", indice);
        scanf("%d", &valor);
        pthread_mutex_lock(&mutex);
        arreglo[indice] = valor;
        indice++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void* consumidor(void* arg) {
    int i;
    while (1) {
        pthread_mutex_lock(&mutex);
        for (i = 0; i < TAM_ARREGLO; i++) {
            if (arreglo[i] != 0) {
                printf("Valor consumido: %d\n", arreglo[i]);
                arreglo[i] = 0;
            }
        }
        if (num_productores_terminados && indice == TAM_ARREGLO) {
            break;
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t hilo_productor;
    pthread_t hilo_consumidor;
    int i;

    pthread_create(&hilo_productor, NULL, productor, NULL);
    pthread_create(&hilo_consumidor, NULL, consumidor, NULL);

    pthread_join(hilo_productor, NULL);
    num_productores_terminados = 1;

    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&condicion_consumidor);
    pthread_mutex_unlock(&mutex);

    pthread_join(hilo_consumidor, NULL);

    printf("Hemos terminado.\n");

    return 0;
}
