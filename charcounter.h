#ifndef _charcounter_h_
#define _charcounter_h_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
 * Keeps track of ASCII character count
*/

static const int MAX_CHAR_VALUE = 256;

typedef struct CharCounter {

	int32_t counts[MAX_CHAR_VALUE];

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

} CharCounter;

#endif
