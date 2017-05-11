/*
 *
 *	The regex test framwork header
 *
 */

//add one regex test moudule
#pragma once
#define BOOST_TEST_MODULE REGEX_TEST_MOUDLE
#include <iostream>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/timer/timer.hpp>
#include <vector>
#include <utility>
#include <string>
#include <boost/regex.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/bind.hpp>
#include "DirectedGraph.h"
using namespace boost::unit_test;
namespace tt = boost::test_tools;
using namespace boost;
using std::pair;
using boost::timer::cpu_timer;
using boost::timer::cpu_times;
using boost::timer::format;
using boost::timer::default_places;
using boost::regex;
using boost::smatch;
using boost::sregex_iterator;
using boost::regex_replace;
using boost::match_results;

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

//perform one normal test for pre compile pattern
#define TEST_NORMAL_COMPILE_PATTERN(pattern)																		\
	do{																												\
		::anyun_regex::DirectedGraph test_diagraph(pattern);														\
		::std::cout<<"test normal DirectedGraph.compile for '"<<pattern<<"'"<<std::endl;							\
		::anyun_regex::RegexParseCode parse_result_code = test_diagraph.get_parse_result_code();					\
		BOOST_TEST(parse_result_code == ::anyun_regex::REGEX_PARSE_OK,												\
				  "the compile test result code for '" << pattern <<	"' is'"										\
				  <<::anyun_regex::PARSE_RESULT_MESSAGE[parse_result_code]											\
				   <<"' (expected:'REGEX_PARSE_OK')");																\
	}while(false)


//perform one error test for compile pattern
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

//add normal test case for compile pattern
#define ADD_NORMAL_TESTCASE_FOR_COMPILE(test_case_name,testcases)													\
	ADD_DATA_TEST_CASE(test_case_name,testcases,one_testcase)	{TEST_NORMAL_COMPILE_PATTERN(one_testcase);}	


//add error test case for compile pattern
#define ADD_ERROR_TESTCASE_FOR_COMPILE(test_case_name,testcases)													\
	ADD_DATA_TEST_CASE(test_case_name,testcases,one_testcase)	{TEST_ERROR_COMPILE_PATTERN(one_testcase.first,one_testcase.second);}				


//test suit macro
#define BEGING_TEST_SUIT(test_suit_name) BOOST_AUTO_TEST_SUITE(test_suit_name)
#define END_TEST_SUIT() BOOST_AUTO_TEST_SUITE_END();


typedef std::pair<const char*, std::vector<const char*>> match_testcases_t;
typedef match_testcases_t search_testcases_t;

inline cpu_times &operator+=(cpu_times &t1, const cpu_times &t2)
{
	t1.wall += t2.wall;
	t1.system += t2.system;
	t1.user += t2.user;
	return t1;
}

inline cpu_times &operator/=(cpu_times &t1, unsigned num)
{
	t1.wall /= num;
	t1.system /= num;
	t1.user /= num;
	return t1;
}

struct TestFixture
{
	anyun_regex::NFA nfa;
	boost::regex standard_regex;

	TestFixture(std::string pattern)
		:nfa(pattern), standard_regex(pattern)
	{}

	pair<cpu_times, cpu_times> test_match(const std::string &testcase)
	{
		anyun_regex::NFAMatcher match_result;
		smatch std_result;
		::std::cout << "test match pattern:" << standard_regex.expression() << " ,text:" << testcase<<std::endl;
		cpu_timer t_1;
		bool test_match = anyun_regex::NFAMatcher::match(testcase, match_result, nfa);
		t_1.stop();
		cpu_timer t_2;
		bool standard_match = regex_match(testcase, std_result, standard_regex);
		t_2.stop();
		BOOST_TEST(test_match == standard_match); //if the match result is wrong
		if (standard_match)
		{
			BOOST_TEST(std_result.str() == match_result.group());
			BOOST_TEST(std_result.size() == match_result.group_count());
			size_t group_size = std_result.size();
			for (size_t i = 1; i < group_size; i++)
				BOOST_TEST(std_result[i] == match_result.group(i));
		}
		::std::cout << "anyun regex cost:" << format(t_1.elapsed(), default_places, "%ws,") 
			<<"boost regex cost:"<< format(t_2.elapsed(), default_places, "%ws") << std::endl;
		return{ t_1.elapsed() ,t_2.elapsed() };
	}


	pair<cpu_times, cpu_times> test_search(const std::string &testcase)
	{
		
		std::vector<smatch> boost_search_results;
		std::vector<anyun_regex::NFAMatcher> test_search_results;
		anyun_regex::NFAMatcher search_result;
		search_result.set_content(testcase, nfa);
		::std::cout << "test search pattern:" << standard_regex.expression() << " ,text:" << testcase << std::endl;
		cpu_timer t_2;
		sregex_iterator begin(testcase.begin(), testcase.end(), standard_regex);
		sregex_iterator end;
		for (; begin != end; begin++)boost_search_results.push_back(*begin);
		t_2.stop();
		cpu_timer t_1;
		while (search_result.search())test_search_results.push_back(search_result);
		t_1.stop();
		BOOST_TEST(boost_search_results.size() == test_search_results.size());
		size_t search_amount = boost_search_results.size();
		for(size_t i=0;i<search_amount;i++)
		{
			anyun_regex::NFAMatcher &one_test_result = test_search_results[i];
			smatch & one_boost_result = boost_search_results[i];
			BOOST_TEST(one_boost_result.str() == one_test_result.group());
			BOOST_TEST(one_boost_result.size() == one_test_result.group_count());
			size_t group_size = one_boost_result.size();
			for (size_t j = 1; j < group_size; j++)
				BOOST_TEST(one_boost_result[j] == one_test_result.group(j));
		}
		::std::cout << "anyun regex cost:" << format(t_1.elapsed(), default_places, "%ws,")
			<< "boost regex cost:" << format(t_2.elapsed(), default_places, "%ws") << std::endl;
		return{ t_1.elapsed() ,t_2.elapsed() };
	}
};

//add match test case
#define ADD_MATCH_TEST_SUIT(test_case_name,match_test_cases)																\
	ADD_ONE_TEST_CASE(test_case_name)																						\
	{																														\
	for(std::vector<match_testcases_t>::iterator b =  match_test_cases.begin(),												\
		e = match_test_cases.end();b!=e;b++) {																				\
		match_testcases_t one_match_test_case = *b;																			\
		std::string pattern = one_match_test_case.first;																	\
		std::vector<const char*> test_texts = one_match_test_case.second;													\
		TestFixture testFixture(pattern);																					\
		cpu_times cost_time;																								\
		cost_time.clear();																									\
		for(std::vector<const char*>::iterator b= test_texts.begin(),e= test_texts.end();b!=e;b++)							\
		cost_time += testFixture.test_match(*b).first;																		\
		::std::cout << "anyun average regex cost:" << format(cost_time/=test_texts.size(), default_places, "%ws\n");		\
	}}

//add serach test case
#define ADD_SERACH_TEST_SUIT(test_case_name,match_test_cases)																\
	ADD_ONE_TEST_CASE(test_case_name)																						\
	{																														\
	for(std::vector<match_testcases_t>::iterator b =  match_test_cases.begin(),												\
		e = match_test_cases.end();b!=e;b++) {																				\
		match_testcases_t one_match_test_case = *b;																			\
		std::string pattern = one_match_test_case.first;																	\
		std::vector<const char*> test_texts = one_match_test_case.second;													\
		TestFixture testFixture(pattern);																					\
		cpu_times cost_time;																								\
		cost_time.clear();																									\
		for(std::vector<const char*>::iterator b= test_texts.begin(),e= test_texts.end();b!=e;b++)							\
		cost_time += testFixture.test_search(*b).first;																		\
		::std::cout << "anyun average regex cost:" << format(cost_time/=test_texts.size(), default_places, "%ws\n");		\
	}}