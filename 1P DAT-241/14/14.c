#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 4 // Tamaño de las matrices (N x N)

void print_matrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    int rank, size;
    int A[N][N], B[N][N], C[N][N] = {0}; // Matrices A, B y C (resultado)

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Inicializar matrices A y B solo en el proceso maestro
    if (rank == 0) {
        // Matriz A
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = i + j; // Ejemplo: A[i][j] = i + j
            }
        }

        // Matriz B
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                B[i][j] = i * j; // Ejemplo: B[i][j] = i * j
            }
        }
    }

    // Enviar las matrices A y B a todos los procesos
    MPI_Bcast(B, N * N, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        MPI_Bcast(A, N * N, MPI_INT, 0, MPI_COMM_WORLD);
    }

    // Cada proceso calcula su parte de la matriz C
    for (int i = rank; i < N; i += size) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Recolectar los resultados en el proceso maestro
    if (rank != 0) {
        for (int i = rank; i < N; i += size) {
            MPI_Send(C[i], N, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    } else {
        // El proceso maestro copia su resultado
        for (int i = 0; i < N; i++) {
            printf("C[%d]: ", i);
            for (int j = 0; j < N; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }

        // Recibir resultados de otros procesos
        for (int source = 1; source < size; source++) {
            for (int i = source; i < N; i += size) {
                MPI_Recv(C[i], N, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
    }

    // Solo el proceso maestro imprime el resultado final
    if (rank == 0) {
        printf("\nResultado de la multiplicación de matrices A y B (C):\n");
        print_matrix(C);
    }

    MPI_Finalize();
    return 0;
}
