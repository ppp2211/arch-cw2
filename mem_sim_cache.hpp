#ifndef MEM_SIM_CACHE_HPP
#define MEM_SIM_CACHE_HPP

#include "mem_sim_set.hpp"
#include <cmath>
#include <vector>
#include <cstdlib>
using namespace std;

class cache{
	public:	
		
		cache(int bw, int wblk, int nblk, int nset, int clh, int clr, int clw);
		~cache();
		
		int tag_gen(uint32_t addr);
		int index_gen(uint32_t addr);
		
		bool cache_read(uint32_t addr, vector<uint8_t> &data, int &index);
		bool cache_loadin(uint32_t addr, const vector<uint8_t> &data, vector<uint8_t> &evicted, int &etag);
		
	private:
	
		vector<set> sets;		
		
		int bytes;
		int wordblk;
		int blocks;
		int nsets;
		int cl_hit;
		int cl_read;
		int cl_write;
};

int msb1(uint32_t n);

#endif
