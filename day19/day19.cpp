#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <unordered_map>
#include "helper_functions.h"

using namespace std;

struct node{
    bool is_leaf;
    char val;
    vector<vector<string>> rules;
};

bool traverse_tree(string rule, map<string, node> &tree, string &message, int &ind);
void count_tree(string rule, map<string, node> &tree, int &sum);

int main(){
    
    map<string, node> rule_tree;
    vector<string> messages;

    string filename = "../../data/day19input.txt";
    ifstream file;
    file.open(filename);

    if (file.is_open()){
        string line;
        getline(file, line);
        while(line != ""){
            int ind = line.find(':');
            string rulenum = line.substr(0, ind);

            node n;
            if (line.find('"') != string::npos){
                n.is_leaf = true;
                n.val = line[line.find('"')+1];
            }
            else{
                n.is_leaf = false;
                vector<string> rules = string_split(line.substr(ind+2, line.length()-(ind+2)), " | ");
                for (int i=0; i<rules.size(); i++){
                    n.rules.push_back(string_split(rules.at(i), ' '));
                }
            }

            rule_tree[rulenum] = n;
            getline(file, line);
        }

        while (getline(file, line)){
            messages.push_back(line);
        }
    }

    // map<string, node>::iterator it = rule_tree.begin();
    // while (it != rule_tree.end()){
    //     cout << it->first << ": ";
    //     if (it->second.is_leaf){
    //         cout << it->second.val << endl;
    //     }
    //     else{
    //         log_vector(it->second.rules, ",", "|");
    //         cout<<endl;
    //     }
    //     it++;
    // }

    // part 1
    int sum = 0;
    for (int i=0; i<messages.size(); i++){
        int ind = 0;

        bool is_true = traverse_tree("0", rule_tree, messages.at(i), ind);
        if (is_true){
            sum ++;
        }
    }
    cout << "part 1: " << sum << endl;

    // part 2
    int counter = 0;
    count_tree("42", rule_tree, counter);
    int length42 = counter;
    counter = 0;
    count_tree("31", rule_tree, counter);
    int length31 = counter;

    sum = 0;
    for (int i=0; i<messages.size(); i++){
        
        // check last section matches rule 31
        int ind31 = messages.at(i).length()-length31;
        int tree_ind = 0;
        string message_substr = messages.at(i).substr(ind31, length31);
        bool is_true_31 = traverse_tree("31", rule_tree, message_substr, tree_ind);

        if (!is_true_31){
            continue;
        }
        ind31 -= length31;
        int counter31 = 1;

        // find how many adjacent sections from end match rule 31
        while(is_true_31 && ind31 >= 0){
            message_substr = messages.at(i).substr(ind31, length31);
            tree_ind = 0;
            is_true_31 = traverse_tree("31", rule_tree, message_substr, tree_ind);

            if (is_true_31){
                counter31++;
                ind31 -= length31;
            }
        }

        // find how many adjacent sections match rule 42
        int ind42 = ind31 + length31 - length42;
        bool is_true_42 = true;
        int counter42 = 0;

        while(is_true_42 && ind42 >= 0){
            message_substr = messages.at(i).substr(ind42, length42);
            tree_ind = 0;
            is_true_42 = traverse_tree("42", rule_tree, message_substr, tree_ind);

            if (is_true_42){
                counter42++;
                ind42 -= length42;
            }
        }

        // ensure that rule 11 is followed, number of matches for 31 must not be greater than or equal to matches for 42
        // also ensure we ended at the beginning of the message
        if (counter42 > counter31 && (ind42 + length42) == 0){
            sum++;
        }
    }

    cout << "part 2: " << sum << endl;
    return 0;
}

bool traverse_tree(string rule, map<string, node> &tree, string &message, int &ind){
    
    node n = tree[rule];
    bool is_true = false;

    if (n.is_leaf){
        is_true = message[ind] == n.val;
        if (is_true){
            ind++;
        }
    }
    else{
        int save_ind = ind;
        for (int i=0; i<n.rules.size(); i++){
            ind = save_ind;
            is_true = false;
            for (int j=0; j<n.rules.at(i).size(); j++){
                is_true = traverse_tree(n.rules.at(i).at(j), tree, message, ind);

                if (!is_true){
                    break;
                }
            }
            if (is_true){
                break;
            }
        }
    }
    
    if (rule == "0" && ind < message.length()){
        is_true = false;
    }

    return is_true;


}

void count_tree(string rule, map<string, node> &tree, int &sum){

    node n = tree[rule];

    if (n.is_leaf){
        sum++;
    }
    else{
        for (int i=0; i<n.rules.at(0).size(); i++){
                count_tree(n.rules.at(0).at(i), tree, sum);
        }
    }
}
