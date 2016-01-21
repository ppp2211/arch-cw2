#include "mem_sim_cache.hpp"
#include <iostream> // delete this plz

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

bool cache::cache_read(unsigned addr,vector<uint8_t> &data, int &index) {
		
	index = index_gen(addr);
	//cout << "index generated " << endl;
	return sets[index].getdata(addr, data);
	//cout << "sets returned" << endl;
	
}

bool cache::cache_loadin(unsigned addr,vector<uint8_t> &data, vector<uint8_t> &evicted, int &etag){
	int index = index_gen(addr);
	//cout << "index generated " << endl;
	bool was_dirty = sets[index].loadin(addr, data, evicted, etag);	
		
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
