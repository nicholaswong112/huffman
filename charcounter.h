#ifndef _charcounter_h_
#define _charcounter_h_

#include <stdlib.h>
#include <stdint.h>

class CharCounter {
public:
	static const int MAX_CHAR_VALUE = 256;

private:
	uint32_t counts[MAX_CHAR_VALUE];

public:

	void increment(char c) {
		counts[(int) c]++;
	}

	uint32_t getCount(char c) {
		return counts[(int) c];
	}

};

#endif
