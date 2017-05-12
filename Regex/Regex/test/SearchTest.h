#pragma once
#include "../RegexTestFramework.h"


std::vector<search_testcases_t> escape_search_testcases
{
	{"\\s+ab*\\s+",
		{
			" abb ",
			"a",
			" abbc",
			"\ta\n",
			"aa",
			"ab\nabbb",
			" ab\nabbb\n",
			"ab\nabbb\n12",
		}
	},
	{"[a-zA-Z]\\w*",
		{
			"cout",
			"set_pattern",
			"nfa_test",
			"test1",
			"1a",
			"a1",
			"d_string",
			"parse_index",
			"++i",
			"NFA_test",
			"main",
		}
	}
};

ADD_SERACH_TEST_SUIT(escape_search_test, escape_search_testcases)

std::vector<search_testcases_t> group_search_testcases
{
	{"(a)+(acd)",
		{
			"abb",
			"a",
			"abbbb",
			"acdbbbb",
			"abaaacdbbb",
			"abaacdaa",
			"aaadbaaaaa",
			"ab\nabbb",
			"ab\nabbb\n",
			"ab\nabbb\n12",
			"aacdabded",
		}
	},
	{"(a|b)+(a.*d)",
		{
			"abb",
			"a",
			"abbbb",
			"abaacdaa",
			"aaadbaaaaa",
			"ab\nabbb",
			"ab\nabbb\n",
			"ab\nabbb\n12",
			"aacdabded",
			"aaabababacdabded",
			"aaaaaaaaaaaaacdabdbed",
			"acdadbadeadafgacdabded",
		}
	},
	{"(12|34|56)+(a|e|i|o|u)",
		{
			"12abb",
			"34a",
			"13abbb",
			"24eaacdaa",
			"12a34e",
			"123456i",
			"4523a",
			"563412e",
			"1212121212343434aa1234565656ecdabded",
		}
	},
	{"([ab]+).\\1",
		{
			"a.a",
			"b.b",
			"ab.ab",
			"abaacdaa",
			"ababab.ababab",
			"aaaaa.aaaaaaa",
			"aaaaabaaaaabaa",
			"aaabaadbab.aaabaadbab",
			"aaabaadbabaaaaaaabaadbab",
		}
	},
	{ "\\d(\\w+)",
		{
			"12",
			"234a",
			"1235",
			"567g",
			"abc#d124",
			"aaaaa.aaaaaaa",
			"aaaaab@aaaaabaa",
			"aaaba123adaadbab",
			"1a_c_b",
		}
	},
	{ "(\\w)\\1(\\1)+",
		{
			"aaaa1111",
			"aa123",
			"123",
			"1123445690aaa",
			"abcd",
			"aabbccc",
			"11123",
		}
	},
	{"(\\w)\\1{2,}",
		{
			"aaaa1111",
			"aa123",
			"123",
			"1123445690aaa",
			"abcd",
			"aabbccc",
			"11123",
		}
	},
	{ "(\\w)(\\1){2,}",
		{
			"aaaa1111",
			"aa123",
			"123",
			"1123445690aaa",
			"abcd",
			"aabbccc",
			"11123",
		}
	},
	{"(\\w)(\\1){2,3}",
		{ 
			"aaaa1111",
			"aa123",
			"123",
			"1123445690aaa",
			"abcd",
			"aabbccc",
			"11123",
		}
	},
	{ "(\\w+)(\\1)(\\2)",
		{
			"aaaa1111",
			"aa123",
			"123",
			"1123445690aaa",
			"abcd",
			"aabbccc",
			"11123",
		}
	},
	//ip address test
	{ "((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)\\.){3}(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)",
		{
			"0.0.0.00",
			"11.1.1.",
			"0.0.0.0",
			"01.0.0.1",
			"192.168.0.1",
			"321.168.0.1",
			"192.168.00.1",
			"288.168.0.1",
			"0.168.0.1",
			"0.0.0.0",
		}
	},
	//url test
	{"[a-zA-z]+://[^\\s]*",
		{
			"http://www.baidu.com",
			"http://deerchao.net/tutorials/regex/regex.htm",
			"https://www.google.com.hk/",
			"http://msdn.itellyou.cn/",
			"a://b.c.com",
			"foo@demo.net",
			"bar.ba@test.co.uk",
			"www.demo.com",
			"http://foo.co.uk/",
			"http://regexr.com/foo.html?q=bar",
			"https://mediatemple.net",
		}
	},
	//email test
	{ "\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*",
		{
			"foo@demo.net",
			"bar.ba@test.co.uk",
			"zsy296@gmail.com",
			"1007252397@qq.com",
			"b-+  ar.ba@test.co.uk",
			"http://deerchao.net/tutorials/regex/common.htm",
		}
	},
	/*
	hrer are very long group name and reference test
	*/
	{ "(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)(p)(q)(r)(s)(t)(u)(v)(w)(x)(y)(z*)\\g{26}",
		{
			"abdefpqrstuvwxyzz",
			"abcdefghijklmnopqrstuvwxyz",
			"abcdefghijklmnopqrstuvwxyzzz",
			"abcdefghijklmnopqrstuvwxyzzzz",
			"abcdefghijklmnopqrstuvwxy",
			"abcdefghijklmnopqrstuvwxyzz",
			"abdefghijklmnopqrstuvwxyzz",
			"bdefghijklmnopqrstuvwxyzz",
		}
	},
	{ "(a)(b)?(c)?(d)?(e)?(f)?(g)?(h)?(i)?(j)?(k)?(l)?(m)?(n)?(o)?(p)?(q)?(r)?(s)?(t)?(u)?(v)?(w)?(x)?(y)?(z+)\\g{26}",
		{
			"azz",
			"aceizz",
			"aczeizz",
			"aczeizz",
			"acbzz",
			"abcdefghijklmnopqrstuvwxyz",
			"abcdefghijklmnopqrstuvwxyzzzz",
			"abcdefghijklmnopqrstuvwxyzzz",
			"abcdefghijklmnopqrstuvwxy",
			"abcdefghijklmnopqrstuvwxyzz",
			"abdefghijklmnopqrstuvwxyzz",
			"bdefghijklmnopqrstuvwxyzz",
		}
	}
};

ADD_SERACH_TEST_SUIT(group_search_test, group_search_testcases)

std::vector<search_testcases_t> lazy_match_search_testcases
{
	{"a?(ab)??""(ab)*",
		{
			"aab",
			"aaab",
			"aabab",
			"aaaaab",
			"acab",
			"babaaaab",
			"bbabaabab",
			"bbbbbbbbbbbbbbbbbbbba",
			"abababababababababab",
			"123ab132aab2ababd12f9kababab",
		}
	},
	{ "(\\d )??""( *)([yY]ou|I|[Ss]he|[Hh]e)",
		{
			"I",
			"1  You",
			"2He",
			"She",
			"1  I",
			"you2He3She 1",
			"    You yo   2  She He",
			"               1           She   He",
			"you He 12222    SHe He 12 ",
			"youYouSheheSheshe    1  You",
		}
	},
	{".*(<div>.*?</div>)",
		{
			"<div>  </div",
			"<div></div>",
			"<div>123</div>",
			"<div><div>123</div></div>",
			"<div><div><p>mis /div</p></div>",
			"<div><p>mis div</p></div></div>",
			"</div></div>",
			"<p>mis div</p></div></div></div>",
			"<div><div><div><div><div><p>mis /div</p>",
			"<p>some content</p><div>infor mation for p</div>",
		}
	},
	{"(He|(\\s)he)(\\s+)(\\S*?)e?d",
		{
			"Yet another unusual thing about Harry was how little he looked forward to his birthdays. ",
			"He had never received a birthday card in his life",
			"Harry walked across the dark room, past Hedwig¡¯s large, empty cage, to the open window. ",
			"Hedwig had been absent for two nights now.",
			"Harry recognized the unconscious owl at once",
			"Ron says he¡¯s going to be in London in the last week of the holidays. ",
			"He wanted me to debug the program",
			"It's surprising that he asked she to do this work",
			"\" No no no,it wasn't possible \" ,he said.",
			"He he       no       ",
		}
	},
	{"a?(ab)+?""(ab)*",
		{
			"aab",
			"aaab",
			"aabab",
			"aaaaab",
			"acab",
			"babaaaab",
			"bbabaabab",
			"bbbbbbbbbbbbbbbbbbbba",
			"abababababababababab",
			"123ab132aab2ababd12f9kababab",
		}
	},
	{ "a?(ab)+?""(ab)+",
		{
			"aab",
			"aaab",
			"aabab",
			"aaaaab",
			"acab",
			"babaaaab",
			"bbabaabab",
			"bbbbbbbbbbbbbbbbbbbba",
			"abababababababababab",
			"123ab132aab2ababd12f9kababab",
		}
	},
	{ "ac?a+?(ab)+?",
		{
			"aab",
			"aaab",
			"aabab",
			"aaaaab",
			"aaacab",
			"babaaaab",
			"bbabaabab",
			"bbbbbbbbbbbbbbbbbbbba",
			"abababababababababab",
			"a123ab132aab2ababd12f9kababab",
		}
	},
	{ "a?(ab){2,3}?""(ab)*",
		{ 
			"aab",
			"aaab",
			"aabab",
			"aaaaab",
			"acab",
			"babaaaab",
			"bbabaabab",
			"bbbbbbbbbbbbbbbbbbbba",
			"abababababababababab",
			"123ab132aab2ababd12f9kababab",
		}
	},
	{"a\\d{1,}?345",
		{
			"a345",
			"a1345",
			"a12345",
			"ab3345",
			"a333345",
			"aaaaaaaaa345",
			"a12a1212121345",
			"abcdefg123aaaa12121345",
		}
	}
};

ADD_SERACH_TEST_SUIT(lazy_match_search_test, lazy_match_search_testcases)

std::vector<search_testcases_t> zero_length_assertion_search_testcases
{
	{ "\\b((?!abc)\\w)+\\b",
		{
			"abc",
			"aabc ab ababa abaabc ",
			"aaabbc abaa abababc",
			"abcde ab abc abcccccc ababababababababababababc",
		}
	},
	//C++ identifier
	{"\\b(?!\\d)\\w+\\b",
		{
			"aaa1 cout",
			"test1 i j k 1p",
			"test_group 0group 0i",
			"request1 endl decrese ",
			"_",
			"_1 _2 _at",
		}
	},
	{"(?<=\\bre)\\w+\\b",
		{
			"reading a book",
			"request something",
			"prepare something for eat",
			"request prepare decrese ",
		}
	},
	{"(?<=[yY]ou)\\b\\w+\\b",
		{
			"what do you find",
			"I am singing while you are dancing",
			"are you kidding me? ",
			"what's your name?",
		}
	},
	{"(?<![a-zA-Z])\\d+",
		{
			"aaa1 12",
			"1111 +22 *2 = ",
			"a3 b12 _123 _90282",
			"234567request11 pre2343567pare decrese aaaa 111",
		}
	}
};

ADD_SERACH_TEST_SUIT(zero_length_assertion_search_test, zero_length_assertion_search_testcases)
