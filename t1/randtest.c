#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "prng.h"
#include "lcg.h"
#define LEN (RAND_MAX>>5-1)

int v1[LEN];
int v2[LEN];
int v3[LEN];

int range(unsigned int r, int min, int max)
{
	return min + r % (max - min);
}

void printarray(int* v, int len)
{
	int i;
	for (i = 0; i < len; i++)
		printf("%5d", v[i]);
	printf("\n");
}

double stddev(int* v, int len)
{
	int i;
	double m1 = 0, m2 = 0, mean, var;
	for (i = 0; i < len; i++)
	{
		m1 += (double) v[i];
		m2 += (double) (v[i] * v[i]);
	}
	mean = m1 / len;
	var = m2 / len - mean * mean;
	return sqrt(var * (double) (len - 1) / len);
}

int main()
{
	int i, seed;
	for (i = 0; i < LEN; i++)
	{
		v1[i] = 0;
		v2[i] = 0;
		v3[i] = 0;
	}
	seed = time(NULL);
	srand(seed);
	randk_reset();
	randk_seed_manual(seed);
	lcg_seed(seed);
	
	for (i = 0; i < 10000 * LEN; i++)
	{
		v1[range(rand(), 0, LEN)]++;
		v2[range(randk(), 0, LEN)]++;
		v3[range(lcg_rand(), 0, LEN)]++;
	}
	
	// printarray(v1, LEN);
	printf("Stddev: %.3lf %%\n", 100*stddev(v1, LEN)/LEN);
	// printarray(v2, LEN);
	printf("Stddev: %.3lf %%\n", 100*stddev(v2, LEN)/LEN);
	// printarray(v3, LEN);
	printf("Stddev: %.3lf %%\n", 100*stddev(v3, LEN)/LEN);
	return 0;
}
