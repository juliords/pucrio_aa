#ifndef LIST_H
#define LIST_H

typedef struct list list_t;

list_t* new_list();

int is_empty(list_t* list);

int get_length(list_t* list);

void enqueue(list_t* list, int value);

int dequeue(list_t* list);

void go_to_beginning(list_t* list);

int has_next(list_t* list);

int get_next(list_t* list);

int contains(list_t* list, int value);

#endif
