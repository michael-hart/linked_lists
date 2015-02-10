/**
 *
 * File: linked_list.h
 * Author: Michael Hart
 * Date Created: 10/02/2015
 * Description: Defines the functions and classes for a custom linked list.
 *
 */

#include "linked_list.h"

linked_list::linked_list() {
	start = NULL;
}

linked_list::~linked_list() {
	list_node *previous, *current;
	if (start == NULL) {
		return;
	}
	if (start->next == NULL) {
		delete start;
	} else {
		previous = start;
		current = start->next;
		while (current != NULL) {
			delete previous;
			previous = current;
			current = current->next;
		}
	}

}

void linked_list::append_data(int data) {
	list_node *current;
	current = start;

	// If list is empty, add as first element
	if (start == NULL) {
		start = new list_node(data);
		return;
	}

	// Traverse to end of list
	while (current->next != NULL) {
		current = current->next;
	}

	// Create node and add
	current->next = new list_node(data);
}

void linked_list::remove_data(int data) {
	list_node *current;
	list_node *previous;
	current = start;

	do {
		if (current->data == data) {
			// Found node to delete
			if (current == start) {
				// Requested delete of start node; special case
				if (this->length_list() == 1) {
					delete start;
					start = NULL;
				} else {
					start = current->next;
					delete current;
				}
			} else {
				// Node is in the list. Previous tracks the previous node.
				previous->next = current->next;
				delete current;
			}
			// If we've deleted data, return as work is done
			return;
		}

		// Traverse list, where previous tracks one node behind current
		previous = current;
		current = current->next;

	} while (current != NULL);

	// No op; if data has not been found, do nothing

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

	if (start == NULL) {
		out_handle << "List is empty" << endl;
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

int linked_list::length_list() {
	if (start == NULL) {
		return 0;
	}
	int current_length = 1;
	list_node *current;
	current = start;
	while (current->next != NULL) {
		current_length++;
		current = current->next;
	}
	return current_length;
}

