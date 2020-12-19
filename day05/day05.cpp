#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
#include <cmath>

using namespace std;

// function declarations
vector<string> input_to_string_vector_delim(string filename, char delim_start, int delim_start_skip, char delim_end, int delim_end_skip);


int main(){



    vector<string> data = input_to_string_vector_delim("../day05input.txt", 0, 0, '\n', 0);

    int rows [data.size()];
    int cols [data.size()];
    int IDs [data.size()];



    // part 1

    int max_ID;

    for (int i=0; i<data.size(); i++){
        string line = data.at(i);

        string row_info = line.substr(0, 7);
        string col_info = line.substr(7, 3);

        rows[i] = 0;
        cols[i] = 0;

        // calculate row number
        for (int j=0; j<7; j++){
            
            int bin_val = row_info[j] == 'B';

            if (bin_val){
                rows[i] = rows[i] + pow(2, 7-j-1);
            }
        }

        // calculate col number
        for (int j=0; j<3; j++){
            int bin_val = col_info[j] == 'R';

            if (bin_val){
                cols[i] = cols[i] + pow(2, 3-j-1);
            }
        }

        IDs[i] = rows[i]*8 + cols[i];
        max_ID = max(max_ID, IDs[i]);    

    }

    cout << "Max ID: " << max_ID << endl;

    // part 2
    std::vector<int> IDs_vector(IDs, IDs + data.size());
    sort(IDs_vector.begin(), IDs_vector.end());

    int ind = 0;
    for (int i=1; i<data.size(); i++){
        int diff = IDs_vector.at(i) - IDs_vector.at(i-1);
        if (diff > 1){
            ind = i;
        }
        cout << IDs_vector.at(i) << endl;
    } 

    int missing_ID = IDs_vector.at(ind)-1;

    cout << "Missing ID: " << missing_ID;

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