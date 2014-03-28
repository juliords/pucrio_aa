#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"instance.h"
#include"common.h"
#include"heap.h"
#include"quick.h"
#include"stupid.h"

#define MSG		"%s select found the %d-th element, %d, in %.4fs\n"
#define MSG_NOK	"%s select failed to find the %d-th element in under %ds\n"
#define VSIZE	(1 << 25)

int vet[VSIZE];
int vet2[VSIZE];

void test_one(int n, int k, int (*select)(int*, int, int), char *name, int ntimes)
{
	int i, kth;
	float total = 0;
	for (i = 0; i < ntimes; i++)
	{
		copy_array(vet, vet2, n);
		tic();
		kth = select(vet2, n, k);
		total += toc();
		
		if (kth == ABORTED)
			break;
	}
	if (kth != ABORTED)
		printf(MSG, name, k, kth, total / ntimes);
	else
		printf(MSG_NOK, name, k, TIME_LIMIT);
}

void test_all(int n, int k)
{
	test_one(n, k, stupid_select, "Stupid", 1);
	test_one(n, k, heap_select, "Heap", 1);
	test_one(n, k, quick_select, "Quick", 10);
	printf("\n");
}

void test_battery(int n)
{
	test_all(n, 5);
	test_all(n, log_2(n));
	test_all(n, (int) sqrt((double) n));
	test_all(n, n / 2);
}

int main()
{
	int i, j;

	srand(time(NULL));
	
	for (i = 1; i <= 15; i++)
	{
		int n = 1000 * (1 << i);
		printf("Input with %d elements.\n", n);
		instance_a(vet, n);
		test_battery(n);
	}
	
	for (j = 1; j <= 10; j++)
	{
		int n = 1 << 25;
		int p = 1 << j;
		printf("Input with 2^25 ordered elements and %d permutations.\n", p);
		instance_b(vet, n, p);
		test_battery(n);
	}

	return 0;
}
