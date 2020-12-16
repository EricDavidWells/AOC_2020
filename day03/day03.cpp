#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// function declarations
vector<string> input_to_string_vector_delim(string filename, char delim_start, int delim_start_skip, char delim_end, int delim_end_skip);

int tree_hit_counter(vector<string> data, int right_increment, int down_increment){
    
    int trees_hit = 0;
    int index = 0;

    for (int i=0; i<data.size(); i+=down_increment){
    
        string line = data.at(i);
        if (line[index] == '#'){
            trees_hit += 1;
        }

    index += right_increment;
    index = index % line.length();
    }
    return  trees_hit;
}

int main(){

    vector<string> data = input_to_string_vector_delim("../day03input.txt", 0, 0, '\n', 0);

    // part 1
    int trees_hit = 0;
    int index = 0;
    int right_increment = 3;
    int down_increment = 1;

    trees_hit = tree_hit_counter(data, right_increment, down_increment);
    cout << "Trees hit: " << trees_hit;

    // part 2


    int len=5;
    int right_slopes [len] = {1, 3, 5, 7, 1};
    int down_slopes [len] = {1, 1, 1, 1, 2};

    int trees_hit_2_total = 1;
    for (int i=0; i<len; i++){
                trees_hit_2_total *= tree_hit_counter(data, right_slopes[i], down_slopes[i]);
    }

    cout << "Trees hit: " << trees_hit_2_total;

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