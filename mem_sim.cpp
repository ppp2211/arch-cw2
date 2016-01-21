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
	
	vector<uint8_t> data;
	int index;
		
		if(line.at(0) != '#'){
			
			istringstream row(line);
			string cmd;
			
			row >> cmd;
			
				if(cmd == "read-req"){
					cout << "read-ack ";
					
					unsigned addr;
					row >> addr;
					
					//cout << addr << endl;
					
					//cout << "before hit check " << endl;
					bool hit = mycache.cache_read(addr, data, index);
					//cout << "after hit check " << endl;
										
					cout << index << " ";
					
					if(hit){
						cout << "hit " << clhit << " "; 
						
						//cout << "before hit cout" << endl;
				
						
						for (unsigned i = 0; i < data.size() ; i++){
							cout << i << "=" << unsigned(data[i]) << " ";
						}
						
						cout << endl;
					}
					
					else{
						
						int time(0);
												
						//cout << " before mem load " << endl;
												
						for (unsigned i = 0; i < wperblock * bperword ; i++){
						
							data.push_back(mem[addr+i]);
						}
						
						//cout << "after mem load" << endl;
									
						vector<uint8_t> evicted;
						int etag;
						
						if(mycache.cache_loadin(addr, data, evicted, etag)){
							for (unsigned i = 0 ; i < wperblock * bperword ; i++) {
 								 mem[etag + i] = evicted[i]; 
							}
						}
						
						cout << "miss " << time << " ";
						
						
						for (unsigned i = 0; i < data.size() ; i++){
							cout << i << "=" << unsigned(data[i]) << " ";
							
						}
						data.clear();
						cout << endl;
					}
											
					
				
				}
			
				else if(cmd == "write-req"){ // write code for a hit too pls fix too get a hex
				
					cout << "write-ack ";
					
					unsigned addr;
					uint32_t tostore;
					row >> addr >> tostore;
					
					cout << "tostore " << hex << unsigned(tostore) << endl;
					
					for (unsigned i = 0; i < wperblock * bperword ; i++){	
						uint8_t byte = (tostore >> ((wperblock*bperword - (i+1)) * 8));				
						cout << "byte " << hex << unsigned(byte) << endl;
						cout << " shift " << ((wperblock*bperword - (i+1)) * 8) << endl;
						data.push_back(byte);
					}
						
								
					vector<uint8_t> evicted;
					int etag;
						
					if(mycache.cache_loadin(addr, data, evicted, etag)){
						for (unsigned i = 0 ; i < wperblock * bperword ; i++) {
 							 mem[etag + i] = evicted[i]; 
						}
					}
						
					cout << "miss " << time << " ";
						
						
					for (unsigned i = 0; i < data.size() ; i++){
						cout << i << "=" << hex << unsigned(data[i]) << " ";
						
					}
					data.clear();
					cout << endl;
																			
					cout << addr << " " << tostore << endl;	
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
