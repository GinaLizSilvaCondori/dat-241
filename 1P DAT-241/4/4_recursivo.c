#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define NUM_PUNTOS 1000000 //num tot de puntos a generar

//funcion recursiva para contar los puntos dentro del circulo
int calcular(int contador, int dp,int rank,int size){
	int resultado=contador;
	
	if(size>1){
		int mitad=size/2;
	
	if(rank<mitad){
		if(rank==0){
			int cont_der;
			MPI_Recv(&cont_der,1,MPI_INT,rank+mitad,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			resultado+=cont_der;
			}else{
			resultado=calcular(contador,dp+1,rank,mitad);
			}
		}else{
		MPI_Send(&resultado,1,MPI_INT,rank-mitad,0,MPI_COMM_WORLD);
		}
	}
return resultado;
}

int main(int argc, char *argv[]){
	int rank, size;
	int contador=0;
	double pi,x,y;
	int total_contador;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	srand(rank);
	
	for(int i=0;i<NUM_PUNTOS/size;i++){
		x= (double)rand() / RAND_MAX;
		y= (double)rand() / RAND_MAX;
		
		if(x*x+y*y<=1.0){
			contador++;
		}
	}
	total_contador=calcular(contador,0,rank,size);
	
	
	if(rank==0){
		pi=4.0*total_contador/NUM_PUNTOS;
		printf("Valor aprox de pi: %lf\n",pi);
	}
	MPI_Finalize();
	return 0;
}
