#include "mem_sim_cache.hpp"

cache::cache(int addrb, int bw, int wblk, int nblk, int nset, int clh, int clr, int clw)
	: addr_bit(addrb)
	, b_in_w(bw)
	, w_in_blk(wblk)
	, blks(nblk)
	, sets(nset)
	, cl_hit(clh)
	, cl_read(clr)
	, cl_write(clw)
	{}
	
cache::~cache(){};


