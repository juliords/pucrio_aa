#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"instance.h"
#include"common.h"
#include"heap.h"
#include"quick.h"
#include"stupid.h"
#include"median.h"
#include"prng.h"

#define MSG     "%s select found the %d-th element, %d, in %.4fs\n"
#define MSG_NOK "%s select failed to find the %d-th element in under %ds\n"

int vet[INPUT_MAX];
int vet2[INPUT_MAX];

void test_one(int n, int k, int (*select)(int*, int, int), char *name, int ntimes)
{
	int i, kth = ABORTED;
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
		printf("%f;", total/ntimes); //printf(MSG, name, k, kth, total / ntimes);
	else
		printf("#;"); //printf(MSG_NOK, name, k, TIME_LIMIT);
}

void test_all(int n, int k)
{
	test_one(n, k, stupid_select, "Stupid", 1);
	test_one(n, k, heap_select, "Heap", 1);
	test_one(n, k, median_select, "Median", 1);
	test_one(n, k, quick_select, "Quick", 10);
}

void test_battery(int n)
{
	test_all(n, 5);
	test_all(n, log_2(n));
	test_all(n, (int) sqrt((double) n));
	test_all(n, n / 2);
	printf("\n");
}

int main(int argc, char **argv)
{
	int i, j;
	int seed;

	randk_reset();
	if(argc < 2 || !(seed = atoi(argv[1])))
	{
		//seed = time(NULL);
		randk_seed();
	}
	else
	{
		printf("SEED: %u\n", seed);
		//srand(seed);
		randk_seed_manual(seed);
	}
	
	printf(";;k = 5;;;;k = log2(n);;;;k = sqrt(n);;;;k = n/2;\n");
	printf("i;n;Stupid;Heap;Median;Quick;");
	printf("Stupid;Heap;Median;Quick;");
	printf("Stupid;Heap;Median;Quick;");
	printf("Stupid;Heap;Median;Quick;\n");
	
	for (i = 1; i <= 15; i++)
	{
		int n = 1000 * (1 << i);
		instance_a(vet, n);
		printf("%d;%d;", i, n);
		test_battery(n);
	}
	
	printf("j;p;\n");
	
	for (j = 1; j <= 15; j++)
	{
		int p = 1 << j;
		instance_b(vet, INPUT_MAX, p);
		printf("%d;%d;", j, p);
		test_battery(INPUT_MAX);
	}
	
	return 0;
}
