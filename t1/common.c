#include<stdlib.h>
#include<time.h>
#include"common.h"

int randi(int min, int max)
{
	return ( rand() % (max - min + 1) ) + min;
}

void swap(int *a, int *b)
{
	int swp = *a;
	*a = *b;
	*b = swp;
}

static time_t start = 0;

void tic()
{
	start = clock();
}

float toc()
{
	return (float) (clock() - start) / CLOCKS_PER_SEC;
}
