#include "NFATest.h"

namespace anyun_regex
{
	NFATest::NFATest()
	{
	}

	NFATest::NFATest(const string & pattern) :pattern(pattern), standard_regex(pattern),nfa(pattern)
	{
	}

	NFATest::NFATest(const string & pattern, const string & test_file_path) : pattern(pattern), standard_regex(pattern),nfa(pattern)
	{
		read_testcases_from_file(test_file_path);
	}

	void NFATest::set_pattern(const string & pattern)
	{
		this->pattern = pattern;
		standard_regex = regex(pattern);
		nfa = NFA(pattern);
	}

	void NFATest::set_testcases(const vector<string>& testcases)
	{
		this->testcases = testcases;
	}

	void NFATest::set_testcases(const string & file_path)
	{
		this->testcases.clear();
		read_testcases_from_file(file_path);
	}

	void NFATest::set_testcase(const string & testcase)
	{
		testcases.clear();
		testcases.push_back(testcase);
	}

	void NFATest::add_testcase(const string & testcase)
	{
		testcases.push_back(testcase);
	}

	void NFATest::add_testcases(const vector<string>& testcases)
	{
		std::copy(testcases.begin(), testcases.end(), std::back_inserter(this->testcases));
	}

	void NFATest::add_testcases(const string & test_file_path)
	{
		read_testcases_from_file(test_file_path);
	}



	void NFATest::read_testcases_from_file(const string & test_file_path)
	{
		std::ifstream input(test_file_path);
		if (input.bad())
		{
			std::cout << test_file_path << " file error!" << std::endl;
			return ;
		}
		string line;
		while (input >> line)testcases.push_back(line);
		input.close();
	}


	void NFATest::test()
	{
		cout << "------------------------begein test--------------------" << endl;
		print_test_information();
		size_t testcase_size = testcases.size();
		size_t pass_count = 0, failed_count = 0;
		for (size_t i = 0; i < testcase_size; i++)
		{
			if (test_one_testcase(testcases[i]))pass_count++;
			else failed_count++;
		}
		print_test_result_information(testcase_size, pass_count, failed_count);
		cout << "--------------------------end test---------------------" << endl;


	}
	void NFATest::print_test_information()
	{
		//to do
	}

	bool NFATest::test_one_testcase(const string & testcase)
	{
		//to do 
		return false;
	}

	void NFATest::print_test_result_information(size_t total_test_count, size_t pass_count, size_t failed_count)
	{
		//to do
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
		for (; begin != end; begin++)
			std::cout << i++ << ":" << (*begin).str() << std::endl;
		return 0;
	}
}
