/* Source: http://en.wikipedia.org/wiki/Linear_congruential_generator */
/* Parameters: glibc */
static const unsigned int a = 1103515245;
static const unsigned int c = 12345;
static const unsigned int m = 1 << 31;
static const unsigned int mask = 0x7fffffff; // bits 30..0

static unsigned int state;

void lcg_seed(unsigned int seed)
{
	state = seed;
}

unsigned int lcg_rand()
{
	state = (a * state + c) % m;
	return state & mask;
}
