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
string get_value_string_from_line(string line, string label);


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
    passport_lines.push_back(str);

    int valid_passports = 0;

    for (int i=0; i<passport_lines.size(); i++){
        
        string line = passport_lines.at(i);

        string birth_value = get_value_string_from_line(line, "byr");
        string issue_value = get_value_string_from_line(line, "iyr");
        string expiration_value = get_value_string_from_line(line, "eyr");
        string height_value = get_value_string_from_line(line, "hgt");
        string hair_value = get_value_string_from_line(line, "hcl");
        string eye_value = get_value_string_from_line(line, "ecl");
        string PID_value = get_value_string_from_line(line, "pid");

        // cout << birth_value << " " << issue_value << " " << expiration_value << " " << height_value << " " << hair_value << " " << eye_value << " " << PID_value << endl;

        // check birth year
        if (birth_value == ""){
            continue;
        }
        else if (stoi(birth_value) < 1920 || stoi(birth_value) > 2002){
            continue;
        }

        // check issue year
        if (issue_value == ""){
            continue;
        }
        else if (stoi(issue_value) < 2010 || stoi(issue_value) > 2020){
            continue;
        }

        //check expiration year
        if (expiration_value == ""){
            continue;
        }
        else if (stoi(expiration_value) < 2020 || stoi(expiration_value) > 2030){
            continue;
        }

        //check height
        if (height_value == ""){
            continue;
        }
        else{
            int cm_ind = height_value.find("cm");
            int inch_ind = height_value.find("in");

            if (cm_ind >= 0){
                int cm_value = stoi(height_value.substr(0, cm_ind));
                if (cm_value < 150 || cm_value > 193){
                    // cout << line << "      " << "cm: " << cm_value << endl;
                    continue;
                }
            }
            else{
                int in_value = stoi(height_value.substr(0, inch_ind));

                if (in_value < 59 || in_value > 76){
                    // cout << line << "      " << "in: " << in_value << endl;
                    continue;
                }
            }
        }   

        // check hair color
        if (hair_value[0] != '#'){
            // cout << line << "      " << "hcl: " << hair_value << endl;
            continue;
        }
        else if (hair_value.length() != 7){
            continue;
        }
        else{
            bool hair_flag = true;
            for (int j=1; j<hair_value.length(); j++){
                if (hair_value[j] < 48 || (hair_value[j] > 57 && hair_value[j] < 97) || hair_value[j] > 102){

                    hair_flag = false;
                }
            }
            if (hair_flag == false){
                continue;
            }
        }

        // check eye color
        string matching_eye_colors [7] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        bool eye_flag = false;
        for (int j=0; j<7; j++){
            if (eye_value == matching_eye_colors[j]){
                eye_flag = true;
            }
        }
        if (eye_flag == false){
            continue;
        }
        // check passport ID
        if (PID_value.length() != 9){
            continue;
        }
        else{

            bool PID_flag = false;
            for (int j=0; j<9; j++){
                if (PID_value[j] < 48 | PID_value[j] > 57){
                    PID_flag = true;
                }
            }
            if (PID_flag == true){
                cout << "fk";
                continue;
            }
        }

        valid_passports += 1;
    }

    cout << "Valid Passports: " << valid_passports;
}

string get_value_string_from_line(string line, string label){
    
        int ind = line.find(label);
        if (ind == -1){
            return "";
        }
        else{
            int space_ind = line.find(" ", ind);

            return line.substr(ind+4, space_ind - (ind+4));
        }
}