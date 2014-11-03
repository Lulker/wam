#pragma once
#include <cstdint>

class cmwc {
	uint32_t Q[4096];
	uint32_t i;
	uint32_t c;
	public:
		cmwc(uint32_t seed = 42);
		uint32_t rand();
};
