#include "Matcher.h"

namespace anyun_regex {
	NFAMatcher NFAMatcher::match(const string & text, const NFA & nfa, size_t offset)
	{
		return NFAMatcher(text,nfa,offset);
	}
	bool NFAMatcher::find()
	{
		return false;
	}

	bool NFAMatcher::find(size_t offset)
	{
		return false;
	}

	string NFAMatcher::group(size_t index) const
	{
		return string();
	}

	string NFAMatcher::group(string group_name) const
	{
		return string();
	}

	size_t NFAMatcher::group_count() const
	{
		return size_t();
	}

	size_t NFAMatcher::peek()
	{
		return text[cursor];
	}

	size_t NFAMatcher::next()
	{
	}

	size_t NFAMatcher::back()
	{
		return text[cursor--];
	}

	size_t NFAMatcher::get_edge_pass_count(size_t edge_id) const
	{
		return edges_count[edge_id];
	}

	size_t NFAMatcher::get_node_pass_count(size_t node_id) const
	{
		return nodes_count[node_id];
	}

	void NFAMatcher::add_edge_pass_count(size_t edge_id)
	{
		edges_count[edge_id] ++;
	}

	void NFAMatcher::add_node_pass_count(size_t node_id)
	{
		nodes_count[node_id]++;
	}

	NFAMatcher::NFAMatcher(const string & text, const NFA & nfa, size_t offset):Matcher(text,offset)
	{
	}

}

