/*
 *
 *	The regex test framwork header
 *
 */

//add one regex test moudule
#pragma once
#define BOOST_TEST_MODULE REGEX_TEST_MOUDLE

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <vector>
#include <utility>
#include <string>
#include "DirectedGraph.h"

namespace regex_test_data = boost::unit_test::data;

//add one test case macro
#define ADD_ONE_TEST_CASE BOOST_AUTO_TEST_CASE

//add several test case macro
#define ADD_DATA_TEST_CASE BOOST_DATA_TEST_CASE

typedef std::pair<const char*, const char*> pre_process_normal_test_case_t;
BOOST_TEST_DONT_PRINT_LOG_VALUE(pre_process_normal_test_case_t)

typedef std::pair<const char*, anyun_regex::RegexParseCode> pre_process_error_test_case_t;
BOOST_TEST_DONT_PRINT_LOG_VALUE(pre_process_error_test_case_t)

typedef pre_process_error_test_case_t compile_error_test_case_t;

//perform one normal test for pre process pattern
#define TEST_NORMAL_PRE_PROCESS_PATTERN(pattern,after_pre_process_pattern)											\
	do{																												\
		::anyun_regex::DirectedGraph test_diagraph;																	\
		::std::string pre_process_result = test_diagraph.pre_process_pattern(pattern);								\
		::std::cout<<"test normal DirectedGraph.pre_process_pattern for '"<<pattern<<"'"<<std::endl;				\
		::anyun_regex::RegexParseCode parse_result_code = test_diagraph.get_parse_result_code();					\
		BOOST_TEST(pre_process_result == (after_pre_process_pattern),												\
				   "the pre process test result for '" << pattern <<	"' is '"<<pre_process_result				\
				   <<"' (expected:'" <<(after_pre_process_pattern) <<"')");											\
		BOOST_TEST(parse_result_code == ::anyun_regex::REGEX_PARSE_OK,												\
				  "the pre process test result code for '" << pattern <<	"' is'"									\
				  <<::anyun_regex::PARSE_RESULT_MESSAGE[parse_result_code]											\
				   <<"' (expected:'REGEX_PARSE_OK')");																\
	}while(false)

//perform one error test for pre process pattern
#define TEST_ERROR_PRE_PROCESS_PATTERN(pattern,excepted_parase_error_code)											\
	do{																												\
		::anyun_regex::DirectedGraph test_diagraph;																	\
		::std::string pre_process_result = test_diagraph.pre_process_pattern(pattern);								\
		::std::cout<<"test error DirectedGraph.pre_process_pattern for '"<<pattern<<"'"<<std::endl;					\
		::anyun_regex::RegexParseCode parse_result_code = test_diagraph.get_parse_result_code();					\
		BOOST_TEST(pre_process_result == "",																		\
				   "the pre process test result for '" << pattern <<	"' is '"<<pre_process_result				\
				   <<"' (expected:'')");																			\
		BOOST_TEST(parse_result_code == excepted_parase_error_code,													\
				  "the pre process test result code for '" << pattern <<	"' is'"									\
				  <<::anyun_regex::PARSE_RESULT_MESSAGE[parse_result_code]											\
				   <<"' (expected:'"<<::anyun_regex::PARSE_RESULT_MESSAGE[excepted_parase_error_code]<<"')");		\
	}while(false)

//perform one error test for COMPILE pattern
#define TEST_ERROR_COMPILE_PATTERN(pattern,excepted_parase_error_code)												\
	do{																												\
		::anyun_regex::DirectedGraph test_diagraph(pattern);														\
		::std::cout<<"test error DirectedGraph.compile for '"<<pattern<<"'"<<std::endl;								\
		::anyun_regex::RegexParseCode parse_result_code = test_diagraph.get_parse_result_code();					\
		BOOST_TEST(parse_result_code == excepted_parase_error_code,													\
				  "the compile test result code for '" << pattern <<	"' is'"										\
				  <<::anyun_regex::PARSE_RESULT_MESSAGE[parse_result_code]											\
				   <<"' (expected:'"<<::anyun_regex::PARSE_RESULT_MESSAGE[excepted_parase_error_code]<<"')");		\
	}while(false)

//add one test case for pre process pattern
#define ADD_ONE_NORMAL_TEST_CASE_FOR_PRE_PROCESS_PATTERN(test_case_name,pattern,after_pre_process_pattern)			\
	ADD_ONE_TEST_CASE(test_case_name) {TEST_NORMAL_PRE_PROCESS_PATTERN(pattern,after_pre_process_pattern);}

//add normal test case for pre process pattern
#define ADD_NORMAL_TESTCASE_FOR_PRE_PROCESS(test_case_name,testcases)												\
	ADD_DATA_TEST_CASE(test_case_name,testcases,one_testcase)	{TEST_NORMAL_PRE_PROCESS_PATTERN(one_testcase.first,one_testcase.second);}	

//add error test case for pre process pattern
#define ADD_ERROR_TESTCASE_FOR_PRE_PROCESS(test_case_name,testcases)												\
	ADD_DATA_TEST_CASE(test_case_name,testcases,one_testcase)	{TEST_ERROR_PRE_PROCESS_PATTERN(one_testcase.first,one_testcase.second);}	

//add error test case for compile pattern
#define ADD_ERROR_TESTCASE_FOR_COMPILE(test_case_name,testcases)													\
	ADD_DATA_TEST_CASE(test_case_name,testcases,one_testcase)	{TEST_ERROR_COMPILE_PATTERN(one_testcase.first,one_testcase.second);}	

//test suit macro
#define BEGING_TEST_SUIT(test_suit_name) BOOST_AUTO_TEST_SUITE(test_suit_name)
#define END_TEST_SUIT() BOOST_AUTO_TEST_SUITE_END();
