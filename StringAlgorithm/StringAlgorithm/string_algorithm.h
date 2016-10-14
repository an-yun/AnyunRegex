#pragma once
#include<string>
#include<vector>
#include<utility>

using std::string;
using std::pair;
using std::vector;

typedef vector<string::size_type> position_type;
typedef position_type (*string_matching_algorithm_type )(const string&, const string &);
typedef pair<string, string_matching_algorithm_type> matching_algorithm_information_type;


position_type naive_string_mather(const string &T, const string &P);
position_type rabin_karp_matcher(const string &T, const string &P);
position_type finite_automaton_matcher(const string &T, const string &P);
position_type kmp_matcher(const string &T, const string &P);
bool string_match_edge_case(position_type &result, size_t t_size, size_t p_size);
