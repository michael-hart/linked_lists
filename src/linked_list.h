/**
 *
 * File: linked_list.h
 * Author: Michael Hart
 * Date Created: 10/02/2015
 * Description: Defines the functions and classes for a custom linked list.
 *
 */
#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <iostream>
#include <fstream>

using namespace std;

class linked_list {

private:
	class list_node {
	public:
		int data;
		list_node* next;
		list_node(int node_data) {
			data = node_data;
			next = NULL;
		}
	};
	list_node *start;

public:
	linked_list(int data);
	~linked_list();
	void append_data(int data);
	void print_list(string out_path);
	void destroy_list();
};



#endif /* _LINKED_LIST_H_ */
