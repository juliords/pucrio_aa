#include<stdio.h>
#include<stdlib.h>
#include"instance.h"
#include"common.h"
#include"heap.h"
#include"quick.h"

#define NUM 1000 * 1 << 15

int vet[NUM];
int vet2[NUM];

int main()
{
	int i, median;
	float dt;

	srand(time(NULL));
	
	for (i = 1; i <= 15; i++)
	{
		int n = 1000 * (1 << i);
		printf("\nInput with %d elements.\n", n);
		
		instance_a(vet, n);
		
		copy_array(vet, vet2, n);
		tic();
		median = heap_select(vet2, n, n / 2);
		dt = toc();
		printf("Heap select found the median %d in %.3fs\n", median, dt);
		
		copy_array(vet, vet2, n);
		tic();
		median = quick_select(vet2, n, n / 2);
		dt = toc();
		printf("Quick select found the median %d in %.3fs\n", median, dt);
	}

	return 0;
}
