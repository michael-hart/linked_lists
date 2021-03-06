/**
 *
 * File: linked_list.cpp
 * Author: Michael Hart
 * Date Created: 10/02/2015
 * Description: Implements custom linked list class defined in linked_list.h
 *
 */

#include "linked_list.h"

// Constructor: Define empty, unsorted list
linked_list::linked_list() {
	start = NULL;
	sorted = false;
}

// Destructor: Destroy each individual node in the list,
// if not empty
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

// append: Iterates to the end of the list and creates a new node
// with the given data
void linked_list::append(int data) {
	list_node *current;
	current = start;
	// We are appending, so we cannot guarantee sorted data
	sorted = false;

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

// insert: Identical to append if the list is unsorted. If sorted, retain ascending
// order by iterating over the list and creating a new node in the correct position
void linked_list::insert(int data) {
	list_node *current, *previous;

	// If list is empty, add as first node
	if (start == NULL) {
		start = new list_node(data);
		return;
	}

	if (!sorted) {
		// If not already sorted, append the data
		append(data);
	} else {
		// If sorted, check for the first node with data larger than the argument
		current = start;
		while (current != NULL) {
			if (current->data > data) {
				// If the first node is larger than the argument, insert at the front
				if (current == start) {
					current = start->next;
					start = new list_node(data);
					start->next = current;
				} else {
					// If in the middle previous must point to new node
					previous->next = new list_node(data);
					previous = previous->next;
					previous->next = current;
				}
				return;
			}

			previous = current;
			current = current->next;
		}
		if (current == NULL) {
			// Looped through without inserting, so the value must be inserted at the end.
			previous->next = new list_node(data);
		}
	}
}

// remove: Searches for the first occurrence of data in the list and deletes that node.
// Note: This retains sorted order if the list has been sorted
void linked_list::remove(int data) {
	list_node *current;
	list_node *previous;
	current = start;

	do {
		if (current->data == data) {
			// Found node to delete
			if (current == start) {
				// Requested delete of start node; special case
				if (this->length() == 1) {
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

// sort: Sort list using bubble sort algorithm. Node pointers must be swapped instead of
// nodes created and deleted.
void linked_list::sort() {
	// Sorting, so we can guarantee sorted data
	sorted = true;
	list_node *current, *previous, *temp;

	// Empty or single item lists are already sorted
	int list_length = length();
	if (list_length < 2) {
		return;
	}

	// Traverse the list length-1 times to ensure sorted, using bubble sort
	for (int i = 0; i < list_length-1; i++) {
		current = start->next;
		previous = start;
		while (current != NULL) {
			if (current->data < previous->data) {
				// Swap nodes
				previous->next = current->next;
				current->next = previous;
				// Check whether the swapped value is now the start
				if (previous == start) {
					start = current;
				} else {
					// List is in the middle, so the element before previous must be set to current
					temp = start;
					while (temp->next != previous) {
						// Traverse list until the node before previous
						temp = temp->next;
					}
					// Set node before previous to point to current, which points to previous
					temp->next = current;
				}

				// Set previous and current to new list positions
				previous = current;
				current = current->next;
			}

			previous = current;
			current = current->next;

		}
	}
}

// print_list: Opens the given output file and appends the list contents, line by line
void linked_list::print_list(string out_path) {

	list_node *current;
	current = start;

	ofstream out_handle;
	out_handle.open(out_path.c_str(), ios::app);
	if (!out_handle.is_open()) {
		cout << "Failed to open file to print list" << endl;
		out_handle.close();
		return;
	}

	if (start == NULL) {
		out_handle.close();
		return;
	}

	while (current != NULL) {
		out_handle << current->data << endl;
		current = current->next;
	}
	out_handle.close();
}

// length: Iterates over list, incrementing a counter. Returns the number of nodes
// in the list
int linked_list::length() {
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

// minimum: iterate over the last and return the smallest data point.
// Note: Undesirable behaviour occurs for an empty list, where 0 is returned
int linked_list::minimum() {
	list_node *current;

	// If list is empty, return 0 for lack of anything better
	if (start==NULL) {
		return 0;
	}
	// If list is sorted or contains one item, the min is the first item
	if (sorted || length() == 1) {
		return start->data;
	} else {
		int minimum = start->data;
		current = start->next;
		while (current != NULL) {
			if (current->data < minimum) {
				minimum = current->data;
			}
			current = current->next;
		}
		return minimum;
	}
}

// smooth: Given max_difference, continuously iterates over the list and inserts
// new nodes containing the average between two consecutive nodes, if those nodes
// contain data larger than max_difference
void linked_list::smooth(int max_difference) {
	list_node *previous, *current;
	int difference = 0;
	bool limit_broken = true;
	while (limit_broken) {
		current = start->next;
		previous = start;
		limit_broken = false;

		while (current != NULL) {
			difference = abs(current->data - previous->data);
			if (difference > max_difference) {
				limit_broken = true;
				previous->next = new list_node( round(difference/2.0) + min(current->data, previous->data) );
				previous = previous->next;
				previous->next = current;
			}

			previous = current;
			current = current->next;
		}

	}
}
