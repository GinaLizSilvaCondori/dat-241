#include <stdio.h>

#define N 10  // Número de términos de la secuencia a calcular

int main() {
    int fibonacci[N];  // Array para almacenar los términos de Fibonacci

    // Inicializamos los dos primeros términos
    fibonacci[0] = 0;  
    fibonacci[1] = 1;  

    // Calculamos los siguientes términos
    for (int i = 2; i < N; i++) {
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
    }

    // Imprimimos la secuencia de Fibonacci
    printf("Secuencia de Fibonacci:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", fibonacci[i]);
    }
    printf("\n");

    return 0;
}
