#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"instance.h"
#include"common.h"
#include"heap.h"
#include"quick.h"
#include"stupid.h"
#include"median.h"

int vet[INPUT_MAX];
int vet2[INPUT_MAX];

int main_stupid_test()
{
	int n = 20;
	srand(time(NULL));
	instance_a(vet, n);
	print_array(vet, n);
	printf("%d\n", stupid_select(vet, n, n/2));
	print_array(vet, n);

	return 0;
}

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
		median = stupid_select(vet2, n, n / 2);
		dt = toc();
		printf("Stupid select found the median %d in %.3fs\n", median, dt);

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

		copy_array(vet, vet2, n);
		tic();
		median = median_select(vet2, n, n / 2);
		dt = toc();
		printf("Median select found the median %d in %.3fs\n", median, dt);
	}

	return 0;
}
