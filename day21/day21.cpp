#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <unordered_map>
#include "helper_functions.h"
#include <algorithm>

using namespace std;

class Ingredient {
public:
    string name;
    string allergen;
};

class Allergen {
public:
    string name;
    string ingredient;
};

class Food {
public:
    vector<string> ingredients;
    vector<string> allergens;

    void display() {
        log_vector(ingredients, ",");
        cout << "contains: ";
        log_vector(allergens, ",");
        cout << endl;
    }
};

int main(){
    
    map<Ingredient, Allergen> ing_to_allergen_map;

    map<string, vector<vector<string>>> allergen_list;

    vector<Ingredient> ingredients;
    vector<Allergen> allergens;

    //vector<Food> foods;

    string filename = "../../data/day21input_example.txt";
    ifstream file;
    file.open(filename);


    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t ind1 = line.find('(');
            size_t ind2 = line.find("contains");
            size_t ind3 = line.find(')');

            Food food;
            vector<string> ing_list = string_split(line.substr(0, ind1 - 1), ' ');
            vector<string> allergen_list = string_split(line.substr(ind2 + 9, ind3-(ind2 + 9)), ',');

            //(contains dairy, soy)
            //012345678901234567890
            //0         1         2
            //ind1 = 0; ind2 = 1; ind3 = 20;
            //10 ----> 10 long

            for (string ing : ing_list) {
                
                auto it = find_if(ingredients.begin(), ingredients.end(), [ing](Ingredient X) {return X.name == ing; });
                
                if (it == ingredients.end()) {
                    Ingredient new_ing;
                    new_ing.name = ing;
                    ingredients.push_back(new_ing);
                }
            }

            for (string allergen : allergen_list) {

                ltrim(allergen);
                rtrim(allergen);
                auto it = find_if(allergens.begin(), allergens.end(), [allergen](Allergen X) {return X.name == allergen; });

                if (it == allergens.end()) {
                    Allergen new_allergen;
                    new_allergen.name = allergen;
                    allergens.push_back(new_allergen);
                }
            }
        }
    }

   /* for (Food f : foods) {
        f.display();
    }*/

    cout << "Ingredient List:" << endl;
    for (Ingredient i : ingredients) {
        cout << i.name << endl;
    }

    cout << "Allergen List:" << endl;
    for (Allergen a : allergens) {
        cout << a.name << endl;
    }


    /*int ind = 0;
    auto it = allergen_list.begin();

    while (ind < allergen_list.size()) {
        string allergen = it->first;
        vector<vector<string>> ingredient_list = it->second;

        map<string, int> ing_count_map;

        for (int i = 0; i < ingredient_list.size; i++) {
            for (int j = 0; j < ingredient_list.at(i).size(); j++) {
                ing_count_map[ingredient_list.at(i).at(j)] += 1;
            }
        }

        using pair_type = decltype(ing_count_map)::value_type;

        auto pr = std::max_element
        (
            std::begin(ing_count_map), std::end(ing_count_map),
            [](const pair_type& p1, const pair_type& p2) {
            return p1.second < p2.second;
        }
        );

        cout << pr->first << endl;
        it++;*/
    //}

    return 0;
}