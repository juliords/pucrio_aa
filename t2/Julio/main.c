/* -------------------------------------------------------------------------- */

#include<stdio.h>
#include<assert.h>

/* -------------------------------------------------------------------------- */

typedef struct {
	int state;
	int zero_i;
	int visited;
	int component;
	int pre, post;
} Node; 

Node nodes[400000]; 
int nodes_l;

int components[100];
int components_l;

Node* queue[400000];
int queue_ini, queue_fin;

/* -------------------------------------------------------------------------- */

#define NORTH 	0
#define EAST	1 
#define SOUTH	2
#define WEST	3
/* Positions:
 * -------------
 * | 0 | 1 | 2 |
 * -------------
 * | 3 | 4 | 5 |
 * -------------
 * | 6 | 7 | 8 |
 * -------------
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

const int pot10[9] = {
	100000000, 10000000, 1000000, 
	100000, 10000, 1000, 100, 10, 1
};

int read_state(int state, int pos)
{

	return (state/pot10[pos])%10;
}

int write_state(int state, int pos, int value)
{
	state -= pot10[pos]*read_state(state,pos);
	state += pot10[pos]*(value%10);
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

/* total of 9! = 362880 */
void init_nodes()
{
	static int used[9], result = 0, n = 0, zero_i;
	int i;

	if(n == 0) 
		for(i = 0; i < 9; i++) 
			used[i] = 0;

	if(n == 9)
	{
		nodes[nodes_l].zero_i = zero_i;
		nodes[nodes_l].state = result;
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

void bfs()
{
	int i, j;

	for(i = 0; i < nodes_l; i++)
		nodes[i].visited = 0;
	
	queue_ini = queue_fin = 0; 

	for(i = 0; i < nodes_l; i++)
	{
		if(nodes[i].visited) continue;

		nodes[i].visited = 1;
		queue[queue_fin++] = &nodes[i];

		while(queue_ini < queue_fin)
		{
			Node* node = queue[queue_ini++];
			
			for(j = 0; j < 4; j++)
			{
				int new_pos = neighbour[node->zero_i][j];
				
				if(new_pos < 9)
				{
					int new_state = swap_pos(node->state, node->zero_i, new_pos); 
					int node_i = search_node(new_state);

					if(nodes[node_i].visited == 0)
					{
						nodes[node_i].visited = 1;
						queue[queue_fin++] = &nodes[node_i];
					}
				}
			}
		}
	}
}

/* -------------------------------------------------------------------------- */

void init_components_visit(int i)
{
	int dir;

	nodes[i].visited = 1;
	nodes[i].component = components_l;
	components[components_l]++;

	for(dir = 0; dir < 4; dir++)
	{
		int new_pos = neighbour[nodes[i].zero_i][dir];
		
		if(new_pos < 9)
		{
			int new_state = swap_pos(nodes[i].state, nodes[i].zero_i, new_pos); 
			int new_node_i = search_node(new_state);

			if(nodes[new_node_i].visited == 0)
				init_components_visit(new_node_i);
		}
	}
}

void init_components()
{
	int i;

	for(i = 0; i < nodes_l; i++)
		nodes[i].visited = 0;
	
	for(i = 0; i < nodes_l; i++)
	{
		if(nodes[i].visited) continue;

		init_components_visit(i);

		components_l++;
	}
}

/* -------------------------------------------------------------------------- */

int main ()
{
	int i;

	/* initialization */
	init_nodes();
	init_components();

	/* bin search test */
	assert(search_node(12345678) == 0);

	/* zero_i test */
	for(i = 0; i < nodes_l; i++)
		assert(read_state(nodes[i].state, nodes[i].zero_i) == 0);

	/* task 1 */
	printf("components_l: %d\n", components_l);
	for(i = 0; i < components_l; i++)
		printf("component[%d]: %d\n", i, components[i]);

	return 0;
}

/* -------------------------------------------------------------------------- */
