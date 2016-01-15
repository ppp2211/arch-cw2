#ifndef MEM_SIM_CACHE_HPP
#define MEM_SIM_CACHE_HPP

#include "mem_sim_set.hpp"
#include <vector>
using namespace std;

class cache{
	public:	
		
		cache(int bw, int wblk, int nblk, int nset, int clh, int clr, int clw);
		~cache();				
		
	private:
	
		vector<set> sets;
		
		int cl_hit;
		int cl_read;
		int cl_write;
};

#endif
