#include"instance.h"
#include"common.h"

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

void instance_b(int *inst, int n, int p) // n = 2^25; p = 2^j; j = 1:15
{
	int i;

	for(i = 1; i <= n; i++)
		inst[i] = i;

	for(i = 1; i <= p; i++)
	{
		int a = randi(1,n);
		int b = randi(1,n);

		int swp = inst[a];
		inst[a] = inst[b];
		inst[b] = swp;
	}
}
