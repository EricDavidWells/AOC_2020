#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <unordered_map>
#include "helper_functions.h"
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

template <class T>
void log_matrix(T matrix);

struct Piece{
    
    MatrixXi img;
    vector<vector<int>> valid_neighbours;   // [right, top, left, bottom][neighbour1, neighbour2] = neighbourID
    bool isedge;
    bool iscorner;
};

int main(){
    
    map<int, Piece> pieces;

    string filename = "../../data/day20input_example.txt";
    ifstream file;
    file.open(filename);

    if (file.is_open()){

        string line;
        int ID;
        int ind = 0;
        MatrixXi img(10, 10);

        while (getline(file, line)){
            if (line.substr(0, 4) == "Tile"){
                ID = stoi(line.substr(5, 4));
                ind = 0;
                img.setConstant(0);
            }
            else if (line == ""){
                Piece p;
                p.img = img;
                pieces[ID] = p;
                continue;
            }
            else{
                VectorXi v(line.size());
                for (int i=0; i<line.size(); i++){
                    if (line[i] == '.'){
                        v[i] = 0;
                    }
                    else{
                        v[i] = 1;
                    }
                }
                img.row(ind) = v;
                ind += 1;
            }
        }
    }
    
    map<int, Piece>::iterator it = pieces.begin();
    while (it != pieces.end()){
        cout << it->first << endl;
        log_matrix(it->second.img);
        it++;
    }

    return 0;
}

template <class T>
void log_matrix(T matrix){
    for (int i=0; i<matrix.rows(); i++){
        for (int j=0; j<matrix.cols(); j++){
            cout << matrix(i, j);
        }
        cout << endl;
    }
}
