#include "Matcher.h"

namespace anyun_regex {

	NFAMatcher NFAMatcher::match(const string & text, const NFA & nfa, size_t offset)
	{
		return NFAMatcher(text,nfa,offset);
	}

	bool NFAMatcher::find(size_t offset)
	{
		cursor = offset;
		is_find = true;
		return find();
	}

	bool NFAMatcher::find()
	{
		//this is the new find method fisrst copy the old implement
		if (!is_find) return false;
		if (cursor > text_length) return is_find = false;
		//begin to match ,start from the offset
		is_find = false;
		while (!is_find && cursor <= text_length)
		{
			SaveState save_state;
			TrackRecord temp_record;
			temp_record[0] = { cursor,1 };
			save_state.push({ 0,0,temp_record });

			//begin to find
			while (!save_state.empty())
			{
				OneSaveState &one_save_state = save_state.top();
				if (nfa.digraph->end_node_id == std::get<0>(one_save_state))
				{
					size_t temp_cursor = nfa.update_group_node_record(std::get<2>(one_save_state), *this);
					if (temp_cursor == cursor)
						cursor++;
					else cursor = temp_cursor;
					return is_find = true;
				}
				nfa.get_next_state(save_state, text, *this);
				
			}
			cursor++;
		}
		return is_find;
	}

	string NFAMatcher::group(size_t index) const
	{
		if(is_find && groups[index].first !=groups[index].second)return text.substr(groups[index].first, groups[index].second - groups[index].first);
		else return string("");
	}

	string NFAMatcher::group(string group_name) const
	{
		map<string,size_t>::const_iterator result = nfa.digraph->name_groups.find(group_name);
		if (result == nfa.digraph->name_groups.cend()) return string("");
		return group((*result).second);
	}

	size_t NFAMatcher::group_index(string group_name) const
	{
		map<string, size_t>::const_iterator result = nfa.digraph->name_groups.find(group_name);
		if (result == nfa.digraph->name_groups.cend()) return static_cast<size_t>(-1);
		return (*result).second;
	}

	size_t NFAMatcher::group_count() const
	{
		return nfa.group_size();
	}

	pair<size_t, size_t> NFAMatcher::get_groups_node(size_t group_id)
	{
		Group &group = nfa.digraph->groups[group_id];
		return pair<size_t, size_t>(group.group_start_node,group.group_end_node);
	}


	NFAMatcher::NFAMatcher(const string & text, const NFA & nfa, size_t offset)
		:Matcher(text,offset,nfa.group_size())
		, nfa(nfa), is_find(true), text_length(text.length())
	{
	}

}

