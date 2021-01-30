#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <unordered_map>
#include "helper_functions.h"

using namespace std;

long long evaluate(string equation);
long long evaluate_pt2(string equation);


int main(){
    
    vector<string> lines;

    string filename = "../../data/day18input.txt";
    ifstream file;
    file.open(filename);

    if (file.is_open()){
        string line;
        while(getline(file, line)){
            lines.push_back(line);
        }
    }
    
    // // part 1
    long long sum = 0;
    for (int i=0; i<lines.size(); i++){
        sum += evaluate(lines.at(i));
    }
    cout << "part 1: " << sum << endl;

    // part 2
    sum = 0;
    for (int i=0; i<lines.size(); i++){
        sum += evaluate_pt2(lines.at(i));
    }
    cout << "part 2: " << sum << endl;

    return 0;
}

long long evaluate_pt2(string equation){
    int ind = 0;
    long long result = 0;
    long long newvalue = 0;
    char op = '+';

    if (equation.length() == 1){
        result = stoi(equation.substr(0,1));
        return result;
    }

    while (ind < equation.length()){

        if (op == '*'){
                string subequation = equation.substr(ind, equation.length()-ind);
                newvalue = evaluate_pt2(subequation);
                ind += equation.length()-ind;
            }
        else if (isdigit(equation[ind])){
                newvalue = stoi(equation.substr(ind,1));
        }
        else if (equation[ind] == '('){
            int bracket_count = 0;
            int bracket_ind = ind;
            while (bracket_count < 1){
                bracket_ind += 1;

                if (equation[bracket_ind] == '('){
                    bracket_count -= 1;
                }
                else if (equation[bracket_ind] == ')'){
                    bracket_count += 1;
                }
            }
            string subequation = equation.substr(ind+1, bracket_ind-ind-1);
            newvalue = evaluate_pt2(subequation);
            ind = bracket_ind;
        }

        if (op == '+'){
            result += newvalue;
        }
        else if (op == '*'){
            result *= newvalue;   
        }

        ind += 2;
        op = equation[ind];
        ind += 2;

    }
return result;
}

long long evaluate(string equation){
    
    int ind = 0;
    long long result = 0;
    long long newvalue = 0;
    char op = '+';

    if (equation.length() == 1){
        return stoi(equation.substr(0,1));
    }

    while (ind < equation.length()){

        if (isdigit(equation[ind])){
            newvalue = stoi(equation.substr(ind,1));
        }
        else if (equation[ind] == '('){
            int bracket_count = 0;
            int bracket_ind = ind;
            while (bracket_count < 1){
                bracket_ind += 1;

                if (equation[bracket_ind] == '('){
                    bracket_count -= 1;
                }
                else if (equation[bracket_ind] == ')'){
                    bracket_count += 1;
                }
            }
            string subequation = equation.substr(ind+1, bracket_ind-ind-1);
            newvalue = evaluate(subequation);
            ind = bracket_ind;
        }

        if (op == '+'){
            result += newvalue;
        }
        else if (op == '*'){
            result *= newvalue;   
        }

        ind += 2;
        op = equation[ind];
        ind += 2;

    }

return result;
}