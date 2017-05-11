#pragma once

#include "../RegexTestFramework.h"

std::vector<pre_process_normal_test_case_t> pre_process_normal_test_cases
{
	{ "", "" },
	{ "ab", "a\\Nb" },
	{ "abbba", "a\\Nb\\Nb\\Nb\\Na" },
	{ "a|b", "a|b" },
	{ "a|bc", "a|b\\Nc" },
	{ "a|b|123", "a|b|1\\N2\\N3" },
	{ "(a|b)c", "(a|b)\\Nc" }, 
	{ "(a|bb)c", "(a|b\\Nb)\\Nc" },
	{ "(a|b)|123", "(a|b)|1\\N2\\N3" },
	{ "(A|a)(B|b)(C|c)(E|e)", "(A|a)\\N(B|b)\\N(C|c)\\N(E|e)" },
	{ "[0-9]c", "[0-9]\\Nc" },
	{ "[0-9a-z]c", "[0-9a-z]\\Nc" },
	{ "[0-9A-Z!]c", "[0-9A-Z!]\\Nc" },
	{ "[0-9A-Z!](are|you)c", "[0-9A-Z!]\\N(a\\Nr\\Ne|y\\No\\Nu)\\Nc" },
	{ "(a|b){2}", "(a|b){2}" },
	{ "(a|b){2,5}", "(a|b){2,5}" },
	{ "(a|b){2,}", "(a|b){2,}" },
	{ "(a|b){2,}c", "(a|b){2,}\\Nc" },
	{ "(a|b){2,}c", "(a|b){2,}\\Nc" },
	{ "(A|a)(B|b)c{2,5}D", "(A|a)\\N(B|b)\\Nc{2,5}\\ND" },
	{ "(a|b|c|d){2,5}D", "(a|b|c|d){2,5}\\ND" },
	{ "(a|b|c|d){2,5}D", "(a|b|c|d){2,5}\\ND" },
	{ "[0-9](a|b|c|d){2,5}D", "[0-9]\\N(a|b|c|d){2,5}\\ND" },
	{ "^", "^" },
	{ "$", "$" },
	{ "^$", "^\\N$" },
	{ "^a$", "^\\Na\\N$" },
	{ "^(ab|bc[123])$", "^\\N(a\\Nb|b\\Nc\\N[123])\\N$" },
	{ "^[0-9](a|b|c|d){2,5}D$", "^\\N[0-9]\\N(a|b|c|d){2,5}\\ND\\N$" },
	{ "\\n", "\\n" },
	{ "a\\n", "a\\N\\n" },
	{ "^ab$\\nc", "^\\Na\\Nb\\N$\\N\\n\\Nc" },
	{ "ab\\nb\\rba", "a\\Nb\\N\\n\\Nb\\N\\r\\Nb\\Na" },
	{ "a(?<my_name>a)", "a\\N(?<my_name>a)" },
	{ "a(?'my_name'ab)", "a\\N(?'my_name'a\\Nb)" },
};

ADD_NORMAL_TESTCASE_FOR_PRE_PROCESS(pre_process_normal_test, regex_test_data::make(pre_process_normal_test_cases))
