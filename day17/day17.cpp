#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <unordered_map>
#include <Eigen/Core>
#include "helper_functions.h"
#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>

using namespace std;
using namespace Eigen;

template <class T>
void log_matrix(T matrix);
void expand_state(vector<MatrixXi> &state);

int main(){
    
    
    string filename = "../../data/day17input.txt";
    ifstream file;
    file.open(filename);

    MatrixXi initial_slice;
    vector<MatrixXi> state;

    int n = 0;
    int m = 0;
    if (file.is_open()){
        string line;
        while(getline(file, line)){
            
            m = line.length();
            VectorXi slice(m);
            //  = new VectorXi(m);

            for (int i=0; i<line.size(); i++){
                if (line[i] == '.'){
                    slice[i] = 0;
                }
                else if (line[i] == '#'){
                    slice[i] = 1;
                }
            }
            initial_slice.conservativeResize(n+1, m);
            initial_slice.row(n) = slice;
            n++;
        }
    }
    
    // expand by 1 in each direction
    state.push_back(initial_slice);
    expand_state(state);

    log_matrix(state.at(0));
    cout << endl;
    log_matrix(state.at(1));
    cout << endl;
    log_matrix(state.at(2));
    
    // MatrixXi expanded_slice;
    // expanded_slice.conservativeResize(n+2, m+2);
    // expanded_slice.block(1, 1, n, m) = initial_slice;

    // state.emplace(state.begin(), MatrixXi::Zero(n+2, m+2));
    // state.push_back(expanded_slice);
    // state.push_back(MatrixXi::Zero(n+2, m+2));

    int timesteps = 6;
    for (int i=0; i<timesteps; i++){
        // expand
        // count neighbours
        // update state
    }

    // log_matrix(initial_slice);

    return 0;
}

void expand_state(vector<MatrixXi> &state){
    int n = state.at(0).rows();
    int m = state.at(0).cols();

    for (int i=0; i<state.size(); i++){
        MatrixXi expanded_slice = MatrixXi::Zero(n+2, m+2);
        expanded_slice.block(1, 1, n, m) = state.at(i);
        state.at(i) = expanded_slice;
    }

    state.emplace(state.begin(), MatrixXi::Zero(n+2, m+2));
    state.push_back(MatrixXi::Zero(n+2, m+2));

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