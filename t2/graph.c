#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "common.h"
#include "list.h"
#include "graph.h"

typedef struct vertex
{
	list_t* edges;
} vertex_t;

struct graph
{
	vertex_t* vertices;
	int num_vertices;
};

graph_t* new_graph(int num_vertices)
{
	graph_t* graph = new_empty_graph(num_vertices);
	int i;
	for (i = 0; i < num_vertices; i++)
		insert_vertex(graph);
	return graph;
}

graph_t* new_empty_graph(int max_vertices)
{
	graph_t* graph = (graph_t*) malloc(sizeof(graph_t));
	assert(graph != NULL && "Could not allocate graph_t");
	graph->vertices = (vertex_t*) malloc(max_vertices * sizeof(vertex_t));
	assert(graph->vertices != NULL && "Could not allocate vertices");
	graph->num_vertices = 0;
	return graph;
}

static vertex_t* new_vertex()
{
	vertex_t* vertex = (vertex_t*) malloc(sizeof(vertex_t));
	assert(vertex != NULL && "Could not allocate vertex_t");
	vertex->edges = new_list();
	return vertex;
}

int insert_vertex(graph_t* graph)
{
	int index = graph->num_vertices;
	vertex_t* vertex = new_vertex();
	graph->vertices[index] = *vertex;
	graph->num_vertices++;
	return index;
}

int get_num_vertices(graph_t* graph)
{
	return graph->num_vertices;
}

void insert_edge(graph_t* graph, int v1, int v2)
{
	vertex_t vertex1 = graph->vertices[v1];
	vertex_t vertex2 = graph->vertices[v2];
	if (!contains(vertex1.edges, v2))
		enqueue(vertex1.edges, v2);
	if (!contains(vertex2.edges, v1))
		enqueue(vertex2.edges, v1);
}

int has_edge(graph_t* graph, int v1, int v2)
{
	vertex_t vertex1 = graph->vertices[v1];
	return contains(vertex1.edges, v2);
}

int get_degree(graph_t* graph, int v)
{
	vertex_t vertex = graph->vertices[v];
	return get_length(vertex.edges);
}

static int dfs_visit(graph_t* graph, int v, char* visited,
	int component, int (*visit)(int v, int component))
{
	vertex_t vertex = graph->vertices[v];
	visited[v] = 1;
	if (visit(v, component))
		return 1;
	
	go_to_beginning(vertex.edges);
	while (has_next(vertex.edges))
	{
		int w = get_next(vertex.edges);
		if (!visited[w])
		{
			if (dfs_visit(graph, w, visited, component, visit))
				return 1;
		}
	}
	
	return 0;
}

int dfs_do(graph_t* graph, int (*visit)(int v, int component),
	char* visited, int component)
{
	int v, n = graph->num_vertices;
	for (v = 0; v < n; v++)
	{
		if (!visited[v]) {
			if (dfs_visit(graph, v, visited, component, visit))
				return 1;
			component++;
		}
	}
	
	return 0;
}

int depth_first_search(graph_t* graph,
	int (*visit)(int v, int component))
{
	char* visited = new_char_array(graph->num_vertices);
	int ret = dfs_do(graph, visit, visited, 0);
	free(visited);
	return ret;
}

int rooted_depth_first_search(graph_t* graph,
	int (*visit)(int v, int component), int root)
{
	char* visited = new_char_array(graph->num_vertices);
	int ret;
	ret = dfs_visit(graph, root, visited, 0, visit);
	if (!ret)
		ret = dfs_do(graph, visit, visited, 0);
	free(visited);
	return ret;
}
