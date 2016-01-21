#include <iostream>
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
					
					cout << "addr " << addr;
					cout << " woffset " << woffset << " ";
					
					if(hit){
						cout << "hit " << clhit << " "; 
						
						unsigned offset = (wperblock-woffset-1)*bperword;
											
						for (unsigned i = offset; i < offset+bperword ; i++){
							cout << hex << unsigned(data[i]);
						}
						
						cout << endl;
					}
					
					else{
						
						int time(0);
														
						for (unsigned i = 0; i < wperblock * bperword ; i++){						
							data.push_back(mem[addr+i]);
						}
									
						vector<uint8_t> evicted;
						int etag;
						
						if(mycache.cache_loadin(addr, data, evicted, etag)){
							for (unsigned i = 0 ; i < wperblock * bperword ; i++) {
 								 mem[etag + i] = evicted[i]; 
							}
						}
						
						cout << "miss " << time << " ";
						
						
						unsigned offset = (wperblock-woffset-1)*bperword;
											
						for (unsigned i = offset; i < offset+bperword ; i++){
							cout << hex << unsigned(data[i]);
						}
							
						
						data.clear();
						cout << endl;
					}
											
					
				
				}
			
				/*else if(cmd == "write-req"){ // write code for a hit too pls fix too - get a hex
				
					cout << "write-ack ";
					
					unsigned addr;
					unsigned tostore;
					row >> addr >> hex >> tostore; 
					
					vector<uint8_t> data;
					int index;
												
					bool hit = mycache.cache_read(addr, data, index);
										
					cout << index << " ";
					
					unsigned woffset = (addr/bperword) % wperblock;
					
					for (unsigned i = 0; i < bperword ; i++){	
						uint8_t byte = (tostore >> ((bperword - (i+1)) * 8));				
					}
					
					if(hit){
						cout << "hit " << clhit << " "; 
											
						for (unsigned i = woffset*bperword; i < bperword ; i++){
							cout << hex << unsigned(data[i]);
						}
						
						cout << endl;
					}
					
					if 
						
								
					vector<uint8_t> evicted;
					int etag;
						
					if(mycache.cache_loadin(addr, data, evicted, etag)){
						for (unsigned i = 0 ; i < wperblock * bperword ; i++) {
 							 mem[etag + i] = evicted[i]; 
						}
					}
						
					cout << "miss " << time << " ";
						
						
					for (unsigned i = 0; i < data.size() ; i++){
						cout << hex << unsigned(data[i]);
						
					}
					data.clear();
																								
					cout << endl;	
				}*/
				
				else if(cmd == "flush-req"){
					cout << "flush-ack " << endl;	
				}
			
				else if(cmd == "debug-req"){
					cout << "debug-ack-begin" << endl;
					cout << "debug-ack-end" << endl;	
				}
			}
		}
	
	return 0;
}
