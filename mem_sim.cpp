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
					
					uint32_t addr;
					row >> addr;
					
					vector<uint8_t> data;
					int index;
					
					bool hit = mycache.cache_read(addr, data, index);
					
					cout << index << " ";
					
					if(hit){
						cout << "hit " << clhit << hex; 
						
						for (unsigned i = 0; i < data.size() ; i++){
							cout << data[i];
						}
						cout << dec << endl;
					}
					else{
						
						int time(0);
						
						data = mem[addr];		// fix this first - handle as vectors not as a retard				
						vector<uint8_t> evicted;
						int etag;
						
						if(mycache.loadin(addr, data, evicted, etag){
							for (i = 0 ; i < wperblock * bperword ; i++) {
 								 memory[etag + i] = evicted[i]; 
							}
						}
						
						cout << "miss " << time << data << endl;
					}
											
					
				
				}
			
				else if(cmd == "write-req"){
				
					uint32_t addr, data;
					row >> addr >> data;
					cout << "write-ack " << addr << " " << data << endl;	
				}
				
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
