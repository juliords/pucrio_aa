#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph graph_t;

graph_t* new_graph(int num_vertices);

graph_t* new_empty_graph(int max_vertices);

int insert_vertex(graph_t* graph);

int get_num_vertices(graph_t* graph);

void insert_edge(graph_t* graph, int v1, int v2);

int has_edge(graph_t* graph, int v1, int v2);

int get_degree(graph_t* graph, int v);

int depth_first_search(graph_t* graph,
	int (*visit)(int v, int component));

int rooted_depth_first_search(graph_t* graph,
	int (*visit)(int v, int component), int root);

#endif
