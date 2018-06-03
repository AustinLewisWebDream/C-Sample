#pragma once
#include "node.h"
#include "iostream"

node::node()
{
	key = 0;
	data = "";
	left = nullptr;
	equal = nullptr;
	right = nullptr;
}

node::~node()
{
	delete left;
	delete equal;
	delete right;
	cout << key << " = " << data << " destroyed" << endl;
}
