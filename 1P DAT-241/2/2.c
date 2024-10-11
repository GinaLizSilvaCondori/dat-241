#include "stdio.h"
//suma de dos num
int suma(int a,int b){
	return a+b;
}
//resta de dos num
int resta(int a,int b){
	return a-b;
}
//multiplicaion en base a sumas
int multi(int a,int b){
	int c=0;
	for (int i=0;i<b;i++){
		c=suma(a,b);
	}
	return c;
}
//division en base a restas
int div(int a,int b){
	int c;
	int coci=0;
	while(c>=b){
		c=resta(a,b);
		coci++;
	}
	return coci;	
}

void main()
{
	int a,b;
	printf("Introduzca dos numeros:\n");
	scanf("%d",&a);
	scanf("%d",&b);	
	printf("a: %d, b:%d\n",a,b);
	
	int s=suma(a,b);
	printf("La suma de ambos numeros es: %d\n",s);
	
	int m=multi(a,b);
	printf("La multiplicacion de ambos numeros es: %d\n",m);
	
	int r=resta(a,b);	
	printf("La resta de ambos numeros es: %d\n",r);
	
	int d=div(a,b);
	printf("La division de ambos numeros es: %d\n",d);
}

