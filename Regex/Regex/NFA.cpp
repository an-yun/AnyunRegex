#include "NFA.h"

namespace anyun_regex
{
	NFA::NFA():text(nullptr),offset(0),is_find(false)
	{

	}

	NFA::NFA(const char * pattern) : digraph(pattern), start_state({ 0 }),text(nullptr), offset(0), start_is_final(false),is_find(false)
	{
		if (digraph.parse_result == REGEX_PARSE_OK)get_sigma_closure(start_state, start_is_final);
	}

	NFA::NFA(const string & pattern) :digraph(pattern), start_state({ 0 }), text(nullptr), offset(0), start_is_final(false), is_find(false)
	{
		if(digraph.parse_result== REGEX_PARSE_OK)get_sigma_closure(start_state, start_is_final);
	}

	NFA::~NFA()
	{
	}

	bool NFA::find()
	{
		//if last time search could not find,then return false
		if (!is_find) return false;
		
		//begin to match ,start from the offset
		size_t start = offset;
		match_start = match_end = offset;

		if (start_is_final)
		{
			is_find = (text[offset]!='\0');
			offset++;
			return true;
		}
		else is_find = false;


		while ((!is_find) && text[start] != '\0')
		{
			list<size_t> state = start_state;
			for (size_t index = start; !state.empty() && text[index] != '\0'; index++)
			{
				get_next_state(state, text[index], is_find);
				//if match,set is_find to true,save the result range to match ,else set false;
				if (is_find)
				{
					match_start = start;
					match_end = index+1;
					offset = start + 1;
					break;
				}
			}
			start++;
		}

		return is_find;
	}

	void NFA::match(const char * text, postoin_type offset)
	{
		is_find = (digraph.parse_result == REGEX_PARSE_OK);
		this->offset = offset;
		this->text = text;
	}

	char* NFA::get_match(char *match)
	{
		if (start_is_final && !is_find) return match;
		else if (is_find)
		{
			char *end =copy(text + match_start, text + match_end, match);
			*end = '\0';
			return end;
		}
		else return nullptr;
	}

	size_t NFA::get_match_start()
	{
		return match_start;
	}

	size_t NFA::get_match_end()
	{
		return match_end;
	}

	const char * NFA::get_pattern()
	{
		return digraph.pattern.c_str();
	}

	void NFA::get_sigma_closure(list<size_t>& source, bool &is_find)
	{

		//breath first search
		vector<bool> visited(digraph.v(), false);
		queue<size_t> node_ids;

		//add all source nodes
		for (list<size_t>::iterator b = source.begin(), e = source.end(); b != e; b++)
		{
			size_t id = *b;
			visited[id] = true;
			node_ids.push(id);
			if (digraph.nodes[id].is_final())is_find = true;
		}

		while (!node_ids.empty())
		{
			size_t node_id = node_ids.front();
			node_ids.pop();
			const vector<size_t> &out_edges = digraph.nodes[node_id].get_out_edges();
			for (vector<size_t>::const_iterator b = out_edges.cbegin(), e = out_edges.cend(); b != e; b++)
			{
				size_t edge_id = *b;
				size_t end_node_id = digraph.edges[edge_id].get_end_node_id();
				if ((!visited[end_node_id]) && digraph.edges[edge_id].is_sigma_edge())
				{
					visited[end_node_id] = true;
					node_ids.push(end_node_id);
					source.push_back(end_node_id);
					if (digraph.nodes[end_node_id].is_final())is_find = true;
				}
			}

		}
	}
	void NFA::get_next_state(list<size_t>& state, char ch, bool &is_find)
	{
		set<size_t> next_state;
		vector<DirectedEdge> &edges = digraph.edges;
		for (list<size_t>::iterator b = state.begin(), e = state.end(); b != e; b++)
		{
			//check every edge that can accept ch
			const vector<size_t> &out_edges = digraph.nodes[*b].get_out_edges();
			for (vector<size_t>::const_iterator edge_b = out_edges.begin(), edge_e = out_edges.cend(); edge_b != edge_e; edge_b++)
				if (edges[*edge_b].accept(ch))next_state.insert(edges[*edge_b].get_end_node_id());
		}
		state.clear();
		copy(next_state.begin(), next_state.end(), back_inserter(state));
		get_sigma_closure(state,is_find);
	}
}
