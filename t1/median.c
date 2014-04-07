#include<assert.h>
#include"common.h"
#include"stupid.h"

#define PSIZE 5

/* returns index of k-th element */
static int do_median_select(int *v, int n, int k)
{
	int i;
	assert(v && n);
	assert(k >= 1 && k <= n);

	/* base case */
	if(n == 1) return 0;

	for(i = 0; i < n/PSIZE; i++)
	{
		int *pv = v+(PSIZE*i);
		int mid = (PSIZE+1)/2;

		/* assuming that stupid select shifts k-th element to its position */
		stupid_select(pv, PSIZE, mid);
		swap(&v[i], &pv[mid-1]);
	}

	if(n%PSIZE) 
	{
		int *pv = v+(PSIZE*i);
		int mid = ((n%PSIZE)+1)/2; // ceil( ( n % PSIZE ) / 2 )

		stupid_select(pv, n%PSIZE, mid);
		swap(&v[i], &pv[mid-1]);

		i++;
	}

	/* "i" is now the index of median */
	i = do_median_select(v, i, (i/2)+1);
	i = partition(v, 0, n-1, i);

	if(k < (i+1)) 
		return do_median_select(v, i, k);

	else if(k > (i+1))
		return (i+1) + do_median_select(&v[i+1], n-(i+1), k-(i+1));

	else
		return i;
}

int median_select(int *v, int n, int k)
{
	return v[do_median_select(v,n,k)];
}
