#include "NFATest.h"

namespace anyun_regex
{
	NFATest::NFATest()
	{
	}

	NFATest::NFATest(const string & pattern)
	{
	}

	NFATest::NFATest(const string & pattern, const string & test_file_path)
	{
	}

	void NFATest::set_pattern(const string & pattern)
	{
	}

	void NFATest::set_testcases(const vector<string>& testcases)
	{
	}

	void NFATest::set_testcases(const string & file_path)
	{
	}

	void NFATest::set_testcase(const string & testcase)
	{
	}

	void NFATest::add_testcase(const string & testcase)
	{
	}

	void NFATest::test()
	{
	}

	int testNFA()
	{
		std::string s =
			"aaabbb";
		std::regex a_b_more("a*b*");
		anyun_regex::NFA nfa("a*b*");
		std::sregex_iterator begin =
			std::sregex_iterator(s.begin(), s.end(), a_b_more);
		std::sregex_iterator end = std::sregex_iterator();
		nfa.match(s);
		int i = 1;
		for (; begin != end && nfa.find(); begin++)
			std::cout << "test " << i++ << ":" << (*begin).str() << " " << nfa.get_match() << std::endl;
		std::cout << "Test pass?" << (begin == end && !nfa.find() ? "true" : "false") << std::endl;
		return 0;
	}
}
