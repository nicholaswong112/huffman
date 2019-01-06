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
	int32_t counts[MAX_CHAR_VALUE];

public:

	CharCounter() {
		memset(counts, 0, MAX_CHAR_VALUE * sizeof(uint32_t));
	}

	void increment(int c) {
		if (c < 0 || c >= MAX_CHAR_VALUE) return;
		counts[c]++;
	}

	int32_t getCount(int c) {
		if (c < 0 || c >= MAX_CHAR_VALUE) return -1;
		return counts[c];
	}

};

#endif
