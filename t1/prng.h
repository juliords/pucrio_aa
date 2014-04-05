#ifndef PRNG_H
#define PRNG_H

#include <stdint.h>

void randk_reset(void);
void randk_seed(void);
void randk_seed_manual(uint64_t seed);
void randk_warmup(int rounds);
uint64_t randk(void);

#endif
