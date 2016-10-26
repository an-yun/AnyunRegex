#include "Matcher.h"

namespace anyun_regex {

	NFAMatcher NFAMatcher::match(const string & text, const NFA & nfa, size_t offset)
	{
		return NFAMatcher(text,nfa,offset);
	}
	bool NFAMatcher::find()
	{
		//if last search could not find,then return false
		if (!is_find) return false;
		if (cursor > text_length) return is_find = false;
		//begin to match ,start from the offset
		size_t next_start = cursor,start = cursor;
		is_find = false;
		while (!is_find && start <= text_length)
		{
			cursor = start;
			list<size_t> state = start_state;
			if (nfa.has_final_state(state))
			{
				next_start = start + 1;
				is_find = true;
				//if greedy remove break
			}			
			nfa.update_group_start_state(state, *this);
			nfa.update_group_end_state(state, *this);
			for (; !state.empty() && cursor < text_length; next())
			{
				nfa.get_next_state(state, text, cursor, *this);
				nfa.get_sigma_closure(state);
				//if match,set is_find to true,save the result range to match ,else set false;
				if (nfa.has_final_state(state))
				{
					next_start = cursor + 1;
					is_find = true;
					//if greedy remove break
				}
				nfa.update_group_start_state(state, *this);
				nfa.update_group_end_state(state, *this);
			}
			start++;
		}
		cursor = next_start;
		return is_find;
	}

	bool NFAMatcher::find(size_t offset)
	{
		cursor = offset;
		is_find = true;
		return find();
	}

	string NFAMatcher::group(size_t index) const
	{
		if(is_find)return text.substr(groups[index].first, groups[index].second - groups[index].first);
		else return string("");
	}

	string NFAMatcher::group(string group_name) const
	{
		map<string,size_t>::const_iterator result = name_groups.find(group_name);
		if (result == name_groups.cend()) return string("");
		else return group((*result).second);
	}

	size_t NFAMatcher::group_count() const
	{
		return nfa.group_size();
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

	NFAMatcher::NFAMatcher(const string & text, const NFA & nfa, size_t offset)
		:Matcher(text,offset,nfa.group_size())
		,nfa(nfa),edges_count(nfa.edge_size()),nodes_count(nfa.node_size())
		,start_state{0}, start_is_final(false),is_find(true),text_length(text.length())
	{
		this->nfa.get_sigma_closure(start_state);
		start_is_final = this->nfa.has_final_state(start_state);
	}

}

