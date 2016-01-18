#ifndef MEM_SIM_BLOCK_HPP
#define MEM_SIM_BLOCK_HPP

#include <vector>
#include <stdint.h>
using namespace std;
	
	class block{
	
		public:
			
			block(int bw, int wb);
			~block();
			
			bool tag_match(int searchtag) const;			
			bool is_valid() const;
			bool is_dirty() const;
			
			void read_data(vector<uint8_t> &dest) const;
			int get_tag() const;
			
			void validate();
			void dirty();
			void clean();
			void store(vector<uint8_t> &src, int newtag);
			
		private:
			int tag;
			bool valid;
			bool dirty;
			vector<uint8_t> data;
	};
	
#endif
