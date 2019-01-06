#include "charcounter.h"
#include "hftree.h"
#include "minheap.h"
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>

int main(int argc, char	*argv[]) {

	if (argc != 2) {
		cout << "Incorrect usage of huff -- correct usage:\n" <<
			"./huff [textfile to compress]\n\n";
		return -1;
	}

	// TODO check if infile is .txt

	ifstream infile (argv[1]);
	if (infile.is_open()) {
		// make the char counts
		CharCounter cc;
		while (true) {
			int ch = infile.get();
			// check if EOF
			if (infile.eof())
				break;
			// check if ASCII
			if (ch < 0 || ch >= CharCounter::MAX_CHAR_VALUE) {
				cout << "File contains non-ASCII characters\n";
				exit(-1);
			}
			cc.increment(ch);
		}

		// make the hufftree
		HFTree hftree {&cc};

		// create the encoded file
		string out (argv[1]);
		out.append(".hf");
		ofstream outfile (out, ios::out|ios::binary|ios::trunc);

		if (!outfile.is_open()) {
			cout << "Can't open " << out << " for output\n\n";
			exit(-1);
		}

		// output the char counts
		outfile.write((char *) &cc.counts, 4 * CharCounter::MAX_CHAR_VALUE);

		// output the encodings
		encodingmap map = hftree.generateEncoding();
		string encoding;

		infile.seekg(0, ios::beg);
		while (true) {
			int ch = infile.get();
			// check if EOF
			if ((infile.rdstate() & ifstream::failbit) != 0)
				break;
			// TODO add bits to a buffer
		}


	} else {
		cout << "Unable to open file\n\n";
		return -1;
	}

	return 0;
}
