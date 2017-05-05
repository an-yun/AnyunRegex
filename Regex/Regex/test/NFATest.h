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
#include "../DirectedGraph.h"
#include "../NFA.h"
#include "../Matcher.h"
#include "../Replacer.h"
#include <boost/regex.hpp>
#include <boost/timer/timer.hpp>

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

#define Println(content) \
	cout<<content<<endl;
#ifdef _DEBUG
	void test_nfa_match();
	void test_nfa_search();
	void test_nfa_escape();
	void test_nfa_group();
	void test_nfa_replace();
	void test_nfa_capture();
	void test_lazy_match();
	void test_zero_length_assertions();
	void print_string_format(size_t length, const string &str, char fill_char, bool is_middle= false);

	template<typename NumType>
	void print_number_format(size_t length, NumType num,  bool is_left = false);
	class NFATest
	{
	public:
		NFATest();
		NFATest(const string &pattern);
		NFATest(const string &pattern,const string& test_file_path);
		void set_pattern(const string &pattern, bool no_std_regex = false);
		void set_testcases(const vector<string> &testcases);
		void set_testcases(const string &test_file_path);
		void set_testcase(const string &testcase);
		void add_testcase(const string &testcase);
		void add_replace_testcase(const string &testcase,const string &replace_str);
		void add_testcases(const vector<string> &testcases);
		void add_testcases(const string &test_file_path);
		void test_match();
		void test_search();
		void test_group();
		void test_replace();
		void test_group_capture();
		void test_single_group_capture();
		void test_lazy_match_can_none();
		void test_lazy_match_zero_more();
		void test_lazy_match_one_more();
		void test_lazy_match_repeat_count();
		void test_pla_zero_length_assertions();
		void test_nla_zero_length_assertions();
	private:
		string pattern;
		regex standard_regex;
		NFA nfa;
		vector<string> testcases;
		vector<string> replaec_strs;

		void read_testcases_from_file(const string &test_file_path);
		void print_test_information();
		bool test_one_match_testcase(const string &testcase);
		bool test_one_search_testcase(const string &testcase);
		bool test_one_group_testcase(const string &testcase);
		bool test_one_replace_testcase(const string &testcase, const string &new_string);
		bool test_one_capture_testcase(const string &testcase, const string &group_name);
		void print_test_result_information(size_t total_test_count, size_t pass_count, size_t failed_count);
	};

	int singal_test(const string& pattern ,const string &text);
	int test_standard(const string& pattern, const string &text);
#endif // DEBUG
}
#endif // !NFA_TEST_H
