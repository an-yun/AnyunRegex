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
	{ "aaaa1111",
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
		Println("验证密码：" + password);
		if (matcher.find())
		{
			Println("包含重复3个以上,重复段为");
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
	password_validate();
	return 0;
}
