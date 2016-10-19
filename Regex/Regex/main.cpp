#include <iostream>
#include <fstream>
#include "NFA.h"

using namespace anyun_regex;
using namespace std;

int main(int argc, char **argv)
{
	string test_files[] = { "and_test_case.txt" ,"or_test_case.txt" ,"dot_test_case.txt" ,"question_mark_test_case.txt" };
	ifstream input;
	for (size_t i = 0; i < sizeof(test_files)/sizeof(string); i++)
	{
		input.open(test_files[i]);
		if (input.bad())
		{
			std::cout << test_files[i] << " file error!" << std::endl;
			return 0;
		}
		cout << "-------------------------------------" << test_files[i] << "-----------------------------------------------------" << endl;
		size_t case_num;
		string str;
		while (input >> case_num)
		{
			input >> str;
			NFA nfa(str.substr(1, str.size() - 2));
			cout << "grep " << nfa.get_pattern() << endl;
			string line;
			getline(input, line);
			getline(input, line);
			for (unsigned line_no = 1; line_no <= case_num; getline(input, line)) {
				nfa.match(line.c_str());
				if (nfa.find())
					cout << line << std::endl;
				line_no++;
			}
			cout << endl;
		}
		input.close();
	}
	return 0;
}