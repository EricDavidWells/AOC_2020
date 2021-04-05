#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <unordered_map>
#include "helper_functions.h"
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

template <class T>
void log_matrix(T matrix) {
    for (int i = 0; i < matrix.rows(); i++) {
        for (int j = 0; j < matrix.cols(); j++) {
            cout << matrix(i, j);
        }
        cout << endl;
    }
}

template <class T>
void log_vector(T vector) {
    for (int i = 0; i < vector.size(); i++) {
        cout << vector(i);
    }
    cout << endl;
}


class Piece {
public:
    int ID = NULL;
    MatrixXi img;
    Piece* neighbours[4] = {};   // top, right, bottom, left
    VectorXi edges[4] = {};
    bool isplaced = false;
    bool iscorner = false;
    bool isalligned = false;
    bool issearched = false;
};

// return -1 for reverse match, 0 for no match, 1 for correct match
int check_edge_match(VectorXi edge1, VectorXi edge2) {

    int match = 1;

    bool forward_match = true;
    for (int i = 0; i < edge1.size(); i++) {
        if (edge1[i] != edge2[i]) {
            forward_match = false;
            break;
        }
    }

    bool backward_match = true;
    for (int i = 0; i < edge1.size(); i++) {
        if (edge1[i] != edge2[edge1.size() - i - 1]) {
            backward_match = false;
            break;
        }
    }

    if (forward_match && backward_match) {
        throw std::runtime_error("matches both forward and backwards, algorithm not gonna work");
        return 1;
    }
    else if (forward_match) {
        return 1;
    }
    else if (backward_match) {
        return -1;
    }
    else {
        return 0;
    }
}

void rotate_matrix(MatrixXi& mat) {

    MatrixXi rotated_mat(mat.cols(), mat.rows());

    int m = mat.rows();
    int n = mat.cols();

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            rotated_mat(j, m - i - 1) = mat(i, j);
        }
    }

    mat = rotated_mat;
}

void flip_matrix(MatrixXi& mat, bool horizontal_axis) {

    MatrixXi flipped_mat(mat.rows(), mat.cols());
    if (horizontal_axis) {
        mat = mat.colwise().reverse().eval();

    }
    else {
        mat = mat.rowwise().reverse().eval();
    }
}

void rotate_piece(Piece& piece, int num_rots) {

    int m = piece.img.rows();
    int n = piece.img.cols();

    for (int k = 0; k < num_rots; k++) {

        // rotate image
        rotate_matrix(piece.img);

        // rotate neighbours
        Piece* temp = piece.neighbours[3];
        for (int i = 3; i > 0; i--) {
           piece.neighbours[i] = piece.neighbours[i - 1];
        }
        piece.neighbours[0] = temp;
    }
}

void flip_piece(Piece& piece, bool horz) {

    // flip image
    flip_matrix(piece.img, horz);

    // flip neighbours
    if (horz) {
        Piece* temp = piece.neighbours[0];
        piece.neighbours[0] = piece.neighbours[2];
        piece.neighbours[2] = temp;
    }
    else {
        Piece* temp = piece.neighbours[1];
        piece.neighbours[1] = piece.neighbours[3];
        piece.neighbours[3] = temp;
    }
}

Piece* find_and_allign_matching_piece(VectorXi edge, Piece& piece, int location, map<int, Piece>& pieces) {

    map<int, Piece>::iterator it = pieces.begin();
    while (it != pieces.end()) {
        
        // skip existing piece
        if (it->second.ID == piece.ID){
            it++;
            continue;
        }

        // check all edges for match
        for (int i = 0; i < 4; i++) {

            VectorXi edge2;
            if (i == 0) {
                edge2 = (it->second).img.row(0);
            }
            else if (i == 1) {
                edge2 = (it->second).img.col((it->second).img.cols() - 1);
            }
            else if (i == 2) {
                edge2 = (it->second).img.row((it->second).img.rows() - 1).reverse();
            }
            else {
                edge2 = (it->second).img.col(0).reverse();
            }

            int check = check_edge_match(edge, edge2);

            // if no match move on
            if (check == 0) {
                continue;
            }

            // if match has been placed already, return it without transforming
            Piece* match = &(it->second);
            if (match->isplaced || match->isalligned) {
                return match;
                continue;
            }

            // if the match is exact, rotate it to correct position and flip it
            if (check == 1) {
                rotate_piece(*match, ((-(i - location) + 2) + 4) % 4);

                if (location % 2 == 0) {
                    flip_piece(*match, false);
                }
                else {
                    flip_piece(*match, true);
                }
                return match;
            }

            // if match is exact opposite, rotate it to correct position
            if (check == -1) {
                rotate_piece(*match, ((-(i - location) + 2) + 4) % 4);
                return match;
            }
        }
        it++;
    }
    return nullptr;
}

void allign_pieces_recursively(Piece* base_piece, map<int, Piece>& pieces) {

    // base case (i.e. looking off the puzzle)
    if (!base_piece) {
        return;
    }

    // if already aligned
    if (base_piece->issearched) {
        return;
    }

    Piece* top_match = nullptr;
    Piece* right_match = nullptr;
    Piece* bottom_match = nullptr;
    Piece* left_match = nullptr;

    if (!base_piece->neighbours[0]) {
        top_match = find_and_allign_matching_piece(base_piece->img.row(0), *base_piece, 0, pieces);
        base_piece->neighbours[0] = top_match;

        if (top_match) {
            top_match->neighbours[2] = base_piece;
            top_match->isalligned = true;
        }
    }

    if (!base_piece->neighbours[1]) {
        right_match = find_and_allign_matching_piece(base_piece->img.col(base_piece->img.cols() - 1), *base_piece, 1, pieces);
        base_piece->neighbours[1] = right_match;

        if (right_match) {
            right_match->neighbours[3] = base_piece;
            right_match->isalligned = true;
        }
    }

    if (!base_piece->neighbours[2]) {
        bottom_match = find_and_allign_matching_piece(base_piece->img.row(base_piece->img.rows() - 1).reverse(), *base_piece, 2, pieces);
        base_piece->neighbours[2] = bottom_match;
        if (bottom_match) {
            bottom_match->neighbours[0] = base_piece;
            bottom_match->isalligned = true;
        }
    }

    if (!base_piece->neighbours[3]) {
        left_match = find_and_allign_matching_piece(base_piece->img.col(0).reverse(), *base_piece, 3, pieces);
        base_piece->neighbours[3] = left_match;
        if (left_match) {
            left_match->neighbours[1] = base_piece;
            left_match->isalligned = true;
        }
    }

    base_piece->isalligned = true;
    base_piece->issearched = true;

    if (count(base_piece->neighbours, base_piece->neighbours + 4, nullptr) == 2) {
        base_piece->iscorner = true;
    }


    allign_pieces_recursively(top_match, pieces);
    allign_pieces_recursively(right_match, pieces);
    allign_pieces_recursively(bottom_match, pieces);
    allign_pieces_recursively(left_match, pieces);

    return;
}

int check_for_sea_monsters(MatrixXi& image, MatrixXi &sea_monster) {

    int n = image.rows();
    int m = image.cols();

    int sea_n = sea_monster.rows();
    int sea_m = sea_monster.cols();

    int count = 0;

    for (int i = 0; i < n - sea_n; i++) {

        for (int j = 0; j < m - sea_m; j++) {

            MatrixXi chunk = image.block(i, j, sea_n, sea_m);

            bool flag = true;
            for (int k = 0; k < chunk.rows(); k++) {
                for (int l = 0; l < chunk.cols(); l++) {
                    if (sea_monster(k, l) == 1 && chunk(k, l) == 0) {
                        flag = false;
                    }
                    else if (sea_monster(k, l) == 1 && chunk(k, l) == 1){
                        chunk(k, l) = 2;
                    }
                }
            }

            if (flag) {
                count++;
                image.block(i, j, sea_n, sea_m) = chunk;
            }

        }

    }

    return count;
}

int main(){
    
    map<int, Piece> pieces;

    string filename = "../../data/day20input.txt";
    ifstream file;
    file.open(filename);

    // load data
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
                p.ID = ID;
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
        Piece p;
        p.img = img;
        p.ID = ID;
        pieces[ID] = p;
    }
    
    auto it = pieces.begin();
    allign_pieces_recursively(&(it->second), pieces);


    Piece* topleftpiece;
    long long sum = 1;
    it = pieces.begin();
    while (it != pieces.end()) {
        if (it->second.iscorner) {
            sum *= it->second.ID;
            if (it->second.neighbours[0] == nullptr && it->second.neighbours[3] == nullptr)
                topleftpiece = &(it->second);
        }
        it++;
    }

    cout << "part 1: " << sum << endl;

    // construct full image
    int N = 8 * (sqrt(pieces.size()));
    MatrixXi image(N, N);
    
    int indx = 0;
    int indy = 0;

    // start from top left, go down till bottom, move to right, go down till bottom, repeat
    Piece* current_base = topleftpiece;
    Piece* current_piece = topleftpiece;
    while (current_base) {
        while (current_piece) {

            // trim edges
            MatrixXi trimmed_piece = current_piece->img.block(1, 1, 8, 8);

            // add to image
            image.block(indx, indy, 8, 8) = trimmed_piece;

            // walk down till we get to the bottom
            current_piece = current_piece->neighbours[2];
            indx += 8;
        }

        // walk current piece to the right
        current_base = current_base->neighbours[1];
        current_piece = current_base;
        indx = 0;
        indy += 8;
    }
    
    // create matrix representing sea monster
    string sea_monster_str[3]{
        {"                  # "},
        {"#    ##    ##    ###"},
        {" #  #  #  #  #  #   "}};

    MatrixXi sea_monster(3, sea_monster_str[0].size());
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < sea_monster_str[i].size(); j++) {
            
            if (sea_monster_str[i][j] == '#') {
                sea_monster(i, j) = 1;
            }
            else {
                sea_monster(i, j) = 0;
            }
        }
    }

    int num_sea_monsters = 0;
    for (int i = 0; i < 4; i++) {

        num_sea_monsters = check_for_sea_monsters(image, sea_monster);
        if (num_sea_monsters > 0) {
            break;
        }

        flip_matrix(image, true);

        num_sea_monsters = check_for_sea_monsters(image, sea_monster);
        if (num_sea_monsters > 0) {
            break;
        }

        flip_matrix(image, true);
        rotate_matrix(image);
    }

    // count unused #'s
    int sum2 = 0;
    for (int i = 0; i < image.rows(); i++) {
        for (int j = 0; j < image.cols(); j++) {
            if (image(i, j) == 1) {
                sum2++;
            }
        }
    }
    cout << "part 2: " << sum2 << endl;

    return 0;
}



