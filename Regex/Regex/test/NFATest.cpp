#include "NFATest.h"

namespace anyun_regex
{

#ifdef _DEBUG

	

	void test_nfa_match()
	{
		cout << endl;
		print_string_format(80, "Test class NFA and NFAMatcher for match", '-', true);
		cout << endl;
		NFATest nfa_test;

		nfa_test.set_pattern(".*");
		nfa_test.add_testcase("1b");
		nfa_test.add_testcase("4a");
		nfa_test.add_testcase("Mayflies, also known as shadflies or fishflies in Canada");
		nfa_test.add_testcase(".cc .cpp .cxx .C .c++ .h .hh .hpp .hxx .h++");
		nfa_test.add_testcase("are aquatic insects belonging to the order Ephemeroptera");
		nfa_test.add_testcase("Immature mayflies are aquatic");
		nfa_test.add_testcase("Adult mayflies, or imagos, are relatively primitive in structure");
		nfa_test.add_testcase("Often, all the mayflies in a population mature at once (a hatch), and for a day or two in the spring or autumn");
		nfa_test.add_testcase("1c23abcb");
		nfa_test.add_testcase("1ab2ab3abbb");
		nfa_test.add_testcase("1)*&^$3b3abbb");
		nfa_test.test_match();

		nfa_test.set_pattern("[123]ab*");
		nfa_test.add_testcase("1a");
		nfa_test.add_testcase("1b");
		nfa_test.add_testcase("4a");
		nfa_test.add_testcase("2abb");
		nfa_test.add_testcase("23abb");
		nfa_test.add_testcase("c23abcb");
		nfa_test.add_testcase("1c23abcb");
		nfa_test.add_testcase("1ab2ab3abbb");
		nfa_test.add_testcase("1abbadafdasfdasfdasfdfdasf2abbb3abasdfbb");

		nfa_test.test_match();

		nfa_test.set_pattern("[a-zA-Z_][a-zA-Z0-9_]*");
		nfa_test.add_testcase("dfe");
		nfa_test.add_testcase("12fe");
		nfa_test.add_testcase("abdfe");
		nfa_test.add_testcase("c_edfe");
		nfa_test.add_testcase("_hell1a001");
		nfa_test.add_testcase("AB_Edsae12nfa_hell");
		nfa_test.add_testcase("nfa&helld1a AB_c0 001");
		nfa_test.add_testcase("nfa _hell 1a AB_c0 001");

		nfa_test.test_match();

		nfa_test.set_pattern("^ab*$");
		nfa_test.add_testcase("abb");
		nfa_test.add_testcase("a");
		nfa_test.add_testcase("abbbb");
		nfa_test.add_testcase("abaacdaa");
		nfa_test.add_testcase("aaadbaaaaa");
		nfa_test.add_testcase("ab\nabbb");
		nfa_test.add_testcase("ab\nabbb\n");
		nfa_test.add_testcase("ab\nabbb\n12");

		nfa_test.test_match();

		nfa_test.set_pattern("a+\\d{2,6}");
		nfa_test.add_testcase("a");
		nfa_test.add_testcase("a1");
		nfa_test.add_testcase("ba12");
		nfa_test.add_testcase("aba123456");
		nfa_test.add_testcase("a1234567");
		nfa_test.add_testcase("aaaaaaa36");
		nfa_test.add_testcase("11111112a3");
		nfa_test.add_testcase("1aa1aa112a3");
		nfa_test.add_testcase("a&1@b#a1908");
		nfa_test.add_testcase("123aaaji8eaa");

		nfa_test.test_match();

		nfa_test.set_pattern("a*a{2,}b{1,}");
		nfa_test.add_testcase("ab");
		nfa_test.add_testcase("aaab");
		nfa_test.add_testcase("aaaabbb");
		nfa_test.add_testcase("aaaabbabaa");
		nfa_test.add_testcase("aaaabbbbaaab");
		nfa_test.add_testcase("aaaab12abaabaa");
		nfa_test.add_testcase("12aaaabbbbbbbbbbbb");
		nfa_test.add_testcase("aca12\\^%12asdaaaabb");
		nfa_test.test_match();

		nfa_test.set_pattern("\\s+ab*\\s+");
		nfa_test.add_testcase(" abb ");
		nfa_test.add_testcase("a");
		nfa_test.add_testcase(" abbc");
		nfa_test.add_testcase("\ta\n");
		nfa_test.test_match();


		//url test
		nfa_test.set_pattern("[a-zA-z]+://[^\\s]*");
		nfa_test.add_testcase("http://www.baidu.com");
		nfa_test.add_testcase("http://deerchao.net/tutorials/regex/regex.htm");
		nfa_test.add_testcase("https://www.google.com.hk/");
		nfa_test.add_testcase("http://msdn.itellyou.cn/");
		nfa_test.add_testcase("a://b.c.com");
		nfa_test.add_testcase("foo@demo.net");
		nfa_test.add_testcase("bar.ba@test.co.uk");
		nfa_test.add_testcase("www.demo.com");
		nfa_test.add_testcase("http://foo.co.uk/");
		nfa_test.add_testcase("http://regexr.com/foo.html?q=bar");
		nfa_test.add_testcase("https://mediatemple.net");
		nfa_test.test_match();

		//email test
		nfa_test.set_pattern("\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*");
		nfa_test.add_testcase("foo@demo.net");
		nfa_test.add_testcase("bar.ba@test.co.uk");
		nfa_test.add_testcase("zsy296@gmail.com");
		nfa_test.add_testcase("1007252397@qq.com");
		nfa_test.add_testcase("b-+  ar.ba@test.co.uk");
		nfa_test.add_testcase("http://deerchao.net/tutorials/regex/common.htm");
		nfa_test.test_match();

	}

	void test_nfa_search()
	{
		cout << endl;
		print_string_format(80, "Test class NFA and NFAMatcher for search", '-', true);
		cout << endl;
		NFATest nfa_test;
		nfa_test.set_pattern("");
		nfa_test.add_testcase("1a");
		nfa_test.add_testcase("1234");
		nfa_test.add_testcase("1b");
		nfa_test.add_testcase("4a");
		nfa_test.add_testcase("!@#");
		nfa_test.add_testcase("2abb");
		nfa_test.add_testcase("23abb");
		nfa_test.add_testcase("c23abcb");
		nfa_test.add_testcase("1c23abcb");
		nfa_test.add_testcase("1ab2ab3abbb");
		nfa_test.add_testcase("1)*&^$3b3abbb");
		nfa_test.test_search();

		nfa_test.set_pattern(".*");
		nfa_test.add_testcase("1b");
		nfa_test.add_testcase("4a");
		nfa_test.add_testcase("Mayflies, also known as shadflies or fishflies in Canada");
		nfa_test.add_testcase(".cc .cpp .cxx .C .c++ .h .hh .hpp .hxx .h++");
		nfa_test.add_testcase("are aquatic insects belonging to the order Ephemeroptera");
		nfa_test.add_testcase("Immature mayflies are aquatic");
		nfa_test.add_testcase("Adult mayflies, or imagos, are relatively primitive in structure");
		nfa_test.add_testcase("Often, all the mayflies in a population mature at once (a hatch), and for a day or two in the spring or autumn");
		nfa_test.add_testcase("1c23abcb");
		nfa_test.add_testcase("1ab2ab3abbb");
		nfa_test.add_testcase("1)*&^$3b3abbb");
		nfa_test.test_search();

		nfa_test.set_pattern("[123]ab*");
		nfa_test.add_testcase("1a");
		nfa_test.add_testcase("1b");
		nfa_test.add_testcase("4a");
		nfa_test.add_testcase("2abb");
		nfa_test.add_testcase("23abb");
		nfa_test.add_testcase("c23abcb");
		nfa_test.add_testcase("1c23abcb");
		nfa_test.add_testcase("1ab2ab3abbb");
		nfa_test.add_testcase("1abbadafdasfdasfdasfdfdasf2abbb3abasdfbb");

		nfa_test.test_search();

		nfa_test.set_pattern("[a-zA-Z_][a-zA-Z0-9_]*");
		nfa_test.add_testcase("dfe");
		nfa_test.add_testcase("12fe");
		nfa_test.add_testcase("abdfe");
		nfa_test.add_testcase("c_edfe");
		nfa_test.add_testcase("_hell1a001");
		nfa_test.add_testcase("AB_Edsae12nfa_hell");
		nfa_test.add_testcase("nfa&helld1a AB_c0 001");
		nfa_test.add_testcase("nfa _hell 1a AB_c0 001");

		nfa_test.test_search();

		nfa_test.set_pattern("^ab*$");
		nfa_test.add_testcase("abb");
		nfa_test.add_testcase("a");
		nfa_test.add_testcase("abbbb");
		nfa_test.add_testcase("abaacdaa");
		nfa_test.add_testcase("aaadbaaaaa");
		nfa_test.add_testcase("ab\nabbb");
		nfa_test.add_testcase("ab\nabbb\n");
		nfa_test.add_testcase("ab\nabbb\n12");

		nfa_test.test_search();

		nfa_test.set_pattern("a+\\d{2,6}");
		nfa_test.add_testcase("a");
		nfa_test.add_testcase("a1");
		nfa_test.add_testcase("ba12");
		nfa_test.add_testcase("aba123456");
		nfa_test.add_testcase("a1234567");
		nfa_test.add_testcase("aaaaaaa36");
		nfa_test.add_testcase("11111112a3");
		nfa_test.add_testcase("1aa1aa112a3");
		nfa_test.add_testcase("a&1@b#a1908");
		nfa_test.add_testcase("123aaaji8eaa");

		nfa_test.test_search();

		nfa_test.set_pattern("a*a{2,}b{1,}");
		nfa_test.add_testcase("ab");
		nfa_test.add_testcase("aaab");
		nfa_test.add_testcase("aaaabbb");
		nfa_test.add_testcase("aaaabbabaa");
		nfa_test.add_testcase("aaaabbbbaaab");
		nfa_test.add_testcase("aaaab12abaabaa");
		nfa_test.add_testcase("12aaaabbbbbbbbbbbb");
		nfa_test.add_testcase("aca12\\^%12asdaaaabb");
		nfa_test.test_search();
	}

	void test_nfa_escape()
	{
		cout << endl;
		print_string_format(80, "Test class NFA for escape chracters ", '-', true);
		cout << endl;
		NFATest nfa_test;
		nfa_test.set_pattern("\\s+ab*\\s+");
		nfa_test.add_testcase(" abb ");
		nfa_test.add_testcase("a");
		nfa_test.add_testcase(" abbc");
		nfa_test.add_testcase("\ta\n");
		nfa_test.add_testcase("aa");
		nfa_test.add_testcase("ab\nabbb");
		nfa_test.add_testcase(" ab\nabbb\n");
		nfa_test.add_testcase("ab\nabbb\n12");

		nfa_test.test_search();

		nfa_test.set_pattern("\\a\\w*");
		nfa_test.add_testcase("cout");
		nfa_test.add_testcase("set_pattern");
		nfa_test.add_testcase("nfa_test");
		nfa_test.add_testcase("test1");
		nfa_test.add_testcase("1a");
		nfa_test.add_testcase("a1");
		nfa_test.add_testcase("d_string");
		nfa_test.add_testcase("parse_index");
		nfa_test.add_testcase("++i");
		nfa_test.add_testcase("NFA_test");
		nfa_test.add_testcase("main");
		nfa_test.test_search();
	}

	void test_nfa_group()
	{
		cout << endl;
		print_string_format(80, "Test class NFA and NFAMatcher for group", '-', true);
		cout << endl;
		NFATest nfa_test;
		nfa_test.set_pattern("(a)+(acd)");
		nfa_test.add_testcase("abb");
		nfa_test.add_testcase("a");
		nfa_test.add_testcase("abbbb");
		nfa_test.add_testcase("acdbbbb");
		nfa_test.add_testcase("abaaacdbbb");
		nfa_test.add_testcase("abaacdaa");
		nfa_test.add_testcase("aaadbaaaaa");
		nfa_test.add_testcase("ab\nabbb");
		nfa_test.add_testcase("ab\nabbb\n");
		nfa_test.add_testcase("ab\nabbb\n12");
		nfa_test.add_testcase("aacdabded");
		nfa_test.test_group();

		nfa_test.set_pattern("(a|b)+(a.*d)");
		nfa_test.add_testcase("abb");
		nfa_test.add_testcase("a");
		nfa_test.add_testcase("abbbb");
		nfa_test.add_testcase("abaacdaa");
		nfa_test.add_testcase("aaadbaaaaa");
		nfa_test.add_testcase("ab\nabbb");
		nfa_test.add_testcase("ab\nabbb\n");
		nfa_test.add_testcase("ab\nabbb\n12");
		nfa_test.add_testcase("aacdabded");
		nfa_test.add_testcase("aaabababacdabded");
		nfa_test.add_testcase("aaaaaaaaaaaaacdabdbed");
		nfa_test.add_testcase("acdadbadeadafgacdabded");
		nfa_test.test_group();

		nfa_test.set_pattern("(12|34|56)+(a|e|i|o|u)");
		nfa_test.add_testcase("12abb");
		nfa_test.add_testcase("34a");
		nfa_test.add_testcase("13abbb");
		nfa_test.add_testcase("24eaacdaa");
		nfa_test.add_testcase("12a34e");
		nfa_test.add_testcase("123456i");
		nfa_test.add_testcase("4523a");
		nfa_test.add_testcase("563412e");
		nfa_test.add_testcase("1212121212343434aa1234565656ecdabded");
		nfa_test.test_group();

		nfa_test.set_pattern("([ab]+).\\1");
		nfa_test.add_testcase("a.a");
		nfa_test.add_testcase("b.b");
		nfa_test.add_testcase("ab.ab");
		nfa_test.add_testcase("abaacdaa");
		nfa_test.add_testcase("ababab.ababab");
		nfa_test.add_testcase("aaaaa.aaaaaaa");
		nfa_test.add_testcase("aaaaabaaaaabaa");
		nfa_test.add_testcase("aaabaadbab.aaabaadbab");
		nfa_test.add_testcase("aaabaadbabaaaaaaabaadbab");
		nfa_test.test_group();

		nfa_test.set_pattern("\\d(\\w+)");
		nfa_test.add_testcase("12");
		nfa_test.add_testcase("234a");
		nfa_test.add_testcase("1235");
		nfa_test.add_testcase("567g");
		nfa_test.add_testcase("abc#d124");
		nfa_test.add_testcase("aaaaa.aaaaaaa");
		nfa_test.add_testcase("aaaaab@aaaaabaa");
		nfa_test.add_testcase("aaaba123adaadbab");
		nfa_test.add_testcase("1a_c_b");
		nfa_test.test_group();

		nfa_test.set_pattern("(\\w)\\1(\\1)+");
		nfa_test.add_testcase("aaaa1111");
		nfa_test.add_testcase("aa123");
		nfa_test.add_testcase("123");
		nfa_test.add_testcase("1123445690aaa");
		nfa_test.add_testcase("abcd");
		nfa_test.add_testcase("aabbccc");
		nfa_test.add_testcase("11123");
		nfa_test.test_group();

		nfa_test.set_pattern("(\\w)\\1{2,}");
		nfa_test.add_testcase("aaaa1111");
		nfa_test.add_testcase("aa123");
		nfa_test.add_testcase("123");
		nfa_test.add_testcase("1123445690aaa");
		nfa_test.add_testcase("abcd");
		nfa_test.add_testcase("aabbccc");
		nfa_test.add_testcase("11123");
		nfa_test.test_group();

		nfa_test.set_pattern("(\\w)(\\1){2,}");
		nfa_test.add_testcase("aaaa1111");
		nfa_test.add_testcase("aa123");
		nfa_test.add_testcase("123");
		nfa_test.add_testcase("1123445690aaa");
		nfa_test.add_testcase("abcd");
		nfa_test.add_testcase("aabbccc");
		nfa_test.add_testcase("11123");
		nfa_test.test_group();

		nfa_test.set_pattern("(\\w)(\\1){2,3}");
		nfa_test.add_testcase("aaaa1111");
		nfa_test.add_testcase("aa123");
		nfa_test.add_testcase("123");
		nfa_test.add_testcase("1123445690aaa");
		nfa_test.add_testcase("abcd");
		nfa_test.add_testcase("aabbccc");
		nfa_test.add_testcase("11123");
		nfa_test.test_group();

		nfa_test.set_pattern("(\\w+)(\\1)(\\2)");
		nfa_test.add_testcase("aaaa1111");
		nfa_test.add_testcase("aa123");
		nfa_test.add_testcase("123");
		nfa_test.add_testcase("1123445690aaa");
		nfa_test.add_testcase("abcd");
		nfa_test.add_testcase("aabbccc");
		nfa_test.add_testcase("11123");
		nfa_test.test_group();


		//ip address test
		nfa_test.set_pattern("((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)\\.){3}(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)");
		nfa_test.add_testcase("0.0.0.00");
		nfa_test.add_testcase("11.1.1.");
		nfa_test.add_testcase("0.0.0.0");
		nfa_test.add_testcase("01.0.0.1");
		nfa_test.add_testcase("192.168.0.1");
		nfa_test.add_testcase("321.168.0.1");
		nfa_test.add_testcase("192.168.00.1");
		nfa_test.add_testcase("288.168.0.1");
		nfa_test.add_testcase("0.168.0.1");
		nfa_test.add_testcase("0.0.0.0");
		nfa_test.test_group();

		//url test
		nfa_test.set_pattern("[a-zA-z]+://[^\\s]*");
		nfa_test.add_testcase("http://www.baidu.com");
		nfa_test.add_testcase("http://deerchao.net/tutorials/regex/regex.htm");
		nfa_test.add_testcase("https://www.google.com.hk/");
		nfa_test.add_testcase("http://msdn.itellyou.cn/");
		nfa_test.add_testcase("a://b.c.com");
		nfa_test.add_testcase("foo@demo.net");
		nfa_test.add_testcase("bar.ba@test.co.uk");
		nfa_test.add_testcase("www.demo.com");
		nfa_test.add_testcase("http://foo.co.uk/");
		nfa_test.add_testcase("http://regexr.com/foo.html?q=bar");
		nfa_test.add_testcase("https://mediatemple.net");
		nfa_test.test_group();

		//email test
		nfa_test.set_pattern("\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*");
		nfa_test.add_testcase("foo@demo.net");
		nfa_test.add_testcase("bar.ba@test.co.uk");
		nfa_test.add_testcase("zsy296@gmail.com");
		nfa_test.add_testcase("1007252397@qq.com");
		nfa_test.add_testcase("b-+  ar.ba@test.co.uk");
		nfa_test.add_testcase("http://deerchao.net/tutorials/regex/common.htm");
		nfa_test.test_group();

		/*
		hrer are very long group name and reference test
		*/
		nfa_test.set_pattern("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)(p)(q)(r)(s)(t)(u)(v)(w)(x)(y)(z*)\\26");
		nfa_test.add_testcase("abdefpqrstuvwxyzz");
		nfa_test.add_testcase("abcdefghijklmnopqrstuvwxyz");
		nfa_test.add_testcase("abcdefghijklmnopqrstuvwxyzzz");
		nfa_test.add_testcase("abcdefghijklmnopqrstuvwxyzzzz");
		nfa_test.add_testcase("abcdefghijklmnopqrstuvwxy");
		nfa_test.add_testcase("abcdefghijklmnopqrstuvwxyzz");
		nfa_test.add_testcase("abdefghijklmnopqrstuvwxyzz");
		nfa_test.add_testcase("bdefghijklmnopqrstuvwxyzz");
		nfa_test.test_group();

		nfa_test.set_pattern("(a)(b)?(c)?(d)?(e)?(f)?(g)?(h)?(i)?(j)?(k)?(l)?(m)?(n)?(o)?(p)?(q)?(r)?(s)?(t)?(u)?(v)?(w)?(x)?(y)?(z+)\\26");
		nfa_test.add_testcase("azz");
		nfa_test.add_testcase("aceizz");
		nfa_test.add_testcase("aczeizz");
		nfa_test.add_testcase("aczeizz");
		nfa_test.add_testcase("acbzz");
		nfa_test.add_testcase("abcdefghijklmnopqrstuvwxyz");
		nfa_test.add_testcase("abcdefghijklmnopqrstuvwxyzzzz");
		nfa_test.add_testcase("abcdefghijklmnopqrstuvwxyzzz");
		nfa_test.add_testcase("abcdefghijklmnopqrstuvwxy");
		nfa_test.add_testcase("abcdefghijklmnopqrstuvwxyzz");
		nfa_test.add_testcase("abdefghijklmnopqrstuvwxyzz");
		nfa_test.add_testcase("bdefghijklmnopqrstuvwxyzz");
		nfa_test.test_group();

	}

	void test_lazy_match()
	{
		//to do
		cout << endl;
		print_string_format(80, "Test Lazy match in class NFA  ", '-', true);
		cout << endl;
		NFATest nfa_test;
		nfa_test.test_lazy_match_can_none();
		nfa_test.test_lazy_match_zero_more();
		nfa_test.test_lazy_match_one_more();
		nfa_test.test_lazy_match_repeat_count();
	}

	void test_zero_length_assertions()
	{
		cout << endl;
		print_string_format(80, "Test Zero-Length Assertions", '-', true);
		cout << endl;
		NFATest nfa_test;
		nfa_test.test_pla_zero_length_assertions();
		cout << endl;
	}

	void NFATest::test_lazy_match_can_none()
	{
		set_pattern("a?(ab)??""(ab)*");
		add_testcase("aab");
		add_testcase("aaab");
		add_testcase("aabab");
		add_testcase("aaaaab");
		add_testcase("acab");
		add_testcase("babaaaab");
		add_testcase("bbabaabab");
		add_testcase("bbbbbbbbbbbbbbbbbbbba");
		add_testcase("abababababababababab");
		add_testcase("123ab132aab2ababd12f9kababab");
		test_group();

		set_pattern("(\\d )??""( *)([yY]ou|I|[Ss]he|[Hh]e)");
		add_testcase("I");
		add_testcase("1  You");
		add_testcase("2He");
		add_testcase("She");
		add_testcase("1  I");
		add_testcase("you2He3She 1");
		add_testcase("    You yo   2  She He");
		add_testcase("               1           She   He");
		add_testcase("you He 12222    SHe He 12 ");
		add_testcase("youYouSheheSheshe    1  You");
		test_group();

		//here should be more testcases
	}

	void NFATest::test_lazy_match_zero_more()
	{
		//to do
		set_pattern(".*(<div>.*?</div>)");
		add_testcase("<div>  </div");
		add_testcase("<div></div>");
		add_testcase("<div>123</div>");
		add_testcase("<div><div>123</div></div>");
		add_testcase("<div><div><p>mis /div</p></div>");
		add_testcase("<div><p>mis div</p></div></div>");
		add_testcase("</div></div>");
		add_testcase("<p>mis div</p></div></div></div>");
		add_testcase("<div><div><div><div><div><p>mis /div</p>");
		add_testcase("<p>some content</p><div>infor mation for p</div>");
		test_group();

		set_pattern("(He|(\\s)he)(\\s+)(\\S*?)e?d");//search sentence like 'He looked' or 'he had'
		add_testcase("Yet another unusual thing about Harry was how little he looked forward to his birthdays. ");
		add_testcase("He had never received a birthday card in his life");
		add_testcase("Harry walked across the dark room, past Hedwig¡¯s large, empty cage, to the open window. ");
		add_testcase("Hedwig had been absent for two nights now.");
		add_testcase("Harry recognized the unconscious owl at once");
		add_testcase("Ron says he¡¯s going to be in London in the last week of the holidays. ");
		add_testcase("He wanted me to debug the program");
		add_testcase("It's surprising that he asked she to do this work");
		add_testcase("\" No no no,it wasn't possible \" ,he said.");
		add_testcase("He he       no       ");
		test_group();
	}

	void NFATest::test_lazy_match_one_more()
	{
		set_pattern("a?(ab)+?""(ab)*");
		add_testcase("aab");
		add_testcase("aaab");
		add_testcase("aabab");
		add_testcase("aaaaab");
		add_testcase("acab");
		add_testcase("babaaaab");
		add_testcase("bbabaabab");
		add_testcase("bbbbbbbbbbbbbbbbbbbba");
		add_testcase("abababababababababab");
		add_testcase("123ab132aab2ababd12f9kababab");
		test_group();

		//here need more testcases

		set_pattern("a?(ab)+?""(ab)+");
		add_testcase("aab");
		add_testcase("aaab");
		add_testcase("aabab");
		add_testcase("aaaaab");
		add_testcase("acab");
		add_testcase("babaaaab");
		add_testcase("bbabaabab");
		add_testcase("bbbbbbbbbbbbbbbbbbbba");
		add_testcase("abababababababababab");
		add_testcase("123ab132aab2ababd12f9kababab");
		test_group();

		set_pattern("ac?a+?(ab)+?");
		add_testcase("aab");
		add_testcase("aaab");
		add_testcase("aabab");
		add_testcase("aaaaab");
		add_testcase("aaacab");
		add_testcase("babaaaab");
		add_testcase("bbabaabab");
		add_testcase("bbbbbbbbbbbbbbbbbbbba");
		add_testcase("abababababababababab");
		add_testcase("a123ab132aab2ababd12f9kababab");
		test_group();
	}

	void NFATest::test_lazy_match_repeat_count()
	{
		set_pattern("a?(ab){2,3}?""(ab)*");
		add_testcase("aab");
		add_testcase("aaab");
		add_testcase("aabab");
		add_testcase("aaaaab");
		add_testcase("acab");
		add_testcase("babaaaab");
		add_testcase("bbabaabab");
		add_testcase("bbbbbbbbbbbbbbbbbbbba");
		add_testcase("abababababababababab");
		add_testcase("123ab132aab2ababd12f9kababab");
		test_group();

		set_pattern("a\\d{1,}?345");
		add_testcase("a345");
		add_testcase("a1345");
		add_testcase("a12345");
		add_testcase("ab3345");
		add_testcase("a333345");
		add_testcase("aaaaaaaaa345");
		add_testcase("a12a1212121345");
		add_testcase("abcdefg123aaaa12121345");
		test_group();

	}

	void NFATest::test_pla_zero_length_assertions()
	{
		cout << endl;
		print_string_format(80, "Test Positive Lookahead Zero-Length Assertions", '-', true);
		cout << endl;
		set_pattern("\\b\\w+(?=ing\\b)");
		add_testcase("inging");
		add_testcase("I'm singing while you're dancing");
		add_testcase("are you kidding me? ");
		add_testcase("inginging reading");
		test_group();
		cout << endl;
	}

	void test_nfa_replace()
	{
		cout << endl;
		print_string_format(80, "Test class NFA and Repalacer ", '-', true);
		cout << endl;
		NFATest nfa_test;
		nfa_test.set_pattern("(a|b)+(a.*d)");
		nfa_test.add_replace_testcase("abb", "c");
		nfa_test.add_replace_testcase("a", "c");
		nfa_test.add_replace_testcase("abbbb", "c");
		nfa_test.add_replace_testcase("abaacdaa", "c");
		nfa_test.add_replace_testcase("aaadbaaaaa", "c");
		nfa_test.add_replace_testcase("ab\nabbb", "c");
		nfa_test.add_replace_testcase("ab\nabbb\n", "c");
		nfa_test.add_replace_testcase("ab\nabbb\n12", "c");
		nfa_test.add_replace_testcase("aacdabded", "c");
		nfa_test.add_replace_testcase("aaabababacdabded", "c");
		nfa_test.add_replace_testcase("aaaaaaaaaaaaacdabdbed", "c");
		nfa_test.add_replace_testcase("acdadbadeadafgacdabded", "c");
		nfa_test.test_replace();

		nfa_test.set_pattern("(\\w)\\1{2,}");
		nfa_test.add_replace_testcase("aaaa1111", "repeat");
		nfa_test.add_replace_testcase("aa123", "repeat");
		nfa_test.add_replace_testcase("123", "repeat");
		nfa_test.add_replace_testcase("1123445690aaa", "repeat");
		nfa_test.add_replace_testcase("abcd", "repeat");
		nfa_test.add_replace_testcase("aabbccc", "repeat");
		nfa_test.add_replace_testcase("11123", "repeat");
		nfa_test.test_replace();
		DirectedGraphPoint diagaph(new DirectedGraph("(\\w)\\1{2,}"));
		NFA nfa(diagaph);
		class PasswordReplacer :public Replacer
		{
		public:
			string replace_match(const Matcher &matcher) const override
			{
				return "<----" + matcher.group() + "----->";
			}
		};
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
		PasswordReplacer password_replacer;
		cout << "replace will like this: 1aaaa2  =>  1<----aaaa----->2 \n" << endl;
		for (string password : passwords)
			cout << password + ":" << replace(nfa, password_replacer, password) << endl;

	}

	void test_nfa_capture()
	{
		cout << endl;
		print_string_format(80, "Test class NFA and Repalacer ", '-', true);
		cout << endl;
		NFATest nfa_test;
		nfa_test.set_pattern("(a|b)+(?<captrue_name>a.*d)", true);
		// for convinient, I reuse the add_replace_testcase
		nfa_test.add_replace_testcase("abb", "captrue_name");
		nfa_test.add_replace_testcase("a", "captrue_name");
		nfa_test.add_replace_testcase("abbbb", "captrue_name");
		nfa_test.add_replace_testcase("abaacdaa", "captrue_name");
		nfa_test.add_replace_testcase("aaadbaaaaa", "captrue_name");
		nfa_test.add_replace_testcase("ab\nabbb", "captrue_name");
		nfa_test.add_replace_testcase("ab\nabbb\n", "captrue_name");
		nfa_test.add_replace_testcase("ab\nabbb\n12", "captrue_name");
		nfa_test.add_replace_testcase("aacdabded", "captrue_name");
		nfa_test.add_replace_testcase("aaabababacdabded", "captrue_name");
		nfa_test.add_replace_testcase("aaaaaaaaaaaaacdabdbed", "captrue_name");
		nfa_test.add_replace_testcase("acdadbadeadafgacdabded", "captrue_name");
		nfa_test.test_single_group_capture();

		nfa_test.set_pattern("(?'repeat'(\\w)\\1{2,})", true);
		nfa_test.add_replace_testcase("aaaa1111", "repeat");
		nfa_test.add_replace_testcase("aa123", "repeat");
		nfa_test.add_replace_testcase("123", "repeat");
		nfa_test.add_replace_testcase("1123445690aaa", "repeat");
		nfa_test.add_replace_testcase("abcd", "repeat");
		nfa_test.add_replace_testcase("aabbccc", "repeat");
		nfa_test.add_replace_testcase("11123", "repeat");
		nfa_test.test_single_group_capture();
	}


	void print_string_format(size_t length, const string &str, char fill_char, bool is_middle)
	{
		if (str.size() > length) cout << "legth:" << std::left << setw(length - 6) << str.size();
		else if (!is_middle)
			cout << str << string(length - str.size(), fill_char);
		else
		{
			size_t before_length = (length - str.size()) / 2, after_length = length - before_length - str.size();
			cout << string(before_length, fill_char) << str << string(after_length, fill_char);
		}
	}
	template<typename NumType>
	void print_number_format(size_t length, NumType num, bool is_left)
	{
		cout << (is_left ? std::left : std::right) << setw(length) << num;
	}
	NFATest::NFATest()
		:nfa(DirectedGraphPoint(new DirectedGraph()))
	{
	}

	NFATest::NFATest(const string & pattern) :pattern(pattern), standard_regex(pattern), nfa(DirectedGraphPoint(new DirectedGraph(pattern)))
	{
	}

	NFATest::NFATest(const string & pattern, const string & test_file_path) : pattern(pattern), standard_regex(pattern), nfa(DirectedGraphPoint(new DirectedGraph(pattern)))
	{
		read_testcases_from_file(test_file_path);
	}

	void NFATest::set_pattern(const string & pattern, bool no_std_regex)
	{
		
		this->pattern = pattern;
		if (!no_std_regex)//especial case for alphabetic chracters
			standard_regex = regex(std::regex_replace(pattern, regex("\\\\a"), "[a-zA-Z]"));
		nfa.compile(pattern);
		testcases.clear();
		replaec_strs.clear();
	}

	void NFATest::set_testcases(const vector<string>& testcases)
	{
		this->testcases = testcases;
	}

	void NFATest::set_testcases(const string & file_path)
	{
		this->testcases.clear();
		read_testcases_from_file(file_path);
	}

	void NFATest::set_testcase(const string & testcase)
	{
		testcases.clear();
		testcases.push_back(testcase);
	}

	void NFATest::add_testcase(const string & testcase)
	{
		testcases.push_back(testcase);
	}

	void NFATest::add_replace_testcase(const string & testcase, const string & replace_str)
	{
		testcases.push_back(testcase);
		replaec_strs.push_back(replace_str);
	}

	void NFATest::add_testcases(const vector<string>& testcases)
	{
		std::copy(testcases.begin(), testcases.end(), std::back_inserter(this->testcases));
	}

	void NFATest::add_testcases(const string & test_file_path)
	{
		read_testcases_from_file(test_file_path);
	}




	void NFATest::read_testcases_from_file(const string & test_file_path)
	{
		std::ifstream input(test_file_path);
		if (input.bad())
		{
			std::cout << test_file_path << " file error!" << std::endl;
			return;
		}
		string line;
		while (input >> line)testcases.push_back(line);
		input.close();
	}

	void NFATest::test_match()
	{
		print_test_information();
		cout << endl;
		size_t testcase_size = testcases.size();
		size_t pass_count = 0, failed_count = 0;
		for (size_t i = 0; i < testcase_size; i++)
		{
			cout << "Test case :";
			print_number_format(5, i + 1);
			if (test_one_match_testcase(testcases[i]))
			{
				pass_count++;
				cout << " Passed!" << endl;
			}
			else
			{
				failed_count++;
				cout << " Failed!" << endl;
				print_string_format(10, "\tPattern", ' ');
				cout << ":" << pattern << endl;
				print_string_format(10, "\tText", ' ');
				cout << ":" << endl << "\t\t";
				print_string_format(70, testcases[i], ' ');
				cout << endl;
			}
		}
		cout << endl;
		print_test_result_information(testcase_size, pass_count, failed_count);
		cout << endl;

	}

	void NFATest::test_search()
	{
		print_test_information();
		cout << endl;
		size_t testcase_size = testcases.size();
		size_t pass_count = 0, failed_count = 0;
		for (size_t i = 0; i < testcase_size; i++)
		{
			cout << "Test case :";
			print_number_format(5, i + 1);
			if (test_one_search_testcase(testcases[i]))
			{
				pass_count++;
				cout << " Passed!" << endl;
			}
			else
			{
				failed_count++;
				cout << " Failed!" << endl;
				print_string_format(10, "\tPattern", ' ');
				cout << ":" << pattern << endl;
				print_string_format(10, "\tText", ' ');
				cout << ":" << endl << "\t\t";
				print_string_format(70, testcases[i], ' ');
				cout << endl;
			}
		}
		cout << endl;
		print_test_result_information(testcase_size, pass_count, failed_count);
		cout << endl;

	}
	void NFATest::test_group()
	{
		print_test_information();
		cout << endl;
		size_t testcase_size = testcases.size();
		size_t pass_count = 0, failed_count = 0;
		for (size_t i = 0; i < testcase_size; i++)
		{
			cout << "Test case :";
			print_number_format(5, i + 1);
			if (test_one_group_testcase(testcases[i]))
			{
				pass_count++;
				cout << " Passed!" << endl;
			}
			else
			{
				failed_count++;
				cout << " Failed!" << endl;
				print_string_format(10, "\tPattern", ' ');
				cout << ":" << pattern << endl;
				print_string_format(10, "\tText", ' ');
				cout << ":" << endl << "\t\t";
				print_string_format(70, testcases[i], ' ');
				cout << endl;
			}
		}
		cout << endl;
		print_test_result_information(testcase_size, pass_count, failed_count);
		cout << endl;
	}
	void NFATest::test_replace()
	{
		print_test_information();
		cout << endl;
		size_t testcase_size = testcases.size();
		size_t pass_count = 0, failed_count = 0;
		for (size_t i = 0; i < testcase_size; i++)
		{
			cout << "Test case :";
			print_number_format(5, i + 1);
			if (test_one_replace_testcase(testcases[i], replaec_strs[i]))
			{
				pass_count++;
				cout << " Passed!" << endl;
			}
			else
			{
				failed_count++;
				cout << " Failed!" << endl;
				print_string_format(10, "\tPattern", ' ');
				cout << ":" << pattern << endl;
				print_string_format(10, "\tText", ' ');
				cout << ":" << endl << "\t\t";
				print_string_format(70, testcases[i], ' ');
				cout << endl;
				print_string_format(10, "\tRepalcer", ' ');
				cout << ":" << endl << "\t\t";
				print_string_format(30, testcases[i], ' ');
				cout << endl;
			}
		}
		cout << endl;
		print_test_result_information(testcase_size, pass_count, failed_count);
		cout << endl;
	}
	void NFATest::test_group_capture()
	{
		print_test_information();
		cout << endl;
		size_t testcase_size = testcases.size();
		size_t pass_count = 0, failed_count = 0;
		for (size_t i = 0; i < testcase_size; i++)
		{
			cout << "Test case :";
			print_number_format(5, i + 1);
			if (test_one_capture_testcase(testcases[i], replaec_strs[i]))
			{
				pass_count++;
				cout << " Passed!" << endl;
			}
			else
			{
				failed_count++;
				cout << " Failed!" << endl;
				print_string_format(10, "\tPattern", ' ');
				cout << ":" << pattern << endl;
				print_string_format(10, "\tText", ' ');
				cout << ":" << endl << "\t\t";
				print_string_format(70, testcases[i], ' ');
				cout << endl;
				print_string_format(10, "\tGroup Name", ' ');
				cout << ":" << endl << "\t\t";
				print_string_format(30, replaec_strs[i], ' ');
				cout << endl;
			}
		}
		cout << endl;
		print_test_result_information(testcase_size, pass_count, failed_count);
		cout << endl;
	}
	void NFATest::print_test_information()
	{
		cout << endl;
		print_string_format(80, "Begein Test Pattern :" + pattern, ' ');
		cout << endl;
		print_string_format(25, "Test Case Amount", ' ');
		cout << ":" << testcases.size() << endl;
	}

	bool NFATest::test_one_match_testcase(const string & testcase)
	{
		NFAMatcher match_result;
		std::smatch std_result;
		bool is_match = std::regex_match(testcase, std_result, standard_regex);
		if (is_match^NFAMatcher::match(testcase, match_result, nfa)) //if the match result is wrong
			return false;
		if (is_match)
		{
			if (std_result.str() != match_result.group()) return false;
			else
			{
				if (std_result.size() != match_result.group_count())return false;
				size_t group_size = std_result.size();
				for (size_t i = 1; i < group_size; i++)
					if (std_result[i] != match_result.group(i))return false;
			}
		}
		return true;
	}

	bool NFATest::test_one_search_testcase(const string & testcase)
	{
		NFAMatcher search_result;
		search_result.set_content(testcase, nfa);
		sregex_iterator begin(testcase.begin(), testcase.end(), standard_regex);
		sregex_iterator end;
		for (; begin != end && search_result.search(); begin++)
			if ((*begin).str() != search_result.group()) return false;
		return begin == end && !search_result.search();
	}

	bool NFATest::test_one_group_testcase(const string & testcase)
	{
		NFAMatcher search_result;
		search_result.set_content(testcase, nfa);
		sregex_iterator begin(testcase.begin(), testcase.end(), standard_regex);
		sregex_iterator end;
		for (; begin != end && search_result.search(); begin++)
		{
			auto &result = *begin;
			if (result.str() != search_result.group()) return false;
			else
			{
				if (result.size() != search_result.group_count())return false;
				size_t group_size = result.size();
				for (size_t i = 1; i < group_size; i++)
					if (result[i] != search_result.group(i))return false;
			}
		}
		return begin == end && !search_result.search();
	}

	bool NFATest::test_one_replace_testcase(const string & testcase, const string &new_string)
	{
		return regex_replace(testcase, standard_regex, new_string) == replace(nfa, new_string, testcase);
	}

	bool NFATest::test_one_capture_testcase(const string & testcase, const string & group_name)
	{

		NFAMatcher search_result;
		search_result.set_content(testcase, nfa);
		sregex_iterator begin(testcase.begin(), testcase.end(), standard_regex);
		sregex_iterator end;
		for (; begin != end && search_result.search(); begin++)
		{
			auto &result = *begin;
			if (result.str() != search_result.group()) return false;
			if (result[search_result.group_index(group_name)] != search_result.group(group_name)) return false;
		}
		return begin == end && !search_result.search();
	}

	void NFATest::test_single_group_capture()
	{
		print_test_information();
		cout << endl;
		size_t testcase_size = testcases.size();
		for (size_t i = 0; i < testcase_size; i++)
		{
			cout << "Test case :";
			print_number_format(5, i + 1);
			//if (test_one_capture_testcase(testcases[i], replaec_strs[i]))
			cout << endl;
			print_string_format(10, "\tPattern", ' ');
			cout << ":" << pattern << endl;
			print_string_format(10, "\tText", ' ');
			cout << ":" << endl << "\t\t";
			print_string_format(70, testcases[i], ' ');
			cout << endl;
			print_string_format(20, "\tGroup Name", ' ');
			cout << ":" << endl << "\t\t";
			print_string_format(30, replaec_strs[i], ' ');
			cout << endl;
			NFAMatcher search_result;
			NFAMatcher::search(testcases[i], search_result, nfa);
			while (search_result.search())
			{
				print_string_format(20, "\tGroup Capture", ' ');
				cout << ":" << endl << "\t\t";
				print_string_format(70, search_result.group(replaec_strs[i]), ' ');
				cout << endl;
			}
		}
		cout << endl;
	}

	

	void NFATest::print_test_result_information(size_t total_test_count, size_t pass_count, size_t failed_count)
	{
		cout << pass_count << "/" << total_test_count << " ";
		print_number_format(10, (100.0*pass_count / total_test_count));
		cout << "% Passed!" << endl;
	}

	int singal_test(const string& pattern, const string &text)
	{
		regex standard_regex(pattern);
		DirectedGraphPoint diagaph(new DirectedGraph(pattern));
		NFA nfa(diagaph);
		sregex_iterator begin(text.begin(), text.end(), standard_regex);
		sregex_iterator end;
		NFAMatcher search_result;
		search_result.set_content(text, nfa);
		int i = 1;
		for (; begin != end && search_result.search(); begin++)
			std::cout << "test " << i++ << ":" << (*begin).str() << " " << search_result.group() << std::endl;
		std::cout << "Test pass?" << (begin == end && !search_result.search() ? "true" : "false") << std::endl;
		return 0;
	}
	int test_standard(const string& pattern, const string &text)
	{
		regex standard_regex(pattern);
		sregex_iterator begin(text.begin(), text.end(), standard_regex);
		sregex_iterator end;
		int i = 1;
		for (; begin != end; begin++)
		{
			auto &result = *begin;
			std::cout << i++ << ":" << result.str() << std::endl;
			size_t group_size = result.size();
			for (size_t j = 0; j < group_size; j++)
			{
				cout << result[j] << endl;
			}
		}
		return 0;
	}
#endif // DEBUG
}
