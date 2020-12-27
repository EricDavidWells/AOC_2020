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
vector<long long> find_two_sum_brute_force(vector<long long> data, long long answer);
vector<long long> find_contiguous_sum_brute_force(vector<long long> data, long long answer);



int main(){
    
    vector<string> data = input_to_string_vector_delim("../../data/day09input.txt", 0, 0, '\n', 0);
    vector<long long> values;

    for (int i=0; i<data.size(); i++){
        values.push_back(stoll(data.at(i)));
    }

    // part 1
    int broken_index = 0;

    int preamble = 25;
    for (int i=preamble; i<values.size(); i++){

        long long current_number = values.at(i);

        vector<long long> sub_values(values.begin() + i - preamble, values.begin() + i);
        vector<long long> result = find_two_sum_brute_force(sub_values, current_number);

        if (result.at(0) == 0){
            cout << current_number << " " << result.at(1) << " " << result.at(2) << endl;
            broken_index = i;
            break;
        }
    }

    cout << "first broken number: " << values.at(broken_index) << endl;

    // part 2
    vector<long long> result2 = find_contiguous_sum_brute_force(values, values.at(broken_index));
    vector<long long> sub_values(values.begin() + result2.at(1), values.begin() + result2.at(2));
    long long minimum = *min_element(sub_values.begin(), sub_values.end());
    long long maximum = *max_element(sub_values.begin(), sub_values.end());

    cout << "contiguous sum indices: " << result2.at(1) << " " << result2.at(2) << endl;


    cout << "minimum element: " << minimum << " max element: " << maximum << " sum: " << minimum + maximum << endl;


    return 0;
}
        
vector<long long> find_contiguous_sum_brute_force(vector<long long> data, long long answer){

    vector<long long> result(3, 0);

    for (int i=0; i<data.size(); i++){
        int j = i + 1;

        long long sum = 0;

        while (j < data.size() && sum < answer){
            sum = accumulate(data.begin() + i, data.begin() + j, long(0));

            if (sum == answer){
                result.at(0) = 1;
                result.at(1) = i;
                result.at(2) = j;
                return result;
            }
            j++;
        }
    }
    return result;
}
        
vector<long long> find_two_sum_brute_force(vector<long long> data, long long answer){
    
    // return integer array with elements 0 = true or false whether result was found, 1 & 2 = indices of two numbers if found

    vector<long long> result(3, 0);

    for (int i=0; i<data.size(); i++){
        for (int j=i+1; j<data.size(); j++){
            if (data.at(i) + data.at(j) == answer){
                result.at(0) = 1;
                result.at(1) = i;
                result.at(2) = j;
                return result;
            }
        }
    }

    return result;
}