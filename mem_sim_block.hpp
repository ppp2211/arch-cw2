#ifndef MEM_SIM_BLOCK_HPP
#define MEM_SIM_BLOCK_HPP

#include <vector>
#include <stdint.h>
using namespace std;
	
	class block{
	
		public:
			
			block(int bw, int wb);
			~block();
			
			bool tag_match(unsigned searchtag) const;			
			bool is_valid() const;
			bool is_dirty() const;
			
			void read_data(vector<uint8_t> &dest) const;
			int get_tag() const;
			
			void validate();
			void dirt();
			void clean();
			void store(vector<uint8_t> &src, unsigned newtag);
			void replace_data(vector<uint8_t> &src);
			void flush(vector<uint8_t> &toflush, vector<unsigned> &tags);
			
		private:
			unsigned tag;
			bool valid;
			bool dirty;
			vector<uint8_t> data;
	};
	
#endif
