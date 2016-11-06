#include <iostream>
#include <string>
#include <fstream>
#include "DirectedGraphTest.h"
#include "NFATest.h"
#include "RegexTest.h"
#include "../Matcher.h"

using namespace anyun_regex;
using namespace std;

int main()
{
	/*test_directedgraph();
	test_nfa_match();
	test_nfa_group();*/
	size_t position = 1;
	cout << std::stoi("12ac", &position) << endl;
	cout << position << endl;
	return 0;
}
