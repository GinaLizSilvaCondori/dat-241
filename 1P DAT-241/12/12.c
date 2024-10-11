#include "stdio.h"
#include "omp.h"
void main()
{
	int a=0,b=1,c;
	int procesadores, maquina;
	
	#pragma omp parallel private(procesadores, maquina) shared(b,a) private(c)
	{
		int i;
		procesadores=omp_get_num_threads();
		maquina= omp_get_thread_num();
		#pragma omp for
		for(i=0;i<10;i++)
		{
			printf("%d ",b);
			c=a+b;
			a=b;
			b=c;
		}
	}
	//printf("La suma externa es %d :" suma total");
}
