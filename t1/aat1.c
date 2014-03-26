#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int randi(int min, int max)
{
	return ( rand() % (max - min + 1) ) + min;
}

void instance_a(int *inst, int n) // n = 1000*(2^i); i = 1:15
{
	int cont;

	for(cont = 1; cont <= n; cont++)
		inst[cont] = cont;

	cont = 1;
	while(cont <= n)
	{
		int j = randi(cont, n);

		int swp = inst[j];
		inst[j] = inst[cont];
		inst[cont] = swp;

		cont++;
	}
}

void instance_b(int *inst, int n, int j) // n = 2^25; p = 2^j; j = 1:15
{
	int i;

	for(i = 1; i <= n; i++)
		inst[i] = i;

	for(i = 1; i <= j; i++)
	{
		int a = randi(1,n);
		int b = randi(1,n);

		int swp = inst[a];
		inst[a] = inst[b];
		inst[b] = swp;
	}
}

int vet[35000000];

int main ()
{
	int i;

	srand(time(NULL));
	printf("%d\n", 2<<(4-1));

	for(i = 1; i <= 15; i++)
		instance_a(vet, 1000*(2<<(i-1)));

	for(i = 1; i <= 15; i++)
		instance_b(vet, 2<<(25-1), 2<<(i-1));

	return 0;
}

