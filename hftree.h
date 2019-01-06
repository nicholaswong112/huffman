#ifndef _hftree_h_
#define _hftree_h_

#include "charcounter.h"
#include <stdlib.h>
#include <string>
#include <unordered_map>

typedef struct TreeNode {
	int32_t value;
	TreeNode *left;
	TreeNode *right;
	int ch;
	bool isLeaf;
} TreeNode;

// maps from int ASCII value to a string of 0s and 1s
typedef std::unordered_map<int, std::string> encodingmap;

class HFTree {

	CharCounter *charcounts;
	TreeNode *head;
	TreeNode *current;
	encodingmap encoding;

	// helps to free TreeNodes
	void freeNode(TreeNode *node);

	// recursive function for generating encoding
	void findEncodings(TreeNode *n, std::string path);

public:

	// given a CharCounter, generates the huffman tree
	HFTree(CharCounter *cc);

	// frees the HFTree (just Nodes, CharCounter is callers responsibility)
	~HFTree();

	// helps to free TreeNodes
	// FOR ENCODING
	// generates the encoding mapping
	encodingmap generateEncoding();

	// FOR DECODING
	// Takes in a bit.
	// If the bit finishes an encoding sequence true is returned and
	//   the character is put at *c
	// Otherwise, false is returned and the internal state of
	//   the HFTree is change accordingly
	bool processBit(int bit, int *c);

};

#endif
