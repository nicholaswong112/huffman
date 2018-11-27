#ifndef _charcounter_h_
#define _charcounter_h_

#include <stdlib.h>
#include <stdint.h>

class CharCounter {

	uint32_t counts[256];

public:

	void increment(char c) {
		counts[(int) c]++;
	}

	uint32_t getCount(char c) {
		return counts[(int) c];
	}

};

#endif
