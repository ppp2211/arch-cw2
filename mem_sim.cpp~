#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]){	
	
	unsigned addr_bits = atoi(argv[1]);
	unsigned mem_size = (1 << addr_bits);
	vector<uint8_t> mem (mem_size, 0);
	
	string line;
	
	while(getline(cin,line)){
		
		if(line.at(0) != '#'){
			
			istringstream row(line);
			string cmd;
			
			row >> cmd;
			
				if(cmd == "read-req"){
			
					unsigned addr;
					row >> addr;
					
					cout << "read-ack " << addr << endl;	
				
				}
			
				else if(cmd == "write-req"){
				
					unsigned addr, data;
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
