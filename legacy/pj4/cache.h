#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* cache.h : Declare functions and data necessary for your project*/

int miss_penalty; // number of cycles to stall when a cache miss occurs
uint32_t ***Cache; // data cache storing data [set][way][byte]

void setupCache(int, int, int);
void setCacheMissPenalty(int);
uint32_t* Cache_Search(uint32_t);
uint32_t* Cache_Evict(uint32_t);