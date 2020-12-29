#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
#include <cmath>
#include "helper_functions.h"
#include <numeric>

using namespace std;

bool increment_time(vector<vector<int>> &states, vector<vector<int>> &num_adjacent, int max_adjacent);
void increment_adjacents(vector<vector<int>> &states, vector<vector<int>> &num_adjacent, int row, int col);
void count_adjacents(vector<vector<int>> &states, vector<vector<int>> &num_adjacent, void (*increment)
                    (vector<vector<int>> &states, vector<vector<int>> &num_adjacent, int row, int col));
void increment_visual_adjacents(vector<vector<int>> &states, vector<vector<int>> &num_adjacent, int row, int col);

int main(){
    
    // parse input
    vector<string> data = input_to_string_vector_delim("../../data/day11input.txt", 0, 0, '\n', 0);
    
    vector<vector<int>> states;
    for (int i=0; i<data.size(); i++){

        vector<int> row;
        string line = data.at(i);

        for (int j=0; j<line.length(); j++){
            char letter = line[j];
            if (letter == 'L'){
                row.push_back(0);
            }
            else if (letter == '#'){
                row.push_back(1);
            }
            else if (letter == '.'){
                row.push_back(2);
            }
        }

        states.push_back(row);
    }

    // part 1
    vector<vector<int>> num_adjacent(states.size(), vector<int>(states.at(0).size(), 0));

    // cycle until no changes
    bool change_flag = true;
    while (change_flag == true){
        count_adjacents(states, num_adjacent, increment_adjacents);
        change_flag = increment_time(states, num_adjacent, 4);
    }

    // count occupied seats
    int occupied_count = 0;
    for (int i=0; i<states.size(); i++){
        occupied_count += count(states.at(i).begin(), states.at(i).end(), 1);
    }

    cout << "number of occupied seats: " << occupied_count << endl;


    // part 2

    // reset states and adjacent count
    states.clear();
    for (int i=0; i<data.size(); i++){

        vector<int> row;
        string line = data.at(i);

        for (int j=0; j<line.length(); j++){
            char letter = line[j];
            if (letter == 'L'){
                row.push_back(0);
            }
            else if (letter == '#'){
                row.push_back(1);
            }
            else if (letter == '.'){
                row.push_back(2);
            }
        }
        states.push_back(row);
    }
    num_adjacent = vector<vector<int>>(states.size(), vector<int>(states.at(0).size(), 0)); // reset adjacents

    // cycle until no changes
    change_flag = true;
    while (change_flag == true){
        count_adjacents(states, num_adjacent, increment_visual_adjacents);
        change_flag = increment_time(states, num_adjacent, 5);
    }

    // count occupied seats
    occupied_count = 0;
    for (int i=0; i<states.size(); i++){
        occupied_count += count(states.at(i).begin(), states.at(i).end(), 1);
    }

    cout << "number of occupied seats: " << occupied_count << endl;

    return 0;
}

bool increment_time(vector<vector<int>> &states, vector<vector<int>> &num_adjacent, int max_adjacent){
    
    bool change_flag = false;
    // adjust states based on num_adjacent values and maximum allowable adjacent values
    for (int i=0; i<states.size(); i++){
        vector<int> state_row = states.at(i);
        vector<int> num_adjacent_row = num_adjacent.at(i);

        for (int j=0; j<state_row.size(); j++){
            int value = state_row.at(j);
            int num_adjacent_value = num_adjacent_row.at(j);

            if (value == 2){
                continue;
            }
            else if (value == 0 && num_adjacent_value == 0){
                states.at(i).at(j) = 1;
                change_flag = true;    
            }
            else if (value == 1 && num_adjacent_value >= max_adjacent){
                states.at(i).at(j) = 0;
                change_flag = true;
            }            
        }
    }

    return change_flag;
}

void count_adjacents(vector<vector<int>> &states, vector<vector<int>> &num_adjacent, void (*increment)
                    (vector<vector<int>> &states, vector<vector<int>> &num_adjacent, int row, int col)){
    
    num_adjacent = vector<vector<int>>(states.size(), vector<int>(states.at(0).size(), 0)); // reset adjacents
    // increment all adjacent seats
    for (int i=0; i<states.size(); i++){
        vector<int> state_row = states.at(i);
        vector<int> num_adjacent_row = num_adjacent.at(i);

        for (int j=0; j<state_row.size(); j++){
            int value = state_row.at(j);

            if (value == 2 || value == 0){
                continue;
            }
            else if (value == 1){
                // increment nearby values
                (*increment)(states, num_adjacent, i, j);
            }
        }
    }
}

void increment_adjacents(vector<vector<int>> &states, vector<vector<int>> &num_adjacent, int row, int col){

    int start_row = max(0, row-1);
    int end_row = min((int)states.size()-1, row+1);
    int start_col = max(0, col-1);
    int end_col = min((int)states.at(0).size()-1, col+1);

    for (int i=start_row; i<=end_row; i++){
        for (int j=start_col; j<=end_col; j++){
            
            if (i == row && j == col){
                continue;
            }
            num_adjacent.at(i).at(j) += 1;
        }
    }
}

void increment_visual_adjacents(vector<vector<int>> &states, vector<vector<int>> &num_adjacent, int row, int col){

    int start_row = max(0, row-1);
    int end_row = min((int)states.size()-1, row+1);
    int start_col = max(0, col-1);
    int end_col = min((int)states.at(0).size()-1, col+1);

    for (int i=start_row; i<=end_row; i++){
        for (int j=start_col; j<=end_col; j++){
            
            if (i == row && j == col){
                continue;
            }
            
            bool vision_impact = false;
            int vision_x = 0;
            int vision_y = 0;
            while (vision_impact != true){
                // cout << row << " " << col << " " << i << " " << j << " " << vision_y<< " " << vision_x << endl;

                if (states.at(i + vision_y).at(j + vision_x) < 2){
                    num_adjacent.at(i + vision_y).at(j + vision_x) += 1;
                    vision_impact = true;
                }
                else{
                    vision_x += (j - col);
                    vision_y += (i - row);


                    if ((j + vision_x) < 0 || (j + vision_x) >= states.at(0).size()){
                        vision_impact = true;
                    }
                    else if ((i + vision_y) < 0 || (i + vision_y) >= states.size()){
                        vision_impact = true;
                    }
                }
            }
        }
    }
}