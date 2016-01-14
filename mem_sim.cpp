#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char *argv[]){
	
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
