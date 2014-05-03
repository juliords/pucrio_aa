/* -------------------------------------------------------------------------- */

#include<stdio.h>

/* -------------------------------------------------------------------------- */

typedef struct 
{
	/* state variables */
	int node_i;
	int state;
	int zero_i;
	int component;
	int neighbours_d[4], neighbours_i[4], neighbours_l;

	/* auxiliar variables */
	int visited;
	int pre, post;
	int parent_i;
} Node; 

Node nodes[362880]; 
int nodes_l;

struct
{
	int vertices_l;
	int edges_l;
} components[10];
int components_l;

Node* queue[362880];
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

/* -------------------------------------------------------------------------- */

/* total of 9! = 362880 */
void init_nodes()
{
	/* NOTE: this function should be used once only */
	static int used[9] = {0,0,0,0,0,0,0,0,0};
	static int result = 0, n = 0, zero_i;
	int i;

	if(n == 9)
	{
		nodes[nodes_l].node_i = nodes_l;
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

void init_graph_visit(int i)
{
	int dir;

	nodes[i].visited = 1;
	nodes[i].component = components_l;
	components[components_l].vertices_l++;

	for(dir = 0; dir < 4; dir++)
	{
		int new_pos = neighbour[nodes[i].zero_i][dir];
		
		if(new_pos < 9)
		{
			int new_state = swap_pos(nodes[i].state, nodes[i].zero_i, new_pos); 
			int new_node_i = search_node(new_state);

			nodes[i].neighbours_d[nodes[i].neighbours_l] = dir;
			nodes[i].neighbours_i[nodes[i].neighbours_l] = new_node_i;
			nodes[i].neighbours_l++;

			components[components_l].edges_l++;

			if(!nodes[new_node_i].visited)
				init_graph_visit(new_node_i);
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

		init_graph_visit(i);

		components_l++;
	}
}

/* -------------------------------------------------------------------------- */

void bfs(int node_i)
{
	int nb;

	if(nodes[node_i].visited) return;

	nodes[node_i].visited = 1;
	nodes[node_i].parent_i = -1;

	queue_ini = queue_fin = 0; 
	queue[queue_fin++] = &nodes[node_i];

	while(queue_ini < queue_fin)
	{
		Node* node = queue[queue_ini++];
		
		for(nb = 0; nb < node->neighbours_l; nb++)
		{
			int new_node_i = node->neighbours_i[nb];

			if(!nodes[new_node_i].visited)
			{
				nodes[new_node_i].visited = node->visited+1;
				nodes[new_node_i].parent_i = node->node_i;

				queue[queue_fin++] = &nodes[new_node_i];
			}
		}
	}
}

/* -------------------------------------------------------------------------- */

int main ()
{
	int i, nb, max_d_i;

	/* initialization */
	init_nodes();
	init_graph();

	printf("%d\n", sizeof(Node));
	/* task 1 */
	printf("\n== task1 ==\n");
	printf("components_l: %d\n", components_l);
		
	for(i = 0; i < components_l; i++)
		printf("component[%d]: vertices(%d) - edges(%d)\n", i, components[i].vertices_l, components[i].edges_l/2);

	/* task 2 */
	printf("\n== task2 ==\n");

	cleanup_visited();
	bfs(search_node(123456780));

	for(max_d_i = i = 0; i < nodes_l; i++)
		if(nodes[i].visited > nodes[max_d_i].visited) 
			max_d_i = i;
	printf("max distance: %d\n", nodes[max_d_i].visited-1);

	i = max_d_i;
	while(nodes[i].parent_i >= 0)
	{
		print_state(nodes[i].state);
		for(nb = 0; nb < nodes[i].neighbours_l; nb++)
		{
			if(nodes[i].neighbours_i[nb] == nodes[i].parent_i)
			{
				switch(nodes[i].neighbours_d[nb])
				{
					case 0: printf("direction: NORTH\n"); break;
					case 1: printf("direction: EAST \n"); break;
					case 2: printf("direction: SOUTH\n"); break;
					case 3: printf("direction: WEST \n"); break;
					default: break;
				}
			}
		}
		i = nodes[i].parent_i;
	}
	print_state(nodes[i].state);

	return 0;
}

/* -------------------------------------------------------------------------- */
