#ifndef NFA_H
#define NFA_H

#include <algorithm>
#include <string>
#include <list>
#include <set>
#include <utility>
#include <map>
#include <queue>
#include <iterator>
#include <memory>
#include "DirectedGraph.h"

namespace anyun_regex
{
	using std::string;
	using std::list;
	using std::queue;
	using std::map;
	using std::pair;
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

		//the new design for NFAMatcher
		pair<size_t, TrackRecode>  * has_final_state(State &states) const;
		void get_next_state(State & state, const string &text,  Matcher &matcher) const;
		void read_nochar_edge(State & state, const string &text, Matcher &matcher) const;
		void update_group_node_record(State & state, Matcher &matcher) const;
		void visit_one_node(size_t parent_node_id, size_t visit_node_id, State & state, queue<size_t> &node_ids,vector<bool> &visited,Matcher &matcher) const;

		OneState &get_one_node_record(size_t node_id, State& state) const;
	};

}

#endif // !NFA