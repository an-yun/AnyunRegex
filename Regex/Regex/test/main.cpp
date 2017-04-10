#include <iostream>
#include <string>
#include <fstream>
#include "DirectedGraphTest.h"
#include "NFATest.h"
#include "RegexTest.h"
#include "../Matcher.h"

using namespace anyun_regex;
using namespace std;

void test_auto()
{
	test_directedgraph();
	test_nfa_match();
	test_nfa_group();
	test_lazy_match();
}

void test_capture()
{
	test_nfa_replace();
	test_nfa_capture();
	password_validate();
}

int main()
{
	//test_auto();
	test_capture();
	test_boost_regex();
	return 0;
}
