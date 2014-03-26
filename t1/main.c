#include<stdio.h>
#include<stdlib.h>
#include"instance.h"
#include"common.h"

int vet[35000000];

int main ()
{
	int i;

	srand(time(NULL));

	tic();
	for(i = 1; i <= 15; i++)
		instance_a(vet, 1000*(2<<(i-1)));
	printf("Instance A: %.3fs\n", toc());

	tic();
	for(i = 1; i <= 15; i++)
		instance_b(vet, 2<<(25-1), 2<<(i-1));
	printf("Instance B: %.3fs\n", toc());

	return 0;
}
