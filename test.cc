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

void charCounterTest() {

	{
		CharCounter cc;

		// initial values should all be 0
		unsigned char c = 0;
		for (int i = 0; i < CharCounter::MAX_CHAR_VALUE; i++, c++) {
			if (cc.getCount(c) != 0) {
				printf("init count for char %d is %d\n", c, cc.getCount(c));
				exit(-1);
			}
		}

		cc.increment('a');

		if (cc.getCount('a') != 1) {
			cout << "incrementing 'a' had no effect\n";
			exit(-1);
		}

		c = 0;
		for (int i = 0; i < CharCounter::MAX_CHAR_VALUE; i++, c++)
			cc.increment(c);

		c = 0;
		for (int i = 0; i < CharCounter::MAX_CHAR_VALUE; i++, c++) {
			unsigned target = c == 'a' ? 2 : 1;
			if (cc.getCount(c) != target) {
				printf("count for char %d is incorrect\n", c);
				exit(-1);
			}
		}

	}

	{
		std::string text =
			"welkrj43230fjdsfknl2rMa6pOtsxYuqiel0tX4UXQEY9VnO9GJL4ILla7hknWd9h5zSS9xseTC7qwxMBeUAwqaj1twKEQPdowt2ZHRRhqv4UC2gLWN6jHnWr0O2FK8tGsXwMuz0HjCmPxrUl8tODgqqdbLBuSiCzuIqcWOkGmLSLUsPwWcKCkdpzTKngk1Owf64oQoj";
		CharCounter cc;

		for (unsigned i = 0; i < text.length(); i++)
			cc.increment(text[i]);

		int count;

		unsigned char c = 0;
		for (int i = 0; i < CharCounter::MAX_CHAR_VALUE; i++, c++)
			count += cc.getCount(c);

		if (count != 200) {
			cout << "count is " << count << ", should be 200\n";
			exit(-1);
		}

	}

	cout << "[charCounterTest passed]\n";

}

void hftreeTest() {

	cout << "[hftreeTest passed]\n";

}

// and so on

int main() {

	minheapTest();

	charCounterTest();

	//hftreeTest();

	cout << "All tests passed\n";

    return 0;
}
