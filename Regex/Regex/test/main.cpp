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

int main()
{
	test_directedgraph();
	test_nfa_match();
	test_nfa_group();
	cout << endl;
	string passwords[] =
	{ "aaaa1111",
		"aa123",
		"123",
		"1123445690aaa",
		"abcd",
		"aabbccc",
		"11123" };
	NFA pattern("(\\w)\\1(\\1)+");
	for (string &password : passwords)
	{
		NFAMatcher matcher = NFAMatcher::match(password, pattern);
		Println("��֤���룺" + password);
		if (matcher.find())
		{
			Println("�����ظ�3������,�ظ���Ϊ");
			Println(matcher.group());
		}
		else
			Println("OK");
		Println("");
	}


	return 0;
}
