#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "common.h"

char* new_char_array(int size)
{
	char* array = (char*) malloc(size * sizeof(char));
	int i;
	assert(array != NULL && "Could not allocate array");
	for (i = 0; i < size; i++)
		array[i] = 0;
	return array;
}

int* new_int_array(int size)
{
	int* array = (int*) malloc(size * sizeof(int));
	int i;
	assert(array != NULL && "Could not allocate array");
	for (i = 0; i < size; i++)
		array[i] = 0;
	return array;
}

void print_array(int *v, int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("[%d] = %d\n", i, v[i]);
}
