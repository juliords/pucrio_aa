#include"instance.h"
#include"common.h"

void instance_a(int *v, int n) // n = 1000*(2^i); i = 1:15
{
	int i;

	for(i = 0; i < n; i++)
		v[i] = i + 1;

	for(i = 0; i < n; i++)
	{
		int j = randi(i, n - 1);

		swap(&v[i], &v[j]);
	}
}

void instance_b(int *v, int n, int p) // n = 2^25; p = 2^j; j = 1:15
{
	int i;

	for(i = 0; i < n; i++)
		v[i] = i + 1;

	for(i = 0; i < p; i++)
	{
		int a = randi(0, n - 1);
		int b = randi(0, n - 1);

		swap(&v[a], &v[b]);
	}
}
