#include<stdlib.h>
#include"common.h"

int randi(int min, int max)
{
	return ( rand() % (max - min + 1) ) + min;
}

void swap(int *a, int *b)
{
	int swp = *a;
	*a = *b;
	*b = swp;
}
