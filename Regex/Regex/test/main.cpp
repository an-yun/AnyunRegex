#include <iostream>
#include <string>
#include <fstream>
#include "DirectedGraphTest.h"
#include "NFATest.h"
#include "RegexTest.h"
#include "../Matcher.h"

using namespace anyun_regex;
using namespace std;

#define Println(content) \
	cout<<content<<endl;

void password_validate()
{
	string passwords[] =
	{ 
		"1aaaa2",
		"aaaa1111",
		"aa123",
		"123",
		"1123445690aaa",
		"abcd",
		"aabbccc",
		"11123" };
	NFA pattern("(\\w)\\1{2,}");
	for (string &password : passwords)
	{
		NFAMatcher matcher = NFAMatcher::match(password, pattern);
		Println("validate the password:" + password);
		if (matcher.find())
		{
			Println("contain repeated chars more than three times,the repeat string i");
			Println(matcher.group());
		}
		else
			Println("OK");
		Println("");
	}
	cout << endl;
}
int main()
{
	test_directedgraph();
	test_nfa_match();
	test_nfa_group(); 
	//test_nfa_replace();
	//test_nfa_capture();
	//password_validate();
	return 0;
}
