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

class Displacement {
public:
	int x;
	int y;

	Displacement(int x_, int y_);
};

Displacement::Displacement(int x_=0, int y_=0) {
		x = x_;
		y = y_;
}

class Direction {
public:
	vector<Displacement> steps;
};

void increment_neighbours(map<vector<int>, int> &neighbour_map, vector<int> loc) {
	vector<vector<int>> locs;
	locs.push_back(vector<int>{2 + loc[0], 0 + loc[1]});
	locs.push_back(vector<int>{1 + loc[0], -1 + loc[1]});
	locs.push_back(vector<int>{-1 + loc[0], -1 + loc[1]});
	locs.push_back(vector<int>{-2 + loc[0], 0 + loc[1]});
	locs.push_back(vector<int>{-1 + loc[0], 1 + loc[1]});
	locs.push_back(vector<int>{1 + loc[0], 1 + loc[1]});

	for (vector<int> pos : locs) {
		neighbour_map[pos]++;
	}

	// initiate new black tile in neighbour_map so it gets iterated through
	if (neighbour_map.count(loc) == 0) {
		neighbour_map[loc] = 0;
	}
}

void decrement_neighbours(map<vector<int>, int>& neighbour_map, vector<int> loc) {
	vector<vector<int>> locs;
	locs.push_back(vector<int>{2 + loc[0], 0 + loc[1]});
	locs.push_back(vector<int>{1 + loc[0], -1 + loc[1]});
	locs.push_back(vector<int>{-1 + loc[0], -1 + loc[1]});
	locs.push_back(vector<int>{-2 + loc[0], 0 + loc[1]});
	locs.push_back(vector<int>{-1 + loc[0], 1 + loc[1]});
	locs.push_back(vector<int>{1 + loc[0], 1 + loc[1]});

	for (vector<int> pos : locs) {
		neighbour_map[pos]--;
	}
}


int main() {

	vector<Direction> directions;

	string filename = "../../data/day24input.txt";
	ifstream file;
	file.open(filename);

	Displacement e(2, 0);
	Displacement se(1, -1);
	Displacement sw(-1, -1);
	Displacement w(-2, 0);
	Displacement nw(-1, 1);
	Displacement ne(1, 1);
	map<string, Displacement> direction_to_value{
		{ "e", Displacement(2, 0) },
		{ "se", Displacement(1, -1) },
		{ "sw", Displacement(-1, -1) },
		{ "w",  Displacement(-2, 0) },
		{ "nw", Displacement(-1, 1) },
		{ "ne", Displacement(1, 1) } 
	};

	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			Direction direction;
			int ind = 0;
			while (ind < line.size()) {
				string dir;
				if (line[ind] == 's' || line[ind] == 'n') {
					dir = line.substr(ind, 2);
					ind += 2;
				}
				else {
					dir = line.substr(ind, 1);
					ind += 1;
				}

				auto dis = direction_to_value[dir];
				direction.steps.push_back(dis);
			}
			directions.push_back(direction);
		}
	}
	else {
		cout << "couldn't find file" << endl;
	}

	map<vector<int>, bool> tile_map;
	for (Direction direction : directions) {
		int x = 0;
		int y = 0;
		for (Displacement dis : direction.steps) {
			x += dis.x;
			y += dis.y;
		}
		vector<int> x_y { x, y };
		tile_map[x_y] = !tile_map[x_y];
	}
	
	int sum = 0;
	for (auto& item : tile_map) {
		if (item.second) {
			sum++;
		}
	}

	cout << "part 1: " << sum << endl;


	// part 2
	
	// count initial neighbours
	map<vector<int>, int> neighbour_map;
	for (auto& item : tile_map) {
		if (item.second) {
			increment_neighbours(neighbour_map, item.first);
		}
	}

	for (int i = 0; i < 100; i++) {

		vector<vector<int>> flipped_black;
		vector<vector<int>> flipped_white;

		// flip tiles
		for (auto &item : neighbour_map) {

			bool isblack = tile_map[item.first];
			int n = item.second;

			if (isblack) {
				if (n == 0 || n > 2) {
					tile_map[item.first] = false;
					flipped_white.push_back(item.first);
				}
			}
			else {
				if (n == 2) {
					tile_map[item.first] = true;
					flipped_black.push_back(item.first);
				}
			}
		}

		// adjust neighbours
		for (auto &pos : flipped_black) {
			increment_neighbours(neighbour_map, pos);
		}

		for (auto &pos : flipped_white) {
			decrement_neighbours(neighbour_map, pos);
		}

	}

	// count tiles
	sum = 0;
	for (auto item : tile_map) {
		if (item.second) {
			sum++;
		}
	}
	cout << "number of black tiles: " << sum << endl;
	return 0;
}