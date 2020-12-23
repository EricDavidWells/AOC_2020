#ifndef helper_functions
#define helper_functions

#include <string>
#include <vector>

using namespace std;

vector<string> input_to_string_vector_delim(string filename, char delim_start, int delim_start_skip, char delim_end, int delim_end_skip);
vector<string> string_split(string line, char delim);
vector<string> string_split(string line, string delim);

#endif