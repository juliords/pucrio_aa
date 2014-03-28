#include<stdlib.h>
#include<assert.h>
#include"common.h"
#include"stupid.h"

/* returns index of k-th element */
static int do_median_select(int *v, int n, int k)
{
	int i;
	assert(v && n);
	assert(k >= 1 && k <= n);

	/* base case */
	if(n == 1) return 0;

#if 1 // switch between median select and quick select, for test purposes only
	for(i = 0; i < n/5; i++)
	{
		int *pv = v+(5*i);

		/* assuming that stupid select shifts k-th element to its position */
		stupid_select(pv, 5, 3);
		swap(&v[i], &pv[3]);
	}

	if(n%5) 
	{
		int *pv = v+(5*i);
		int mid = ((n%5)+1)/2; // ceil( ( n % 5 ) / 2 )

		stupid_select(pv, n%5, mid);
		swap(&v[i], &v[mid]);

		i++;
	}

	/* "i" is now the index of median */
	i = do_median_select(v, i, (i/2)+1);
#else
	i = randi(0, n-1);
#endif
	i = partition(v, 0, n-1, i);

	if(k < (i+1)) 
		return do_median_select(v, i, k);
	
	else if(k > (i+1))
		return do_median_select(&v[i+1], n-i-1, k-i-1);
	
	else
		return i;
}

int median_select(int *v, int n, int k)
{
	return v[do_median_select(v,n,k)];
}
