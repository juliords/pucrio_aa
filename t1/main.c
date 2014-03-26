#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"instance.h"

int vet[35000000];

int main ()
{
	int i;

	srand(time(NULL));

	for(i = 1; i <= 15; i++)
		instance_a(vet, 1000*(2<<(i-1)));

	for(i = 1; i <= 15; i++)
		instance_b(vet, 2<<(25-1), 2<<(i-1));

	return 0;
}
