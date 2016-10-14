#include "string_algorithm.h"
#include "string_algorithm_test.h"


int main()
{
	
	vector<matching_algorithm_information_type> algorithms =
	{
		{ "naive_string_mather",naive_string_mather },
		{ "rabin_karp_matcher",rabin_karp_matcher},
		{ "finite_automaton_matcher",finite_automaton_matcher },
		{ "kmp_matcher",kmp_matcher },

	};
	ofstream out_result("result.txt");
	cout.rdbuf(out_result.rdbuf());
	test(algorithms, "testcases.txt");
	out_result.flush();
	out_result.close();
	return 0;
}