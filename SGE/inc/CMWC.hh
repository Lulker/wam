#include <cstdint>
class CMWC {
	uint32_t i;
	uint32_t c;
	uint32_t Q[4096];
	public:
		CMWC(uint32_t seed = 42):i(4095),c(362436){
				Q[0] = seed;
				Q[1] = seed + 0x9e3779b9;
				Q[2] = seed + (0x9e3779b9<<1);
				for (int i = 3; i < 4096; i++)
					Q[i] = Q[i - 3] ^ Q[i - 2] ^ 0x9e3779b9 ^ i;
		}
		uint32_t operator()(){
			i = (i + 1) & 4095;
			uint64_t t = 18782LL * Q[i] + c;
			c = (t >> 32);
			uint32_t x = t + c;
			if (x < c) {
				x++;
				c++;
			}
			return (Q[i] = 0xfffffffe - x);
		}
		uint32_t operator()(int l,int h){return l+((*this)()%(h-l));}
};
