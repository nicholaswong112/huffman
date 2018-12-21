#ifndef _charcounter_h_
#define _charcounter_h_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
 * Keeps track of ASCII character count
*/

class CharCounter {
public:
	static const int MAX_CHAR_VALUE = 256;

private:
	uint32_t counts[MAX_CHAR_VALUE];

public:

	CharCounter() {
		memset(counts, 0, MAX_CHAR_VALUE * sizeof(uint32_t));
	}

	void increment(unsigned char c) {
		counts[c]++;
	}

	uint32_t getCount(unsigned char c) {
		return counts[c];
	}

};

#endif
