//--------------------------------------------------------------------
//                            class tst
//--------------------------------------------------------------------
// Describes a Trinary Search Tree, a variation of a Binary Search 
// Tree where each node (in addition to a left and right subtree) 
// has a linked list of nodes with the same key value,
// where the most-recent value for the key is stored in the BST node
// and the older nodes are stored in a linked list in historical order
//--------------------------------------------------------------------
#pragma once
#include <string>
#include "node.h"
using namespace std;

class tst
{
public:
	tst();                                     // constructor
	~tst();                                    // destructor
	void insert(const int k, const string s);  // insert new node with given key/data
	void print() const;                        // print the TST
	void read();                               // reads data from a file
	int  height() const;                       // returns the Tree Height 
	int  count() const;                        // returns number of BST nodes 
	int  fullCount() const;                    // returns number of all nodes
	int  maxKey() const;                       // returns the largest key in the tree
	string search(int k) const;                // returns current and historical data
private:
	void print(node* r, int level) const;
	void insert(node* p, node* r, node* rParent);
	void insertEqual(node* p, node* r, node* rParent);
	int  height(node* parent) const;
	int  count(node* parent, int& num) const;
	int  fullCount(node* parent, int& num) const;
	int  maxKey(node* parent, int& max_key) const;
	string search(node* parent, int key, string& key_chain) const;
	node* root;
};
