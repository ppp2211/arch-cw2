#include "mem_sim_cache.hpp"

cache::cache(int bw, int wblk, int nblk, int nset, int clh, int clr, int clw)
	: sets (nset, set(bw, wblk, nblk))
	, cl_hit(clh)
	, cl_read(clr)
	, cl_write(clw)
	{}
	
cache::~cache(){}


