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

using namespace std;

struct list_node {
	int data;
	list_node* next_node;
};

int main(int argc, char **argv) {

	if (argc != 2) {
		cout << "Program argument data file required. Exiting..." << endl;
		return 0;
	}

	return 0;
}

void append_node(struct list_node start_node, int data) {
	struct list_node current_node = *(start_node.next_node);
	// Traverse linked list until the end
	while (current_node.next_node != NULL) {
		current_node = *(current_node.next_node);
	}

	// current_node points to last node, so create node
	struct list_node new_node;
	new_node.next_node = NULL;
	new_node.data = data;
	current_node.next_node = &new_node;

}
