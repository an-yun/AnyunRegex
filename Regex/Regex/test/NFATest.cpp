#include "NFATest.h"

namespace anyun_regex
{
#ifdef _DEBUG
	
	void test_nfa_match()
	{
		cout << endl;
		print_string_format(80, "Test class NFA and NFAMatcher ", '-', true);
		cout << endl;
		NFATest nfa_test;
		nfa_test.set_pattern("");
		nfa_test.add_testcase("1a");
		nfa_test.add_testcase("1234");
		nfa_test.add_testcase("1b");
		nfa_test.add_testcase("4a");
		nfa_test.add_testcase("!@#");
		nfa_test.add_testcase("2abb");
		nfa_test.add_testcase("23abb");
		nfa_test.add_testcase("c23abcb");
		nfa_test.add_testcase("1c23abcb");
		nfa_test.add_testcase("1ab2ab3abbb");
		nfa_test.add_testcase("1)*&^$3b3abbb");
		nfa_test.test_match();

		nfa_test.set_pattern(".*");
		nfa_test.add_testcase("1b");
		nfa_test.add_testcase("4a");
		nfa_test.add_testcase("Mayflies, also known as shadflies or fishflies in Canada");
		nfa_test.add_testcase(".cc .cpp .cxx .C .c++ .h .hh .hpp .hxx .h++");
		nfa_test.add_testcase("are aquatic insects belonging to the order Ephemeroptera");
		nfa_test.add_testcase("Immature mayflies are aquatic");
		nfa_test.add_testcase("Adult mayflies, or imagos, are relatively primitive in structure");
		nfa_test.add_testcase("Often, all the mayflies in a population mature at once (a hatch), and for a day or two in the spring or autumn");
		nfa_test.add_testcase("1c23abcb");
		nfa_test.add_testcase("1ab2ab3abbb");
		nfa_test.add_testcase("1)*&^$3b3abbb");
		nfa_test.test_match();

		nfa_test.set_pattern("[123]ab*");
		nfa_test.add_testcase("1a");
		nfa_test.add_testcase("1b");
		nfa_test.add_testcase("4a");
		nfa_test.add_testcase("2abb");
		nfa_test.add_testcase("23abb");
		nfa_test.add_testcase("c23abcb");
		nfa_test.add_testcase("1c23abcb");
		nfa_test.add_testcase("1ab2ab3abbb");
		nfa_test.add_testcase("1abbadafdasfdasfdasfdfdasf2abbb3abasdfbb");

		nfa_test.test_match();

		nfa_test.set_pattern("[a-zA-Z_][a-zA-Z0-9_]*");
		nfa_test.add_testcase("dfe");
		nfa_test.add_testcase("12fe");
		nfa_test.add_testcase("abdfe");
		nfa_test.add_testcase("c_edfe");
		nfa_test.add_testcase("_hell1a001");
		nfa_test.add_testcase("AB_Edsae12nfa_hell");
		nfa_test.add_testcase("nfa&helld1a AB_c0 001");
		nfa_test.add_testcase("nfa _hell 1a AB_c0 001");

		nfa_test.test_match();

		nfa_test.set_pattern("^ab*$");
		nfa_test.add_testcase("abb");
		nfa_test.add_testcase("a");
		nfa_test.add_testcase("abbbb");
		nfa_test.add_testcase("abaacdaa");
		nfa_test.add_testcase("aaadbaaaaa");
		nfa_test.add_testcase("ab\nabbb");
		nfa_test.add_testcase("ab\nabbb\n");
		nfa_test.add_testcase("ab\nabbb\n12");

		nfa_test.test_match();

	}

	void test_nfa_group()
	{
		cout << endl;
		print_string_format(80, "Test class NFA and NFAMatcher ", '-', true);
		cout << endl;
		NFATest nfa_test;
		nfa_test.set_pattern("(a)+(acd)");
		nfa_test.add_testcase("abb");
		nfa_test.add_testcase("a");
		nfa_test.add_testcase("abbbb");
		nfa_test.add_testcase("acdbbbb");
		nfa_test.add_testcase("abaaacdbbb");
		nfa_test.add_testcase("abaacdaa");
		nfa_test.add_testcase("aaadbaaaaa");
		nfa_test.add_testcase("ab\nabbb");
		nfa_test.add_testcase("ab\nabbb\n");
		nfa_test.add_testcase("ab\nabbb\n12");
		nfa_test.add_testcase("aacdabded");
		nfa_test.test_group();

		nfa_test.set_pattern("(a|b)+(a.*d)");
		nfa_test.add_testcase("abb");
		nfa_test.add_testcase("a");
		nfa_test.add_testcase("abbbb");
		nfa_test.add_testcase("abaacdaa");
		nfa_test.add_testcase("aaadbaaaaa");
		nfa_test.add_testcase("ab\nabbb");
		nfa_test.add_testcase("ab\nabbb\n");
		nfa_test.add_testcase("ab\nabbb\n12");
		nfa_test.add_testcase("aacdabded");
		nfa_test.add_testcase("aaabababacdabded");
		nfa_test.add_testcase("aaaaaaaaaaaaacdabdbed");
		nfa_test.add_testcase("acdadbadeadafgacdabded");
		nfa_test.test_group();
	}


	void print_string_format(size_t length, const string &str, char fill_char, bool is_middle)
	{
		if (str.size() > length) cout << "legth:" << std::left << setw(length - 6) << str.size();
		else if (!is_middle)
			cout << str << string(length - str.size(), fill_char);
		else
		{
			size_t before_length = (length - str.size()) / 2, after_length = length - before_length - str.size();
			cout << string(before_length, fill_char) << str << string(after_length, fill_char);
		}
	}
	template<typename NumType>
	void print_number_format(size_t length, NumType num, bool is_left)
	{
		cout << (is_left ? std::left : std::right) << setw(length) << num;
	}
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
		testcases.clear();
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


	void NFATest::test_match()
	{
		print_test_information();
		cout << endl;
		size_t testcase_size = testcases.size();
		size_t pass_count = 0, failed_count = 0;
		for (size_t i = 0; i < testcase_size; i++)
		{
			cout << "Test case :";
			print_number_format(5, i + 1);
			if (test_one_match_testcase(testcases[i]))
			{
				pass_count++;
				cout << " Passed!" << endl;
			}
			else
			{
				failed_count++;
				cout << " Failed!" << endl;
				print_string_format(10, "\tPattern", ' ');
				cout << ":" << pattern << endl;
				print_string_format(10, "\tText", ' ');
				cout <<":" <<endl<<"\t\t";
				print_string_format(70, testcases[i], ' ');
				cout << endl;
			}
		}
		cout << endl;
		print_test_result_information(testcase_size, pass_count, failed_count);
		cout << endl;

	}
	void NFATest::test_group()
	{
		print_test_information();
		cout << endl;
		size_t testcase_size = testcases.size();
		size_t pass_count = 0, failed_count = 0;
		for (size_t i = 0; i < testcase_size; i++)
		{
			cout << "Test case :";
			print_number_format(5, i + 1);
			if (test_one_group_testcase(testcases[i]))
			{
				pass_count++;
				cout << " Passed!" << endl;
			}
			else
			{
				failed_count++;
				cout << " Failed!" << endl;
				print_string_format(10, "\tPattern", ' ');
				cout << ":" << pattern << endl;
				print_string_format(10, "\tText", ' ');
				cout << ":" << endl << "\t\t";
				print_string_format(70, testcases[i], ' ');
				cout << endl;
			}
		}
		cout << endl;
		print_test_result_information(testcase_size, pass_count, failed_count);
		cout << endl;
	}
	void NFATest::print_test_information()
	{
		cout << endl;
		print_string_format(80, "Begein Test Pattern :" + pattern, ' ');
		cout << endl;
		print_string_format(25, "Test Case Amount", ' ');
		cout << ":" << testcases.size() << endl;
	}

	bool NFATest::test_one_match_testcase(const string & testcase)
	{
		NFAMatcher matcher = NFAMatcher::match(testcase, nfa);
		sregex_iterator begin(testcase.begin(), testcase.end(), standard_regex);
		sregex_iterator end;
		for (; begin != end && matcher.find(); begin++)
			if((*begin).str() != matcher.group()) return false;
		return begin == end && !matcher.find();
	}

	bool NFATest::test_one_group_testcase(const string & testcase)
	{
		NFAMatcher matcher = NFAMatcher::match(testcase, nfa);
		sregex_iterator begin(testcase.begin(), testcase.end(), standard_regex);
		sregex_iterator end;
		for (; begin != end && matcher.find(); begin++)
		{
			auto &result = *begin;
			if (result.str() != matcher.group()) return false;
			else
			{
				if (result.size() != matcher.group_count())return false;
				size_t group_size = result.size();
				for (size_t i = 1; i < group_size; i++)
					if (result[i] != matcher.group(i))return false;
			}
		}
		return begin == end && !matcher.find();
	}

	void NFATest::print_test_result_information(size_t total_test_count, size_t pass_count, size_t failed_count)
	{
		cout << pass_count << "/" << total_test_count << " ";
		print_number_format(10, (100.0*pass_count / total_test_count));
		cout<< "% Passed!"<<endl;
	}

	int singal_test(const string& pattern, const string &text)
	{
		regex standard_regex(pattern);
		NFA nfa(pattern);
		sregex_iterator begin(text.begin(), text.end(), standard_regex);
		sregex_iterator end;
		NFAMatcher matcher = NFAMatcher::match(text, nfa);
		int i = 1;
		for (; begin != end && matcher.find(); begin++)
			std::cout << "test " << i++ << ":" << (*begin).str() << " " << matcher.group() << std::endl;
		std::cout << "Test pass?" << (begin == end && !matcher.find() ? "true" : "false") << std::endl;
		return 0;
	}
	int test_standard(const string& pattern, const string &text)
	{
		regex standard_regex(pattern);
		sregex_iterator begin(text.begin(), text.end(), standard_regex);
		sregex_iterator end ;
		int i = 1;
		for (; begin != end; begin++)
		{
			auto &result = *begin;
			std::cout << i++ << ":" << result.str() << std::endl;
			size_t group_size = result.size();
			for (size_t i = 0; i < group_size; i++)
			{
				cout << result[i] << endl;
			}
		}
		return 0;
	}
#endif // DEBUG
}
