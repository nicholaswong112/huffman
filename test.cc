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

	{
		MinHeap<Student> mh {};
		Student *students[7];
		students[0] = new Student { "Albert", 3.1 };
		students[1] = new Student { "Brian", 3.9 };
		students[2] = new Student { "Chris", 3.2 };
		students[3] = new Student { "Daniel", 3.7};
		students[4] = new Student { "Elise", 2.9 };
		for (int i = 0; i < 5; i++)
			mh.add(students[i], (int)(students[i]->gpa * 100));

		while (mh.getSize() > 0) {
			Student *s = mh.remove();
			cout << s->name << ":" << s->gpa << std::endl;
		}

		for (int i = 0; i < 5; i++)
			mh.add(students[i], (int)(students[i]->gpa * 100));

		Student *worst = mh.remove();
		cout << worst->name << ":" << worst->gpa << std::endl;

		students[5] = new Student { "Frank", 1.2 };
		students[6] = new Student { "Georgie", 0.9};

		mh.add(students[5], (int)(students[5]->gpa * 100));
		mh.add(students[6], (int)(students[6]->gpa * 100));

		worst = mh.remove();
		cout << worst->name << ":" << worst->gpa << std::endl;

		worst = mh.remove();
		cout << worst->name << ":" << worst->gpa << std::endl;

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
		while (mh.getSize() > 0)
			cout << mh.remove()->data << std::endl;

	}

	cout << "minheapTest passed\n";


}

// and so on

int main() {

	minheapTest();

    return 0;
}
