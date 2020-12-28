#include "helper_functions.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> input_to_string_vector_delim(string filename, char delim_start, int delim_start_skip, char delim_end, int delim_end_skip){
    // reads advent of code style input into a vector of lines.  included optional deliminator start character, number of start characters to skip
    // deliminator end character, and number of end characters to skip.  This was to pull only certain information out into vectors in a single line
    // however it may be easier to just bring the entire line through and than use sscanf() to read them into variables, since each input is always so different

    // to read into just lines: delim_start = 0, delim_start_skip = 0, delim_end = '\n', delim_end_skip = 0

    ifstream file;
    file.open(filename);

    vector<string> data;

    if (file.is_open()){
        
        string line;

        while(std::getline(file, line)){
            
            int start_ind = 0;

            if (delim_start != 0){
                start_ind = line.find(delim_start, start_ind)+1;
                for (int i=0; i<delim_start_skip; i++){
                    start_ind = line.find(delim_start, start_ind)+1;
                }
            }

            int end_ind = line.find(delim_end);
            for (int i=0; i<delim_end_skip; i++){
                end_ind = line.find(delim_start, start_ind);
            }

            data.push_back(line.substr(start_ind, end_ind-start_ind));
        }
    }
    else {
        cout << "file not opened" << endl;
    }

    return data;
}

vector<string> string_split(string line, char delim){

    // splits a string into vector of substrings based on the delimiter given

    vector<string> data;

    int num_delims = count(line.begin(), line.end(), delim);
    int ind1 = 0;
    int ind2 = 0;
    for (int i=0; i<num_delims; i++){
        ind2 = line.find(delim, ind1);
        data.push_back(line.substr(ind1, ind2-ind1));
        ind1 = ind2;
    }

    return data;
}

vector<string> string_split(string line, string delim){

    vector<string> data;

    int num_delims = 0;
    int ind1 = 0;
    int ind2 = 0;

    while ((ind2 = line.find(delim, ind1)) != string::npos){

        num_delims += 1;
        data.push_back(line.substr(ind1, ind2-ind1));
        ind1 = ind2 + delim.length();

    }
    data.push_back(line.substr(ind1, line.length()-ind1));

    return data;
}

vector<int> find_all_indices(vector<int> data, int key){

    vector<int> indices;

    int ind = 0;
    while (ind < data.size()){
        
        auto itr = std::find(data.begin() + ind, data.end(), key);
        ind = distance(data.begin(), itr);

        if (itr != data.cend()) {
            indices.push_back(ind);
        }
    }

    return indices;
}
