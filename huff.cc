#include "charcounter.h"
#include "hftree.h"
#include "minheap.h"
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char	*argv[]) {

	if (argc != 2) {
		cout << "Incorrect usage of huff -- correct usage:\n" <<
			"./huff [textfile to compress]\n\n";
		return -1;
	}

	// TODO check if infile is .txt

	ifstream infile (argv[1]);
	if (infile.is_open()) {

		cout << "Opened " << argv[1] << " successfully\n";

		// make the char counts
		CharCounter cc;
		while (true) {
			int ch = infile.get();
			// check if EOF
			if (infile.eof())
				break;
			// check if ASCII
			if (ch < 0 || ch >= MAX_CHAR_VALUE) {
				cout << "File contains non-ASCII characters\n";
				exit(-1);
			}
			cc.increment(ch);
		}

		cout << "Counted all the characters\n";

		// make the hufftree
		HFTree hftree {&cc};

		cout << "Huffman tree created\n";

		// create the encoded file
		string out (argv[1]);
		out.append(".hf");
		ofstream outfile (out, ios::out|ios::binary|ios::trunc);

		if (!outfile.is_open()) {
			cout << "Can't open " << out << " for output\n\n";
			exit(-1);
		}

		cout << "Created " << out << endl;

		// output the char counts, takes up a KB
		outfile.write((char *) &cc.counts, 4 * MAX_CHAR_VALUE);

		cout << "Wrote the char counts to output\n";

		// output the encodings
		encodingmap map = hftree.generateEncoding();
		string encoding;
		bool eof = false;

		cout << "Generated the encoding map\n";

		infile.clear();
		infile.seekg(0, ios::beg);

		// will write out the 1024 bytes whenever it fills
		const int buffersize = 256;
		int size = 0;
		uint32_t buffer[buffersize];

		while (!eof) {
			int ch = infile.get();

			// check if EOF --> get EOF encoding
			if (infile.eof()) {
				encoding = map[MAX_CHAR_VALUE];
				eof = true;
			} else {
				encoding = map[ch];
			}

			for (int i = 0; i < (int) encoding.length(); i++) {

				int idx = size / 32;
				int bit = size % 32;

				if (encoding[i] == '0') {
					// set the (size+1)-th bit from the left to 0
					buffer[idx] &= ~(1 << (31 - bit));
				} else if (encoding[i] == '1') {
					// set the (size+1)-th bit from the left to 1
					buffer[idx] |= 1 << (31 - bit);
				} else {
					cout << "Encoding wasn't binary, whaaat\n";
					exit(-1);
				}
				size++;

				// if buffer is full, write it out
				if (size == 8192) {
					outfile.write((char *) &buffer, 4 * buffersize);
					size = 0;
				}
			}
		}

		// write out the rest of buffer
		outfile.write((char *) &buffer, (size / 8) + 1);

		cout << "Finished writing encodings\n";

		outfile.close();

	} else {
		cout << "Unable to open file\n\n";
		return -1;
	}

	infile.close();

	return 0;
}
