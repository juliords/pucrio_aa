#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct node {
	int value;
	struct node* next;
} node_t;

struct list {
	node_t* first;
	node_t* last;
	node_t* current;
	int length;
};

list_t* new_list()
{
	list_t* list = (list_t*) malloc(sizeof(list_t));
	assert(list != NULL && "Could not allocate new list_t");
	list->first = NULL;
	list->last = NULL;
	list->current = NULL;
	list->length = 0;
	return list;
}

static node_t* new_node(int value)
{
	node_t* node = (node_t*) malloc(sizeof(node_t));
	assert(node != NULL && "Could not allocate new node_t");
	node->value = value;
	node->next = NULL;
	return node;
}

int is_empty(list_t* list)
{
	return list->length == 0;
}

int get_length(list_t* list)
{
	return list->length;
}

void enqueue(list_t* list, int value)
{
	node_t* node = new_node(value);
	if (is_empty(list))
		list->first = node;
	else
		list->last->next = node;
	list->last = node;
	list->length++;
}

int dequeue(list_t* list)
{
	int value;
	node_t* node = list->first;
	list->first = node->next;
	if (is_empty(list))
		list->last = NULL;
	list->length--;
	value = node->value;
	free(node);
	return value;
}

void go_to_beginning(list_t* list)
{
	list->current = list->first;
}

int has_next(list_t* list)
{
	return list->current != NULL;
}

int get_next(list_t* list)
{
	node_t* current = list->current;
	int value = current->value;
	list->current = current->next;
	return value;
}

int contains(list_t* list, int value)
{
	node_t* node;
	for (node = list->first; node != NULL; node = node->next)
		if (node->value == value)
			return 1;
	return 0;
}
