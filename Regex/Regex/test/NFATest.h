#ifndef NFA_TEST_H
#define NFA_TEST_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include "../NFA.h"
#include "../Matcher.h"
#include "../Replacer.h"


namespace anyun_regex
{
	using std::string;
	using std::regex;
	using std::smatch;
	using std::sregex_iterator;
	using std::regex_replace;
	using std::match_results;
	using std::vector;
	using std::string;
	using std::ifstream;
	using std::shared_ptr;
	using std::setw;
	using std::cout;
	using std::endl;
	using anyun_regex::NFA;

	typedef shared_ptr<NFAMatcher> NFAMatcherPoint;
#ifdef _DEBUG

	void test_nfa_match();
	void test_nfa_group();
	void test_nfa_replace();
	 
	void print_string_format(size_t length, const string &str, char fill_char, bool is_middle= false);

	template<typename NumType>
	void print_number_format(size_t length, NumType num,  bool is_left = false);
	class NFATest
	{
	public:
		NFATest();
		NFATest(const string &pattern);
		NFATest(const string &pattern,const string& test_file_path);
		void set_pattern(const string &pattern);
		void set_testcases(const vector<string> &testcases);
		void set_testcases(const string &test_file_path);
		void set_testcase(const string &testcase);
		void add_testcase(const string &testcase);
		void add_replace_testcase(const string &testcase,const string &replace_str);
		void add_testcases(const vector<string> &testcases);
		void add_testcases(const string &test_file_path);
		void test_match();
		void test_group();
		void test_replace();
	private:
		string pattern;
		regex standard_regex;
		NFA nfa;
		vector<string> testcases;
		vector<string> replaec_strs;

		void read_testcases_from_file(const string &test_file_path);
		void print_test_information();
		bool test_one_match_testcase(const string &testcase);
		bool test_one_group_testcase(const string &testcase);
		bool test_one_replace_testcase(const string &testcase, const string &new_string);
		void print_test_result_information(size_t total_test_count, size_t pass_count, size_t failed_count);
	};

	int singal_test(const string& pattern ,const string &text);
	int test_standard(const string& pattern, const string &text);
#endif // DEBUG
}
#endif // !NFA_TEST_H
