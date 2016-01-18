#include "mem_sim_set.hpp"

set::set(int bw, int wb, int bs)
	: blocks(bs, block(bw,wb))
	, bytes(bw)
	, words(wb)
	{}

set::~set(){}

bool set::getdata(int tag, vector<uint8_t> &data){

		for(list<block>::iterator i = blocks.begin(); i != blocks.end(); ++i){
			
			if((i->tag_match(tag)) && (i->is_valid())){
				i->read_data(data);
				blocks.push_front(*i);
				blocks.erase(i);
				return true;
			}
		}
		return false;
			
}

bool loadin(int tag, const vector<uint8_t> &data, vector<uint8_t> &evicted, int &etag){
	bool was_dirty = false;
	
	if(blocks.back().is_dirty()){
		blocks.back().read_data(evicted);
		etag = blocks.back().get_tag();
		was_dirty = true;
	}
	blocks.pop_back();
	
	block newblk(bw,wb);
	newblk.store(data,tag);
	blocks.push_front(newblk);
	
	return was_dirty;	
}
