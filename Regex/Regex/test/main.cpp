#include <iostream>
#include <fstream>
#include "../NFA.h"
#include "NFATest.h"
#include "RegexTest.h"

int main(int argc, char **argv)
{
	anyun_regex::singal_test("a|b","aaabbb");
	return 0;
}
