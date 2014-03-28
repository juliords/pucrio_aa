#ifndef COMMON_H
#define COMMON_H

#define TIME_LIMIT 60
#define ABORTED    -1

int randi(int min, int max);
void swap(int *a, int *b);
void tic();
float toc();
void print_array(int *v, int n);
void copy_array(int *src, int *dst, int n);
int partition(int *v, int low, int high, int pivot_position);
int log_2(int n);

#endif
