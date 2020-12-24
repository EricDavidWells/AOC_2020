#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
#include <cmath>
#include "helper_functions.h"

using namespace std;

// function declaration
vector<int> run_instructions(vector <string> instructions, vector<int> values);

int main(){
    
    vector<string> data = input_to_string_vector_delim("../../data/day08input.txt", 0, 0, '\n', 0);
    vector<string> instructions;
    vector<int> values;

    // parse input
    for (int i=0; i<data.size(); i++){

        string line = data.at(i);

        char buf[10];
        int val;
        sscanf(line.c_str(), "%s %i", buf, &val);

        instructions.push_back(string(buf));
        values.push_back(val);

        // cout << instructions.at(i) << " " << val << endl;
    }

    // part 1
    int accumulator = 0;
    vector<bool> execution_flags(instructions.size(), false);
    vector <int> result = run_instructions(instructions, values);

    cout << "accumulator count: " << result.at(1) << endl;

    // part 2

    int i = 0;
    int flip_index = 0;
    fill(execution_flags.begin(), execution_flags.end(), false);
    vector<bool> flip_flags (instructions.size(), false);
    vector<string> modified_instructions;
    
    modified_instructions = instructions;

    int j=0;
    while (j < instructions.size()){

        if (instructions.at(j) == "nop"){
            modified_instructions.at(j) = "jmp";

            result = run_instructions(modified_instructions, values);

            modified_instructions.at(j) = "nop";
        }
        else if (instructions.at(j) == "jmp"){
            modified_instructions.at(j) = "nop";

            result = run_instructions(modified_instructions, values);

            modified_instructions.at(j) = "jmp";
        }

        if (result.at(0) == 1){
            break;
        }

        j += 1;
    }

    cout << "program success: " << result.at(0) << " accumulator value: " << result.at(1) << endl;
    return 0;
}

vector <int> run_instructions(vector <string> instructions, vector<int> values){
    
    vector<bool> execution_flags(instructions.size(), false);
    int N = instructions.size();

    int accumulator = 0;
    int success_flag = 1;
    int i = 0;

    while (i < N){

        // flag that we have executed the current line
        if (execution_flags.at(i) == true){
            success_flag = 0;
            break;
        }
        else{
            execution_flags.at(i) = true;
        }

        string instruction = instructions.at(i);
        int val = values.at(i);

        if (instruction == "nop"){
            i += 1;
        }
        else if (instruction == "acc"){
            i += 1;
            accumulator += val;
        }
        else if (instruction == "jmp"){
            i += val;
        }
    }

    vector<int> result {success_flag, accumulator};
    return result;
}
        