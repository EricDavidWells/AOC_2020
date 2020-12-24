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

int main(){


    vector<string> data = input_to_string_vector_delim("../../data/day07input.txt", 0, 0, '\n', 0);

    vector<string> parent_bag_names;
    vector<vector<string>> child_bag_names;
    vector<vector<int>> child_bag_counts; 

    // parse data
    for (int i=0; i<data.size(); i++){
        
        vector<string> lines = string_split(data.at(i), "contain");
        string parent_line = lines.at(0);
        string child_line = lines.at(1);

        int num_sub_bags = count(parent_line.begin(), parent_line.end(),',') + 1;

        // get parent name of line
        char buf1[10];
        char buf2[10];
        sscanf(parent_line.c_str(), "%s %s", buf1, buf2);
        string name = string(buf1) + string(buf2);
        parent_bag_names.push_back(name);

        // get child bag names
        if (child_line.find("no other", 0) == string::npos){
            vector<string> child_lines_split = string_split(child_line, ",");
            vector<string> temp_child_bag_names;
            vector<int> temp_child_bag_counts;
            for (int j=0; j<child_lines_split.size(); j++){

                char buf1[10];
                char buf2[10];
                int val;

                sscanf(child_lines_split.at(j).c_str(), "%d %s %s", &val, buf1, buf2);
                string name = string(buf1) + string(buf2);
                temp_child_bag_names.push_back(name);
                temp_child_bag_counts.push_back(val);
            }

            child_bag_names.push_back(temp_child_bag_names);
            child_bag_counts.push_back(temp_child_bag_counts);
        }
        else {

            vector<string> temp_child_bag_names;
            temp_child_bag_names.push_back("none");
            child_bag_names.push_back(temp_child_bag_names);
            vector<int> temp_child_bag_counts;
            temp_child_bag_counts.push_back(0);
            child_bag_counts.push_back(temp_child_bag_counts);
        }
    }

    // part 1
    vector<string> search_list_pt1;
    vector<string> next_search_list;
    search_list_pt1.push_back("shinygold");

    int k = 0;
    while (k < search_list_pt1.size()){

        
        string search_name = search_list_pt1.at(k);
        k += 1;

        // find all parent bag names of current search child
        for (int i=0; i<child_bag_names.size(); i++){
            vector<string> children = child_bag_names.at(i);
            for (int j=0; j<children.size(); j++){
                string child = children.at(j);
                
                if (child == search_name){
                    next_search_list.push_back(parent_bag_names.at(i));
                }
            }
        }

        // check which parent bag names have been searched before and append to history if not
        int i=0;
        while (i<next_search_list.size()){
                
            if (find(search_list_pt1.begin(), search_list_pt1.end(), next_search_list.at(i)) != search_list_pt1.end()){
                next_search_list.erase(next_search_list.begin() + i);
            }
            else{
                search_list_pt1.push_back(next_search_list.at(i));
                i++;
            }
        }

        next_search_list.clear();
    }

    cout << "number of colors: " << search_list_pt1.size()-1 << endl;

    // part 2

    vector<string> search_list_pt2;
    vector<int> search_list_count;
    search_list_pt2.push_back("shinygold");
    search_list_count.push_back(1);
    int bag_count = 0;

    int i=0;
    while (i < search_list_pt2.size()){
        
        string search_name = search_list_pt2.at(i);

        // find all children names
        for (int j=0; j<child_bag_names.size(); j++){

            string parent = parent_bag_names.at(j);
            vector<string> children = child_bag_names.at(j);
            vector<int> children_count = child_bag_counts.at(j);

            if (parent == search_name){
                for (int k=0; k<children.size(); k++){
                    string child = children.at(k);
                    int count = children_count.at(k); 

                    search_list_pt2.push_back(child);
                    search_list_count.push_back(count*search_list_count.at(i));
                    bag_count += count*search_list_count.at(i);
                }
            }

        }

        i++;

    }

    cout << "number of bags in shiny gold bag: " << bag_count << endl;
    

    return 0;
}


