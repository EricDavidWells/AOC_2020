#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
#include <cmath>
#include <numeric>
#include <bitset>
#include <unordered_map>
#include <Eigen/Core>
#include "helper_functions.h"


using namespace std;
using namespace Eigen;

struct rules_struct{
    vector<string> titles;
    vector<vector<int>> ranges;
    vector<int> cols;
};


bool check_validity(vector<int> ticket, rules_struct rules, int &counter);
MatrixXi get_valid_fields(vector<int> ticket, rules_struct rules, MatrixXi &valid_fields);
void search_recursive(vector<vector<int>> &potential_inds_arr, vector<int> &order, int &max_size, int ind);


int main(){

    vector<int> my_ticket;
    vector<vector<int>> tickets;

    rules_struct rules;

    // parse input
    string filename = "../../data/day16input.txt";
    ifstream file;
    file.open(filename);

    if (file.is_open()){
        
        string line;
        getline(file, line);

        while(line != ""){
            
            char buf [20];
            int temp_1, temp_2, temp_3, temp_4;
            sscanf(line.c_str(), "%[^:]: %d-%d %*s %d-%d", buf, &temp_1, &temp_2, &temp_3, &temp_4);

            vector<int> ranges_temp = {temp_1, temp_2, temp_3, temp_4};            
            rules.ranges.push_back(ranges_temp);
            rules.titles.push_back(string(buf));
            rules.cols.push_back(0);
            getline(file, line);

        } ;

        getline(file, line);
        getline(file, line);
        vector<string> my_ticket_temp = string_split(line, ',');
        for (int j=0; j<my_ticket_temp.size(); j++){
            my_ticket.push_back(stoi(my_ticket_temp.at(j)));
        }

        getline(file, line);
        getline(file, line);
        while(getline(file, line)){
            vector<string> ticket_temp = string_split(line, ',');
            vector<int> ticket_temp_i;
            for (int j=0; j<ticket_temp.size(); j++){
                ticket_temp_i.push_back(stoi(ticket_temp.at(j)));
            }
            tickets.push_back(ticket_temp_i);
        }
    }

    vector<vector<int>> valid_tickets;

    int invalid_count = 0;
    for (int i=0; i<tickets.size(); i++){
        vector<int> ticket = tickets.at(i);

        bool valid_ticket_flag = check_validity(ticket, rules, invalid_count);
        if (valid_ticket_flag){
            valid_tickets.push_back(ticket);
        }
    }

    cout << "number obviously invalid: " << invalid_count << endl;

    // part 2

    // create a matrix of booleans indicating which ticket fields are valid for which rules
    // row = value position, column = rule number
    MatrixXi rule_valid_count = MatrixXi::Ones(my_ticket.size(), rules.titles.size());
    for (int i=0; i<valid_tickets.size(); i++){
        get_valid_fields(valid_tickets.at(i), rules, rule_valid_count);
    }

    // convert matrix to valid indices for each rule
    vector<vector<int>> potential_inds_arr;
    for (int j=0; j<rule_valid_count.cols(); j++){
        vector<int> potential_inds;
        for (int i=0; i<rule_valid_count.rows(); i++){

            if (rule_valid_count(i,j) == 1){
                potential_inds.push_back(i);
            }
        }
        potential_inds_arr.push_back(potential_inds);
    }

    vector<int> order;
    int max_size = rule_valid_count.cols();
    cout << max_size << endl;
    search_recursive(potential_inds_arr, order, max_size, 0);

    long long value = 1;
    for (int i=0; i<rules.titles.size(); i++){
        if (rules.titles.at(i).find("departure") != string::npos){
            int ind = order.at(i);
            value *= my_ticket.at(ind);
        }
    }

    cout << "part 2 answer: " << value << endl;
    return 0;
}

bool check_validity(vector<int> ticket, rules_struct rules, int &counter){
    
    bool valid_entry_flag;
    bool valid_ticket_flag = true;

    for (int i=0; i<ticket.size(); i++){
        
        int value = ticket.at(i);
        valid_entry_flag = false;

        for (int j=0; j<rules.ranges.size(); j++){

            vector<int> range = rules.ranges.at(j);

            if ((value >= range.at(0) && value <= range.at(1)) || (value >= range.at(2) && value <= range.at(3))){
                valid_entry_flag = true;
                continue;
            }
            else{
            }

        }

        if (valid_entry_flag == false){
            
            counter += value;
            valid_ticket_flag = false;
        }
    }

    return valid_ticket_flag;
}

MatrixXi get_valid_fields(vector<int> ticket, rules_struct rules, MatrixXi &valid_fields){

    for (int i=0; i<ticket.size(); i++){
        
        int value = ticket.at(i);

        for (int j=0; j<rules.ranges.size(); j++){

            vector<int> range = rules.ranges.at(j);

            if ((value >= range.at(0) && value <= range.at(1)) || (value >= range.at(2) && value <= range.at(3))){
                continue;
            }
            else{
                valid_fields(i, j) = 0;
            }
        }
    }

    return valid_fields;
}

void search_recursive(vector<vector<int>> &potential_inds_arr, vector<int> &order, int &max_size, int ind){

    if (order.size() >= max_size){
        return;
    }
    else{
            
        vector<int> potential_inds = potential_inds_arr.at(ind);
        vector<int> non_repeated_inds;

        for (int j=0; j<potential_inds.size(); j++){ 

            bool repeat_flag = false;
            for (int k=0; k<order.size(); k++){
                
                if (potential_inds.at(j) == order.at(k)){
                    repeat_flag = true;
                }
            }

            if (!repeat_flag){
                non_repeated_inds.push_back(potential_inds.at(j));
            }
        }

        if (non_repeated_inds.size() == 0){
            order.pop_back();
            return;
        }
        else{
            for (int j=0; j<non_repeated_inds.size(); j++){
                order.push_back(non_repeated_inds.at(j));  // add to order
                
                if (order.size() >= max_size){
                    return;
                }
                else{
                    search_recursive(potential_inds_arr, order, max_size, ind+1);  
                }
            }
            order.pop_back();
        }
    }
}