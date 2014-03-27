#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"instance.h"
#include"common.h"
#include"heap.h"
#include"quick.h"
#include"stupid.h"

#define VSIZE (1 << 25)

int vet[VSIZE];
int vet2[VSIZE];

void test_stupid_select(int n, int k) {
	int kth;
	float dt;
	copy_array(vet, vet2, n);
	tic();
	kth = stupid_select(vet2, n, k);
	dt = toc();
	printf("Stupid select found the %d-th element, %d, in %.3fs\n", k, kth, dt);
}

void test_heap_select(int n, int k) {
	int kth;
	float dt;
	copy_array(vet, vet2, n);
	tic();
	kth = heap_select(vet2, n, k);
	dt = toc();
	printf("Heap select found the %d-th element, %d, in %.3fs\n", k, kth, dt);
}

void test_quick_select(int n, int k) {
	int i, kth;
	float total = 0;
	for (i = 0; i < 10; i++)
	{
		copy_array(vet, vet2, n);
		tic();
		kth = quick_select(vet2, n, k);
		total += toc();
	}
	printf("Quick select found the %d-th element, %d, in %.3fs\n", k, kth, total/10);
}

void test_all(int n, int k)
{
	//test_stupid_select(n, k);
	test_heap_select(n, k);
	test_quick_select(n, k);
	printf("\n");
}

int main()
{
	int i;
	float dt;

	srand(time(NULL));
	
	for (i = 1; i <= 15; i++)
	{
		int n = 1000 * (1 << i);
		printf("Input with %d elements.\n", n);
		instance_a(vet, n);
		
		test_all(n, 5);
		test_all(n, log_2(n));
		test_all(n, (int) sqrt((double) n));
		test_all(n, n / 2);
	}

	return 0;
}
