#include "helper_functions.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> input_to_string_vector_delim(string filename, char delim_start, int delim_start_skip, char delim_end, int delim_end_skip){
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
