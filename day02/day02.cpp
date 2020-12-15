#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// function declarations
vector<string> input_to_string_vector_delim(string filename, char delim_start, int delim_start_skip, char delim_end, int delim_end_skip);

int main(){

    vector<string> min_char = input_to_string_vector_delim("/home/rico/Documents/AOC_2020/day02/day02input.txt", 0, 0, '-', 0);
    vector<string> max_char = input_to_string_vector_delim("/home/rico/Documents/AOC_2020/day02/day02input.txt", '-', 0, ' ', 0);
    vector<string> char_list = input_to_string_vector_delim("/home/rico/Documents/AOC_2020/day02/day02input.txt", ' ', 0, ':', 0);
    vector<string> passwords = input_to_string_vector_delim("/home/rico/Documents/AOC_2020/day02/day02input.txt", ' ', 1, '\n', 0);

    // part 1
    int valid_passwords = 0;
    for (int i=0; i<min_char.size(); i++){
        string password = passwords.at(i);
        string current_char = char_list.at(i);

        int num_occur = count(password.begin(), password.end(), char_list.at(i)[0]);
        if (num_occur >= stoi(min_char.at(i)) && num_occur <= stoi(max_char.at(i))){
            valid_passwords += 1;
        } 
    }

    // part 2
    int valid_passwords_2 = 0;
        for (int i=0; i<min_char.size(); i++){
        string password = passwords.at(i);
        string current_char = char_list.at(i);
        int ind_1 = stoi(min_char.at(i))-1;
        int ind_2 = stoi(max_char.at(i))-1;

        int valid_count = 0;
        if (password[ind_1] == char_list.at(i)[0]){
            valid_count += 1;
        }
        if (password[ind_2] == char_list.at(i)[0]){
            valid_count += 1;
        }

        if (valid_count == 1){
            valid_passwords_2 += 1;
        } 
    }

    cout << "Valid Passwords Part 1: " << valid_passwords << endl;
    cout << "Valid Passwords Part 2: " << valid_passwords_2 << endl;

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