#include "string_algorithm_test.h"


ostream & operator<<(ostream & out, const position_type &positions)
{
	stringstream sstring;
	sstring << "occurence:" << positions.size();
	out << sstring.str();
	return out;
}

inline void print_position_anwer(const position_type &answer, size_t length)
{
	if (answer.empty()) cout << std::left << setw(length) << "no_positoin";
	else cout << std::left << setw(length) << answer;
}

void print_string_format(size_t length, const string &str, char fill_char, bool is_middle)
{
	if (length < 18) return;
	else if (str.size() > length) cout << "legth:"<<std::left<<setw(length-6)<<str.size();
	else if (!is_middle)
		cout << str << string(length - str.size(), fill_char);
	else
	{
		size_t before_length = (length - str.size()) / 2, after_length = length - before_length - str.size();
		cout << string(before_length, fill_char) << str << string(after_length, fill_char);
	}
}

void expect_position(const position_type &expect, const position_type &actual, clock_t clock_time,size_t length, const char *ok_message)
{
	if (expect == actual)
		cout << ok_message<<std::right << setw(length - strlen(ok_message)-2) << clock_time<<"ms";
	else print_position_anwer(actual, length);
}

void test(const vector<matching_algorithm_information_type> &string_agorighms, const vector<string_testcase_type> &test_cases)
{
	const size_t length = 30;
	print_string_format(1 + (length + 1) * (3 + string_agorighms.size()), "Begin", '-', true);
	cout << endl;
	cout << endl;
	cout << '|';
	cout << "------------Text--------------|";
	cout << "-----------Pattern------------|";
	cout << "--------CorrectAnswer---------|";
	
	//output algorithm information
	for (auto &string_algorithm : string_agorighms)
	{
		print_string_format(length, string_algorithm.first, '-', true);
		cout << '|';
	}
	cout << endl;
	cout << string(1 + (length + 1) * (3 + string_agorighms.size()), '_') << endl;
	cout << endl;

	clock_t begin = clock();
	//begin test
	for (auto &test_case : test_cases)
	{
		const string &T = test_case.first;
		const string &P = test_case.second;
		
		position_type correct_answer;
		for (size_t start = T.find(P); start<T.size()&&start != string::npos; start = T.find(P, start + 1))
			correct_answer.push_back(start);
		cout << '|';
		print_string_format(length, T, ' ', false);
		cout << '|';
		print_string_format(length, P, ' ', false);
		cout << '|';
		print_position_anwer(correct_answer, length);
		cout << '|';
		for (auto &string_algorithm : string_agorighms)
		{
			clock_t clock_time = clock();
			position_type answer = string_algorithm.second(T, P);
			clock_time = clock() - clock_time;
			expect_position(correct_answer, answer, clock_time, length,  "pass");
			cout << '|';
		}
		cout << endl;
	}
	cout << endl;
	stringstream str;
	str << "cost time:"<<(clock() - begin) << " ms";
	print_string_format(1 + (length + 1) * (3 + string_agorighms.size()), str.str(), '-', true);
	cout << endl;

}

void test(const vector<matching_algorithm_information_type> &string_agorighms, const string & testcase_file)
{
	ifstream file(testcase_file);
	if (!file.is_open())
	{
		cout << "open file error" << endl;
		return;
	}
	vector<string_testcase_type> testcases;
	string line;
	while (!file.eof()) 
	{
		std::getline(file, line);
		size_t seperate = line.find(',');
		testcases.push_back({ line.substr(0,seperate), line.substr(seperate + 1) });
	}
	file.close();
	test(string_agorighms, testcases);
}
