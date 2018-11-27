#include "hftree.h"
#include "minheap.h"
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
	Str(const char * str) : str(str) {}
} Str;

void minheapTest() {
	{
		MinHeap<Int> mh {};
		assertEqual(mh.getSize(), 0);

		cout << "new minheap has size 0\n";

		assertNull(mh.peek());

		cout << "new minheap return nullptr when peeking\n";

		assertNull(mh.remove());

		cout << "new minheap returns nullptr when removing\n";

		mh.add(new Int {1}, 5);
		mh.add(new Int {2}, 4);
		mh.add(new Int {3}, 3);
		mh.add(new Int {4}, 2);
		mh.add(new Int {5}, 1);
		assertNotNull(mh.peek());

		cout << "minheap with values has non-null peek()\n";

		for (int i = 0; i < 5; i++) {
			Int *int_ptr = mh.remove();
			assertNotNull(int_ptr);
			assertEqual(int_ptr->data, 5 - i);
			delete int_ptr;
		}

		cout << "values were sorted when removing\n";

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

		cout << "added Str segments\n";

		while (mh.getSize() > 0)
			printf("%s\n", mh.remove()->str);

		cout << "^pretty right?\n";

	}

	cout << "minheapTest passed\n";


}

// and so on

int main() {

	minheapTest();

    return 0;
}
