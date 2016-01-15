#ifndef MEM_SIM_BLOCK_HPP
#define MEM_SIM_BLOCK_HPP

#include <vector>
#include <stdint.h>
using namespace std;
	
	class block{
	
		public:
			
			block(int bw, int wb);
			~block();
			
		private:
			int tag;
			bool valid;
			bool dirty;
			vector<uint8_t> data;
	};
	
#endif
