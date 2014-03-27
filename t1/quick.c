#include<stdio.h>
#include"common.h"

static int do_quick_select(int *v, int low, int high, int k);

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

int quick_select(int *v, int n, int k)
{
	return do_quick_select(v, 1, n - 1, k);
}

static int do_quick_select(int *v, int low, int high, int k)
{
	if (low == high)
		return v[low];
	
	int pivot = randi(low, high), size_l;
	pivot = partition(v, low, high, pivot);
	size_l = pivot - low;
	
	if (size_l == k - 1)
		return v[pivot];
	else if (size_l > k - 1)
		return do_quick_select(v, low, pivot - 1, k);
	else
		return do_quick_select(v, pivot + 1, high, k - size_l - 1);
}
