#include<stdlib.h>
#include<stdio.h>
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

void print_array(int *v, int n)
{
	int i;
	printf("[%d", v[0]);
	for (i = 1; i < n; i++)
		printf(", %d", v[i]);
	printf("]\n");
}

void copy_array(int *src, int *dst, int n)
{
	int i;
	for (i = 0; i < n; i++)
		dst[i] = src[i];
}
