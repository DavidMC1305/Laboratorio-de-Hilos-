#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_HILOS 3

// Estructura para pasar argumentos a los hilos
struct args {
  int inicio;
  int fin;
};

// Función para calcular el factorial de un rango de números
void *factorial(void *arg) {
  struct args *argumentos = (struct args*) arg;
  int resultado = 1;
  for (int i = argumentos->inicio; i <= argumentos->fin; i++) {
    resultado *= i;
  }
  int *ptr = malloc(sizeof(int));
  *ptr = resultado;
  return ptr;
}

int main() {
  // Dividir el número en 3 partes
  int partes[NUM_HILOS][2] = {{1, 3}, {4, 6}, {7, 9}};

  // Crear los hilos secundarios
  pthread_t hilos[NUM_HILOS];
  for (int i = 0; i < NUM_HILOS; i++) {
    struct args *argumentos = malloc(sizeof(struct args));
    argumentos->inicio = partes[i][0];
    argumentos->fin = partes[i][1];
    pthread_create(&hilos[i], NULL, factorial, (void*) argumentos);
  }

  // Esperar a que todos los hilos terminen y obtener los resultados
  int resultados[NUM_HILOS];
  for (int i = 0; i < NUM_HILOS; i++) {
    void *resultado;
    pthread_join(hilos[i], &resultado);
    resultados[i] = *(int*) resultado;
    free(resultado);
  }

  // Calcular el resultado final
  int resultado_final = 1;
  for (int i = 0; i < NUM_HILOS; i++) {
    resultado_final *= resultados[i];
  }

  // Imprimir el resultado final
  printf("El factorial de 9 es: %d\n", resultado_final);

  return 0;
}
