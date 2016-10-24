#include "Matcher.h"

namespace anyun_regex {

	Matcher::Matcher(string text, size_t cursor) :text(text), cursor(cursor)
	{
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

	void NFAMatcher::set_edge_pass_count(size_t edge_id, size_t count)
	{
		edges_count[edge_id] = count;
	}

	void NFAMatcher::set_node_pass_count(size_t node_id, size_t count)
	{
		nodes_count[node_id] = count;
	}

}

