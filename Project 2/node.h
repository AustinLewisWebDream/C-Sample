#pragma once
#include <string>
using namespace std;

class node
{
	friend class tst;
public:
	node();
	~node();
private:
	int key;			// search key
	string data;		// data stored for this key
	node * left;		// pointer to the BST left child (all keys < this key)
	node * equal;		// linked list of old values, all keys are equal to this one
	node * right;		// pointer to the BST right child (all keys > this key)	
};

