#ifndef MEM_SIM_SET_HPP
#define MEM_SIM_SET_HPP

#include "mem_sim_block.hpp"
#include <list>

class set{

	public:
		set(int bw, int wb, int bs);
		~set();
		
	private:
		list<block> blocks;	
};

#endif
