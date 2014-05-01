#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "graph.h"
#include "components.h"

int main() {
	int i, num_components;
	graph_t* graph = new_graph(13);
	int* num_vertices, *num_edges;
	
	insert_edge(graph, 0, 1);
	insert_edge(graph, 0, 2);
	insert_edge(graph, 1, 2);
	insert_edge(graph, 1, 3);
	insert_edge(graph, 1, 4);
	insert_edge(graph, 2, 4);
	insert_edge(graph, 2, 6);
	insert_edge(graph, 2, 7);
	insert_edge(graph, 3, 4);
	insert_edge(graph, 4, 5);
	insert_edge(graph, 6, 7);
	insert_edge(graph, 8, 9);
	insert_edge(graph, 10, 11);
	insert_edge(graph, 11, 12);
	
	num_components = find_components(graph);
	count_vertices_and_edges(&num_vertices, &num_edges);
	
	printf("Vertices\n");
	print_array(num_vertices, num_components);
	printf("Edges\n");
	print_array(num_edges, num_components);
	
	return 0;
}
