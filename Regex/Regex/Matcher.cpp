#include "Matcher.h"

namespace anyun_regex {
	bool NFAMatcher::search(const string & text, NFAMatcher& search_result, const string & pattern, size_t offset)
	{
		search_result.set_content(text,pattern);
		return search_result.search(offset);
	}

	bool NFAMatcher::search(const string & text, NFAMatcher & search_result, const NFA & nfa, size_t offset)
	{
		search_result.set_content(text, nfa);
		return search_result.search(offset);
	}

	bool NFAMatcher::match(const string & text, NFAMatcher& match_result, const string & pattern, size_t offset)
	{
		match_result.set_content(text, pattern);
		return match_result.match(offset, text.size());
	}

	bool NFAMatcher::match(const string & text, NFAMatcher & match_result, const NFA & nfa, size_t offset)
	{
		match_result.set_content(text, nfa);
		return match_result.match(offset, text.size());
	}


	bool NFAMatcher::match(const string & text, NFAMatcher& match_result, const string & pattern, size_t start, size_t end)
	{
		match_result.set_content(text, pattern);
		return match_result.match(start,end);
	}

	bool NFAMatcher::match(const string & text, NFAMatcher & match_result, const NFA & nfa, size_t start, size_t end)
	{
		match_result.set_content(text, nfa);
		return match_result.match(start, end);
	}

	NFAMatcher::NFAMatcher()
		:has_set(false)
	{
	}

	void NFAMatcher::set_content(const string & text, const string & pattern)
	{
		Matcher::set_content(text,pattern);
		is_find = true;
		has_set = true;
	}

	void NFAMatcher::set_content(const string & text, const NFA & nfa)
	{
		set_text(text);
		set_nfa(nfa);
		set_groups(nfa.group_size());
		is_find = true;
		has_set = true;
	}

	
	void NFAMatcher::set_text(const string & text)
	{
		Matcher::set_text(text);
		text_length = text.size();
	}

	void NFAMatcher::set_pattern(const string& pattern)
	{
		nfa.compile(pattern);
		set_groups(nfa.group_size());
	}

	bool NFAMatcher::match()
	{
		return has_set && match(0,text_length);
	}


	bool NFAMatcher::match(size_t start, size_t end)
	{
		if (!has_set || start > text_length) return false;
		SaveState save_state;
		TrackRecord temp_record;
		temp_record[0] = { start,1 };
		save_state.push({ 0,0,temp_record });

		//begin to match
		while (!save_state.empty())
		{
			OneSaveState &one_save_state = save_state.top();
			TrackRecord &track_recode = std::get<2>(one_save_state);
			if (nfa.digraph->end_node_id == std::get<0>(one_save_state))
			{
				if(track_recode[nfa.digraph->end_node_id].first == end)
				{
					nfa.update_group_node_record(std::get<2>(one_save_state), *this);
					return  true;
				}
				save_state.pop();
			}
			nfa.get_next_state(save_state, text, *this);
		}
		return false;
	}


	bool NFAMatcher::search(size_t offset)
	{
		if(!has_set) return false;
		cursor = offset;
		is_find = true;
		return search();
	}


	bool NFAMatcher::search()
	{
		//this is the new find method fisrst copy the old implement
		if (!has_set ||!is_find) return false;
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

	void NFAMatcher::set_nfa(NFA nfa)
	{
		this->nfa = nfa;
	}

}

