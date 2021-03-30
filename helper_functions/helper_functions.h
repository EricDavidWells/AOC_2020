#ifndef helper_functions
#define helper_functions

#include <string>
#include <vector>
// #include "helper_functions.cpp"

using namespace std;

vector<string> input_to_string_vector_delim(string filename, char delim_start, int delim_start_skip, char delim_end, int delim_end_skip);
vector<string> string_split(string line, char delim);
vector<string> string_split(string line, string delim);
vector<int> find_all_indices(vector<int> data, int key);
template<class T> void log_vector(vector<T> data, string delim1 = "\n");
template<class T> void log_vector(vector<vector<T>> data, string delim1 = "\n", string delim2 = "");
void ltrim(std::string& s);
void rtrim(std::string& s);
void trim(std::string& s);

// void log_vector(vector<int> data, string delimiter);
// void log_vector(vector<vector<int>> data, string delimiter);
// void log_vector(vector<int> data);


#endif