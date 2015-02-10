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
	mylist->append_data(20);
	mylist->append_data(13);
	mylist->append_data(31);
	mylist->append_data(29);
	// Delete start node, a middle node, and a non-existent node
	mylist->remove_data(20);
	mylist->remove_data(90);
	mylist->remove_data(31);
	// Length should be 2
	cout << "Length of list is " << mylist->length_list() << endl;
	mylist->print_list("out.txt");

	// Delete the rest of the data
	mylist->remove_data(13);
	mylist->remove_data(29);
	// Length should be 0
	cout << "Length of list is " << mylist->length_list() << endl;
	mylist->print_list("out1.txt");

	delete mylist;

	cout << "Added items and attempted to print list. Exiting..." << endl;

	return 0;
}

