#include "NFATest.h"

namespace anyun_regex
{
	NFATest::NFATest()
	{
	}

	NFATest::NFATest(const string & pattern) :pattern(pattern), standard_regex(pattern)
	{
	}

	NFATest::NFATest(const string & pattern, const string & test_file_path) : pattern(pattern), standard_regex(pattern)
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

	void NFATest::read_testcases_from_file(const string & test_file_path)
	{

	}

	int singal_test(const string& pattern, const string &text)
	{
		regex standard_regex(pattern);
		NFA nfa(pattern);
		sregex_iterator begin(text.begin(), text.end(), standard_regex);
		sregex_iterator end = std::sregex_iterator();
		nfa.match(text);
		int i = 1;
		for (; begin != end && nfa.find(); begin++)
			std::cout << "test " << i++ << ":" << (*begin).str() << " " << nfa.get_match() << std::endl;
		std::cout << "Test pass?" << (begin == end && !nfa.find() ? "true" : "false") << std::endl;
		return 0;
	}
	int test_standard(const string& pattern, const string &text)
	{
		regex standard_regex(pattern, std::regex_constants::ECMAScript);
		sregex_iterator begin(text.begin(), text.end(), standard_regex);
		sregex_iterator end = std::sregex_iterator();
		int i = 1;
		for (; begin != end ; begin++)
			std::cout <<  i++ << ":" << (*begin).str() << std::endl;
		return 0;
	}
}
