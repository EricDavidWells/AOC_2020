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

#include "helper_functions.h"

using namespace std;

int main(){
    
    // parse input
    unordered_map<int, int> m_count;
    unordered_map<int, int> m_last_time;

    vector <int> input = {1, 20, 11, 6, 12, 0}; // puzzle input

    int num_turns = 30000000;   // change to 2020 for part 1

    m_count.reserve(num_turns);
    m_last_time.reserve(num_turns);

    int i = 0;
    for (i; i<input.size()-1; i++){
        m_count[input.at(i)]++;
        m_last_time[input.at(i)] = i;
    }

    int last_number = input.at(i);

    while (i+1 < num_turns){

        if (i%100000 == 0){
            cout << i << " " << last_number << " " << m_count[last_number] << " " << m_last_time[last_number] << endl;
        }

        int count = m_count[last_number];
        m_count[last_number]++;

        if (count < 1){
            m_last_time[last_number] = i;

            last_number = 0;
        }
        else{
            int time_since_last = i - m_last_time[last_number];
            m_last_time[last_number] = i;
            last_number = time_since_last;
        }

        i++;
    }

    cout << "answer: " << last_number << endl;
    return 0;
}