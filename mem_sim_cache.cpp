#include "mem_sim_cache.hpp"

cache::cache(int bw, int wblk, int nblk, int nset, int clh, int clr, int clw)
	: sets (nset, set(bw, wblk, nblk))
	, bytes(bw)
	, blocks(nblk)
	, wordblk(wblk)
	, nsets(nset)
	, cl_hit(clh)
	, cl_read(clr)
	, cl_write(clw)
	{}
	
cache::~cache(){}

bool cache::cache_read(uint32_t addr,vector<uint8_t> &data, int &index) {
		
	return sets[index_gen(addr)].getdata(addr, data);
	
}

bool cache::cache_loadin(uint32_t addr,vector<uint8_t> &data, vector<uint8_t> &evicted, int &etag){
	
	bool was_dirty = sets[index_gen(addr)].loadin(addr, data, evicted, etag);	
		
	return was_dirty;
}

int cache::index_gen(uint32_t addr){
	div_t wordaddr = div(addr,bytes);
	div_t blockaddr = div(wordaddr.quot,wordblk);
	return blockaddr.quot % nsets;
}


/*int msb1(uint32_t n){
	
	for(unsigned i = 0; i < 32; i++){
		if(n & 0x80000000 != 0){
			return 31 - i;
		}
		n << 1;
	}	
	
	return 33;
}
*/
