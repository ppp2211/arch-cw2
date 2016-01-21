#include "mem_sim_set.hpp"
#include <iostream>

set::set(int bw, int wb, int bs)
	: blocks(bs, block(bw,wb))
	, bytes(bw)
	, words(wb)
	{}

set::~set(){}

bool set::getdata(unsigned tag, vector<uint8_t> &data){

		for(list<block>::iterator i = blocks.begin(); i != blocks.end(); ++i){
			
			if((i->tag_match(tag)) && (i->is_valid())){
				//cout << "set: cond start" << endl;
				i->read_data(data);
				//cout << "set: read_data" << endl;
				blocks.push_front(*i);
				//cout << "set: block i moved to front" << endl;
				blocks.erase(i);
				//cout << "set: block i erased" << endl;
				return true;
			}
		}
		return false;
}
		
bool set::storedata(unsigned tag, vector<uint8_t> &data){

		for(list<block>::iterator i = blocks.begin(); i != blocks.end(); ++i){
			
			if((i->tag_match(tag)) && (i->is_valid())){
				i->replace_data(data);
				blocks.push_front(*i);
				blocks.erase(i);
				return true;
			}
		}
		return false;
			
}

bool set::loadin(unsigned tag, vector<uint8_t> &data, vector<uint8_t> &evicted, int &etag){
	bool was_dirty = false;
	
	if(blocks.back().is_dirty()){
		blocks.back().read_data(evicted);
		etag = blocks.back().get_tag();
		was_dirty = true;
	}
	blocks.pop_back();
	
	block newblk(bytes,words);
	newblk.store(data,tag);
	blocks.push_front(newblk);
	
	return was_dirty;	
}

bool set::loadin_dirty(unsigned tag, vector<uint8_t> &data, vector<uint8_t> &evicted, int &etag){
	bool was_dirty = false;
	
	if(blocks.back().is_dirty()){
		blocks.back().read_data(evicted);
		etag = blocks.back().get_tag();
		was_dirty = true;
	}
	blocks.pop_back();
	
	block newblk(bytes,words);
	newblk.store(data,tag);
	newblk.dirt();
	blocks.push_front(newblk);
	
	return was_dirty;	
}

void set::flush(vector<uint8_t> &toflush, vector<unsigned> &tags){
	for(list<block>::iterator i = blocks.begin(); i != blocks.end(); ++i){
		if((i->is_dirty()) && (i->is_valid())){
			i->flush(toflush, tags);
		}
	}
}











