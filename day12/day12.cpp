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

#define PI 3.14159265

using namespace std;

int main(){
    
    // parse input
    string filename = "../../data/day12input.txt";
    ifstream file;

    vector<char> actions;
    vector<int> values;

    file.open(filename);
    if (file.is_open()){
        
        string line;
        while(getline(file, line)){
            
            char action;
            int value;
            sscanf(line.c_str(), "%c%i", &action, &value);

            actions.push_back(action);
            values.push_back(value);
        }
    }
    else {
        cout << "file not opened" << endl;
    }
    
    // part 1
    int direction = 0;
    int xpos = 0;
    int ypos = 0;

    int N = actions.size();
    for (int i=0; i<N; i++){
        char action = actions.at(i);
        int value = values.at(i);

        switch(action){
            case('N'):
                ypos += value;
                break;

            case('S'):
                ypos -= value;
                break;
            
            case('E'):
                xpos += value;
                break;
            
            case('W'):
                xpos -= value;
                break;
            
            case('L'):
                direction += value;
                break;
                
            case('R'):
                direction -= value;
                break;

            case('F'):{

                ypos += round(sin((float)direction/180*PI)) * value;
                xpos += round(cos((float)direction/180*PI)) * value;
                break;
            }



            default:
            cout << "mistake" << endl;
                continue;
        }

        if (direction >= 360){
            direction -= 360;
        }
        else if (direction <= -360){
            direction += 360;
        }
    }
    cout << "manhattan distance pt 1: " << abs(xpos) + abs(ypos) << endl;

    // part 2
    xpos = 0;
    ypos = 0;
    int wp_xpos = 10;
    int wp_ypos = 1;

    for (int i=0; i<N; i++){
        char action = actions.at(i);
        int value = values.at(i);

        switch(action){
            case('N'):
                wp_ypos += value;
                break;

            case('S'):
                wp_ypos -= value;
                break;
            
            case('E'):
                wp_xpos += value;
                break;
            
            case('W'):
                wp_xpos -= value;
                break;
            
            case('L'):{
                float theta = value*PI/180.0;
                int temp1 = (wp_xpos * round(cos(theta)) - wp_ypos * round(sin(theta)));
                int temp2 =  (wp_xpos * round(sin(theta)) + wp_ypos * round(cos(theta)));

                wp_xpos = temp1;
                wp_ypos = temp2;
                break;
            }
                
                
            case('R'):{
                float theta = -value*PI/180.0;
                int temp1 = (wp_xpos * round(cos(theta)) - wp_ypos * round(sin(theta)));
                int temp2 =  (wp_xpos * round(sin(theta)) + wp_ypos * round(cos(theta)));

                wp_xpos = temp1;
                wp_ypos = temp2;
                break;
            }

            case('F'):
                ypos += (wp_ypos) * value;
                xpos += (wp_xpos) * value;
                break;

            default:
                cout << "mistake" << endl;
                continue;
        }
        cout << xpos  << " " << ypos << " " << wp_xpos << " " << wp_ypos << endl;
    }
    cout << "manhattan distance pt 2: " << abs(xpos) + abs(ypos) << endl;

    return 0;
}