#pragma once

#include "../RegexTestFramework.h"


using namespace anyun_regex;

std::vector<const char *> compile_normal_test_cases =
{
	/*  here some test case to add parse
	*/
	"",
	"ab",
	"abbba",
	"a|b",
	"a|bc",
	"a|b|123",
	"(a|b)c",
	"(a|bb)c",
	"(a|b)|123",
	"(A|a)(B|b)(C|c)(E|e)",
	"[0-9]c",
	"[0-9a-z]c",
	"[0-9A-Z!]c",
	"[\\w\\s]ab1",
	"[\\daeiou]ab1",
	"[0-9A-Z!](are|you)c",
	"(a|b){2}",
	"(a|b){2,5}",
	"(a|b){2,}",
	"(a|b){2,}c",
	"(a|b){2,}c",
	"(A|a)(B|b)c{2,5}D",
	"(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)(p)(q)(r)(s)(t)(u)(v)(w)(x)(y)(z+)\\26",
	"(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)(p)(q)(r)(s)(t)(u)(v)(w)(x)(y)(z+)\\g{26}",
	"(a)(b)?(c)?(d)?(e)?(f)?(g)?(h)?(i)?(j)?(k)?(l)?(m)?(n)?(o)?(p)?(q)?(r)?(s)?(t)?(u)?(v)?(w)?(x)?(y)?(z+)\\26",
	"(a)(b)?(c)?(d)?(e)?(f)?(g)?(h)?(i)?(j)?(k)?(l)?(m)?(n)?(o)?(p)?(q)?(r)?(s)?(t)?(u)?(v)?(w)?(x)?(y)?(z+)\\g{26}",
	"(a|b|c|d){2,5}D",
	"(a|b|c|d){2,5}D",
	"[0-9](a|b|c|d){2,5}D",
	"^",
	"$",
	"^$",
	"^a$",
	"^(ab|bc[123])$",
	"^[0-9](a|b|c|d){2,5}D$",
	"\\n",
	"a\\n",
	"^ab$\\nc",
	"ab\\nb\\rba",
	"a(?<my_name>a)",
	"a(?'my_name'ab)",
	"\\b\\w+(?=ing\\b)",
	"\\b((?!abc)\\w)+\\b",
	"\\b(?!\\d)\\w+\\b",
	"(?<=\\bre)\\w+\\b",
	"(?<=[yY]ou)\\b\\w+\\b",
	"(?<![a-zA-Z])\\d+"
};

ADD_NORMAL_TESTCASE_FOR_COMPILE(compile_normal_test, regex_test_data::make(compile_normal_test_cases))