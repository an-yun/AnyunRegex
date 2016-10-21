#include "NFA.h"

namespace anyun_regex
{
	NFA::NFA():offset(0),is_find(false)
	{

	}

	NFA::NFA(const char * pattern) : digraph(pattern), start_state({ 0 }),offset(0), start_is_final(false),is_find(false)
	{
		if (digraph.parse_result == REGEX_PARSE_OK)start_is_final =get_sigma_closure(start_state);
	}

	NFA::NFA(const string & pattern) :digraph(pattern), start_state({ 0 }), offset(0), start_is_final(false), is_find(false)
	{
		if (digraph.parse_result == REGEX_PARSE_OK)start_is_final = get_sigma_closure(start_state);
	}

	NFA::~NFA()
	{
	}

	bool NFA::compile(const string & pattern)
	{
		return digraph.compile(pattern) == REGEX_PARSE_OK;
	}

	RegexParseCode NFA::get_compile_result_code()
	{
		return digraph.parse_result;
	}

	string NFA::get_compile_message()
	{
		switch (digraph.parse_result)
		{
		case REGEX_PARSE_OK:
			return "compile pased!";
		default:
			return "";
		}
	}

	bool NFA::find()
	{
		//if last search could not find,then return false
		if (!is_find) return false;
		if (offset > text_length) return is_find = false;
		//begin to match ,start from the offset
		size_t start = offset;
		match_start = match_end = offset;
		is_find = false;
		bool get_final = false;
		while (!is_find && start <= text_length)
		{
			list<size_t> state = start_state;
			get_final = start_is_final;
			if (get_final)
			{
				match_start = start;
				match_end = start;
				offset = start+1;
				is_find = true;
				//if greedy remove break
			}
			for (size_t index = start;!state.empty() && index < text_length; index++)
			{

				get_final = get_next_state(state, text[index]);
				//if match,set is_find to true,save the result range to match ,else set false;
				if (get_final)
				{
					match_start = start;
					match_end = index+1;
					offset = index+1;
					is_find = true;
					//if greedy remove break
				}
			}
			start++;
		}
		return is_find;

	}

	void NFA::match(const char * text, postoin_type offset)
	{
		match(string(text));
	}

	void NFA::match(const string & text, postoin_type offset)
	{
		is_find = (digraph.parse_result == REGEX_PARSE_OK);
		this->offset = offset;
		this->text = text;
		this->text_length = text.size();
	}



	string NFA::get_match()
	{
		return text.substr(match_start,match_end-match_start);
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

	bool NFA::get_sigma_closure(list<size_t>& source)
	{
		bool get_final = false;
		//breath first search
		vector<bool> visited(digraph.v(), false);
		queue<size_t> node_ids;

		//add all source nodes
		for (list<size_t>::iterator b = source.begin(), e = source.end(); b != e; b++)
		{
			size_t id = *b;
			visited[id] = true;
			node_ids.push(id);
			if (digraph.nodes[id].is_final())get_final = true;
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
					if (digraph.nodes[end_node_id].is_final())get_final = true;
				}
			}

		}
		return get_final;
	}
	bool NFA::get_next_state(list<size_t>& state, char ch)
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
		return get_sigma_closure(state);
	}
}
