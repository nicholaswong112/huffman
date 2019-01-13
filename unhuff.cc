#include "charcounter.h"
#include "hftree.h"
#include "minheap.h"
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {

	if (argc != 2) {
		cout << "Incorrect usage of unhuff -- correct usage:\n" <<
			"./unhuff [textfile to uncompress]\n\n";
		return -1;
	}

	// check if infile is .hf
	int len = strlen(argv[1]);
	char *ext = argv[1] + len - 3;
	if (strcmp(ext, ".hf") != 0) {
		cout << "Input file should be .hf\n";
		exit(-1);
	}

	ifstream infile (argv[1]);
	if (infile.is_open()) {

		cout << "Opened " << argv[1] << " successfully\n";

		// read the char counts
		CharCounter cc;
		infile.read((char *) &cc.counts[0], 4 * MAX_CHAR_VALUE);

		cout << "Read the character count\n";

		// make the hufftree
		HFTree hftree {&cc};

		cout << "Huffman tree created\n";

		// created the decoded file
		*ext = '\0';
		string out (argv[1]);
		out.append(".txt");
		ofstream outfile (out, ios::out|ios::trunc);

		if (!outfile.is_open()) {
			cout << "Can't open " << out << " for output\n\n";
			exit(-1);
		}

		cout << "Created " << out << endl;

		// output decodings
		const int buffersize = 1024;
		uint8_t buffer[buffersize];
		int pos = buffersize * 8; // to let logic below fill the buffer
		int val;
		int ch;

		while (true) {

			do {

				if (pos == buffersize * 8) {
					//replace the buffer
					infile.read((char *) &buffer[0], buffersize);
					// assuming valid .hf file, will terminate decoding before
					// EOF of infile reached

					pos = 0;
				}
				// get the bit value
				int byte = pos / 8;
				int bit = pos % 8;
				val = (buffer[byte] & (1 << (7 - bit))) >> (7 - bit);

				pos++;

			} while (!hftree.processBit(val, &ch));

			// output the character
			if (ch == MAX_CHAR_VALUE) // catch EOF
				break;

			outfile.write((char *) &ch, 1);
		}

		outfile.close();

		cout << "Done decoding\n";

	} else {
		cout << "Unable to open file\n\n";
		return -1;
	}

	infile.close();

	return 0;
}
