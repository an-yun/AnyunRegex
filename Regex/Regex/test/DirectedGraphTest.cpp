#include "DirectedGraphTest.h"

namespace anyun_regex
{

#define TEST_PRE_PROCESS_PATTERN(test_string,except_string)												\
	do {																								\
		test_count++;																					\
		string result = diagraph.pre_process_pattern(test_string);										\
		if(diagraph.parse_result == REGEX_PARSE_OK && result == (except_string))						\
		{																								\
			cout<<"Test function pre_process_pattern in testcase "<<test_string<<" passed! "<<endl;		\
			pass_count++;																				\
		}																								\
		else																							\
		{																								\
			cout<<"Test "<<test_count<<" failed, in file "<<__FILE__<<":"<<__LINE__<<endl;				\
			cout<<"\tactual:"<<result<<endl;															\
			cout<<"\texcept:"<<except_string<<endl;														\
		}																								\
	}while(0)

	int test_directedgraph()
	{
		DirectedGraphTest directedgraph_test;
		directedgraph_test.test();
		return 0;
	}



	DirectedGraphTest::DirectedGraphTest()
	{

	}
	void DirectedGraphTest::test()
	{
		cout << "---------------------Test class DirectedGraph---------------------------" << endl;
		test_count = pass_count = 0;
		test_pre_process_normal();
		test_pre_process_error();
		test_compile_normal();
		test_compile_error();
		cout << pass_count << "/" << test_count << " " << setw(4)<<(100.0*pass_count / test_count) << "% passed!";
	}
	void DirectedGraphTest::test_compile_normal()
	{

	}
	void DirectedGraphTest::test_compile_error()
	{
	}
	void DirectedGraphTest::test_pre_process_normal()
	{
		TEST_PRE_PROCESS_PATTERN("", "");
		TEST_PRE_PROCESS_PATTERN("ab", "a\\Nb");
		TEST_PRE_PROCESS_PATTERN("a|b", "a|b");
		TEST_PRE_PROCESS_PATTERN("a|bc", "a|b\\Nc");
		TEST_PRE_PROCESS_PATTERN("(a|b)c", "(a|b)\\Nc");
		TEST_PRE_PROCESS_PATTERN("[0-9]c", "[0-9]\\Nc");
	}
	void DirectedGraphTest::test_pre_process_error()
	{
	}
}

