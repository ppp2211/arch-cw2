#include "mem_sim_block.hpp"

block::block(int bw, int wb)
	: data (bw*wb, 0)
	, tag(0)
	, valid(0)
	, dirty(0)
	{}
	
block::~block(){}
