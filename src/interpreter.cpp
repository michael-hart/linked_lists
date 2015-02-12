/**
 *
 * File: interpreter.cpp
 * Author: Michael Hart
 * Date Created: 10/02/2015
 * Description: Given command line arguments, will interpret given commands
 * in a text file and perform these commands on a custom linked list.
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

	// Check for and open the command file
	if (argc != 2) {
		cout << "Program argument data file required. Exiting..." << endl;
		return 0;
	}

	command_handle.open(argv[1]);
	if (!command_handle.is_open()) {
		cout << "Failed to open command file. Exiting..." << endl;
		return 0;
	}

	// Save all non-blank lines to a vector and close file
	while (getline(command_handle, command)) {
		if (command.size()>0 && command[0] != '\r') {
			commands.push_back(command);
		}
	}

	command_handle.close();

	linked_list *data_list = new linked_list();
	int file_number = 0;
	char input_file[20];
	char output_file[20];
	ifstream input_handle;
	ofstream output_handle;
	int file_data_point;

	// Iterate over commands, checking first character to determine the command
	for (size_t i=0; i < commands.size(); i++) {
		switch (commands[i][0]) {
		case 'r':
			// The number following 'r' defines the input/output file names
			sscanf(commands[++i].c_str(), "%d", &file_number);
			snprintf(input_file, 20, "data_%d.txt", file_number);
			snprintf(output_file, 20, "output_%d.txt", file_number);

			// Read all data values from the data input file into list
			input_handle.open(input_file);
			if (!input_handle.is_open()) {
				cout << "Failed to open data file: "<< input_file << endl;
				continue;
			}
			while (input_handle >> file_data_point) {
				data_list->append(file_data_point);
			}
			input_handle.close();
			break;
		case 's':
			// Bubble sort algorithm
			data_list->sort();
			break;
		case 'w':
			// Takes an output path and appends list contents
			data_list->print_list(output_file);
			break;
		case 'i':
			// Insert following number
			sscanf(commands[++i].c_str(), "%d", &file_data_point);
			data_list->insert(file_data_point);
			break;
		case 'd':
			// Delete node containing following number
			sscanf(commands[++i].c_str(), "%d", &file_data_point);
			data_list->remove(file_data_point);
			break;
		case 'e':
			// Append data list length
			output_handle.open(output_file, ios::app);
			if (!output_handle.is_open()) {
				cout << "Failed to open output file: "<< output_file << endl;
				continue;
			}
			output_handle << "Number of elements in the list: " << data_list->length() << endl;
			output_handle.close();
			break;
		case 'm':
			// Append data length minimum
			output_handle.open(output_file, ios::app);
			if (!output_handle.is_open()) {
				cout << "Failed to open output file: "<< output_file << endl;
				continue;
			}
			output_handle << "Minimum value: " << data_list->minimum() << endl;
			output_handle.close();
			break;
		case 'a':
			// Smooth out list according to smoothing algorithm
			data_list->smooth(5);
			break;
		default:
			// Unrecognised commands should be noted and ignored
			cout << "Unrecognised command. Ignoring..." << endl;
			continue;
		}
	}

	// Clean up linked list and return success
	delete data_list;
	return 0;
}

