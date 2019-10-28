#include "cache.h"
#include "util.h"

/* cache.c : Implement your functions declared in cache.h */

typedef struct {
	uint8_t valid;
	uint32_t tag;
	unsigned int timestamp;
} Cache_info;

Cache_info **cache_info_table;

int num_way;

/***************************************************************/
/*                                                             */
/* Procedure: setupCache                                       */
/*                                                             */
/* Purpose: Allocates memory for your cache                    */
/*                                                             */
/***************************************************************/

void setupCache(int capacity, int _num_way, int block_size)
{
/*	code for initializing and setting up your cache	*/
/*	You may add additional code if you need to	*/

	int i,j; //counter
	int nset; // number of sets
	int _wpb=0; //words per block
	num_way = _num_way;

	nset=capacity/(block_size*num_way);
	_wpb = block_size/BYTES_PER_WORD;

	Cache = (uint32_t  ***)malloc(nset*sizeof(uint32_t **));

	for (i=0;i<nset;i++) {
		Cache[i] = (uint32_t ** )malloc(num_way*sizeof(uint32_t*));
	}
	for (i=0; i<nset; i++){
		for (j=0; j<num_way; j++){
			Cache[i][j]=(uint32_t*)calloc(sizeof(uint32_t), (_wpb));
		}
	}

	cache_info_table = (Cache_info **)malloc(nset*sizeof(Cache_info *));

	for(i=0;i<nset;i++)
		cache_info_table[i] = (Cache_info *)calloc(num_way, sizeof(Cache_info));
}


/***************************************************************/
/*                                                             */
/* Procedure: setCacheMissPenalty                  	       */
/*                                                             */
/* Purpose: Sets how many cycles your pipline will stall       */
/*                                                             */
/***************************************************************/

void setCacheMissPenalty(int penalty_cycles)
{
/*	code for setting up miss penaly			*/
/*	You may add additional code if you need to	*/
	miss_penalty = penalty_cycles;

}

/* Please declare and implement additional functions for your cache */
uint32_t* Cache_Search(uint32_t addr)
{
	uint32_t set, tag;
	int i;

	set = (addr>>3) & 1;
	tag = addr>>4;

	for(i=0;i<num_way;i++){
		if(cache_info_table[set][i].valid){
			if(cache_info_table[set][i].tag == tag){
				cache_info_table[set][i].timestamp = CYCLE_COUNT;
				return Cache[set][i];
			}
		}
	}

	//miss from here
	return 0;
}

uint32_t* Cache_Evict(uint32_t addr)
{
	uint32_t set, tag, write_addr;
	int min_i=0, i;
	unsigned int min_time;

	set = (addr>>3) & 1;
	tag = addr>>4;

	//if not found, load needed
	for(i=0;i<num_way;i++){
		if(!cache_info_table[set][i].valid){
			mem_read_block(addr, Cache[set][i]);
			cache_info_table[set][i].valid = 1;
			cache_info_table[set][i].tag = tag;
			cache_info_table[set][i].timestamp = CYCLE_COUNT+30;
			return Cache[set][i];
		}
	}

	//eviction needed
	min_time = cache_info_table[set][0].timestamp;
	for(i=1;i<num_way;i++){
		if(cache_info_table[set][i].timestamp < min_time){
			min_time = cache_info_table[set][i].timestamp;
			min_i = i;
		}
	}

	write_addr = (cache_info_table[set][min_i].tag <<4) | (set << 3);
	mem_write_block(write_addr, Cache[set][min_i]);
	cache_info_table[set][min_i].tag = tag;
	cache_info_table[set][min_i].timestamp = CYCLE_COUNT+30;
	mem_read_block(addr, Cache[set][min_i]);
	return Cache[set][i];
}
