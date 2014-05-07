#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "common.h"

char* new_char_array(int size)
{
	char* array = (char*) calloc(size, sizeof(char));
	assert(array != NULL && "Could not allocate array");
	return array;
}

int* new_int_array(int size)
{
	int* array = (int*) calloc(size, sizeof(int));
	assert(array != NULL && "Could not allocate array");
	return array;
}

void print_array(int *v, int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("[%d] = %d\n", i, v[i]);
}
