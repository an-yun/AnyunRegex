#include <iostream>
#include <string>
#include <fstream>
#include "../Matcher.h"

//#define TEST


#ifdef TEST
#define REGEX_TEST_MOUDLE regex test
/*
*add all test moudules that shoul test
*/
#include "PreProcessNormalTest.h"
#include "PreProcessErrorTest.h"
#include "CompileNormalTest.h"
#include "CompileErrorTest.h"

#include "MatchTest.h"
#include "SearchTest.h"

#else
#include "DirectedGraphTest.h"
#include "NFATest.h"

using namespace anyun_regex;
using namespace std;

void password_validate();
void boost_regex_password_validate();

#ifdef _DEBUG
void test_auto();
void test_capture();
#endif

int main()
{

#ifdef _DEBUG

	test_auto();
	//test_capture();
	//boost_regex_password_validate();
#else
	password_validate();
	//boost_regex_password_validate();
#endif
	return 0;
}


void password_validate() {
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
		Println("��֤���룺" + password);
		if (NFAMatcher::search(password, matcher, pattern))
		{
			Println("�����ظ�3������,�ظ���Ϊ");
			Println(matcher.group());
		}
		else
			Println("OK");
		Println("");
	}
	Println("");
	cout << endl;
}
void boost_regex_password_validate()
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
	boost::regex regex_expression("(\\w)\\1{2,}");
	boost::match_results<std::string::const_iterator> what;
	for (string &password : passwords)
	{
		Println("��֤���룺" + password);
		if (regex_search(password.cbegin(), password.cend(), what, regex_expression))
		{
			Println("�����ظ�3������,�ظ���Ϊ");
			Println(what[0]);
		}
		else
			Println("OK");
		Println("");
	}
	cout << endl;
	Println("");
}
#ifdef _DEBUG
void test_auto()
{
	test_directedgraph();
	test_nfa_match();
	test_nfa_search();
	test_nfa_escape();
	test_nfa_group();
	test_lazy_match();
	test_zero_length_assertions();
}

void test_capture()
{
	test_nfa_replace();
	test_nfa_capture();
	password_validate();
}
#endif

#endif
