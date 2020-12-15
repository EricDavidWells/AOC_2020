#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// function declarations
vector<int> input_to_vector(string filename);

int main(){

    vector<int> data = input_to_vector("/home/rico/Documents/AOC_2020/day01/day01input.txt");
    
    // part 1
    int answer1;
    for (int i=0; i<data.size(); i++){
        
        int num1 = data.at(i);

        for (int j=i+1; j<data.size(); j++){

            int num2 = data.at(j);

            if (num1 + num2 == 2020){
                answer1 = num1 * num2;
            }
        }

    }
    cout << "the answer to part 1 is: " << answer1 << endl;
    
    // part 2
    int answer2;
    for (int i=0; i<data.size(); i++){
        
        int num1 = data.at(i);

        for (int j=i+1; j<data.size(); j++){

            int num2 = data.at(j);

            for (int k=j+1; k<data.size(); k++){
                int num3 = data.at(k);
                if (num1 + num2 + num3 == 2020){
                    answer2 = num1 * num2 * num3;
                }
            }
        }

    }
    cout << "the answer to part 2 is: " << answer2 << endl;


    return 0;
}

vector<int> input_to_vector(string filename){

    ifstream file;
    file.open(filename);
    vector<int> data;

    if (file.is_open()){
        
        string line;
        while(std::getline(file, line)){
  
            data.push_back(stoi(line));
        }
    }
    else {
        cout << "file not opened" << endl;
    }

    return data;
}