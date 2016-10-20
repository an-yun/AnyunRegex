#ifndef NFA_TEST_H
#define NFA_TEST_H
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <regex>
#include "NFA.h"


namespace anyun_regex
{
	using std::string;
	using std::regex;
	using std::smatch;
	using std::sregex_iterator;
	using std::string;
	using std::ifstream;
	using std::cout;
	using std::endl;
	using anyun_regex::NFA;

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
		void test();
	private:
		regex standrad_regex;
	};

	int testNFA();
}
#endif // !NFA_TEST_H
