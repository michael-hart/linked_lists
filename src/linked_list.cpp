/**
 *
 * File: linked_list.h
 * Author: Michael Hart
 * Date Created: 10/02/2015
 * Description: Defines the functions and classes for a custom linked list.
 *
 */

#include "linked_list.h"

linked_list::linked_list(int data) {
	start = new list_node(data);
}

void linked_list::append_data(int data) {
	list_node *current;
	current = start;
	// Traverse to end of list
	while (current->next != NULL) {
		current = &(*(current->next));
	}

	// Create node and add
	current->next = new list_node(data);
}

void linked_list::print_list(string out_path) {
	list_node *current;
	current = start;

	ofstream out_handle;
	out_handle.open(out_path.c_str());
	if (!out_handle.is_open()) {
		cout << "Failed to open file to print list" << endl;
		out_handle.close();
		return;
	}

	out_handle << "List contents are as follows: " << endl;

	while (current->next != NULL) {
		out_handle << current->data << endl;
		current = current->next;
	}
	out_handle << current->data << endl;
	out_handle << "End list" << endl;
	out_handle.close();
}

linked_list::~linked_list() {
	list_node *previous, *current;
	if (start->next == NULL) {
		delete start;
	} else {
		previous = start;
		current = start->next;
		while (current->next != NULL) {
			delete previous;
			previous = current;
			current = current->next;
		}
		delete current;
	}

}
