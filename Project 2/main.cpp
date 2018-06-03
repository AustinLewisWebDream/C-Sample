#include <iostream>
#include <string>
#include "tst.h"

char getOption() {
	string option;
	cout << "\n------ Test Menu ------\n";
	cout << "P. Print\n";
	cout << "R. Read file\n";
	cout << "I. Insert\n";
	cout << "H. Get Height\n";
	cout << "C. Get BST Count\n";
	cout << "F. Get Full Count of all nodes\n";
	cout << "M. Get Max Key\n";
	cout << "S. Search\n";
	cout << "X. Exit\n";
	cout << "===> ";
	cin >> option;
	return toupper(option[0]);
} // getOption()

void doInsert(tst & t) {
	int key;
	string data;
	cout << "Enter key:  ";
	cin >> key;
	cout << "Enter data: ";
	cin.ignore();
	getline(cin, data);
	t.insert(key, data);
} // doInsert()

void doSearch(tst & t) {
	int key;
	cout << "Enter key: ";
	cin >> key;
	cout << t.search(key) << endl << endl;
} // doSearch()

int main() {
	{	tst t;

	char option = '1';
	while (option != 'X') {
		option = getOption();
		switch (option) {
		case 'P': t.print();	break;
		case 'R': t.read();		break;
		case 'I': doInsert(t);  break;
		case 'H': cout << "Current Height = " << t.height() << endl; break;
		case 'C': cout << "Current BST Count = " << t.count() << endl; break;
		case 'F': cout << "Current Full Count = " << t.fullCount() << endl; break;
		case 'M': cout << "Current Max Key = " << t.maxKey() << endl; break;
		case 'S': doSearch(t); break;
		case 'X': break;
		default:  cout << "Invalid option!\n";
		} // switch
	} // while
	} // t's destructor triggered here

	system("pause");
	return 0;
} // main()