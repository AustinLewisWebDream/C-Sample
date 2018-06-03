#include <iostream>
#include <fstream>
#include <iomanip>
#include "tst.h"
using namespace std;

//--------------------------------------------------------------------
//                      Constructor/Destructor
//--------------------------------------------------------------------

tst::tst() { root = nullptr; }

tst::~tst() { delete root; }

//--------------------------------------------------------------------
//                             insert - public
//--------------------------------------------------------------------
// given a new key and data, allocates and populates a new node
// When the tree is empty, makes the new node the root
// When the tree is not empty, inserts the new node into the root
// (parent of root is nullptr)
//--------------------------------------------------------------------
void tst::insert(const int k, const string s)
{
	node* p = new node;
	p->key = k;
	p->data = s;
	if (root == nullptr) // If tree has no root, new node is root
	{
		root = p;
		return;
	}
	insert(p, root, nullptr);
} // public

//--------------------------------------------------------------------
//                             insert - private
//--------------------------------------------------------------------
// given: pointer to a newly-allocated and populated node to insert
//        pointer to the tree/subtree into which the new node is to
//                be inserted
//        pointer to the parent of r. The parent's right or left
//                child will need to be modified if this is a 
//                "duplicate" key, as the new node replaces the 
//                current node (r) in the tree.
//		  bool    indicates when the new node has been inserted to
//                exit stack
//--------------------------------------------------------------------
void tst::insert(node* p, node* r, node* rParent)
{
	if (p->key < r->key)
	{
		if (r->left != nullptr)
		{
			insert(p, r->left, r);
		}
		else
			r->left = p;
	}
	// Insert new node on right side of r
	else if (p->key > r->key)
	{
		if (r->right != nullptr)
		{
			insert(p, r->right, r);
		}
			// else r has no left child
		else
			r->right = p;
	}
	// New node key is equal to r key
	else
		insertEqual(p, r, rParent);
} // insert()

//--------------------------------------------------------------------
//                             insertEqual
//--------------------------------------------------------------------
// Sub method of insert()-private
// p's key and r's key are equal, so p's node will replace r's in the
// BST.
//--------------------------------------------------------------------

void tst::insertEqual(node* p, node* r, node* rParent)
{
	// Re-assign r's children to p
	p->left = r->left;
	p->right = r->right;
	p->equal = r;
	// p will be new parent, so set r's children to nullptr
	r->left = nullptr;
	r->right = nullptr;
	// TODO create new pointer for parent, points to r assign to p
	if (rParent != nullptr)
	{
		if (rParent->key > r->key) rParent->left = p;
		else if (rParent->key < r->key) rParent->right = p;
		else rParent->equal = p;
	}
	// Parent is nullptr, so r was root
	else root = p;
}

//--------------------------------------------------------------------
//                               maxKey - public
//--------------------------------------------------------------------
// returns the highest key in the tree, or -1 for an empty tree
//--------------------------------------------------------------------

int tst::maxKey() const
{
	int max_key = -1;
	if (root == nullptr) return -1;
	maxKey(root, max_key);
	return max_key;
}

//--------------------------------------------------------------------
//                               maxKey - private
//--------------------------------------------------------------------
// Modifies: max_key every time a new highest key found
//--------------------------------------------------------------------

int tst::maxKey(node* parent, int& max_key) const
{
	if (parent == nullptr) return -1;
	maxKey(parent->left, max_key);
	if (parent->key > max_key) max_key = parent->key;
	maxKey(parent->right, max_key);
	if (parent->key > max_key) max_key = parent->key;
	// On each parent, check key number
	return max_key;
}


//--------------------------------------------------------------------
//                               print
//--------------------------------------------------------------------
void tst::print() const
{
	cout << "--------------------- TST PRINT -------------------------\n";
	print(root, 0); // invoke on root, starting with level 0
} // print()

void tst::print(node* r, const int level) const
{
	if (!r) return; // nothing to print!

	// print the right sub tree
	print(r->right, level + 1);

	// print this node
	for (int i = 0; i < level; i++) // print tabs per level
		cout << "\t";
	cout << "KEY=" << setw(3) << r->key << " DATA=" << r->data;

	// print the equal nodes of this node
	node* p = r->equal;
	while (p != nullptr)
	{
		cout << "::" << p->data;
		p = p->equal;
	}
	cout << "\n";

	// print left sub tree
	print(r->left, level + 1);
} // print()

//--------------------------------------------------------------------
//                               read
//--------------------------------------------------------------------
void tst::read()
{
	ifstream f;
	int k;
	string data;

	// open input file
	cout << "Enter input file name: ";
	cin >> data;
	f.open(data);
	if (f.fail())
	{
		cout << "Error opening input file.\n";
		return;
	}

	// get key and data from first line
	f >> k;
	f.ignore();
	getline(f, data);
	while (k != -1)
	{
		// while not sentinel value
		insert(k, data); // insert data into TST
		f >> k; // read next record
		f.ignore();
		getline(f, data);
	}
	f.close();
} // read()

//--------------------------------------------------------------------
//                               height - public
//--------------------------------------------------------------------
// Returns 0 if no root exists
// Calls private height function to count the height
//--------------------------------------------------------------------
int tst::height() const
{
	if (root == nullptr) return 0;
	return height(root);
}

//--------------------------------------------------------------------
//                               height - private
//--------------------------------------------------------------------
// Given node pointer to parent (Initially always root)
// Return height of the tree
//--------------------------------------------------------------------
int tst::height(node* parent) const
{
	// Pop from call stack when last valid node reached
	if (parent == nullptr) return 0;

	const int left_h = height(parent->left);
	const int right_h = height(parent->right);

	if (left_h > right_h) return left_h + 1;

	return right_h + 1;
}

//--------------------------------------------------------------------
//                               count - public
//--------------------------------------------------------------------
// returns the number of nodes in the BST, not including the nodes
// in the equal lists
//--------------------------------------------------------------------
int tst::count() const
{
	if (root == nullptr) return 0;
	int num = 1;
	return count(root, num);
}

//--------------------------------------------------------------------
//                               count - private
//--------------------------------------------------------------------
// Counts the number of nodes without equal nodes
// Given the node parent pointer (root) and num which is the return 
//--------------------------------------------------------------------

int tst::count(node* parent, int& num) const
{
	if (parent == nullptr) return 0;
	count(parent->left, num);
	count(parent->right, num);
	return num++;
}

//--------------------------------------------------------------------
//                               fullCount - public
//--------------------------------------------------------------------
// returns the number of nodes in the entire structure, including the
// nodes in the equal lists.
//--------------------------------------------------------------------

int tst::fullCount() const
{
	if (root == nullptr) return 0;
	int num = 1;
	return fullCount(root, num);
}

//--------------------------------------------------------------------
//                               fullCount - private
//--------------------------------------------------------------------
// Given node pointer (root) and num for a return value
//--------------------------------------------------------------------

int tst::fullCount(node* parent, int& num) const
{
	if (parent == nullptr) return 0;
	fullCount(parent->left, num);
	fullCount(parent->right, num);
	while (parent->equal != nullptr)
	{
		parent = parent->equal;
		num++;
	}
	return num++;
}

//--------------------------------------------------------------------
//                               search - public
//--------------------------------------------------------------------
// given:   a key to search for
// returns: When found: a string with the current data, with the data
//          for any equal nodes appended with a :: between each value.
//          When not found: returns "NOT FOUND"
//--------------------------------------------------------------------
string tst::search(const int k) const
{
	if (root == nullptr) return "NOT FOUND";
	string key_chain = "";
	string key = search(root, k, key_chain);
	// If search returns empty, return NOT FOUND
	if (key_chain == "") return "NOT FOUND";
	return key;
}

//--------------------------------------------------------------------
//                               search - private
//--------------------------------------------------------------------
// given:   a key to search for, node parent pointer, string to acc.
// returns: When found: a string with the current data, with the data
//          for any equal nodes appended with a :: between each value.
//--------------------------------------------------------------------

string tst::search(node* parent, const int key, string& key_chain) const
{
	if (parent == nullptr) return "";
	if (parent->key > key) search(parent->left, key, key_chain);
	if (parent->key < key) search(parent->right, key, key_chain);
	if (key == parent->key)
	{
		key_chain += parent->data + "::";
		while (parent->equal != nullptr) { key_chain += parent->data + "::"; }
	}
	return key_chain;
}
