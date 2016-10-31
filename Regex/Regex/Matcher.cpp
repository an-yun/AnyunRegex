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
			State state;
			TrackRecode temp_record;
			temp_record[0] = current_cursor();
			state.push_back({ 0,temp_record });
			nfa.read_nochar_edge(state, text, cursor, *this);
			if (nfa.has_final_state(state))
			{
				nfa.update_group_node_record(state,*this,true);
				next_start = start + 1;
				is_find = true;
				//if greedy remove break
			}	
			for (; !state.empty() && cursor < text_length; next())
			{
				nfa.get_next_state(state, text, cursor, *this);
				nfa.read_nochar_edge(state, text, cursor, *this);
				//if match,set is_find to true,save the result range to match ,else set false;
				if (nfa.has_final_state(state))
				{
					nfa.update_group_node_record(state, *this);
					next_start = cursor + 1;
					is_find = true;
					//if greedy remove break
				}
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


	NFAMatcher::NFAMatcher(const string & text, const NFA & nfa, size_t offset)
		:Matcher(text,offset,nfa.group_size())
		, nfa(nfa), is_find(true), text_length(text.length())
	{
	}

}

