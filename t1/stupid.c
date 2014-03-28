#include"stupid.h"
#include"common.h"

/* stupid select - O(n^2) */
int stupid_select(int *v, int n, int k)
{
	int i, j;

	for(i = 0; i < k; i++)
	{
		int min = v[i], imin = i;

		for(j = i+1; j < n; j++)
		{
			if(v[j] < min)
			{
				min = v[j];
				imin = j;
			}
		}

		swap(&v[i], &v[imin]);
		
		if (toc() > TIME_LIMIT)
			return ABORTED;
	}

	return v[k-1];
}
