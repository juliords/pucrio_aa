#include<stdio.h>
#include<time.h>
#include<math.h>
#include"common.h"
#include"prng.h"

/* ------------------------------------------------------ */

unsigned int randi(int min, int max)
{
	return (unsigned int) ( randk() % (max - min + 1) ) + min;
}

/* ------------------------------------------------------ */

void swap(int *a, int *b)
{
	int swp = *a;
	*a = *b;
	*b = swp;
}

/* ------------------------------------------------------ */

static time_t start = 0;

void tic()
{
	start = clock();
}

float toc()
{
	return (float) (clock() - start) / CLOCKS_PER_SEC;
}

/* ------------------------------------------------------ */

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

/* ------------------------------------------------------ */

int partition(int *v, int low, int high, int pivot_position)
{
	int pivot = v[pivot_position];
	int i = low, j = high - 1;

	// store pivot at the end of the array
	v[pivot_position] = v[high];
	v[high] = pivot;

	while (i < j)
	{
		while (i < j && v[i] <= pivot)
			i++;

		while (i < j && v[j] > pivot) 
			j--;

		if (i < j)
			swap(&v[i], &v[j]);
	}
    
    // adjust pivot's new position, if necessary
	if (v[i] <= pivot)
		i++;

	v[high] = v[i]; // restore pivot to new position
	v[i] = pivot;
	
	return i;
}

/* ------------------------------------------------------ */

int log_2(int n)
{
	return (int) (log(n) / log(2));
}

/* ------------------------------------------------------ */
