#include"common.h"

static void heap_sort(int *v, int n);
static void heapify(int *v, int n);
static void sink(int *v, int start, int end);
static int is_heap(int *v, int n);

int heap_select(int *v, int n, int k)
{
	int end;
	heapify(v, n);
	for (end = n - 1; end >= n - k; end--)
	{
		swap(&v[0], &v[end]);
		sink(v, 0, end - 1);
		
		if (toc() > TIME_LIMIT)
			return ABORTED;
	}
	return v[end + 1];
}

static void heap_sort(int *v, int n)
{
	int end;
	heapify(v, n);
	for (end = n - 1; end > 0; end--)
	{
		swap(&v[0], &v[end]);
		sink(v, 0, end - 1);
	}
}

static void heapify(int *v, int n)
{
	int start = (n - 2) / 2;
	while (start >= 0)
	{
		sink(v, start, n - 1);
		start--;
	}
}

static void sink(int *v, int start, int end)
{
	int root = start, child, swap_node;
	
	while (2 * root + 1 <= end)
	{
		child = 2 * root + 1; // left child
		swap_node = root;
		
		// compare with left child
		if (v[swap_node] > v[child])
			swap_node = child;
			
		// compare with right child
		if (child + 1 <= end && v[swap_node] > v[child + 1])
			swap_node = child + 1;
		
		// if there is a smaller child, swap
		if (swap_node != root)
		{
			swap(&v[swap_node], &v[root]);
			root = swap_node;
		}
		
		// otherwise, keep it
		else
			return;
	}
}

static int is_heap(int *v, int n)
{
	int i, end = (n - 2) / 2;
	for (i = 0; i < end; i++)
	{
		if (2*i+1 < n && v[i] > v[2*i+1])
			return 0;
		if (2*i+2 < n && v[i] > v[2*i+2])
			return 0;
	}
	return 1;
}
