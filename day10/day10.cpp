#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
#include <cmath>
#include "helper_functions.h"
#include <numeric>

using namespace std;

// function declaration
void count_paths_recursive(vector<vector <int>> &linked_representation, int i, int d, long long &pathCount);
void count_paths_recursive(vector<vector <int>> &linked_representation, long long lookup_table[], int i, int d, long long &pathCount);


int main(){
    
    // parse input
    vector<string> data = input_to_string_vector_delim("../../data/day10input.txt", 0, 0, '\n', 0);
    vector<int> values;
    for (int i=0; i<data.size(); i++){
        values.push_back(stoi(data.at(i)));
    }

    // add max value and zero value to input
    int max_adapter = *max_element(values.begin(), values.end());
    values.push_back(max_adapter + 3);
    values.push_back(0);
    // sort values for easier calculations
    sort(values.begin(), values.end());

    // get difference values
    vector<int> differences;
    int voltage = 0;
    int max_diff = 3;

    for (int i=0; i<values.size(); i++){

        int adapter_value = values.at(i);
        differences.push_back(adapter_value - voltage);
        voltage = adapter_value;
    }

    int num_of_1_diffs = count_if(differences.begin(), differences.end(), [](int i){return i==1;});
    int num_of_3_diffs = count_if(differences.begin(), differences.end(), [](int i){return i==3;});

    cout << "one jolt diffs: " <<  num_of_1_diffs << " three jolt diffs: " << num_of_3_diffs << endl;
    cout << "part 1 answer: " << num_of_1_diffs * num_of_3_diffs << endl;
    
    // part 2, need to get a little graph theory involved

    // construct graph
    vector<vector<int>> linked_representation_graph;
    for (int i=0; i<values.size(); i++){

        vector<int> link_indices;    // hold indices of all next possible nodes accessible from current node;

        int diff_count = 0;
        int j = i+1;

        while (j < values.size()){
            
            diff_count += differences.at(j);

            if (diff_count <= 3){
                link_indices.push_back(j);
            }
            else{
                break;
            }
            j++;
        }

        linked_representation_graph.push_back(link_indices);
    }

    // recursively look through list and count paths 
    long long pathCount = 0;
    long long lookupTable[values.size()] = {0}; 
    count_paths_recursive(linked_representation_graph, lookupTable, 0, values.size()-1, pathCount);

    cout << "part 2 path count: " << pathCount << endl;

    return 0;

}

    void count_paths_recursive(vector<vector <int>> &linked_representation, int i, int d, long long &pathCount){

        // recursive without lookup table, takes forever.........

        if (i == d){
            pathCount++;
        }
        else{

            vector <int> adjacent_nodes = linked_representation.at(i);

            for (int j=0; j<adjacent_nodes.size(); j++){
                count_paths_recursive(linked_representation, adjacent_nodes.at(j), d, pathCount);
            }
        }

        if ((pathCount%1000) == 0){
            cout << pathCount << endl;
        }
    }

    void count_paths_recursive(vector<vector <int>> &linked_representation, long long lookup_table[], int i, int d, long long &pathCount){

        // recursive with lookup table, much more efficient

        if (i == d){
            pathCount++;
        }
        else{

            vector <int> adjacent_nodes = linked_representation.at(i);

            for (int j=0; j<adjacent_nodes.size(); j++){    // for all possible next nodes
                
                int next_node_value = adjacent_nodes.at(j);

                if (lookup_table[next_node_value] != 0){    // check if this calculation has been done before
                    pathCount += lookup_table[next_node_value];     // if it has, add possible paths from this node
                }
                else{
                    long long pathCountLocal = 0;   // create new variable to represent number of possible paths from this node
                    count_paths_recursive(linked_representation, lookup_table, adjacent_nodes.at(j), d, pathCountLocal);

                    lookup_table[next_node_value] = pathCountLocal;     // add value to lookup table
                    pathCount += pathCountLocal;    // add value to total
                }
            }
        }
    }


