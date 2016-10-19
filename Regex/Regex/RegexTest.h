#ifndef REGEX_TEST_H
#define REGEX_TEST_H
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <regex>

#include "NFA.h"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using anyun_regex::NFA;

int test_exameple();
int test_files();

namespace anyun_regex
{
	using std::string;
	
	class LibraryRegex
	{
	public:
		LibraryRegex();
		LibraryRegex(const string &);

	private:

	};


}

#endif // !REGEX_TEST_H