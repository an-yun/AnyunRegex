#ifndef REGEX_TEST_H
#define REGEX_TEST_H
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <regex>

#include "../NFA.h"
#include "../Matcher.h"


namespace anyun_regex
{
	using std::string;
	using std::regex;
	using std::smatch;
	using std::sregex_iterator;
	using std::string;
	using std::ifstream;
	using std::cout;
	using std::endl;
	using anyun_regex::NFA;
#ifdef _DEBUG	
	class LibraryRegex
	{
	public:
		LibraryRegex();

	private:

	};

	int test_exameple();
	int test_files();
#endif // DEBUG
}

#endif // !REGEX_TEST_H