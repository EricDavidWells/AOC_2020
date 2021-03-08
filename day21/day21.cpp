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
    bool operator< (const Allergen& other) const {
        return name < other.name;
    }
};

// holds all foods (lines) from the input, with each ingredient pointing at an Ingredient object
// and each allergen pointing at an Allergen object
class Food {
public:
    vector<Ingredient*> ings;
    vector<Allergen*> als;

    void display() {
    
        for (auto ing : ings) {
            cout << ing->name << ",";
        }

        for (auto all : als) {
            cout << all->name << ",";
        }

        cout << endl;
    }
};

vector<Food> foods_containing_allergen(vector<Food>& foods, Allergen& allergen);
void check_foods_for_common_ingredients(vector<Food>& foods, Allergen& allergen);
bool check_if_all_allergens_found(vector<Allergen>& allergens);
int count_nonallergy_ingredients(vector<Food>& foods);


int main(){
    
    vector<Ingredient> ingredients(1000);
    vector<Allergen> allergens(1000);
    vector<Food> foods;

    string filename = "../../data/day21input.txt";
    ifstream file;
    file.open(filename);

    int ing_count = 0;
    int all_count = 0;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t ind1 = line.find('(');
            size_t ind2 = line.find("contains");
            size_t ind3 = line.find(')');

            Food food;
            vector<string> ing_list = string_split(line.substr(0, ind1 - 1), ' ');
            vector<string> allergen_list = string_split(line.substr(ind2 + 9, ind3-(ind2 + 9)), ',');

            for (string ing : ing_list) {
                
                auto it = find_if(ingredients.begin(), ingredients.end(), [ing](Ingredient X) {return X.name == ing; });
                
                if (it == ingredients.end()) {
                    Ingredient new_ing;
                    new_ing.name = ing;
                    ingredients.at(ing_count) = new_ing;

                    food.ings.push_back(&ingredients.at(ing_count));
                    ing_count++;
                }
                else {
                    food.ings.push_back(&(*it));
                }
            }

            for (string allergen : allergen_list) {

                ltrim(allergen);
                rtrim(allergen);
                auto it = find_if(allergens.begin(), allergens.end(), [allergen](Allergen X) {return X.name == allergen; });

                if (it == allergens.end()) {
                    Allergen new_allergen;
                    new_allergen.name = allergen;
                    allergens.at(all_count) = new_allergen;

                    food.als.push_back(&allergens.at(all_count));
                    all_count++;

                }
                else {
                    food.als.push_back(&(*it));
                }
            }

            foods.push_back(food);
        }

        ingredients.erase(ingredients.begin() + ing_count, ingredients.end());
        allergens.erase(allergens.begin() + all_count, allergens.end());
    }

    cout << "Ingredient List:" << endl;
    for (Ingredient i : ingredients) {

        if (!i.name.empty()) {
            cout << i.name << endl;
        }
    }

    cout << "Allergen List:" << endl;
    for (Allergen a : allergens) {
        if (!a.name.empty()) {
            cout << a.name << endl;
        }
    }

    cout << "Food List: " << endl;
    for(auto food:foods) {
        food.display();
    }

    bool all_allergens_found = false;

    while (!all_allergens_found) {
        for (auto &allergen : allergens) {

            if (allergen.ingredient.empty()) {
                vector<Food> sub_foods = foods_containing_allergen(foods, allergen);
                check_foods_for_common_ingredients(sub_foods, allergen);
                all_allergens_found = check_if_all_allergens_found(allergens);
            }

            

            /*cout << "Food list containing allergen: " << allergen.name << endl;
            for (auto food : sub_foods) {
                food.display();
            }*/
        }
    }

    cout << "Part 1 Answer: " << count_nonallergy_ingredients(foods) << endl;

    cout << "All Allergens Found:" << endl;
    sort(allergens.begin(), allergens.end());
    for (auto allergen : allergens) {
        cout << allergen.ingredient << ",";
    }

    return 0;
}

vector<Food> foods_containing_allergen(vector<Food> &foods, Allergen &allergen) {
    
    vector<Food> sub_foods;
    for (auto food : foods) {
        
        if (find(food.als.begin(), food.als.end(), &allergen) != food.als.end()) {
            sub_foods.push_back(food);
        }
    }
    return sub_foods;
}

void check_foods_for_common_ingredients(vector<Food>& foods, Allergen& allergen){

    map<Ingredient*, int> count_map;

    // count number of igredients
    for (auto &food : foods) {
        for (auto ingredient : food.ings) {
            if (ingredient->allergen.empty()) {
                count_map[ingredient] += 1;
            }
        }
    }

    // get max count value
    int max_value = 0;
    for (auto item : count_map) {
        max_value = max(item.second, max_value);
    }

    // make sure there is only one num of maxes
    int num_of_maxes = 0;
    Ingredient* max_ing;

    //auto iter = count_map.begin();
    auto iter = std::find_if(count_map.begin(), count_map.end(), [max_value](pair<Ingredient*, int> x) {return x.second == max_value; });

    while (iter != count_map.end())
    {
        max_ing = iter->first;
        num_of_maxes++;
        iter++;
        iter = std::find_if(iter, count_map.end(), [max_value](pair<Ingredient*, int> x) {return x.second == max_value; });
    }

    if (num_of_maxes > 1) {
        return;
    }
    else {
        allergen.ingredient = max_ing->name;
        max_ing->allergen = allergen.name;
        return;
    }
}

bool check_if_all_allergens_found(vector<Allergen>& allergens) {
    
    for (auto allergen : allergens) {
        if (allergen.ingredient.empty()) {
            return false;
        }
    }
    return true;
}

int count_nonallergy_ingredients(vector<Food>& foods) {

    int count = 0;
    for (auto& food : foods) {
        for (auto ingredient : food.ings) {
            if (ingredient->allergen.empty()) {
                count++;
            }
        }
    }
    return count;
}