#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_HILOS 3
#define NUM_ELEMENTOS 12

int arreglo[NUM_ELEMENTOS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int numero_buscado = 7;
int found_flag = 0;

// Estructura para pasar argumentos a los hilos
struct args {
  int inicio;
  int fin;
};

// Función para buscar el número en un rango de elementos
void *buscar_numero(void *arg) {
  struct args *argumentos = (struct args*) arg;
  for (int i = argumentos->inicio; i <= argumentos->fin; i++) {
    if (arreglo[i] == numero_buscado) {
      found_flag = 1;
      return NULL;
    }
  }
  return NULL;
}

int main() {
  // Dividir el arreglo en 3 sub arreglos
  struct args sub_arreglos[NUM_HILOS] = {{0, 3}, {4, 7}, {8, 11}};

  // Crear los hilos secundarios
  pthread_t hilos[NUM_HILOS];
  for (int i = 0; i < NUM_HILOS; i++) {
    pthread_create(&hilos[i], NULL, buscar_numero, (void*) &sub_arreglos[i]);
  }

  // Esperar a que todos los hilos terminen
  for (int i = 0; i < NUM_HILOS; i++) {
    pthread_join(hilos[i], NULL);
  }

  // Imprimir si el número fue encontrado o no
  if (found_flag) {
    printf("El número %d fue encontrado.\n", numero_buscado);
  } else {
    printf("El número %d no fue encontrado.\n", numero_buscado);
  }

  return 0;
}
