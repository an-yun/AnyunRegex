#include "string_algorithm.h"

position_type naive_string_mather(const string & T, const string & P)
{
	position_type result;
	size_t t_size = T.size(), p_size = P.size(), s = t_size - p_size;
	if (string_match_edge_case(result, t_size, p_size))return result;
	for (size_t i = 0; i <= s; i++)
	{
		bool find = true;
		for (size_t j = 0; j < p_size && find; j++)
			if (T[i + j] != P[j]) find = false;
		if (find)  result.push_back(i);
	}
	return result;
}

position_type rabin_karp_matcher(const string & T, const string & P)
{
	position_type result;
	size_t t_size = T.size(), p_size = P.size(), s = t_size - p_size;
	if (string_match_edge_case(result, t_size, p_size))return result;
	const size_t q = 16777619U;   //Prime 
	const size_t d = 255U;			//base,can't be 256

	size_t h = 1, p = P[0] % q, t = T[0] % q; //remove %p is also right
	for (size_t i = 1; i < p_size; i++)
	{
		h = (h *d) % q;
		p = (d*p + P[i]) % q;
		t = (d*t + T[i]) % q;
	}

	for (size_t i = 0; i <= s; i++)
	{
		if (p == t)
		{
			bool find = true;
			for (size_t j = 0; j < p_size; j++)
			{
				if (T[i + j] != P[j])
				{
					find = false;
					break;
				}
			}
			if (find)  result.push_back(i);
		}
		if (i < s)
			t = (d *((t + q - (T[i] * h) % q) % q) + T[i + p_size]) % q;
	}

	return result;
}

position_type finite_automaton_matcher(const string & T, const string & P)
{
	position_type result;
	size_t t_size = T.size(), p_size = P.size(), s = t_size - p_size;
	if (string_match_edge_case(result, t_size, p_size))return result;
	
	
	const size_t base = 256U;//the base
	vector<vector<size_t>> automaton(p_size + 1, vector<size_t>(base, 0));

	//comput the string-matching automaton
	size_t mismatch_state = 0;
	automaton[0][P[0]] = 1;
	for (size_t i = 1; i < p_size; i++)
	{
		for (size_t ch = 0; ch < base; ch++)
			automaton[i][ch] = automaton[mismatch_state][ch];
		automaton[i][P[i]] = i+1;
		mismatch_state = automaton[mismatch_state][P[i]];
	}
	//this end state
	for (size_t ch = 0; ch < base; ch++)
		automaton[p_size][ch] = automaton[mismatch_state][ch];

	//begin to match string
	size_t state = 0;
	for (size_t i = 0; i < t_size; i++)
	{
		state = automaton[state][T[i]];
		if (state == p_size) result.push_back(i + 1 - p_size);
	}

	return result;
}

position_type kmp_matcher(const string & T, const string & P)
{
	position_type result;
	size_t t_size = T.size(), p_size = P.size(), s = t_size - p_size;
	if (string_match_edge_case(result, t_size, p_size))return result;

	//computing prefixfuction
	vector<size_t> pi(p_size, 0);
	size_t k = 0;
	for (size_t i = 1; i < p_size; i++)
	{
		while (k > 0 && P[k] != P[i])  k = pi[k-1];
		if (P[k] == P[i]) k++;
		pi[i] = k;
	}

	//match the text
	size_t state = 0;
	for (size_t i = 0; i < t_size; i++)
	{
		while (state > 0 && P[state] != T[i]) state = pi[state-1];
		if (P[state] == T[i]) state++;
		if (state == p_size)
		{
			result.push_back(i + 1 - p_size);
			state = pi[state - 1];
		}
	}

	return result;
}

bool string_match_edge_case(position_type & result, size_t t_size, size_t p_size)
{
	if (p_size > t_size) return true;
	if (p_size == 0)
	{
		for (size_t i = 0; i<t_size; i++)result.push_back(i);
		return true;
	}
	return false;
}
