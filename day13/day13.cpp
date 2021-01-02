#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
#include <cmath>
#include <numeric>
#include "helper_functions.h"

using namespace std;

long long gcd(long long a, long long b);
long long lcm(long long a, long long b);
long long gcdExtended(long long a, long long b, long long *x, long long *y);

int main(){
    
    // parse input
    string filename = "../../data/day13input.txt";
    ifstream file;

    int departure_time;
    vector <int> busIDs;
    vector <int> desired_offsets;

    file.open(filename);
    if (file.is_open()){
        
        string line;
        getline(file, line);
        sscanf(line.c_str(), "%i", &departure_time);
        
        getline(file, line);
        vector <string> values = string_split(line, ',');

        for (int i=0; i<values.size(); i++){

            if (values.at(i) != "x"){
                busIDs.push_back(stoi(values.at(i)));
                desired_offsets.push_back(i);
            }

        }                   
    }
    else {
        cout << "file not opened" << endl;
    }
    


    vector <int> time_to_next;
    for (int i=0; i<busIDs.size(); i++){
        int busID = busIDs.at(i);

        int next_time = busID - ((departure_time) % busID);
        if (next_time == busID){next_time=0;}

        time_to_next.push_back(busID - ((departure_time) % busID));
    }

    int index = min_element(time_to_next.begin(), time_to_next.end()) - time_to_next.begin();
    cout << "part 1 answer: " << busIDs.at(index) * time_to_next.at(index) << endl;


    // part 2 chinese remainder theorem:
    long long N = 1;
    for (int i=0; i<busIDs.size(); i++){
        N *= busIDs.at(i);
    }

    long long candidate = 0;
    for (int i=0; i<busIDs.size(); i++){
        long long ai = desired_offsets.at(i);
        long long ni = busIDs.at(i);

        long long bi = N/ni;

        long long ri, si;
        long long g = gcdExtended(bi, ni, &si, &ri);

        candidate += (ai*si*bi);
        cout << ai << " " << si << " " << ni << " " << candidate << endl;
    }


    // welp, I have no idea why this works, but modulo starts getting wonky if the candidate is negative
    if (candidate > 0){
        candidate = N - (candidate%N);
    }
    else{
        candidate *= -1;
        candidate %= N;
    }
    cout << "part 2 answer: " << candidate << endl;

    // // part 2 brute force
    // candidate = 0;
    // int ind = 0;
    // long long current_lcm = busIDs.at(0);

    // while (ind < busIDs.size()){


    //     for (int i = ind; i<busIDs.size(); i++){
            
    //         if (candidate % 10000000 == 0){
    //             cout << candidate << endl;
    //         }

    //         long long wait_time = busIDs.at(i) - (candidate % busIDs.at(i));
    //         if (wait_time == busIDs.at(i)){wait_time=0;}

    //         if (wait_time != desired_offsets.at(i)){
                
    //             candidate += current_lcm;
    //             break;
    //         }
    //         else{
    //             current_lcm = lcm(current_lcm, busIDs.at(i+1));
    //             ind = i+1;
    //         }
    //     }
    // }
    // cout << "part 2 answer: " << candidate << endl;

    return 0;
}

long long gcd(long long a, long long b) {
   if (b == 0){return a;}
   return gcd(b, a % b);
}

long long lcm(long long a, long long b)
{
    return (a / gcd(a, b)) * b;
}

long long gcdExtended(long long a, long long b, long long *x, long long *y){  
    // Base Case  
    if (a == 0)  
    {  
        *x = 0;  
        *y = 1;  
        return b;  
    }  
  
    long long x1, y1; // To store results of recursive call  
    long long gcd = gcdExtended(b%a, a, &x1, &y1);  
  
    // Update x and y using results of  
    // recursive call  
    *x = y1 - (b/a) * x1;  
    *y = x1;  
  
    return gcd;  
}