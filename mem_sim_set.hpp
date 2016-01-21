#ifndef MEM_SIM_SET_HPP
#define MEM_SIM_SET_HPP

#include "mem_sim_block.hpp"
#include <list>

class set{

	public:
		set(int bw, int wb, int bs);
		~set();
		
		bool getdata(unsigned tag, vector<uint8_t> &data);
		bool loadin(unsigned tag, vector<uint8_t> &data, vector<uint8_t> &evicted, int &etag);
		
	private:
		list<block> blocks;	
		int bytes;
		int words;
};

#endif
