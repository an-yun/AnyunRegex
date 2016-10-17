#include <iostream>
#include <fstream>
#include "NFA.h"

using namespace anyun_regex;

int main(int argc, char **argv)
{
	std::ifstream input;
	if(argc < 3)input.open("test.txt");
	if (input.bad())
	{
		std::cout << "file error!" << std::endl;
		return 0;
	}
	argv[1] = "i";
	NFA nfa(argv[1]);
	string line;
	unsigned line_no = 0;
	while (std::getline(input, line)) {
		line_no++;
		nfa.match(line.c_str());
		if (nfa.find())
			std::cout << line_no<<" line "<<nfa.get_match_start() << "-" << nfa.get_match_end() << ":" << line << std::endl;
	}
	return 0;
}