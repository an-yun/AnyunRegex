#include "DirectedGraphTest.h"

namespace anyun_regex
{
#ifdef _DEBUG

#define TEST_PRE_PROCESS_PATTERN(test_string,except_string)												\
	do {																								\
		test_count++;																					\
		string result = diagraph.pre_process_pattern(test_string);										\
		if(diagraph.parse_result == REGEX_PARSE_OK && result == (except_string))						\
		{																								\
			cout<<"Test case :"<<test_count<<" passed! "<<endl;											\
			pass_count++;																				\
		}																								\
		else																							\
		{																								\
			cout<<"Test "<<test_count<<" failed, in file "<<__FILE__<<":"<<__LINE__<<endl;				\
			cout<<"\tactual:"<<result<<endl;															\
			cout<<"\texcept:"<<except_string<<endl;														\
		}																								\
	}while(0)

#define TEST_PRE_PROCESS_PATTERN_ERROR(test_string,except_parse_code)									\
	do {																								\
		test_count++;																					\
		string result = diagraph.pre_process_pattern(test_string);										\
		if(diagraph.parse_result == except_parse_code && result == "")									\
		{																								\
			cout<<"Test case :"<<test_count<<" passed! "<<endl;											\
			pass_count++;																				\
		}																								\
		else																							\
		{																								\
			cout<<"Test "<<test_count<<" failed, in file "<<__FILE__<<":"<<__LINE__<<endl;				\
			cout<<"\ttest string:\""<<(test_string)<<"\""<<endl;										\
			cout<<"\tactual:"<<PARSE_RESULT_MESSAGE[diagraph.parse_result]<<endl;						\
			cout<<"\texcept:"<<PARSE_RESULT_MESSAGE[except_parse_code]<<endl;							\
		}																								\
	}while(0)

#define TEST_COMPILE_PATTERN_NORMAL(test_string)														\
	do {																								\
		test_count++;																					\
		diagraph.compile(test_string);																	\
		if(diagraph.parse_result == REGEX_PARSE_OK )													\
		{																								\
			cout<<"Test case :"<<test_count<<" passed! "<<endl;											\
			pass_count++;																				\
		}																								\
		else																							\
		{																								\
			cout<<"Test "<<test_count<<" failed, in file "<<__FILE__<<":"<<__LINE__<<endl;				\
			cout<<"\ttest string:\""<<(test_string)<<"\""<<endl;										\
			cout<<"\tactual:"<<PARSE_RESULT_MESSAGE[diagraph.parse_result]<<endl;						\
			cout<<"\texcept:"<<PARSE_RESULT_MESSAGE[REGEX_PARSE_OK]<<endl;								\
		}																								\
	}while(0)


#define TEST_COMPILE_PATTERN_ERROR(test_string,except_parse_code)										\
	do {																								\
		test_count++;																					\
		diagraph.compile(test_string);																	\
		if(diagraph.parse_result == except_parse_code)													\
		{																								\
			cout<<"Test case :"<<test_count<<" passed! "<<endl;											\
			pass_count++;																				\
		}																								\
		else																							\
		{																								\
			cout<<"Test "<<test_count<<" failed, in file "<<__FILE__<<":"<<__LINE__<<endl;				\
			cout<<"\ttest string:\""<<(test_string)<<"\""<<endl;										\
			cout<<"\tactual:"<<PARSE_RESULT_MESSAGE[diagraph.parse_result]<<endl;						\
			cout<<"\texcept:"<<PARSE_RESULT_MESSAGE[except_parse_code]<<endl;							\
		}																								\
	}while(0)


	int test_directedgraph()
	{
		DirectedGraphTest directedgraph_test;
		directedgraph_test.test();
		return 0;
	}



	DirectedGraphTest::DirectedGraphTest()
		:test_count(0), pass_count(0)
	{

	}
	void DirectedGraphTest::test()
	{
		print_string_format(80, "Test class DirectedGraph Begin", '-', true);
		cout << endl;
		test_count = pass_count = 0;
		test_pre_process_normal();
		test_pre_process_error();
		test_compile_normal();
		test_compile_error();
		cout << pass_count << "/" << test_count << " " << setw(4) << (100.0*pass_count / test_count) << "% passed!" << endl;
		print_string_format(80, "Test class DirectedGraph End", '-', true);
		cout << endl;
	}
	void DirectedGraphTest::test_compile_normal()
	{
		print_string_format(80, "Test function test_compile_normal", ' ');
		cout << endl;
		TEST_COMPILE_PATTERN_NORMAL("");
		TEST_COMPILE_PATTERN_NORMAL("ab");
		TEST_COMPILE_PATTERN_NORMAL("abbba");
		TEST_COMPILE_PATTERN_NORMAL("a|b");
		TEST_COMPILE_PATTERN_NORMAL("a|bc");
		TEST_COMPILE_PATTERN_NORMAL("a|b|123");
		TEST_COMPILE_PATTERN_NORMAL("(a|b)c");
		TEST_COMPILE_PATTERN_NORMAL("(a|bb)c");
		TEST_COMPILE_PATTERN_NORMAL("(a|b)|123");
		TEST_COMPILE_PATTERN_NORMAL("(A|a)(B|b)(C|c)(E|e)");
		TEST_COMPILE_PATTERN_NORMAL("[0-9]c");
		TEST_COMPILE_PATTERN_NORMAL("[0-9a-z]c");
		TEST_COMPILE_PATTERN_NORMAL("[0-9A-Z!]c");
		TEST_COMPILE_PATTERN_NORMAL("[\\w\\s]ab1");
		TEST_COMPILE_PATTERN_NORMAL("[\\daeiou]ab1");
		TEST_COMPILE_PATTERN_NORMAL("[0-9A-Z!](are|you)c");
		TEST_COMPILE_PATTERN_NORMAL("(a|b){2}");
		TEST_COMPILE_PATTERN_NORMAL("(a|b){2,5}");
		TEST_COMPILE_PATTERN_NORMAL("(a|b){2,}");
		TEST_COMPILE_PATTERN_NORMAL("(a|b){2,}c");
		TEST_COMPILE_PATTERN_NORMAL("(a|b){2,}c");
		TEST_COMPILE_PATTERN_NORMAL("(A|a)(B|b)c{2,5}D");
		TEST_COMPILE_PATTERN_NORMAL("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)(p)(q)(r)(s)(t)(u)(v)(w)(x)(y)(z+)\\26");
		TEST_COMPILE_PATTERN_NORMAL("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)(n)(o)(p)(q)(r)(s)(t)(u)(v)(w)(x)(y)(z+)\\g{26}");
		TEST_COMPILE_PATTERN_NORMAL("(a)(b)?(c)?(d)?(e)?(f)?(g)?(h)?(i)?(j)?(k)?(l)?(m)?(n)?(o)?(p)?(q)?(r)?(s)?(t)?(u)?(v)?(w)?(x)?(y)?(z+)\\26");
		TEST_COMPILE_PATTERN_NORMAL("(a)(b)?(c)?(d)?(e)?(f)?(g)?(h)?(i)?(j)?(k)?(l)?(m)?(n)?(o)?(p)?(q)?(r)?(s)?(t)?(u)?(v)?(w)?(x)?(y)?(z+)\\g{26}");
		TEST_COMPILE_PATTERN_NORMAL("(a|b|c|d){2,5}D");
		TEST_COMPILE_PATTERN_NORMAL("(a|b|c|d){2,5}D");
		TEST_COMPILE_PATTERN_NORMAL("[0-9](a|b|c|d){2,5}D");
		TEST_COMPILE_PATTERN_NORMAL("^");
		TEST_COMPILE_PATTERN_NORMAL("$");
		TEST_COMPILE_PATTERN_NORMAL("^$");
		TEST_COMPILE_PATTERN_NORMAL("^a$");
		TEST_COMPILE_PATTERN_NORMAL("^(ab|bc[123])$");
		TEST_COMPILE_PATTERN_NORMAL("^[0-9](a|b|c|d){2,5}D$");
		TEST_COMPILE_PATTERN_NORMAL("\\n");
		TEST_COMPILE_PATTERN_NORMAL("a\\n");
		TEST_COMPILE_PATTERN_NORMAL("^ab$\\nc");
		TEST_COMPILE_PATTERN_NORMAL("ab\\nb\\rba");
		TEST_COMPILE_PATTERN_NORMAL("a(?<my_name>a)");
		TEST_COMPILE_PATTERN_NORMAL("a(?'my_name'ab)");
		TEST_COMPILE_PATTERN_NORMAL("\\b\\w+(?=ing\\b)");
		TEST_COMPILE_PATTERN_NORMAL("\\b((?!abc)\\w)+\\b");
		TEST_COMPILE_PATTERN_NORMAL("\\b(?!\\d)\\w+\\b");
		TEST_COMPILE_PATTERN_NORMAL("(?<=\\bre)\\w+\\b");
		TEST_COMPILE_PATTERN_NORMAL("(?<=[yY]ou)\\b\\w+\\b");
		TEST_COMPILE_PATTERN_NORMAL("(?<![a-zA-Z])\\d+");

		cout << endl;
	}
	void DirectedGraphTest::test_compile_error()
	{
		print_string_format(80, "Test function test_compile_error", ' ');
		cout << endl;
		TEST_COMPILE_PATTERN_ERROR("a{a,}", REGEX_PARSE_ILLEGAL_REPEAT_COUNT);
		TEST_COMPILE_PATTERN_ERROR("12{1,0}", REGEX_PARSE_ILLEGAL_REPEAT_COUNT);
		TEST_COMPILE_PATTERN_ERROR("[9-1]", REGEX_PARSE_WRONG_RANGE_IN_SQUARE_BRAKET);
		TEST_COMPILE_PATTERN_ERROR("[8-6]", REGEX_PARSE_WRONG_RANGE_IN_SQUARE_BRAKET);
		TEST_COMPILE_PATTERN_ERROR("[c-1]", REGEX_PARSE_WRONG_RANGE_IN_SQUARE_BRAKET);
		TEST_COMPILE_PATTERN_ERROR("[\\c]", REGEX_PARSE_ILLEGAL_CHAR_IN_SQUARE_BRAKET);
		TEST_COMPILE_PATTERN_ERROR("[\\q]", REGEX_PARSE_ILLEGAL_CHAR_IN_SQUARE_BRAKET);
		TEST_COMPILE_PATTERN_ERROR("([abc]+)\\0", REGEX_PARSE_ILLEGAL_GROUP_REFERENCE);
		TEST_COMPILE_PATTERN_ERROR("([abc]+)\\2", REGEX_PARSE_ILLEGAL_GROUP_REFERENCE);

		cout << endl;
	}
	void DirectedGraphTest::test_pre_process_normal()
	{
		print_string_format(80, "Test function test_pre_process_normal", ' ');
		cout << endl;
		TEST_PRE_PROCESS_PATTERN("", "");
		TEST_PRE_PROCESS_PATTERN("ab", "a\\Nb");
		TEST_PRE_PROCESS_PATTERN("abbba", "a\\Nb\\Nb\\Nb\\Na");
		TEST_PRE_PROCESS_PATTERN("a|b", "a|b");
		TEST_PRE_PROCESS_PATTERN("a|bc", "a|b\\Nc");
		TEST_PRE_PROCESS_PATTERN("a|b|123", "a|b|1\\N2\\N3");
		TEST_PRE_PROCESS_PATTERN("(a|b)c", "(a|b)\\Nc");
		TEST_PRE_PROCESS_PATTERN("(a|bb)c", "(a|b\\Nb)\\Nc");
		TEST_PRE_PROCESS_PATTERN("(a|b)|123", "(a|b)|1\\N2\\N3");
		TEST_PRE_PROCESS_PATTERN("(A|a)(B|b)(C|c)(E|e)", "(A|a)\\N(B|b)\\N(C|c)\\N(E|e)");
		TEST_PRE_PROCESS_PATTERN("[0-9]c", "[0-9]\\Nc");
		TEST_PRE_PROCESS_PATTERN("[0-9a-z]c", "[0-9a-z]\\Nc");
		TEST_PRE_PROCESS_PATTERN("[0-9A-Z!]c", "[0-9A-Z!]\\Nc");
		TEST_PRE_PROCESS_PATTERN("[0-9A-Z!](are|you)c", "[0-9A-Z!]\\N(a\\Nr\\Ne|y\\No\\Nu)\\Nc");
		TEST_PRE_PROCESS_PATTERN("(a|b){2}", "(a|b){2}");
		TEST_PRE_PROCESS_PATTERN("(a|b){2,5}", "(a|b){2,5}");
		TEST_PRE_PROCESS_PATTERN("(a|b){2,}", "(a|b){2,}");
		TEST_PRE_PROCESS_PATTERN("(a|b){2,}c", "(a|b){2,}\\Nc");
		TEST_PRE_PROCESS_PATTERN("(a|b){2,}c", "(a|b){2,}\\Nc");
		TEST_PRE_PROCESS_PATTERN("(A|a)(B|b)c{2,5}D", "(A|a)\\N(B|b)\\Nc{2,5}\\ND");
		TEST_PRE_PROCESS_PATTERN("(a|b|c|d){2,5}D", "(a|b|c|d){2,5}\\ND");
		TEST_PRE_PROCESS_PATTERN("(a|b|c|d){2,5}D", "(a|b|c|d){2,5}\\ND");
		TEST_PRE_PROCESS_PATTERN("[0-9](a|b|c|d){2,5}D", "[0-9]\\N(a|b|c|d){2,5}\\ND");
		TEST_PRE_PROCESS_PATTERN("^", "^");
		TEST_PRE_PROCESS_PATTERN("$", "$");
		TEST_PRE_PROCESS_PATTERN("^$", "^\\N$");
		TEST_PRE_PROCESS_PATTERN("^a$", "^\\Na\\N$");
		TEST_PRE_PROCESS_PATTERN("^(ab|bc[123])$", "^\\N(a\\Nb|b\\Nc\\N[123])\\N$");
		TEST_PRE_PROCESS_PATTERN("^[0-9](a|b|c|d){2,5}D$", "^\\N[0-9]\\N(a|b|c|d){2,5}\\ND\\N$");
		TEST_PRE_PROCESS_PATTERN("\\n", "\\n");
		TEST_PRE_PROCESS_PATTERN("a\\n", "a\\N\\n");
		TEST_PRE_PROCESS_PATTERN("^ab$\\nc", "^\\Na\\Nb\\N$\\N\\n\\Nc");
		TEST_PRE_PROCESS_PATTERN("ab\\nb\\rba", "a\\Nb\\N\\n\\Nb\\N\\r\\Nb\\Na");
		TEST_PRE_PROCESS_PATTERN("a(?<my_name>a)", "a\\N(?<my_name>a)");
		TEST_PRE_PROCESS_PATTERN("a(?'my_name'ab)", "a\\N(?'my_name'a\\Nb)");

		cout << endl;

	}
	void DirectedGraphTest::test_pre_process_error()
	{
		print_string_format(80, "Test function test_pre_process_error", ' ');
		cout << endl;
		TEST_PRE_PROCESS_PATTERN_ERROR("*", REGEX_PARSE_ILLEGAL_QUALIFIER_CHAR);
		TEST_PRE_PROCESS_PATTERN_ERROR("+", REGEX_PARSE_ILLEGAL_QUALIFIER_CHAR);
		TEST_PRE_PROCESS_PATTERN_ERROR("|", REGEX_PARSE_ILLEGAL_QUALIFIER_CHAR);
		TEST_PRE_PROCESS_PATTERN_ERROR("||", REGEX_PARSE_ILLEGAL_QUALIFIER_CHAR);
		TEST_PRE_PROCESS_PATTERN_ERROR("(", REGEX_PARSE_MISS_RIGHT_BRACKET);
		TEST_PRE_PROCESS_PATTERN_ERROR(")", REGEX_PARSE_MISS_LEFT_BRACKET);
		TEST_PRE_PROCESS_PATTERN_ERROR("(a||b)", REGEX_PARSE_ILLEGAL_CHAR_AFTER_OR);
		TEST_PRE_PROCESS_PATTERN_ERROR("a|*b", REGEX_PARSE_ILLEGAL_CHAR_AFTER_OR);
		TEST_PRE_PROCESS_PATTERN_ERROR("(a()", REGEX_PARSE_MISS_RIGHT_BRACKET);
		TEST_PRE_PROCESS_PATTERN_ERROR("(a(cd)", REGEX_PARSE_MISS_RIGHT_BRACKET);
		TEST_PRE_PROCESS_PATTERN_ERROR("(a(cd)", REGEX_PARSE_MISS_RIGHT_BRACKET);
		TEST_PRE_PROCESS_PATTERN_ERROR("(a(cd)", REGEX_PARSE_MISS_RIGHT_BRACKET);
		TEST_PRE_PROCESS_PATTERN_ERROR("[", REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET);
		TEST_PRE_PROCESS_PATTERN_ERROR("]", REGEX_PARSE_MISS_LEFT_SQUARE_BRACKET);
		TEST_PRE_PROCESS_PATTERN_ERROR("[][", REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET);
		TEST_PRE_PROCESS_PATTERN_ERROR("[1-9][", REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET);
		TEST_PRE_PROCESS_PATTERN_ERROR("[1-9[]][", REGEX_PARSE_SQUARE_BRAKET_NESTED);
		TEST_PRE_PROCESS_PATTERN_ERROR("[a{2,3}", REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET);
		TEST_PRE_PROCESS_PATTERN_ERROR("{", REGEX_PARSE_MISS_RIGHT_BRACES);
		TEST_PRE_PROCESS_PATTERN_ERROR("}", REGEX_PARSE_MISS_LEFT_BRACES);
		TEST_PRE_PROCESS_PATTERN_ERROR("[a]13}", REGEX_PARSE_MISS_LEFT_BRACES);
		TEST_PRE_PROCESS_PATTERN_ERROR("^[1-9][", REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET);
		TEST_PRE_PROCESS_PATTERN_ERROR("[1-9[]][$", REGEX_PARSE_SQUARE_BRAKET_NESTED);
		TEST_PRE_PROCESS_PATTERN_ERROR("^[a{2,3}$", REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET);
		TEST_PRE_PROCESS_PATTERN_ERROR("^{", REGEX_PARSE_MISS_RIGHT_BRACES);
		TEST_PRE_PROCESS_PATTERN_ERROR("}$", REGEX_PARSE_MISS_LEFT_BRACES);
		TEST_PRE_PROCESS_PATTERN_ERROR("\\N", REGEX_PARSE_ILLEGAL_ESCAPE_CHAR);
		TEST_PRE_PROCESS_PATTERN_ERROR("a\\N", REGEX_PARSE_ILLEGAL_ESCAPE_CHAR);
		// here need more test to name capture
		TEST_PRE_PROCESS_PATTERN_ERROR("a(?<my_namea)", REGEX_PARSE_MISS_END_CHAR_FOR_NAMECAPTURE);
		TEST_PRE_PROCESS_PATTERN_ERROR("a(?'my_nameab)", REGEX_PARSE_MISS_END_CHAR_FOR_NAMECAPTURE);
		cout << endl;

	}
#endif // _DEBUG
}

