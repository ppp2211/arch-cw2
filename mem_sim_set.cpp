#include "mem_sim_set.hpp"

set::set(int bw, int wb, int bs)
	: blocks(bs, block(bw,wb))
	{}

set::~set(){}
