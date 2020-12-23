#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "helper_functions.h"

using namespace std;


int main(){

    vector<string> min_char = input_to_string_vector_delim("../../data/day02input.txt", 0, 0, '-', 0);
    vector<string> max_char = input_to_string_vector_delim("../../data/day02input.txt", '-', 0, ' ', 0);
    vector<string> char_list = input_to_string_vector_delim("../../data/day02input.txt", ' ', 0, ':', 0);
    vector<string> passwords = input_to_string_vector_delim("../../data/day02input.txt", ' ', 1, '\n', 0);

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
