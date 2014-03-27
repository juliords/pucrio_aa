#include"instance.h"
#include"common.h"

void instance_a(int *v, int n) // n = 1000*(2^i); i = 1:15
{
	int cont;

	for(cont = 0; cont < n; cont++)
		v[cont] = cont;

	for(cont = 0; cont < n; cont++)
	{
		int j = randi(cont, n-1);

		swap(&v[cont], &v[j]);
	}
}

void instance_b(int *v, int n, int p) // n = 2^25; p = 2^j; j = 1:15
{
	int i;

	for(i = 0; i < n; i++)
		v[i] = i;

	for(i = 0; i < p; i++)
	{
		int a = randi(1,n);
		int b = randi(1,n);

		swap(&v[a], &v[b]);
	}
}
