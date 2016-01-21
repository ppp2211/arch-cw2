#include <iostream>
#include <iomanip> 
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
#include <cstdlib>
#include "mem_sim_cache.hpp"

using namespace std;

int main(int argc, char *argv[]){	
	
	unsigned addr_bits = atoi(argv[1]);
	unsigned bperword = atoi(argv[2]);
	unsigned wperblock = atoi(argv[3]);
	unsigned blockperset = atoi(argv[4]);
	unsigned nsets = atoi(argv[5]);
	unsigned clhit = atoi(argv[6]);
	unsigned clread = atoi(argv[7]);
	unsigned clwrite = atoi(argv[7]);
	
	cache mycache(bperword,wperblock,blockperset,nsets,clhit,clread,clwrite);
	
	unsigned mem_size = (1 << addr_bits);
	vector<uint8_t> mem (mem_size, 0);
		
	string line;
	
	while(getline(cin,line)){
			
		if(line.at(0) != '#'){
			
			istringstream row(line);
			string cmd;
			
			row >> cmd;
			
				if(cmd == "read-req"){
					cout << "read-ack ";
					
					unsigned addr;
					row >> addr;
					
					vector<uint8_t> data;
					int index;
					
					bool hit = mycache.cache_read(addr, data, index);
										
					cout << index << " ";
					
					unsigned woffset = (addr/bperword) % wperblock;
					unsigned offset = woffset*bperword;
					
					//cout << dec << "addr " << addr;
					
					if(hit){
						cout << "hit " << clhit << " ";
						
						/*cout << " DATA LOADED " << endl;
						for(unsigned i = 0; i < data.size(); i++){
							cout << hex << setfill('0') << setw(2) << unsigned(data[i]);
						}
							cout << endl;*/					
											
						for (unsigned i = offset; i < offset+bperword ; i++){
							cout << hex << setfill('0') << setw(2) << unsigned(data[i]);
						}
						
						cout << endl;
					}
					
					else{
						
						int time = clhit + clread;
						
						unsigned blockaddr = ((addr/wperblock)/bperword) * wperblock * bperword;
														
						for (unsigned i = 0; i < wperblock * bperword ; i++){
							data.push_back(mem[blockaddr+i]);
						}
									
						vector<uint8_t> evicted;
						int etag;
						
						if(mycache.cache_loadin(addr, data, evicted, etag)){
							for (unsigned i = 0 ; i < wperblock * bperword ; i++) {
 								 mem[(etag*wperblock*bperword) + i] = evicted[i]; 
							}
							time += clwrite;
						}
						
						cout << "miss " << time << " ";						
						
						unsigned offset = woffset*bperword;
											
						for (unsigned i = offset; i < offset+bperword ; i++){
							cout << hex << setfill('0') << setw(2) << unsigned(data[i]);
						}							
						
						data.clear();
						cout << endl;
					}
											
					
				
				}
			
				else if(cmd == "write-req"){
				
					cout << "write-ack ";
					
					unsigned addr;
					unsigned long long tostore;
					row >> addr >> hex >> tostore; 
					
					vector<uint8_t> store;
					
					for (unsigned i = 0; i < bperword ; i++){	
						uint8_t byte = (tostore >> ((bperword - (i+1)) * 8));
						store.push_back(byte);				
					}
					
					vector<uint8_t> data;
					int index;
												
					bool hit = mycache.cache_read(addr, data, index);
										
					cout << index << " ";
					
					unsigned woffset = (addr/bperword) % wperblock;
					unsigned offset = woffset*bperword;
					
					if(hit){
						for(unsigned i = offset; i < offset+bperword; i++){
							data[i] = store[i-offset];
						}
						
						/*cout << " DATA SAVED " << endl;
						for(unsigned i = 0; i < data.size(); i++){
							cout << hex << setfill('0') << setw(2) << unsigned(data[i]);
						}
							cout << endl;
						*/
							
						mycache.cache_store(addr,data);
						
						cout << "hit " << clhit << " ";					
											
						/*for (unsigned i = offset; i < offset+bperword ; i++){
							cout << hex << setfill('0') << setw(2) << unsigned(data[i]);
						}*/
						
						cout << endl;
						
					}
					else{
						
						int time = clhit + clread;
						
						unsigned blockaddr = ((addr/wperblock)/bperword) * wperblock * bperword;
											
						for (unsigned i = 0; i < wperblock * bperword ; i++){
							data.push_back(mem[blockaddr+i]);
						}
						
						for(unsigned i = offset; i < offset+bperword; i++){
							data[i] = store[i-offset];
						}
						
						/*	cout << " DATA SAVED " << endl;
						for(unsigned i = 0; i < data.size(); i++){
							cout << hex << setfill('0') << setw(2) << unsigned(data[i]);
						}
							cout << endl;*/
									
						vector<uint8_t> evicted;
						int etag;
						
						if(mycache.cache_loadin_dirty(addr, data, evicted, etag)){
							for (unsigned i = 0 ; i < wperblock * bperword ; i++) {
 								 mem[(etag*wperblock*bperword) + i] = evicted[i]; 
							}
							time += clwrite;
						}
						
						cout << "miss " << time << " ";						
						
						unsigned offset = woffset*bperword;
											
						/*for (unsigned i = offset; i < offset+bperword ; i++){
							cout << hex << setfill('0') << setw(2) << unsigned(data[i]);
						}*/							
						
						data.clear();
						cout << endl;
					}
					
					
					
				}
				
				else if(cmd == "flush-req"){
					cout << "flush-ack " << endl;
					vector<uint8_t> toflush;
					vector<unsigned> tags;
					
					mycache.cache_flush(toflush, tags);
					
					int time(0);
					
					for(unsigned i = 0; i < tags.size(); i++){
						for(unsigned j = 0; j < wperblock*bperword; j++){
							mem[(tags[i]*wperblock*bperword)+j] = toflush[(i*wperblock*bperword)+j];
							time += clwrite;
						}
					}
					/*cout << "memory contents" << endl;
					for(unsigned i = 0; i < mem.size(); i++){
							cout << dec << i << " " << hex << setfill('0') << setw(2) << unsigned(mem[i]) << endl;
						}*/
					
					cout << time << endl;
				}
			
				else if(cmd == "debug-req"){
					cout << "debug-ack-begin" << endl;
					cout << "debug-ack-end" << endl;	
				}
			}
		}
	
	return 0;
}
