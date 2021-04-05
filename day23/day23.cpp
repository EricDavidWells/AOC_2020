#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <unordered_map>
#include <cstring>
#include "helper_functions.h"
#include <algorithm>
#include <list>

using namespace std;

int get_destination_value(int start_value, int min_value, int max_value, vector<int> &not_allowed_values);

class Cup
{
public:
	int value;
	Cup* next;

};

Cup* n_cups_forward(Cup* cup, int n) {
	for (int i = 0; i < n; i++) {
		cup = cup->next;
	}
	return cup;
}

void print_cups_from(Cup* cup) {

	Cup* start_cup = cup;
	do{
		cout << cup->value << ",";
		cup = cup->next;
	} while (cup != start_cup);

	cout << endl;
}

int get_destination_value(int start_value, int min_value, int max_value, vector<int>& not_allowed_values) {

	int destination_value = start_value;
	if (destination_value < min_value) {
		destination_value = max_value;
	}

	while (find(not_allowed_values.begin(), not_allowed_values.end(), destination_value) != not_allowed_values.end()) {
		destination_value--;
		if (destination_value < min_value) {
			destination_value = max_value;
		}
	}

	return destination_value;
}

int main(){

	vector<Cup> cups;
	unordered_map<int, Cup*> cup_map;

	cups.reserve(1000000);
	cup_map.reserve(1000000);

	//string input_Str = "389125467";	// example
	string input_Str = "476138259";	// actual

	// part 1

	// initiate cups
	for (char c : input_Str) {
		Cup n;
		n.value = c-48;
		cups.push_back(n);
		cup_map[n.value] = &cups.back();
	}

	// link cups in circular list
	for (int i = 0; i < cups.size()-1; i++) {
		cups[i].next = &cups[i + 1];
	}
	cups.back().next = &cups.front();

	// set starting cup
	Cup* current_cup = &cups[0];

	// loop for 100 iterations
	for (int i = 0; i < 100; i++) {

		// get first cup picked up
		Cup* pickup_cup = current_cup->next;
		vector<int> picked_up_values;
		picked_up_values.push_back(pickup_cup->value);
		picked_up_values.push_back(n_cups_forward(pickup_cup, 1)->value);
		picked_up_values.push_back(n_cups_forward(pickup_cup, 2)->value);

		// get destination cup
		int destination_value = get_destination_value(current_cup->value - 1, 1, cups.size(), picked_up_values);
		Cup* destination_cup = cup_map[destination_value];
		
		// splice lists
		current_cup->next = n_cups_forward(current_cup, 4);
		n_cups_forward(pickup_cup, 2)->next = destination_cup->next;
		destination_cup->next = pickup_cup;
		current_cup = current_cup->next;
	}
	print_cups_from(current_cup);

	// part 2
	cups.clear();
	cup_map.clear();

	for (char c : input_Str) {
		Cup n;
		n.value = c - 48;
		cups.push_back(n);
		cup_map[n.value] = &cups.back();
	}
	for (int i = cups.size(); i < 1000000; i++) {
		Cup n;
		n.value = i+1;
		cups.push_back(n);
		cup_map[n.value] = &cups.back();
	}

	for (int i = 0; i < cups.size() - 1; i++) {
		cups[i].next = &cups[i + 1];
	}
	cups.back().next = &cups.front();

	current_cup = &cups[0];
	for (int i = 0; i < 10000000; i++) {

		// get first cup picked up
		Cup* pickup_cup = current_cup->next;
		vector<int> picked_up_values;
		picked_up_values.push_back(pickup_cup->value);
		picked_up_values.push_back(n_cups_forward(pickup_cup, 1)->value);
		picked_up_values.push_back(n_cups_forward(pickup_cup, 2)->value);

		// get destination cup
		int destination_value = get_destination_value(current_cup->value - 1, 1, cups.size(), picked_up_values);
		Cup* destination_cup = cup_map[destination_value];

		// splice lists
		current_cup->next = n_cups_forward(current_cup, 4);
		n_cups_forward(pickup_cup, 2)->next = destination_cup->next;
		destination_cup->next = pickup_cup;
		current_cup = current_cup->next;

	}
	
	Cup* final_cup_1 = cup_map[1]->next;

	long long answer = (long long) final_cup_1->value * final_cup_1->next->value;
	cout << answer;

	return 0;
}