#ifndef _minheap_h_
#define _minheap_h_

#include <stdlib.h>

template<typename T>
struct Node {
	T *data;
	int priority;
};

template<typename T>
class MinHeap {

	static const int DEFAULT_INIT_CAPACITY = 128;

	Node<T>** arr; // index 1 is root
	int capacity;
	int size;

	// helper functions for add and remove
	inline int parentOf(int index) {
		return index / 2;
	}
	inline int lChildOf(int index) {
		return 2 * index;
	}
	inline int rChildOf(int index) {
		return 2 * index + 1;
	}
	void memcopy(u_int32_t *from, u_int32_t *to, int entries) {
		for (int i = 0; i < entries; i++)
			to[i] = from[i];
	}
	inline int switchWithRightChild(int idx) {
		Node<T> *temp = arr[rChildOf(idx)];
		arr[rChildOf(idx)] = arr[idx];
		arr[idx] = temp;
		return idx * 2 + 1;

	}
	inline int switchWithLeftChild(int idx) {
		Node<T> *temp = arr[lChildOf(idx)];
		arr[lChildOf(idx)] = arr[idx];
		arr[idx] = temp;
		return idx * 2;
	}

public:

	MinHeap() : MinHeap(DEFAULT_INIT_CAPACITY) {}

	MinHeap(int initial_capacity): capacity(initial_capacity) {
		this->arr = new Node<T>*[initial_capacity + 1]; // index 0 un-used
		this->size = 0;
	}

	~MinHeap() {
		delete arr;
	}

	void add(T *data, int priority) {
		// double capacity if full
		if (size == capacity) {
			Node<T>** temp = new Node<T>*[capacity * 2 + 1];
			capacity *= 2;
			memcopy((u_int32_t *) arr, (u_int32_t *) temp, size + 1);
			delete arr;
			arr= temp;
		}

		// place a new Node* in the next available position in arr
		Node<T> *node = new Node<T>;
		node->data = data;
		node->priority = priority;
		arr[1 + size] = node;
		size++;

		// swap it with its parent as long as the element is smaller or not root
		int idx = size;
		while (idx != 1 && arr[parentOf(idx)]->priority > arr[idx]->priority) {
			Node<T> *temp = arr[parentOf(idx)];
			arr[parentOf(idx)] = arr[idx];
			arr[idx] = temp;
			idx /= 2;
		}

	}

	T *remove() {
		if (this->size < 1)
			return nullptr;

		// save the root variable
		T *result = arr[1]->data;
		delete arr[1];

		// move the last element to the root position
		arr[1] = arr[size];
		arr[size] = nullptr;
		size--;

		// swap the moved element with smaller child until in proper place
		int idx = 1;
		while (true) {
			// check if element moved to bottom of tree
			if (2 * idx > this->size)
				break;

			// check if only one child
			bool hasRChild = true;
			if (2 * idx + 1 > this->size)
				hasRChild = false;

			int priority = arr[idx]->priority;
			int lPriority = arr[lChildOf(idx)]->priority;
			if (hasRChild) {
				int rPriority = arr[rChildOf(idx)]->priority;

				// only compare with smaller child priority

				if (lPriority <= rPriority) {
					// left child is smaller

					if (lPriority < priority) {
						idx = switchWithLeftChild(idx);
					} else {
						break;
					}

				} else {
					// right child is smaller

					if (rPriority < priority) {
						idx = switchWithRightChild(idx);
					} else {
						break;
					}

				}

			} else {
				// only a left child

				if (lPriority < priority) {
					idx = switchWithLeftChild(idx);
				} else {
					break;
				}

			}
		}

		return result;
	}

	T *peek() {
		if (size < 1)
			return nullptr;
		return this->arr[1]->data;
	}

	int getSize() {
		return this->size;
	}

};

#endif
