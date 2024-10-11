#include "stdio.h"
//suma de dos num
void suma(int a,int b,int *c){
	*c=a+b;
}
//resta de dos num
void resta(int a,int b,int *c){
	*c=a-b;
}
//multiplicaion en base a sumas
int multi(int a,int b,int *c){
	*c=0;
	for (int i=0;i<b;i++){
		suma(*c,a,c);
	}
}
//division en base a restas
int div(int a,int b,int *c,int *coci){
	*coci=0;
	*c=a;
	while(*c>=b){
		resta(*c,b,c);
		(*coci)++;
	}
	
}

void main()
{
	int a,b,c;
	printf("Introduzca dos numeros:\n");
	scanf("%d",&a);
	scanf("%d",&b);	
	printf("a: %d, b:%d\n",a,b);
	suma(a,b,&c);
	printf("La suma de ambos numeros es: %d\n",c);
	multi(a,b,&c);
	printf("La multiplicacion de ambos numeros es: %d\n",c);
	resta(a,b,&c);
	printf("La resta de ambos numeros es: %d\n",c);
	int coci;
	div(a,b,&c,&coci);
	printf("La division de ambos numeros es: %d\n",coci);
}

