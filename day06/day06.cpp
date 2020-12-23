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


    vector<string> data = input_to_string_vector_delim("../../data/day06input.txt", 0, 0, '\n', 0);

    vector<vector<int>> answers; 
    
    vector<int> temp_answers(26, 0);

    vector<int> num_people;
    int people_count = 0;

    for (int i=0; i<data.size(); i++){

        string line = data.at(i);

        if (line != ""){
            people_count += 1;
        }

        for (int j=0; j<line.length(); j++){
            char letter = line[j];
            temp_answers.at(letter-97) += 1;
        }

        if (line == "" || i == data.size()-1){
            answers.push_back(temp_answers);
            num_people.push_back(people_count);

            fill(temp_answers.begin(), temp_answers.end(), 0);
            people_count = 0;
        }
    }

    // part 1
    int num_answers [answers.size()];
    int sum_answers = 0;

    for (int i=0; i<answers.size(); i++){
        vector<int> group = answers.at(i);
        num_answers[i] = count_if(group.begin(), group.end(), [](int j) {return j>0;});
        sum_answers += num_answers[i];
    }

    cout << "The sum of the number of answers of each group is: " << sum_answers << endl;

    // part 2

    int num_answers2 [answers.size()];
    int sum_answers2 = 0;


    for (int i=0; i<answers.size(); i++){
        vector<int> group = answers.at(i);

        int people = num_people.at(i);
        auto func2 = [&people](int j){return j>=people;};

        num_answers2[i] = count_if(group.begin(), group.end(), func2);
        sum_answers2 += num_answers2[i];

    }

    cout << "The sum of the number of unanimous answers from each group is: " << sum_answers2 << endl;

    return 0;
}
