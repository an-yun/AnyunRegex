#include <iostream>
#include	<string>
#include <fstream>
#include <boost\regex.hpp>
#include "DirectedGraphTest.h"
#include "NFATest.h"
#include "RegexTest.h"

int main(int argc, char **argv)
{
	boost::regex e1("a|b");
	std::string text("aaabbb");
	boost::match_results<std::string::iterator> result;
	boost::match_flag_type flags = boost::match_default;
	std::string::iterator start = text.begin(), end = text.end();
	while (boost::regex_search(start, end, result, e1, flags))
	{
		std::cout << result[0].str() << std::endl;
		start = result[0].second;
		// update flags: 
		flags |= boost::match_prev_avail;
		flags |= boost::match_not_bob;
	}
	//anyun_regex::test_directedgraph();
	return 0;
}
