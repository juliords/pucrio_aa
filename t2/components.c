#include <stdio.h>
#include "graph.h"
#include "common.h"

static graph_t* graph;
static int* components;
static int total_vertices;
static int num_components;

static int print(int v, int component)
{
	printf("Visiting vertex %d in component %d\n", v, component);
	return 0;
}

static int get_components(int v, int component)
{
	print(v, component);
	components[v] = component;
	num_components = component + 1;
	return 0;
}

int find_components(graph_t* g)
{
	graph = g;
	total_vertices = get_num_vertices(graph);
	components = new_int_array(total_vertices);
	depth_first_search(graph, get_components);
	return num_components;
}

void count_vertices_and_edges(int** num_vertices, int** num_edges)
{
	int v, c;
	int* nv = new_int_array(num_components);
	int* ne = new_int_array(num_components);
	
	for (v = 0; v < total_vertices; v++)
	{
		nv[components[v]] += 1;
		ne[components[v]] += get_degree(graph, v);
	}
	
	for (c = 0; c < num_components; c++)
		ne[c] /= 2;
	
	*num_vertices = nv;
	*num_edges = ne;
}
