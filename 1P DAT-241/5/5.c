#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_POINTS 1000000 //num tot de puntos a generar

//estructura para pasar argumentos a la funcion del hilo
typedef struct{
	int start;
	int end;
	int *count;
}ThreadArgs;

//funcion para generar puntos aleatorios y contar cuantos caen dentro del circulo
void *monteCarlo(void *args){
	ThreadArgs *threadArgs=(ThreadArgs *)args;
	int start=threadArgs->start;
	int end=threadArgs->end;
	int *count=threadArgs->count;
	
	//semilla de generacion de num aleatorios
	unsigned int seed=time(NULL)^pthread_self();
	
	//contador para puntos dentro del circulo
	int local_count=0;
	
	for(int i=start;i<end;i++){
		//Genrear coordenadas aleatorias entre -1 y 1
		double x= (double)rand_r(&seed) / RAND_MAX * 2-1;
		double y= (double)rand_r(&seed) / RAND_MAX * 2-1;
		
		//Verificar si el punto esta dentro del circulo
		if(x*x+y*y<=1){
			local_count++;
		}
	}
	*count=local_count;
	pthread_exit(NULL);
}

int main(){
	pthread_t threads[4];//almacena los identificadoes de los hilos
	int counts[4];//almacena los recuentos locales de cada hilo
	
	//Crear hilos y realizar el calculo en paralelo
	for(int i=0;i<4;i++){
		ThreadArgs *args=(ThreadArgs *)malloc(sizeof(ThreadArgs));
		args->start=i*NUM_POINTS/4;
		args->end=(i+1)*NUM_POINTS/4;
		args->count=&counts[i];
		pthread_create(&threads[i],NULL,monteCarlo,(void *)args);
	}
	for(int i=0;i<4;i++){
		pthread_join(threads[i],NULL);
	}
	int total_count=0;
	for(int i=0;i<4;i++){
		total_count+=counts[i];
	}
	
	//Calcular la aprox de pi
	double pi_approx=(double)total_count/NUM_POINTS*4;
	
	printf("Aproximacion de pi: %lf\n",pi_approx);
}
	
	
