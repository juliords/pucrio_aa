/* -------------------------------------------------------------------------- */

#include<stdio.h>
#include<stdlib.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define MAX_NODES 362880

/* -------------------------------------------------------------------------- */

/*
# variable name suffix dictionary:
_t -> type
_i -> index
_l -> length
_p -> pointer
_f -> flag
_d -> direction
*/

typedef struct _node node_t;
struct _node 
{
	/* node variables */
	int state;
	int zero_i;

	/* graph variables */
	int component;
	int neighbours_l;
	int neighbours_d[4];
	node_t* neighbours_p[4];

	/* auxiliar variables */
	int visited;
	int pre, post;
	int parent_d;
	node_t* parent_p;
}; 

node_t nodes[MAX_NODES]; 
int nodes_l;

struct
{
	node_t *node_p;
	int vertices_l;
	int edges_l;
	int bridges_l;
} components[MAX_NODES];
int components_l;

node_t* queue[MAX_NODES];
int queue_ini, queue_fin;

/* -------------------------------------------------------------------------- */

/* Positions:
 * -------------
 * | 0 | 1 | 2 |
 * -------------
 * | 3 | 4 | 5 |
 * -------------
 * | 6 | 7 | 8 |
 * -------------
 *
 * v[0] == NORTH
 * v[1] == EAST
 * v[2] == SOUTH
 * v[3] == WEST
 * 
 * OBS: 9 means out of border
 */ 
int neighbour[9][4] = { 
	{9, 1, 3, 9}, /* 0 */
	{9, 2, 4, 0}, /* 1 */
	{9, 9, 5, 1}, /* 2 */
	{0, 4, 6, 9}, /* 3 */
	{1, 5, 7, 3}, /* 4 */
	{2, 9, 8, 4}, /* 5 */
	{3, 7, 9, 9}, /* 6 */
	{4, 8, 9, 6}, /* 7 */
	{5, 9, 9, 7}  /* 8 */
};

/* -------------------------------------------------------------------------- */

const int pow10inv[9] = {
	100000000, 10000000, 1000000, 
	100000, 10000, 1000, 100, 10, 1
};

int read_state(int state, int pos)
{
	return (state/pow10inv[pos])%10;
}

int write_state(int state, int pos, int value)
{
	state -= pow10inv[pos]*read_state(state,pos);
	state += pow10inv[pos]*(value%10);
	return state;
}

int swap_pos(int state, int pos1, int pos2)
{
	int val1 = read_state(state, pos1);
	int val2 = read_state(state, pos2);

	state = write_state(state,pos1,val2);
	state = write_state(state,pos2,val1);

	return state;
}

/* -------------------------------------------------------------------------- */

void print_state(int state)
{
	printf("-------------\n");
	printf("| %d | %d | %d |\n", read_state(state, 0),read_state(state, 1),read_state(state, 2));
	printf("-------------\n");
	printf("| %d | %d | %d |\n", read_state(state, 3),read_state(state, 4),read_state(state, 5));
	printf("-------------\n");
	printf("| %d | %d | %d |\n", read_state(state, 6),read_state(state, 7),read_state(state, 8));
	printf("-------------\n");
}

void print_direction(int direction_i)
{
	char direction_string[4][6] = {"NORTH", "EAST", "SOUTH", "WEST"};
	printf("direction: %s\n", direction_string[direction_i]);
}

/* -------------------------------------------------------------------------- */

/* total of 9! = MAX_NODES */
void init_nodes()
{
	/* NOTE: this function should be used once only */
	static int used[9] = {0,0,0,0,0,0,0,0,0};
	static int result = 0, n = 0, zero_i;
	int i;

	if(n == 9)
	{
		nodes[nodes_l].state = result;
		nodes[nodes_l].zero_i = zero_i;
		nodes_l++;

		return;
	}

	for(i = 0; i < 9; i++)
	{
		if(used[i]) continue;
		result *= 10;
		result += i;

		if(i == 0) zero_i = n;

		n++;
		used[i] = 1;
		init_nodes();
		used[i] = 0;
		n--;

		result /= 10;
	}
}

/* -------------------------------------------------------------------------- */

/* returns its index */
int search_node(int state)
{
	int ini = 0, fin = nodes_l;

	while(ini <= fin)
	{
		int mid = (ini+fin)/2;

		if(state < nodes[mid].state)
			fin = mid-1;
		else if(state > nodes[mid].state)
			ini = mid+1;
		else
			return mid;
	}

	return -1;
}

/* -------------------------------------------------------------------------- */

void cleanup_visited()
{
	int i;
	for(i = 0; i < nodes_l; i++)
		nodes[i].visited = 0;
}

/* -------------------------------------------------------------------------- */

/* DFS */

void init_graph_visit(node_t *node_p)
{
	int dir;

	node_p->visited = 1;
	node_p->component = components_l;
	components[components_l].vertices_l++;

	for(dir = 0; dir < 4; dir++)
	{
		int new_pos = neighbour[node_p->zero_i][dir];
		
		if(new_pos < 9)
		{
			int new_state = swap_pos(node_p->state, node_p->zero_i, new_pos); 
			node_t *neighbour_p = &nodes[search_node(new_state)];

			node_p->neighbours_d[node_p->neighbours_l] = dir;
			node_p->neighbours_p[node_p->neighbours_l] = neighbour_p;
			node_p->neighbours_l++;

			components[components_l].edges_l++;

			if(!neighbour_p->visited)
				init_graph_visit(neighbour_p);
		}
	}
}

void init_graph()
{
	int i;

	cleanup_visited();
	components_l = 0;
	
	for(i = 0; i < nodes_l; i++)
	{
		if(nodes[i].visited) continue;

		init_graph_visit(&nodes[i]);

		components[components_l].node_p = &nodes[i];
		components_l++;
	}
}

/* -------------------------------------------------------------------------- */

/* BFS */

void find_shortest_path(node_t *init_node_p)
{
	int nb;

	if(!init_node_p || init_node_p->visited) return;

	init_node_p->visited = 1;
	init_node_p->parent_p = NULL;

	queue_ini = queue_fin = 0; 
	queue[queue_fin++] = init_node_p;

	while(queue_ini < queue_fin)
	{
		node_t* node_p = queue[queue_ini++];
		
		for(nb = 0; nb < node_p->neighbours_l; nb++)
		{
			node_t *neighbour_p = node_p->neighbours_p[nb];

			if(!neighbour_p->visited)
			{
				neighbour_p->visited = node_p->visited+1;

				neighbour_p->parent_d = node_p->neighbours_d[nb];
				neighbour_p->parent_p = node_p;

				queue[queue_fin++] = neighbour_p;
			}
		}
	}
}

/* -------------------------------------------------------------------------- */

/* http://www.geeksforgeeks.org/bridge-in-a-graph/ */
int find_bridges(node_t *node_p)
{
	static int time = 0;
	int min_time;
	int i;

	node_p->visited = 1;
	node_p->parent_p = NULL;
	node_p->pre = min_time = time++;

	for(i = 0; i < node_p->neighbours_l; i++)
	{
		node_t *neighbour_p = node_p->neighbours_p[i];

		if(!neighbour_p->visited)
		{
			int ret_time;
			neighbour_p->parent_p = node_p;
			ret_time = find_bridges(neighbour_p);

			min_time = MIN(min_time, ret_time);

			if(ret_time > node_p->pre)
				components[node_p->component].bridges_l++;
		}
		else if(node_p->parent_p != neighbour_p)
			min_time = MIN(min_time, neighbour_p->pre);
	}

	return min_time;
}

/* -------------------------------------------------------------------------- */

int main ()
{
	int i;
	node_t *p;

	/* initialization */
	init_nodes();
	init_graph();

	/* task 1 */
	printf("\n== task1 ==\n");
	printf("components_l: %d\n", components_l);
		
	for(i = 0; i < components_l; i++)
		printf("component[%d]: vertices(%d) - edges(%d)\n", i, components[i].vertices_l, components[i].edges_l/2);

	/* task 2 */
	printf("\n== task2 ==\n");

	cleanup_visited();
	find_shortest_path(&nodes[search_node(123456780)]);

	p = queue[queue_fin-1];
	printf("max distance: %d\n", p->visited-1);

	for(; p->parent_p; p = p->parent_p)
	{
		print_state(p->state);
		print_direction(p->parent_d);
	}
	print_state(p->state);

	/* task 3 */
	printf("\n== task3 ==\n");

	printf("# of bridges\n");
	cleanup_visited();
	for(i = 0; i < components_l; i++)
	{
		find_bridges(components[i].node_p);
		printf("component %d: %d\n", i, components[i].bridges_l);
	}

	return 0;
}

/* -------------------------------------------------------------------------- */
