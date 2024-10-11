#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define VECTOR_SIZE 10

int main(int argc, char** argv) {
    int rank, size;
    int vec1[VECTOR_SIZE], vec2[VECTOR_SIZE], result[VECTOR_SIZE] = {0};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Inicializar los vectores en el procesador maestro
        for (int i = 0; i < VECTOR_SIZE; i++) {
            vec1[i] = i + 1;  // Ejemplo: 1, 2, 3, ..., VECTOR_SIZE
            vec2[i] = (i + 1) * 2; // Ejemplo: 2, 4, 6, ..., VECTOR_SIZE * 2
        }
    }

    // Broadcast los vectores a todos los procesos
    MPI_Bcast(vec1, VECTOR_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(vec2, VECTOR_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada procesador suma su parte
    for (int i = rank; i < VECTOR_SIZE; i += size) {
        if (rank == 1 && i % 2 != 0) { // Procesador 1: posiciones impares
            result[i] = vec1[i] + vec2[i];
        } else if (rank == 2 && i % 2 == 0) { // Procesador 2: posiciones pares
            result[i] = vec1[i] + vec2[i];
        }
    }

    // El procesador maestro recoge los resultados
    MPI_Gather(result, VECTOR_SIZE / size, MPI_INT, result, VECTOR_SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Solo el procesador maestro imprime el resultado
    if (rank == 0) {
        printf("Resultado de la suma:\n");
        for (int i = 0; i < VECTOR_SIZE; i++) {
            // Sumar los resultados de los diferentes procesos
            result[i] = vec1[i] + vec2[i];  // Sumar todos los elementos
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
