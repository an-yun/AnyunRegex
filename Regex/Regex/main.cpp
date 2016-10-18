#include <iostream>
#include <fstream>
#include "NFA.h"

using namespace anyun_regex;
using namespace std;

int main(int argc, char **argv)
{
	NFA nfa("ab(bc)|(cd)");
	nfa.match("abcd");
	cout << nfa.find() << endl;
	/*ifstream input;
	input.open("and_test_case.txt");
	if (input.bad())
	{
		std::cout << "file error!" << std::endl;
		return 0;
	}
	size_t case_num;
	string str;
	while (input >> case_num)
	{
		input >> str;
		NFA nfa(str.substr(1,str.size()-2).c_str());
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
		getline(input, line);
		cout << endl;
	}*/
	return 0;
}