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

    ifstream file;
    file.open("../day04input.txt");
    string line;

    vector<string> passport_lines;
    string str = "";

    // convert all passports to one string
    while(std::getline(file, line)){
        
        if (line == ""){
            passport_lines.push_back(str);
            str = "";
        }
        
        str += line;
        str += " ";
    }

    int len=8;
    string name_list [len] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};
    int ind_list [len];
    int ind;
    int space_ind;

    for (int i=0; i<passport_lines.size(); i++){
        
        string line = passport_lines.at(i);
        char * char_array = new char [line.length() + 1];
        strcpy(char_array, line.c_str());

        // check birth year

        ind = line.find("byr");
        if (ind == -1){
            continue;
        }
        else{
        
            space_ind = line.find(" ", ind);

            string value_str = line.substr(ind+4, space_ind);
            char * char_array = new char [value_str.length() + 1];
            strcpy(char_array, value_str.c_str());

            int value;
            sscanf(char_array, "%d", &value);

            if (value < 1920 || value > 2002){
                continue
            }
        }




        // for (int j=0; j<len; j++){
        //     ind_list[j] = line.find(name_list[j]);

        //     if (ind_list[j] != -1){
                
        //     }
        // }

        
    }



    // for (int i=0; i<passport_lines.size(); i++){
    //     cout << passport_lines.at(i) << endl;
    // }
    // vector<string> data = input_to_string_vector_delim("../day04input.txt", 0, 0, '\n', 0);

    // int valid_passports = 0;

    // int len = 8;

    // bool flag_list [len];
    // int ind_list [len];
    // string name_list [len] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};

    // for (int i=0; i<data.size(); i++){
        
    //     string line = data.at(i);
    //     if (line == ""){
            
    //         int flag_sum = 0;
    //         for (int j=0; j<len; j++){
    //             flag_sum += (flag_list[j] == true);
    //         }

    //         if (flag_sum == len || (flag_sum == 7 && flag_list[7] == false)){
    //             valid_passports += 1;
    //         }
            
    //         for (int j=0; j<len; j++){
    //             flag_list[j] = false;
    //         }
    //         continue;
    //     }

    //     for (int j=0; j<8; j++){
    //         ind_list[j] = line.find(name_list[j]);
    //         if (ind_list[j] != -1){
    //             flag_list[j] = true;
    //         }
    //     }
    // }

    // cout << "Valid Passports: " << valid_passports;
    // return 0;
}
