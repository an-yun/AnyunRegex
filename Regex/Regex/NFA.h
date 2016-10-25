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
	class NFA
	{
		friend class NFAMatcher;
	public:
		NFA(const char *pattern = "");
		NFA(const string & pattern);
		~NFA();
		//recompline another pattern,success return true else false
		bool compile(const string &pattern);
		RegexParseCode get_compile_result_code() const;
		string get_compile_message() const;
		string get_pattern() const;

		size_t group_size() const;
		size_t node_size() const;
		size_t edge_size() const;

	private:
		DirectedGraphPoint digraph;
		
		//is there a group start state,if the answer is yes then mark it in matcher
		void update_group_start_state(list<size_t> &states,Matcher &matcher);
		void update_group_end_state(list<size_t> &states, Matcher &matcher);
		void get_sigma_closure(list<size_t> &source);
		void get_next_state(list<size_t> & state, const string &text, size_t index, Matcher &matcher);

		bool has_final_state(list<size_t> &states);
	};

}

#endif // !NFA