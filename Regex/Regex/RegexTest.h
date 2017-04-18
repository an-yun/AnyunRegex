/*
 *
 *	The regex test framwork header
 *
 */


//add one regex test moudule
#define BOOST_TEST_MODULE REGEX_TEST_MOUDLE

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <string>

//add one test case macro
#ifndef ADD_ONE_TEST_CASE
#define ADD_ONE_TEST_CASE BOOST_AUTO_TEST_CASE
#endif

//add one test case for pre process pattern
#ifndef ADD_ONE_TEST_CASE_FOR_PRE_PROCESS_PATTERN
#define ADD_ONE_TEST_CASE_FOR_PRE_PROCESS_PATTERN(test_case_name,pattern,after_pre_process_pattern)				\
ADD_ONE_TEST_CASE(test_case_name)																				\
{																												\
	::anyun_regex::DirectedGraph test_diagraph;																	\
	::std::string pre_process_result = test_diagraph.pre_process_pattern(pattern);								\
	::anyun_regex::RegexParseCode parse_result_code = test_diagraph.get_parse_result_code();					\
	BOOST_TEST(pre_process_result == (after_pre_process_pattern),												\
			   "test pre process result for '" << pattern <<	"':'"<<pre_process_result						\
			   <<"' is not as expected '" <<(after_pre_process_pattern) <<"'.");											\
	BOOST_TEST(parse_result_code == ::anyun_regex::REGEX_PARSE_OK,												\
			  "the pre process result code for '" << pattern <<	"':'"											\
			  <<::anyun_regex::PARSE_RESULT_MESSAGE[parse_result_code]											\
			   <<"' is not as expected  'REGEX_PARSE_OK'.");																	\
}
#endif

#ifndef ADD_TEST_CASE_FOR_PRE_PROCESS_PATTERN
namespace regex_test_data = boost::unit_test::data;
#include "DirectedGraph.h"
#define ADD_NORMAL_TESTCASE_FOR_PRE_PROCESS(test_case_name,testcases,pattern,after_pre_process_pattern)			\
BOOST_DATA_TEST_CASE(test_case_name)																			\
{																												\
	::anyun_regex::DirectedGraph test_diagraph;																	\
	BOOST_TEST(test_diagraph.pre_process_pattern(pattern) == (after_pre_process_pattern),"");					\
}														
#endif