#include "hftree.h"
#include "minheap.h"
#include "charcounter.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using std::cout;

void assertNotNull(void *ptr) {
	if (ptr == nullptr) {
		cout << "null pointer\n";
		exit(1);
	}
}

void assertNull(void *ptr) {
	if (ptr != nullptr) {
		cout << "not null pointer\n";
		exit(1);
	}
}

void assertEqual(int x, int y) {
	if (x != y) {
		cout << x << "and" << y << "aren't equal\n";
		exit(1);
	}
}

typedef struct Int {
	int data;
	Int(int num) : data(num) {}
} Int;

typedef struct Str {
	const char *str;
	Str(const char *str) : str(str) {}
} Str;

typedef struct Student {
	const char *name;
	double gpa;
	Student(const char *name, double gpa) : name(name), gpa(gpa) {}
} Student;

void minheapTest() {
	{
		MinHeap<Int> mh {};
		assertEqual(mh.getSize(), 0);

		assertNull(mh.peek());

		assertNull(mh.remove());

		mh.add(new Int {1}, 5);
		mh.add(new Int {2}, 4);
		mh.add(new Int {3}, 3);
		mh.add(new Int {4}, 2);
		mh.add(new Int {5}, 1);
		assertNotNull(mh.peek());

		for (int i = 0; i < 5; i++) {
			Int *int_ptr = mh.remove();
			assertNotNull(int_ptr);
			assertEqual(int_ptr->data, 5 - i);
			delete int_ptr;
		}

	}

	{
		MinHeap<Str> mh {};
		mh.add(new Str {"*******"}, 7);
		mh.add(new Str {"*****"}, 5);
		mh.add(new Str {"**"}, 2);
		mh.add(new Str {"*****"}, 9);
		mh.add(new Str {"****"}, 10);
		mh.add(new Str {"**"}, 12);
		mh.add(new Str {"******"}, 6);
		mh.add(new Str {"****"}, 4);
		mh.add(new Str {"***"}, 11);
		mh.add(new Str {"***"}, 3);
		mh.add(new Str {"*"}, 1);
		mh.add(new Str {"*"}, 13);
		mh.add(new Str {"******"}, 8);

		while (mh.getSize() > 0)
			printf("%s\n", mh.remove()->str);

	}

	{
		MinHeap<Student> mh {};
		Student *students[7];
		students[0] = new Student { "Albert", 3.1 };
		students[1] = new Student { "Brian", 3.9 };
		students[2] = new Student { "Chris", 3.2 };
		students[3] = new Student { "Daniel", 3.7};
		students[4] = new Student { "Elise", 2.9 };
		students[5] = new Student { "Frank", 1.2 };
		students[6] = new Student { "Georgie", 0.9};

		for (int i = 0; i < 7; i++)
			mh.add(students[i], (int)(students[i]->gpa * 100));

		if (std::string(mh.remove()->name).compare("Georgie") != 0) {
			cout << "Didn't sort students correctly\n";
			exit(-1);
		}
		if (std::string(mh.remove()->name).compare("Frank") != 0) {
			cout << "Didn't sort students correctly\n";
			exit(-1);
		}
		if (std::string(mh.remove()->name).compare("Elise") != 0) {
			cout << "Didn't sort students correctly\n";
			exit(-1);
		}
		if (std::string(mh.remove()->name).compare("Albert") != 0) {
			cout << "Didn't sort students correctly\n";
			exit(-1);
		}
		if (std::string(mh.remove()->name).compare("Chris") != 0) {
			cout << "Didn't sort students correctly\n";
			exit(-1);
		}
		if (std::string(mh.remove()->name).compare("Daniel") != 0) {
			cout << "Didn't sort students correctly\n";
			exit(-1);
		}
		if (std::string(mh.remove()->name).compare("Brian") != 0) {
			cout << "Didn't sort students correctly\n";
			exit(-1);
		}
		if (mh.remove() != nullptr) {
			cout << "Student minheap isn't empty\n";
			exit(-1);
		}

	}

	{
		MinHeap<Int> mh {};
		for (int i = 0; i < 500; i++) {
			int random = rand();
			mh.add(new Int {random}, random);
		}
		// test duplicate values
		mh.add(new Int{0}, 0);
		mh.add(new Int{0}, 0);
		mh.add(new Int{0}, 0);

		int prev = -1;
		while (mh.getSize() > 0) {
			int temp = mh.remove()->data;
			if (prev > temp) {
				cout << "failed to sort int values properly\n";
				exit(-1);
			}
			prev = temp;
		}

	}

	cout << "[minheapTest passed]\n";

}

void hftreeTest() {

	char original[] = "abbcccddddeeeee";

	cout << "Original: " << original << std::endl;

	uint8_t encoded[15]; // should be at most the uncompressed length

	CharCounter cc;
	for (int i = 0; i < 15; i++)
		cc.increment(original[i]);

	cout << "Got the char counts\n";

	{
		// FAKE ENCODING
		HFTree hft {&cc};
		encodingmap map = hft.generateEncoding();

		cout << "Got the encoding map\n";

		// encoding the original
		int bit = 0;
		for (int i = 0; i < 15; i++) {
			std::string encoding = map[original[i]];

			cout << "about to encode " << original[i] << std::endl;

			for (unsigned j = 0; j < encoding.length(); j++) {
				int byte = bit / 8;
				int inbit = bit % 8;

				if (encoding[j] == '1') {
					encoded[byte] = encoded[byte] | (1 << (7 - inbit));

				} else if (encoding[j] == '0') {
					encoded[byte] = encoded[byte] & (~(1 << (7 - inbit)));

				} else {
					cout << "The encoding contains stuff other than 0 or 1\n";
					exit(-1);
				}

				bit++;
			}

		}

		// getting the psuedo EOF
		std::string encoding = map[(char) CharCounter::MAX_CHAR_VALUE];

		for (unsigned j = 0; j < encoding.length(); j++) {
			int byte = bit / 8;
			int inbit = bit % 8;

			if (encoding[j] == '1') {
				encoded[byte] = encoded[byte] | (1 << (7 - inbit));

			} else if (encoding[j] == '0') {
				encoded[byte] = encoded[byte] & (~(1 << (7 - inbit)));

			} else {
				cout << "The encoding contains stuff other than 0 or 1\n";
				exit(-1);
			}

			bit++;
		}

	}

	{
		// FAKE DECODING
		HFTree hft {&cc};

		char decoded[16];
		decoded[15] = '\0';
		int index = 0;

		char decodedChar = (char) 0;

		int bitIdx = 0;

		while (decodedChar != (char) CharCounter::MAX_CHAR_VALUE) {

			int bit;

			do {
				int byte = bitIdx / 8;
				int bitPos = bitIdx % 8;

				bit = (encoded[byte] & (1 << (7 - bitPos))) >> (7 - bitPos);

				cout << "got bit " << bit << " at bitIdx " << bitIdx << std::endl;

				bitIdx++;

			} while (!hft.processBit(bit, &decodedChar));

			if (decodedChar == (char) CharCounter::MAX_CHAR_VALUE)
				break;

			decoded[index++] = decodedChar;

			if (index > 14) {
				cout << "Hm, decoded more chars than were encoded...\n";
				exit(-1);
			}

		}

		if (index != 15) {
			cout << "Didn't decode the right amount of chars\n";
			exit(-1);
		}

		cout << "Decoded: " << decoded << std::endl;

	}

	cout << "[hftreeTest passed]\n";

}

// and so on

int main() {

	minheapTest();

	hftreeTest();

	cout << "All tests passed\n";

    return 0;
}
