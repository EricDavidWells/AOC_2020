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

#include "helper_functions.h"

using namespace std;

struct mask_str {
    bitset<36> onemask = 0;
    bitset<36> zeromask = 0;
    bitset<36> xmask = 0;
};

bitset<36> flip_specific_bits(bitset<36> number, bitset<36> mask, bool value);
void write_memory_recursive(int ind, mask_str &mask, bitset<36> memory_location, bitset<36> memory_value, map<long long, long long> &m);

int main(){
    
    // parse input
    string filename = "../../data/day14input.txt";
    ifstream file;

    vector<mask_str> masks;
    vector<vector<long long>> memory;
    vector<vector<bitset<36>>> values;
    map<long long, long long> m;

    file.open(filename);

    vector<long long> memory_temp;
    vector<bitset<36>> values_temp;
    if (file.is_open()){
        
        string line;

        while(getline(file, line)){
            char action[3];
            sscanf(line.c_str(), "%s ", action);
            
            if (string(action) == "mask"){
                char mask[36];
                sscanf(line.c_str(), "%*s = %s", mask);

                mask_str mask_temp;

                for (int i=0; i<36; i++){
                    if (mask[i] == 'X'){
                        mask_temp.xmask[i] = 1;
                    }
                    else if (mask[i] == '0'){
                        mask_temp.zeromask[i] = 1;
                    }
                    else if (mask[i] == '1'){
                        mask_temp.onemask[i] = 1;
                    }
                }
                masks.push_back(mask_temp);

                if (masks.size() > 1){
                    values.push_back(values_temp);
                    memory.push_back(memory_temp);
                    values_temp.clear();
                    memory_temp.clear();
                }
            }

            if (string(action).find("mem") != string::npos){
                long long mem;
                long long value;
                sscanf(line.c_str(), "mem[%lli] = %lli", &mem, &value);

                values_temp.push_back(value);
                memory_temp.push_back(mem);
            }
        }

        values.push_back(values_temp);
        memory.push_back(memory_temp);
    }
    else {
        cout << "file not opened" << endl;
    }

    // part 1
    for (int i=0; i<masks.size(); i++){
        mask_str mask_temp = masks.at(i);

        for (int j=0; j<memory.at(i).size(); j++){
            bitset<36> value_temp = values.at(i).at(j);
            bitset<36> mem_temp = memory.at(i).at(j);
            value_temp = flip_specific_bits(value_temp, mask_temp.onemask, 1);
            value_temp = flip_specific_bits(value_temp, mask_temp.zeromask, 0);
            
            m[mem_temp.to_ullong()] = value_temp.to_ullong();
        }
    }

    // sum up hash map
    long long sum = 0;
    for (map<long long, long long>::iterator it = m.begin(); it != m.end(); it++){
        sum += it->second;
    }
    cout << "part 1: " << sum << endl;

    // part 2
    m.clear();
    for (int i=0; i<masks.size(); i++){
        mask_str mask_temp = masks.at(i);

        for (int j=0; j<memory.at(i).size(); j++){
            bitset<36> value_temp = values.at(i).at(j);
            bitset<36> mem_temp = memory.at(i).at(j);

            mem_temp = flip_specific_bits(mem_temp, mask_temp.onemask, 1);
            write_memory_recursive(0, mask_temp, mem_temp, value_temp, m);
        }
    }

    // sum up hash map
    sum = 0;
    for (map<long long, long long>::iterator it = m.begin(); it != m.end(); it++){
        sum += it->second;
    }
    cout << "part 2: " << sum << endl;

    return 0;
}

bitset<36> flip_specific_bits(bitset<36> number, bitset<36> mask, bool value){
    // sets all bits specified by 'mask' to 'value' in variable 'number'
    for (int i=0; i<number.size(); i++){
        if (mask[i] == 1){
            number.set(35-i, value);
        }
    }

    return number;
}

void write_memory_recursive(int ind, mask_str &mask, bitset<36> memory_location, bitset<36> memory_value, map<long long, long long> &m){

    // recursively write to hashmap all memory values branching off of original memory value
    // as specified by the "floating bits" in xmask

    if (ind == 36){
        m[memory_location.to_ullong()] = memory_value.to_ullong();
    }
    else{
        write_memory_recursive(ind+1, mask, memory_location, memory_value, m);

        if (mask.xmask[ind] == 1){
            write_memory_recursive(ind+1, mask, memory_location.flip(35-ind), memory_value, m);
        }
    }
}