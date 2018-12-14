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

	ifstream infile (argv[1]);
	if (infile.is_open()) {
		// make the char counts
		CharCounter *cc = new CharCounter;

		string line;
		while (getline(infile, line)) {
			for (unsigned i = 0; i < line.length(); i++)
				cc->increment(str.at(i));
		}

		// make the hufftree
		HFTree hftree {cc};

		// create the encoded file
		string out (argv[1]);
		out.append(".hf");
		ofstream outfile (out, ios::out|ios::binary|ios::trunc);

		if (!outfile.is_open()) {
			cout << "Can't open " << out << " for output\n\n";
			exit(-1);
		}

		// output the char counts
		for (char i = 0; i < CharCounter::MAX_CHAR_VALUE; i++)
			outfile.write((char *) &(cc->getCount(i)), 4);

		// output the encodings
		encodingmap map = hftree.generateEncoding();
		string encoding;

		infile.seekg(0, ios::beg);
		while (getline(infile, line)) {
			for (unsigned i = 0; i < line.length(); i++) {
				char c = str.at(i);
				encoding = map[c];
				// TODO write the encoding string in binary
			}
		}


		delete cc;

	} else {
		cout << "Unable to open file\n\n";
		return -1;
	}

	return 0;
}
