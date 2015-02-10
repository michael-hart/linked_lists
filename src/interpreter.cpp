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

	linked_list *mylist = new linked_list(20);
	mylist->append_data(40);
	mylist->append_data(60);
	mylist->append_data(13);
	mylist->append_data(29);
	mylist->remove_data(60);
	// Length should be 4
	cout << "Length of list is " << mylist->length_list() << endl;
	mylist->print_list("out.txt");
	delete mylist;

	cout << "Added items and attempted to print list. Exiting..." << endl;

	return 0;
}

