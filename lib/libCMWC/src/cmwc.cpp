#include <cmwc.h>
#define PHI 0x9e3779b9

cmwc::cmwc(uint32_t seed){
	i = 4095;
	c = 362436;
	Q[0] = seed;
	Q[1] = seed + PHI;
	Q[2] = seed + (PHI<<1);

	for (int i = 3; i < 4096; i++)
		Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
}

uint32_t cmwc::rand(){
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
