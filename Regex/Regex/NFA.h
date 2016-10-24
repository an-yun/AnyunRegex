#ifndef NFA_H
#define NFA_H

#include <algorithm>
#include <string>
#include <list>
#include <set>
#include <queue>
#include <iterator>
#include <memory>
#include "DirectedGraph.h"

namespace anyun_regex
{
	using std::string;
	using std::list;
	using std::queue;
	using std::set;
	using std::back_inserter;
	using std::copy;
	using std::shared_ptr;
	class Matcher;
	class NFAMatcher;
	class NFA
	{
	public:
		typedef size_t postoin_type;

		NFA();
		NFA(const char *pattern);
		NFA(const string & pattern);
		~NFA();

		bool compile(const string &pattern);
		RegexParseCode get_compile_result_code();
		string get_compile_message();
		void match(const char * text, postoin_type offset = 0);
		void match(const string & text, postoin_type offset = 0);
		bool find();
		string get_match();

		size_t get_match_start();
		size_t get_match_end();
		const char *get_pattern();


	private:
		DirectedGraphPoint digraph;
		list<size_t> start_state;
		string text;
		size_t text_length;
		size_t match_start;
		size_t match_end;
		postoin_type offset;
		bool start_is_final;
		bool is_find;

		bool get_sigma_closure(list<size_t> &source);
		bool get_next_state(list<size_t> & state, const string &text, size_t index, Matcher &matcher);
	};

}

#endif // !NFA