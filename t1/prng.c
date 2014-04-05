/* Source: http://zuttobenkyou.wordpress.com/2012/05/01/kiss-2011-version-in-c-and-haskell/ */

/* AUTHOR: Shinobu (zuttobenkyou.wordpress.com) */
/* LICENSE: PUBLIC DOMAIN */
#include"prng.h"
 
#define QSIZE 0x200000
#define CNG (cng = 6906969069ULL * cng + 13579)
#define XS (xs ^= (xs << 13), xs ^= (xs >> 17), xs ^= (xs << 43))
#define KISS (B64MWC() + CNG + XS)
 
static uint64_t QARY[QSIZE];
static int j;
static uint64_t carry;
static uint64_t xs;
static uint64_t cng;
 
void randk_reset(void)
{
    j = QSIZE - 1;
    carry = 0;
    xs = 362436069362436069ULL;
    cng = 123456789987654321ULL; /* use this as the seed */
}
 
static uint64_t B64MWC(void)
{
    uint64_t t, x;
    j = (j + 1) & (QSIZE - 1);
    x = QARY[j];
    t = (x << 28) + carry;
    carry = (x >> 36) - (t < x);
    return (QARY[j] = t - x);
}
 
/* Initialize PRNG with default seed */
void randk_seed(void)
{
    uint64_t i;
    /* Seed QARY[] with CNG+XS: */
    for (i = 0; i < QSIZE; i++)
        QARY[i] = CNG + XS;
}
 
void randk_seed_manual(uint64_t seed)
{
    cng ^= seed;
    xs ^= cng;
    randk_seed();
}
 
void randk_warmup(int rounds)
{
    int i;
    /* Run through several rounds to warm up the state */
    for (i = 0; i < rounds; i++)
        randk();
}
 
/* Generate a pseudorandom 64-bit unsigned integer. */
uint64_t randk(void)
{
    return KISS;
}
