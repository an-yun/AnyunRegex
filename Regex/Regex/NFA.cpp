#include "NFA.h"

namespace anyun_regex
{
#define VISITED_ONE_NODE(visit_node_id,the_queue,the_states)\
	do {										\
		if(visited[visit_node_id] == false)		\
		{										\
			visited[visit_node_id] = true;		\
			the_queue.push(visit_node_id);		\
			the_states.insert(visit_node_id);}	\
	} while (0)



	NFA::NFA(const char * pattern)
		: digraph(new DirectedGraph(pattern))
	{

	}

	NFA::NFA(const string & pattern)
		: digraph(new DirectedGraph(pattern))
	{
	}

	NFA::~NFA()
	{
	}

	bool NFA::compile(const string & pattern)
	{
		digraph.reset(new DirectedGraph(pattern));
		return digraph->parse_result == REGEX_PARSE_OK;
	}

	RegexParseCode NFA::get_compile_result_code() const
	{
		return digraph->parse_result;
	}

	string NFA::get_compile_message() const
	{
		return PARSE_RESULT_MESSAGE[digraph->parse_result];
	}


	string NFA::get_pattern() const
	{
		return digraph->pattern;
	}

	size_t NFA::group_size() const
	{
		return digraph->groups.size();
	}

	size_t NFA::node_size() const
	{
		return digraph->nodes.size();
	}

	size_t NFA::edge_size() const
	{
		return digraph->edges.size();
	}



	void NFA::update_group_start_state(set<size_t>& states, Matcher &matcher)
	{
		vector<Group> &groups = digraph->groups;
		size_t groups_size = groups.size();

		for (size_t i = 0; i < groups_size; i++)
		{
			if (states.find(groups[i].group_start_node) != states.end())matcher.groups[i].first = matcher.current_cursor();
		}
	}

	void NFA::update_group_end_state(set<size_t>& states, Matcher &matcher)
	{
		vector<Group> &groups = digraph->groups;
		size_t groups_size = groups.size();

		for (size_t i = 0; i < groups_size; i++)
		{
			if (states.find(groups[i].group_end_node) != states.end())matcher.groups[i].second = matcher.current_cursor() + 1;
		}
	}

	void NFA::get_sigma_closure(set<size_t>& source)
	{
		//breath first search
		vector<bool> visited(digraph->v(), false);
		queue<size_t> node_ids;

		//add all source nodes
		for (set<size_t>::iterator b = source.begin(), e = source.end(); b != e; b++)
		{
			size_t id = *b;
			visited[id] = true;
			node_ids.push(id);
		}

		while (!node_ids.empty())
		{
			size_t node_id = node_ids.front();
			node_ids.pop();
			const vector<size_t> &out_edges = digraph->nodes[node_id]->get_out_edges();
			for (vector<size_t>::const_iterator b = out_edges.cbegin(), e = out_edges.cend(); b != e; b++)
			{
				size_t edge_id = *b;
				size_t end_node_id = digraph->edges[edge_id]->get_end_node_id();
				if (digraph->edges[edge_id]->get_type() == SIGMA_DIRECTEDEDGE)
					VISITED_ONE_NODE(end_node_id, node_ids, source);

			}

		}
	}
	void NFA::get_next_state(set<size_t> & state, const string &text, size_t index, Matcher &matcher)
	{
		set<size_t> next_state;
		vector<DirectedEdgePoint> &edges = digraph->edges;
		for (set<size_t>::iterator b = state.begin(), e = state.end(); b != e; b++)
		{
			//check every edge that can accept ch
			const vector<size_t> &out_edges = digraph->nodes[*b]->get_out_edges();
			for (vector<size_t>::const_iterator edge_b = out_edges.begin(), edge_e = out_edges.cend(); edge_b != edge_e; edge_b++)
				if (edges[*edge_b]->get_type() == SINGLE_CHAR_DIRECTEDEDGE && edges[*edge_b]->accept(text, index, matcher))
					next_state.insert(edges[*edge_b]->get_end_node_id());
		}

		state.swap(next_state);
	}

	void NFA::read_boundry_edge(set<size_t> & state, const string &text, size_t index, Matcher &matcher)
	{
		vector<DirectedEdgePoint> &edges = digraph->edges;
		set<size_t> next_state;
		for (set<size_t>::iterator b = state.begin(), e = state.end(); b != e; b++)
		{
			next_state.insert(*b);
			//check every edge that can accept ch
			const vector<size_t> &out_edges = digraph->nodes[*b]->get_out_edges();
			for (vector<size_t>::const_iterator edge_b = out_edges.begin(), edge_e = out_edges.cend(); edge_b != edge_e; edge_b++)
				if ((edges[*edge_b]->get_type() == LINE_START_DIRECTEDEDGE
					|| edges[*edge_b]->get_type() == LINE_END_DIRECTEDEDGE)
					&& edges[*edge_b]->accept(text, index, matcher))
				{
					next_state.insert(edges[*edge_b]->get_end_node_id());
				}
		}
		state.swap(next_state);
	}

	void NFA::read_nochar_edge(set<size_t>& state, const string & text, size_t index, Matcher & matcher)
	{
		//breath first search
		vector<bool> visited(digraph->v(), false);
		queue<size_t> node_ids;

		//add all source nodes
		for (set<size_t>::iterator b = state.begin(), e = state.end(); b != e; b++)
		{
			size_t id = *b;
			visited[id] = true;
			node_ids.push(id);
		}

		while (!node_ids.empty())
		{
			size_t node_id = node_ids.front();
			node_ids.pop();
			if (digraph->nodes[node_id]->get_type() == REPEAT_COUNT_DIRECTEDNODE)
			{
				RepeatCountDirectedNode &repeat_node = *dynamic_cast<RepeatCountDirectedNode *>(digraph->nodes[node_id].get());
				matcher.repeat_node_count[node_id]++;
				state.erase(node_id);
				int judge = repeat_node.accept_count(matcher.repeat_node_count[node_id]);
				/*
				0 is the repeat edge
				1 is the pass edge
				*/
				if (judge == -1)
				{
					//the continue repeat node
					size_t out_edge_id = repeat_node.get_out_edges()[0];
					size_t end_node_id = digraph->edges[out_edge_id]->get_end_node_id();
					VISITED_ONE_NODE(end_node_id, node_ids, state);
				}
				else if (judge == 0)
				{
					//the end node
					size_t out_edge_id = repeat_node.get_out_edges()[1];
					size_t end_node_id = digraph->edges[out_edge_id]->get_end_node_id();
					VISITED_ONE_NODE(end_node_id, node_ids, state);
					//the continue repeat node
					out_edge_id = repeat_node.get_out_edges()[0];
					end_node_id = digraph->edges[out_edge_id]->get_end_node_id();
					VISITED_ONE_NODE(end_node_id, node_ids, state);
				}
				else if (judge == 1)
				{
					//the end node
					size_t out_edge_id = repeat_node.get_out_edges()[1];
					size_t end_node_id = digraph->edges[out_edge_id]->get_end_node_id();
					VISITED_ONE_NODE(end_node_id, node_ids, state);
					matcher.repeat_node_count[node_id] = 0;
				}
				else
					matcher.repeat_node_count[node_id] = 0;
			}
			else
			{
				const vector<size_t> &out_edges = digraph->nodes[node_id]->get_out_edges();
				for (vector<size_t>::const_iterator b = out_edges.cbegin(), e = out_edges.cend(); b != e; b++)
				{
					size_t edge_id = *b;
					size_t end_node_id = digraph->edges[edge_id]->get_end_node_id();
					if (digraph->edges[edge_id]->get_type() == SIGMA_DIRECTEDEDGE)
						VISITED_ONE_NODE(end_node_id, node_ids, state);
					else if (digraph->edges[edge_id]->get_type() == LINE_START_DIRECTEDEDGE
						|| digraph->edges[edge_id]->get_type() == LINE_END_DIRECTEDEDGE)
					{
						if (digraph->edges[edge_id]->accept(text, index, matcher))
							VISITED_ONE_NODE(end_node_id, node_ids, state);
					}


				}
			}
		}
	}

	bool NFA::has_final_state(set<size_t>& states)
	{
		return states.find(digraph->end_node_id) != states.end();
	}



	void NFA::get_next_state(State& state, const string & text, size_t index, Matcher & matcher)
	{
		//breath first search
		vector<bool> visited(digraph->v(), false);
		State next_state;
		vector<DirectedEdgePoint> &edges = digraph->edges;
		for (State::iterator b = state.begin(), e = state.end(); b != e; b++)
		{
			//check every edge that can accept ch
			size_t node_id = (*b).first;
			const vector<size_t> &out_edges = digraph->nodes[node_id]->get_out_edges();
			for (vector<size_t>::const_iterator edge_b = out_edges.begin(), edge_e = out_edges.cend(); edge_b != edge_e; edge_b++)
				if (  (edges[*edge_b]->get_type() == SINGLE_CHAR_DIRECTEDEDGE || 
						edges[*edge_b]->get_type() == GROUP_REFERENCE_DIRECTEDGE
					   )
					&& edges[*edge_b]->accept(text, index, matcher))
				{
					size_t end_node_id = edges[*edge_b]->get_end_node_id();
					if (!visited[end_node_id])
					{
						visited[end_node_id] = true;
						next_state.push_back({ end_node_id,(*b).second });
						next_state.back().second[end_node_id] = matcher.current_cursor();
					}
				}
		}

		state.swap(next_state);
	}

	void NFA::read_nochar_edge(State& state, const string & text, size_t index, Matcher & matcher)
	{
		//breath first search
		vector<bool> visited(digraph->v(), false);
		queue<size_t> node_ids;

		//add all source nodes
		for (State::iterator b = state.begin(), e = state.end(); b != e; b++)
		{
			size_t id = (*b).first;
			visited[id] = true;
			node_ids.push(id);
		}

		while (!node_ids.empty())
		{
			size_t node_id = node_ids.front();
			node_ids.pop();
			if (digraph->nodes[node_id]->get_type() == REPEAT_COUNT_DIRECTEDNODE)
			{
				RepeatCountDirectedNode &repeat_node = *dynamic_cast<RepeatCountDirectedNode *>(digraph->nodes[node_id].get());
				matcher.repeat_node_count[node_id]++;
				for (State::iterator b = state.begin(), e = state.end(); b != e; b++)
				{
					if ((*b).first == node_id)
					{
						state.remove(*b);
						break;
					}
				}
				int judge = repeat_node.accept_count(matcher.repeat_node_count[node_id]);
				/*
				0 is the repeat edge
				1 is the pass edge
				*/
				if (judge == -1)
				{
					//the continue repeat node
					size_t out_edge_id = repeat_node.get_out_edges()[0];
					size_t end_node_id = digraph->edges[out_edge_id]->get_end_node_id();
					visit_one_node(node_id, end_node_id, state, node_ids, visited, matcher);
				}
				else if (judge == 0)
				{
					//the end node
					size_t out_edge_id = repeat_node.get_out_edges()[1];
					size_t end_node_id = digraph->edges[out_edge_id]->get_end_node_id();
					visit_one_node(node_id, end_node_id, state, node_ids, visited, matcher);
					//the continue repeat node
					out_edge_id = repeat_node.get_out_edges()[0];
					end_node_id = digraph->edges[out_edge_id]->get_end_node_id();
					visit_one_node(node_id, end_node_id, state, node_ids, visited, matcher);
				}
				else if (judge == 1)
				{
					//the end node
					size_t out_edge_id = repeat_node.get_out_edges()[1];
					size_t end_node_id = digraph->edges[out_edge_id]->get_end_node_id();
					visit_one_node(node_id, end_node_id, state, node_ids, visited, matcher);
					matcher.repeat_node_count[node_id] = 0;
				}
				else
					matcher.repeat_node_count[node_id] = 0;
			}
			else
			{
				const vector<size_t> &out_edges = digraph->nodes[node_id]->get_out_edges();
				for (vector<size_t>::const_iterator b = out_edges.cbegin(), e = out_edges.cend(); b != e; b++)
				{
					size_t edge_id = *b;
					size_t end_node_id = digraph->edges[edge_id]->get_end_node_id();
					if (digraph->edges[edge_id]->get_type() == SIGMA_DIRECTEDEDGE)
						visit_one_node(node_id, end_node_id, state, node_ids, visited, matcher);
					else if (digraph->edges[edge_id]->get_type() == LINE_START_DIRECTEDEDGE
						|| digraph->edges[edge_id]->get_type() == LINE_END_DIRECTEDEDGE)
					{
						if (digraph->edges[edge_id]->accept(text, index, matcher))
							visit_one_node(node_id, end_node_id, state, node_ids, visited, matcher);
					}

				}
			}
		}
	}

	void NFA::update_group_node_record(State & state, Matcher & matcher)
	{
		for (State::iterator b = state.begin(), e = state.end(); b != e; b++)
		{
			if ((*b).first == digraph->end_node_id)
			{
				TrackRecode &record = (*b).second;
				vector<Group> &groups = digraph->groups;
				size_t groups_size = groups.size();

				for (size_t i = 0; i < groups_size; i++)
				{
					size_t group_start_node_id = groups[i].group_start_node;
					size_t group_end_node_id = groups[i].group_end_node;
					matcher.groups[i].first = record[group_start_node_id]+1;
					matcher.groups[i].second = record[group_end_node_id] + 1;
				}
			}
		}
	}

	inline void NFA::visit_one_node(size_t parent_node_id, size_t visit_node_id, State & state, queue<size_t>& node_ids, vector<bool> &visited, Matcher & matcher)
	{
		//find the parent node
		for (State::iterator p_b = state.begin(), p_e = state.end(); p_b != p_e; p_b++)
		{
			if ((*p_b).first == parent_node_id)
			{
				TrackRecode &parent_record = (*p_b).second;
				if (visited[visit_node_id])
				{
					//find the child node
					for (State::iterator c_b = state.begin(), c_e = state.end(); c_b != c_e; c_b++)
					{
						//if find the child
						if ((*c_b).first == visit_node_id)
						{
							(*c_b).second = parent_record;
							(*c_b).second[visit_node_id] = matcher.current_cursor();
							break;
						}
					}

				}
				else
				{
					visited[visit_node_id] = true;
					state.push_back({ visit_node_id ,parent_record });
					state.back().second[visit_node_id] = matcher.current_cursor();
				}
				node_ids.push(visit_node_id);
				break;
			}
		}

	}

	bool NFA::has_final_state(State& states)
	{
		for (State::iterator b = states.begin(), e = states.end(); b != e; b++)
			if ((*b).first == digraph->end_node_id) return true;
		return false;
	}
}
