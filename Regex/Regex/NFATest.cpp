#include "NFATest.h"

int test()
{
	std::string s =
		"aaabbb\nab\nab\nabc";
	std::regex a_b_more("");
	std::sregex_iterator begin =
		std::sregex_iterator(s.begin(), s.end(), a_b_more);
	std::sregex_iterator end = std::sregex_iterator();
	int i = 1;
	for (; begin != end; begin++)
		std::cout << i++<<(*begin).str() << std::endl;
	return 0;
}

int testNFA()
{
	std::string s =
		"aaabbb";
	std::regex a_b_more("");
	anyun_regex::NFA nfa("");
	std::sregex_iterator begin =
		std::sregex_iterator(s.begin(), s.end(), a_b_more);
	std::sregex_iterator end = std::sregex_iterator();
	nfa.match(s);
	int i = 1;
	for (; begin != end && nfa.find(); begin++)
		std::cout<<"test " << i++ <<":"<< (*begin).str() <<" "<<nfa.get_match()<< std::endl;
	std::cout << "Test pass?" << (begin == end && !nfa.find() ? "true" : "false") << std::endl;
	return 0;
}
