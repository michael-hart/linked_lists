/**
 *
 * File: interpreter.cpp
 * Author: Michael Hart
 * Date Created: 10/02/2015
 * Description: Given command line arguments, will interpret given commands
 * in a text file to perform commands on a custom linked list.
 *
 */

#include <iostream>
#include <fstream>
#include "linked_list.h"

using namespace std;

int main(int argc, char **argv) {

//	if (argc != 2) {
//		cout << "Program argument data file required. Exiting..." << endl;
//		return 0;
//	}

	linked_list *mylist = new linked_list();
	// Add 4 data points
	mylist->append(20);
	mylist->append(13);
	mylist->append(31);
	mylist->append(29);
	// Delete start node, a middle node, and a non-existent node
	mylist->remove(20);
	mylist->remove(90);
	mylist->remove(31);
	// Length should be 2
	cout << "Length of list is " << mylist->length() << endl;
	mylist->print_list("out.txt");

	// Delete the rest of the data
	mylist->remove(13);
	mylist->remove(29);
	// Length should be 0
	cout << "Length of list is " << mylist->length() << endl;
	mylist->print_list("out1.txt");

	mylist->insert(10);
	mylist->insert(5);
	mylist->sort();
	mylist->insert(7);
	// Length should be 3
	cout << "Length of list is " << mylist->length() << endl;
	mylist->print_list("out2.txt");

	// Test with larger list contents
	for (int i = 20; i > 0; i-=2) {
		mylist->append(i);
	}
	// Length should be 13
	cout << "Length of list is " << mylist->length() << endl;
	mylist->print_list("out3.txt");
	mylist->sort();
	mylist->print_list("out4.txt");

	delete mylist;

	cout << "Added items and attempted to print list. Exiting..." << endl;

	return 0;
}

