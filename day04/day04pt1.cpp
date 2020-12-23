#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

// function declarations
vector<string> input_to_string_vector_delim(string filename, char delim_start, int delim_start_skip, char delim_end, int delim_end_skip);


int main(){

    vector<string> data = input_to_string_vector_delim("../../data/day04input.txt", 0, 0, '\n', 0);

    int valid_passports = 0;

    int len = 8;

    bool flag_list [len];
    int ind_list [len];
    string name_list [len] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};

    for (int i=0; i<data.size(); i++){
        
        string line = data.at(i);
        if (line == ""){
            
            int flag_sum = 0;
            for (int j=0; j<len; j++){
                flag_sum += (flag_list[j] == true);
            }

            if (flag_sum == len || (flag_sum == 7 && flag_list[7] == false)){
                valid_passports += 1;
            }
            
            for (int j=0; j<len; j++){
                flag_list[j] = false;
            }
            continue;
        }

        for (int j=0; j<8; j++){
            ind_list[j] = line.find(name_list[j]);
            if (ind_list[j] != -1){
                flag_list[j] = true;
            }
        }
    }

    cout << "Valid Passports: " << valid_passports;
    return 0;
}

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