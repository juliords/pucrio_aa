#ifndef COMMON_H
#define COMMON_H

#define INPUT_MAX (1 << 25)

int randi(int min, int max);
void swap(int *a, int *b);

void tic();
float toc();

void print_array(int *v, int n);
void copy_array(int *src, int *dst, int n);

int partition(int *v, int low, int high, int pivot_position);

#endif
