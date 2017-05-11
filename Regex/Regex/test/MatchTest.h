#pragma once
#include "../RegexTestFramework.h"
std::vector<match_testcases_t> match_testcases
{

	{".*",{
"1b",
"4a",
"Mayflies, also known as shadflies or fishflies in Canada",
".cc .cpp .cxx .C .c++ .h .hh .hpp .hxx .h++",
"are aquatic insects belonging to the order Ephemeroptera",
"Immature mayflies are aquatic",
"Adult mayflies, or imagos, are relatively primitive in structure",
"Often, all the mayflies in a population mature at once (a hatch), and for a day or two in the spring or autumn",
"1c23abcb",
"1ab2ab3abbb",
"1)*&^$3b3abbb",

}},{"a|b",{
"a",
"b",
"ab",
"aaa",
"bbbb",
"134erq",
"abceefaeq",
"ewqtefadsfqrte",
"ewrertrtweryrrety4",
"$^(4ad)(^(03431)))923",

}},{"a1|2bc",{
"a",
"b",
"2bc",
"a1aa",
"a1bca",
"ba2bcbb",
"134erq",
"abcea1bcaefaeq",
"ewqtefadsfqrte",
"ewrertrtweryrrety4",
"$^(4ad)(^(03431",
"a111bbbbcc$^cca_)&",
"b1#a2^22a2bcbbbcbb)))923",
"C++ Is Designed by	Bjarne Stroustrup",
"can you find me is a1|2bc match this a12bc ro match this a1bc",

}},{"am|is|are",{
"are you ok?",
"I am fine!",
"thank you.",
"who is he?",
"can the regex engine find me aa aa aa ia sr s  ar aa a aam ,ok you get it",
"",

}},{"he(r|ll)o",{
"hello",
"hero",
"are you ok?",
"I am fine!",
"can the regex engine find me aa aa aa ia sr s  ar aa a aam ,ok you get it wrong",
}
},{"[123]ab*",{
"1a",
"1b",
"4a",
"2abb",
"23abb",
"c23abcb",
"1c23abcb",
"1ab2ab3abbb",
"1abbadafdasfdasfdasfdfdasf2abbb3abasdfbb",


}},{"[a-zA-Z_][a-zA-Z0-9_]*",{
"dfe",
"12fe",
"abdfe",
"c_edfe",
"_hell1a001",
"AB_Edsae12nfa_hell",
"nfa&helld1a AB_c0 001",
"nfa _hell 1a AB_c0 001",

}
},{"^ab*$",{
"abb",
"a",
"abbbb",
"abaacdaa",
"aaadbaaaaa",
"ab\nabbb",
"ab\nabbb\n",
"ab\nabbb\n12",
}

},{"a+\\d{2,6}",{
"a",
"a1",
"ba12",
"aba123456",
"a1234567",
"aaaaaaa36",
"11111112a3",
"1aa1aa112a3",
"a&1@b#a1908",
"123aaaji8eaa",

}
}, { "a*a{2,}b{1,}",{
"ab",
"aaab",
"aaaabbb",
"aaaabbabaa",
"aaaabbbbaaab",
"aaaab12abaabaa",
"12aaaabbbbbbbbbbbb",
"aca12\\^%12asdaaaabb",
}
}, { "\\s+ab*\\s+",{
" abb ",
"a",
" abbc",
"\ta\n",

}
//url test
}, { "[a-zA-z]+://[^\\s]*",{
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
//email test
},{"\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*",{
"foo@demo.net",
"bar.ba@test.co.uk",
"zsy296@gmail.com",
"1007252397@qq.com",
"b-+  ar.ba@test.co.uk",
"http://deerchao.net/tutorials/regex/common.htm",
} } };

ADD_MATCH_TEST_SUIT(test_match, match_testcases);