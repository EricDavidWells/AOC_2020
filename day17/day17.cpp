#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <unordered_map>
#include <Eigen/Core>
#include <Eigen/Dense>
#include "helper_functions.h"
#include <Eigen/unsupported/CXX11/Tensor>

using namespace std;
using namespace Eigen;

template <class T>
void log_matrix(T matrix);
void expand_state(vector<MatrixXi> &state);
vector<MatrixXi> count_neighbours(vector<MatrixXi> &state);
void increment_neighbours(vector<MatrixXi> &state, vector<MatrixXi> &neighbours, int i, int j, int k);
void update_states(vector<MatrixXi> &state, vector<MatrixXi> &neighbours);
void count_neighbours_tensor(Tensor<int, 4> &states, Tensor<int, 4> &neighbours);
void increment_neighbours_tensor(Tensor<int, 4> &neighbours, int i, int j, int k, int l);
void update_states_tensor(Tensor<int, 4> &states, Tensor<int, 4> &neighbours);


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
    
    state.push_back(initial_slice);

    // part 1
    int timesteps = 6;
    vector<MatrixXi> neighbours;
    for (int i=0; i<timesteps; i++){
        expand_state(state);
        neighbours = count_neighbours(state);
        update_states(state, neighbours);
    }

    int sum = 0;
    for (int i=0; i<state.size(); i++){
        sum += state.at(i).sum();
    }

    cout << "part 1: active states: " << sum << endl;

    // part 2
    Tensor<int, 4> states4d(23, 23, 23, 23);    // let's allocate more than enough room
    Tensor<int, 4> neighbours4d(23, 23, 23, 23);
    states4d.setConstant(0);
    neighbours4d.setConstant(0);

    Eigen::array<int, 4> offsets{11, 11, 11, 11};
    Eigen::array<int, 4> extents{1, 1, initial_slice.rows(), initial_slice.cols()};

    Tensor<int, 4> initial_tensor(1, 1, initial_slice.rows(), initial_slice.cols());
    for (int i=0; i<initial_slice.rows(); i++){
        for (int j=0; j<initial_slice.cols(); j++){
            initial_tensor(0,0,i,j) = initial_slice(i,j);
        }
    }

    states4d.slice(offsets, extents) = initial_tensor;

    for (int i=0; i<6; i++){
        count_neighbours_tensor(states4d, neighbours4d);
        update_states_tensor(states4d, neighbours4d);
        cout << states4d.sum() << endl;
    }

    cout << "number of active states: " << states4d.sum() << endl;
    return 0;
}

void update_states_tensor(Tensor<int, 4> &states, Tensor<int, 4> &neighbours){
    
    Tensor<int, 4>::Dimensions d = states.dimensions();
    
    for (int i=0; i<d[0]; i++){
        for (int j=0; j<d[1]; j++){
            for (int k=0; k<d[2]; k++){
                for (int l=0; l<d[3]; l++){

                    int state_value = states(i, j, k, l);
                    int neighbour_count = neighbours(i, j, k, l);

                    if (state_value == 1 && (neighbour_count != 2 && neighbour_count != 3)){
                        states(i,j,k,l) = 0;
                    }

                    if (state_value == 0 && neighbour_count == 3){
                        states(i,j,k,l) = 1;
                    }                
                }
            }
        }
    }
}

void count_neighbours_tensor(Tensor<int, 4> &states, Tensor<int, 4> &neighbours){
    
    Tensor<int, 4>::Dimensions d = states.dimensions();
    neighbours.setConstant(0);

    for (int i=0; i<d[0]; i++){
        for (int j=0; j<d[1]; j++){
            for (int k=0; k<d[2]; k++){
                for (int l=0; l<d[3]; l++){
                    if (states(i, j, k, l) == 1){
                        increment_neighbours_tensor(neighbours, i, j, k, l);
                    }
                }
            }
        }
    }
    return;
}

void increment_neighbours_tensor(Tensor<int, 4> &neighbours, int i, int j, int k, int l){

    Tensor<int, 4>::Dimensions d = neighbours.dimensions();
    Tensor<int, 4> ones(d);
    ones.setConstant(0);
    for (int i_=(i-1); i_<=(i+1); i_++){
        for (int j_=(j-1); j_<=(j+1); j_++){
            for (int k_=(k-1); k_<=(k+1); k_++){
                for (int l_= (l-1); l_<=(l+1); l_++){
                    ones(i_, j_, k_, l_) = 1;
                }
            }
        }
    }
    ones(i, j, k, l) = 0;
    neighbours += ones;
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

vector<MatrixXi> count_neighbours(vector<MatrixXi> &state){

    vector<MatrixXi> neighbours;
    for (int i=0; i<state.size(); i++){
        neighbours.push_back(MatrixXi::Zero(state.at(0).rows(), state.at(0).cols()));
    }

    for (int i=0; i<state.size(); i++){

        MatrixXi slice = state.at(i);

        for (int j=0; j<slice.cols(); j++){
            for (int k=0; k<slice.rows(); k++){

                if (slice(k, j) == 1){
                    increment_neighbours(state, neighbours, i, j, k);
                }
            }
        }
    }

    return neighbours;
}

void increment_neighbours(vector<MatrixXi> &state, vector<MatrixXi> &neighbours, int i, int j, int k){
    int x_start = max(0, i-1);
    int x_end = min(i+1, (int)state.size()-1);
    int y_start = max(0, j-1);
    int y_end = min(j+1, (int)state.at(0).cols()-1);
    int z_start = max(0, k-1);
    int z_end = min(k+1, (int)state.at(0).rows()-1);

    for (int ind=x_start; ind<=x_end; ind++){


        MatrixXi ones_slice = MatrixXi::Ones(z_end-z_start+1, y_end-y_start+1);
        MatrixXi slice = neighbours.at(ind).block(z_start, y_start, z_end-z_start+1, y_end-y_start+1);
        
        neighbours.at(ind).block(z_start, y_start, z_end-z_start+1, y_end-y_start+1) = slice + ones_slice;
    
        if (ind == i){
            neighbours.at(ind)(k, j) -= 1;
        }
    }
}

void update_states(vector<MatrixXi> &state, vector<MatrixXi> &neighbours){
    for (int i=0; i<state.size(); i++){
        MatrixXi slice = state.at(i);
        for (int j=0; j<slice.cols(); j++){
            for (int k=0; k<slice.rows(); k++){

                int neighbour_count = neighbours.at(i)(k,j);
                int state_value = state.at(i)(k,j);
                if (state_value == 1){
                    if (neighbour_count >= 2 && neighbour_count <= 3){
                        state.at(i)(k,j) = 1;
                    }
                    else{
                        state.at(i)(k,j) = 0;
                    }
                }

                if (state_value == 0 && neighbour_count == 3){
                    state.at(i)(k,j) = 1;
                }
            }
        }
    }
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