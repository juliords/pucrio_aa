#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include<pthread.h>
#include<unistd.h>
#include"instance.h"
#include"common.h"
#include"heap.h"
#include"quick.h"
#include"stupid.h"
#include"median.h"
#include"prng.h"

int vet[INPUT_MAX];
int vet2[INPUT_MAX];

typedef struct 
{
	/* input */
	int (*select)(int*, int, int);
	int *v;
	int n;
	int k;

	/* output */
	int running;
	float time;
	int kth;

} ThreadData;

void* thread_exec(void *arg)
{
	ThreadData *p = (ThreadData*) arg;
	p->running = 1;

	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	tic();
	p->kth = p->select(p->v, p->n, p->k);
	p->time = toc();

	p->running = 0;
	return NULL;
}

void test_one(int n, int k, int (*select)(int*, int, int), char *name, int ntimes)
{
	int i;
	float total = 0;
	void *res;

	pthread_t tid;
	ThreadData td;
	td.v = vet2;
	td.n = n;
	td.k = k;
	td.select = select;

	for (i = 0; i < ntimes; i++)
	{
		copy_array(vet, vet2, n);

		pthread_create(&tid, NULL, thread_exec, &td);

		usleep(1000); // 1ms
		while(td.running)
		{
			if (toc() > TIME_LIMIT)
			{
				pthread_cancel(tid);	
				break;
			}

			usleep(100000); // 100ms
		}
		
		pthread_join(tid, &res);
		if(res == PTHREAD_CANCELED)
		{
			// timed out
			printf("#;");
			return;
		}
		else
		{
			assert(td.kth == k);
			total += td.time;
		}
	}

	printf("%f;", total/ntimes);
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

	// PRNG setup
	randk_reset();
	if(argc < 2 || !(seed = atoi(argv[1])))
	{
		randk_seed();
	}
	else
	{
		printf("SEED: %u\n", seed);
		randk_seed_manual(seed);
	}
	randk_warmup(10);
	
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
	
	for (j = 1; j <= 19; j++)
	{
		int p = 1 << j;
		int n = 1 << 20;
		instance_b(vet, n, p);
		printf("%d;%d;", j, p);
		test_battery(n);
	}
	
	return 0;
}
