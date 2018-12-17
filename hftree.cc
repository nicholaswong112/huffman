#include "hftree.h"
#include "charcounter.h"
#include "minheap.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unordered_map>

#define EOF_VALUE 256

using std::cout;

// given a CharCounter, generates the huffman tree
HFTree::HFTree(CharCounter *cc) : charcounts(cc), encoding() {
	// priority queue to hold the Node*
	MinHeap<TreeNode> pq;

	// for all nonzero char counts, add the Node to pq
	for (char c = 0; c < CharCounter::MAX_CHAR_VALUE; c++) {
		if (cc->getCount(c) != 0)
			pq.add(new TreeNode {cc->getCount(c), nullptr, nullptr, c, true},
					cc->getCount(c));
	}

	// add the pseudo EOF
	pq.add(new TreeNode {1, nullptr, nullptr, (char) EOF_VALUE, true}, 1);

	// repeatedly combine small trees together
	while (pq.getSize() > 1) {

		cout << "size of pq: " << pq.getSize() << std::endl;

		TreeNode *x = pq.remove();
		TreeNode *y = pq.remove();

		TreeNode *temp = new TreeNode {x->value + y->value, x, y, 0, false};

		pq.add(temp, temp->value);
	}

	// tree finished, prepare for en/decoding
	head = pq.remove();
	current = head;

}

// helps to free TreeNodes
void HFTree::freeNode(TreeNode *node) {
	if (node == nullptr) return;
	freeNode(node->left);
	freeNode(node->right);
	delete node;
}

// frees the HFTree (just TreeNodes, CharCounter is callers responsibility)
HFTree::~HFTree() {
	freeNode(head);
	// TODO free encodingmap too? idk how objects work
}

// recursive function for generating encoding
void HFTree::findEncodings(TreeNode *n, std::string path) {
	if (n == nullptr) return;
	if (n->isLeaf) {
		encoding[n->c] = path;
		return;
	}
	std::string left(path);
	left.append("0");
	std::string right(path);
	right.append("1");

	findEncodings(n->left, left);
	findEncodings(n->right, right);
}

// FOR ENCODING
// generates the encoding mapping
encodingmap HFTree::generateEncoding() {
	findEncodings(head, "");
	return encoding;
}

// FOR DECODING
// Takes in a bit.
// If the bit finishes an encoding sequence true is returned and
//   the character is put at *c
// Otherwise, false is returned and the internal state of
//   the HFTree is change accordingly
bool HFTree::processBit(int bit, char *c) {
	if (bit != 0 && bit != 1) {
		perror("bit needs to be 0 or 1");
		exit(-1);
	}

	if (bit == 0) // move left
		current = current->left;
	else
		current = current->right;

	if (current == nullptr) {
		perror("invalid encoding");
		exit(-1);
	}

	if (current->isLeaf) {
		*c = current->c;
		current = head;
		return true;
	}

	return false;
}
