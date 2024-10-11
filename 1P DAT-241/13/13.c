#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define VECTOR_SIZE 10
#define STRING_LENGTH 20

int main(int argc, char** argv) {
    int rank, size;
    char strings[VECTOR_SIZE][STRING_LENGTH]; // Vector de cadenas

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Inicializar el vector de cadenas en el procesador maestro
        for (int i = 0; i < VECTOR_SIZE; i++) {
            snprintf(strings[i], STRING_LENGTH, "Cadena %d", i + 1);
        }
    }

    // Broadcast el vector de cadenas a todos los procesos
    MPI_Bcast(strings, VECTOR_SIZE * STRING_LENGTH, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Cada procesador despliega su parte
    for (int i = rank; i < VECTOR_SIZE; i += size) {
        if (rank == 1 && i % 2 == 0) { // Procesador 1: posiciones pares
            printf("Procesador 1 (Par) - Posición %d: %s\n", i, strings[i]);
        } else if (rank == 2 && i % 2 != 0) { // Procesador 2: posiciones impares
            printf("Procesador 2 (Impar) - Posición %d: %s\n", i, strings[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
