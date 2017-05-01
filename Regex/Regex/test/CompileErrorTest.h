#pragma once

#include "../RegexTestFramework.h"


using namespace anyun_regex;

std::vector<compile_error_test_case_t> compile_error_test_cases =
{
	/*  here some test case to add parse
	*/

	{"a{a,}", REGEX_PARSE_ILLEGAL_REPEAT_COUNT},
	{"12{1,0}", REGEX_PARSE_ILLEGAL_REPEAT_COUNT},
	{"[9-1]", REGEX_PARSE_WRONG_RANGE_IN_SQUARE_BRAKET},
	{"[8-6]", REGEX_PARSE_WRONG_RANGE_IN_SQUARE_BRAKET},
	{"[c-1]", REGEX_PARSE_WRONG_RANGE_IN_SQUARE_BRAKET},
	{"[\\c]", REGEX_PARSE_ILLEGAL_CHAR_IN_SQUARE_BRAKET},
	{"[\\q]", REGEX_PARSE_ILLEGAL_CHAR_IN_SQUARE_BRAKET},
	{"([abc]+)\\0", REGEX_PARSE_ILLEGAL_GROUP_REFERENCE},
	{"([abc]+)\\2", REGEX_PARSE_ILLEGAL_GROUP_REFERENCE}
};

ADD_ERROR_TESTCASE_FOR_COMPILE(compile_error_test, regex_test_data::make(compile_error_test_cases))