#include <iostream>
#include <string>
#include <fstream>
#include "Regex/Matcher.h"

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
		NFAMatcher matcher;
		Println("验证密码：" + password);
		if (NFAMatcher::search(password, matcher, pattern))
		{
			Println("包含重复3个以上,重复段为");
			Println(matcher.group());
		}
		else
			Println("OK");
		Println("");
	}
	Println("");
	cout << endl;
}
int main()
{
	password_validate();
	return 0;
}