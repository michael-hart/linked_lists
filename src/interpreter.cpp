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
#include <vector>
#include "linked_list.h"

using namespace std;

int main(int argc, char **argv) {
	ifstream command_handle;
	vector<string> commands;
	string command;

	if (argc != 2) {
		cout << "Program argument data file required. Exiting..." << endl;
		return 0;
	}

	command_handle.open(argv[1]);
	if (!command_handle.is_open()) {
		cout << "Failed to open command file. Exiting..." << endl;
		return 0;
	}

	while (!command_handle.eof()) {
		command_handle >> command;
		commands.push_back(command);
	}

	command_handle.close();

	linked_list *mylist = new linked_list();
	int file_number = 0;
	char input_file[20];
	char output_file[20];
	ifstream input_handle;
	ofstream output_handle;
	int file_data_point;

	for (size_t i=0; i < commands.size(); i++) {
		switch (commands[i][0]) {
		case 'r':
			// Input and output require the following number, so read and format strings
			sscanf(commands[++i].c_str(), "%d", &file_number);
			snprintf(input_file, 20, "data_%d.txt", file_number);
			snprintf(output_file, 20, "output_%d.txt", file_number);
			// Read in all data values
			input_handle.open(input_file);
			if (!input_handle.is_open()) {
				cout << "Failed to open data file: "<< input_file << endl;
				continue;
			}
			while (!input_handle.eof()) {
				input_handle >> file_data_point;
				mylist->append(file_data_point);
			}
			input_handle.close();
			break;
		case 's':
			mylist->sort();
			break;
		case 'w':
			mylist->print_list(output_file);
			break;
		case 'i':
			sscanf(commands[++i].c_str(), "%d", &file_data_point);
			mylist->insert(file_data_point);
			break;
		case 'd':
			sscanf(commands[++i].c_str(), "%d", &file_data_point);
			mylist->remove(file_data_point);
			break;
		case 'e':
			output_handle.open(output_file, ios::app);
			if (!output_handle.is_open()) {
				cout << "Failed to open output file: "<< output_file << endl;
				continue;
			}
			output_handle << "Number of elements in the list: " << mylist->length() << endl;
			output_handle.close();
			break;
		case 'm':
			output_handle.open(output_file, ios::app);
			if (!output_handle.is_open()) {
				cout << "Failed to open output file: "<< output_file << endl;
				continue;
			}
			output_handle << "Minimum value: " << mylist->minimum() << endl;
			output_handle.close();
			break;
		case 'a':
			mylist->smooth(5);
			break;
		default:
			cout << "Unrecognised command. Ignoring..." << endl;
			continue;
		}
	}

	delete mylist;

	return 0;
}

