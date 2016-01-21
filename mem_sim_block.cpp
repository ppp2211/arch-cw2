#include "mem_sim_block.hpp"

block::block(int bw, int wb)
	: data (bw*wb, 0)
	, tag(0)
	, valid(0)
	, dirty(0)
	{}
	
block::~block(){}

bool block::tag_match(unsigned searchtag) const{
	if(tag == searchtag){
		return true;
	}
	else return false;
}
bool block::is_valid() const{
 	return valid;
}

bool block::is_dirty() const{
	return dirty;
}

int block::get_tag() const{
	return tag;
}

void block::read_data(vector<uint8_t> &dest) const{
	for(unsigned i = 0; i < data.size(); i++){
		dest.push_back(data[i]);
	}
}

void block::validate(){
	valid = true;
}

void block::dirt(){
	dirty = true;
}

void block::clean(){
	dirty = false;
}

void block::store(vector<uint8_t> &src, unsigned newtag){
	for(unsigned i = 0; i < src.size(); i++){
		data[i] = src[i];
	}
	tag = newtag;
	validate();
}

void block::replace_data(vector<uint8_t> &src){
	for(unsigned i = 0; i < src.size(); i++){
		data[i] = src[i];
	}
	dirt();
}

void block::flush(vector<uint8_t> &toflush, vector<unsigned> &tags){
	for(unsigned i = 0; i < data.size(); i++){
		toflush.push_back(data[i]);
	}
	tags.push_back(tag);
	clean();
}
