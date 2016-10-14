#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<algorithm>
#include<ctime>
#include<cstring>
#include "string_algorithm.h"

using std::cout;
using std::setw;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::find;
using std::stringstream;

typedef pair<string, string> string_testcase_type;

ostream & operator <<(ostream &out, const position_type &);
void print_position_anwer(const position_type &answer, size_t length);
void print_string_format(size_t length, const string &str, char fill_char, bool is_middle);
void expect_position(const position_type & expect, const position_type & actual, clock_t clock_time, size_t length, const char *ok_message);
void test(const vector<matching_algorithm_information_type> & string_agorighms, const vector<string_testcase_type> &test_cases);
void test(const vector<matching_algorithm_information_type> & string_agorighms, const string &testcase_file);