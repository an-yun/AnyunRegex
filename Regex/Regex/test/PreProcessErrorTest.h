#pragma once

#include "../RegexTestFramework.h"


using namespace anyun_regex;
std::vector<pre_process_error_test_case_t> pre_process_error_test_cases
{
	{ "*", REGEX_PARSE_ILLEGAL_QUALIFIER_CHAR },
	{ "+", REGEX_PARSE_ILLEGAL_QUALIFIER_CHAR },
	{ "|", REGEX_PARSE_ILLEGAL_QUALIFIER_CHAR },
	{ "||", REGEX_PARSE_ILLEGAL_QUALIFIER_CHAR },
	{ "(", REGEX_PARSE_MISS_RIGHT_BRACKET },
	{ ")", REGEX_PARSE_MISS_LEFT_BRACKET },
	{ "(a||b)", REGEX_PARSE_ILLEGAL_CHAR_AFTER_OR },
	{ "a|*b", REGEX_PARSE_ILLEGAL_CHAR_AFTER_OR },
	{ "(a()", REGEX_PARSE_MISS_RIGHT_BRACKET },
	{ "(a(cd)", REGEX_PARSE_MISS_RIGHT_BRACKET },
	{ "(a(cd)", REGEX_PARSE_MISS_RIGHT_BRACKET },
	{ "(a(cd)", REGEX_PARSE_MISS_RIGHT_BRACKET },
	{ "[", REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET },
	{ "]", REGEX_PARSE_MISS_LEFT_SQUARE_BRACKET },
	{ "[][", REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET },
	{ "[1-9][", REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET },
	{ "[1-9[]][", REGEX_PARSE_SQUARE_BRAKET_NESTED },
	{ "[a{2,3}", REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET },
	{ "{", REGEX_PARSE_MISS_RIGHT_BRACES },
	{ "}", REGEX_PARSE_MISS_LEFT_BRACES },
	{ "[a]13}", REGEX_PARSE_MISS_LEFT_BRACES },
	{ "^[1-9][", REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET },
	{ "[1-9[]][$", REGEX_PARSE_SQUARE_BRAKET_NESTED },
	{ "^[a{2,3}$", REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET },
	{ "^{", REGEX_PARSE_MISS_RIGHT_BRACES },
	{ "}$", REGEX_PARSE_MISS_LEFT_BRACES },
	{ "\\N", REGEX_PARSE_ILLEGAL_ESCAPE_CHAR },
	{ "a\\N", REGEX_PARSE_ILLEGAL_ESCAPE_CHAR },
	// here need more test to name capture
	{ "a(?<my_namea)", REGEX_PARSE_MISS_END_CHAR_FOR_NAMECAPTURE },
	{ "a(?'my_nameab)", REGEX_PARSE_MISS_END_CHAR_FOR_NAMECAPTURE }
};


ADD_ERROR_TESTCASE_FOR_PRE_PROCESS(pre_process_error_test, regex_test_data::make(pre_process_error_test_cases))