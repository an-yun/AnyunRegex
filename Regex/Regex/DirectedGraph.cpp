#include "DirectedGraph.h"

namespace anyun_regex
{

	/*
	-----------------------the bad code------------------------------------
	2016-10-17 15:21  T_T T_T T_T o(¦á¦ä¦á)o
	const char DirectedGraph::SINGLE_SPECAIL_CAHR[] = { '\0','(' ,')','|'};
	const size_t DirectedGraph::SINGLE_SPECAIL_CAHR_SIZE = sizeof(DirectedGraph::SINGLE_SPECAIL_CAHR) / sizeof(char);
	bool DirectedGraph::is_special_char(char ch)
	{
		for (size_t i = 0; i < SINGLE_SPECAIL_CAHR_SIZE; i++)
			if (ch == SINGLE_SPECAIL_CAHR[i])return true;
		return false;
	}
	*/
	int DirectedGraph::get_priority(size_t op1, size_t op2)
	{
		static map<size_t, map<size_t, int>> priority;
		if (priority.empty())
		{
			
			priority['\0']['\0'] = 0;
			priority['\0']['('] = -1;
			//priority['\0'][')'] miss left bracket
			priority['\0']['|'] = -1;
			priority['\0']['.'] = -1;

			//priority['(']['\0']  miss right bracket
			priority['(']['('] = -1;
			priority['('][')'] = -1;
			priority['(']['|'] = -1;
			priority['(']['.'] = -1;

			priority[')']['\0'] = 1;
			priority[')']['('] =  1;
			priority[')'][')'] =  1;
			priority[')']['|'] =  1;
			priority[')']['.'] = 1;

			priority['|']['\0'] = 1;
			priority['|']['('] = -1;
			priority['|'][')'] = 1;
			priority['|']['|'] = 1;
			priority['|']['.'] = 1;

			priority['.']['\0'] = 1;
			priority['.']['('] = 1;
			priority['.'][')'] = 1;
			priority['.']['|'] = -1;
			priority['.']['.'] = 1;


		}
		return priority[op1][op2];
	}

	void DirectedGraph::operate(size_t opt, stack<ConnectedFragment>& operands)
	{
		switch (opt)
		{
		case '|':
			{
				ConnectedFragment fra2 = operands.top();
				operands.pop();
				ConnectedFragment fra1 = operands.top();
				operands.pop();

				//connect in node
				DirectedNode in_node(nodes.size());
				nodes.push_back(in_node);
				connect_in_node(in_node.get_id(), fra1);
				connect_in_node(in_node.get_id(), fra2);
				//connect out node
				DirectedNode out_node(nodes.size());
				nodes.push_back(out_node);
				connect_out_node(out_node.get_id(), fra1);
				connect_out_node(out_node.get_id(), fra2);
				//connect in and out edges
				DirectedEdge sigma_edge1(edges.size());
				edges.push_back(sigma_edge1);
				connect_out_node_to_edge(in_node.get_id(),sigma_edge1.get_id());
				DirectedEdge sigma_edge2(edges.size());
				edges.push_back(sigma_edge2);
				connect_in_node_to_edge(out_node.get_id(), sigma_edge2.get_id());

				operands.push(ConnectedFragment(sigma_edge1.get_id(), sigma_edge2.get_id()));
				break;
			}
		//the dot . means concatenation  operator
		case '.':
			{
				ConnectedFragment fra2 = operands.top();
				operands.pop();
				ConnectedFragment fra1 = operands.top();
				operands.pop();
				connect_fragments(fra1, fra2);
				operands.push(ConnectedFragment(fra1.in_edge_id, fra2.out_edge_id));
				break;
			}
		default:
			break;
		}
	}

	DirectedGraph::DirectedGraph()
	{
		pattern = "";
		nodes.push_back(DirectedNode(0, true));
		start_node_id = end_node_id = 0;
		parse_result = REGEX_PARSE_OK;
	}
	DirectedGraph::DirectedGraph(const char * pattern)
	{
		compile(pattern);
	}
	DirectedGraph::~DirectedGraph()
	{

	}

	size_t DirectedGraph::v()
	{
		return nodes.size();
	}

	//rewite the follow bad code
	RegexParseCode DirectedGraph::compile(const char * pattern)
	{
		//check pattern
		if (pattern == NULL) return (parse_result = REGEX_PARSE_PATTERN_IS_NULL);
		this->pattern = pattern;
		//add the start node
		DirectedNode start_node;
		start_node.set_id(0);
		nodes.push_back(start_node);

		//bgein to parse
		ConnectedFragment fragment = parse();
		if (parse_result == REGEX_PARSE_OK)
		{
			DirectedNode end_node;
			end_node.set_id(nodes.size());
			end_node.set_final(true);
			nodes.push_back(end_node);

			connect_in_node(0, fragment);
			connect_out_node(end_node.get_id(), fragment);
		}
		else
		{
			nodes.clear();
			edges.clear();
		}
		return parse_result;
	}



	inline void DirectedGraph::connect_in_node(size_t in_node_id, const ConnectedFragment & fragment)
	{
		edges[fragment.in_edge_id].set_start_node(in_node_id);
		nodes[in_node_id].add_out_edge(fragment.in_edge_id);
	}

	inline void DirectedGraph::connect_out_node(size_t out_node_id, const ConnectedFragment & fragment)
	{
		edges[fragment.out_edge_id].set_end_node(out_node_id);
		nodes[out_node_id].add_in_edge(fragment.out_edge_id);
	}

	inline void DirectedGraph::connect_fragments(const ConnectedFragment & fragment1, const ConnectedFragment & fragment2)
	{
		DirectedNode node(nodes.size());
		nodes.push_back(node);
		connect_out_node(node.get_id(), fragment1);
		connect_in_node(node.get_id(), fragment2);
	}

	inline void DirectedGraph::connect_in_node_to_edge(size_t in_node_id, size_t edge_id)
	{
		edges[edge_id].set_start_node(in_node_id);
		nodes[in_node_id].add_out_edge(edge_id);
	}

	inline void DirectedGraph::connect_out_node_to_edge(size_t out_node_id, size_t edge_id)
	{
		edges[edge_id].set_end_node(out_node_id);
		nodes[out_node_id].add_in_edge(edge_id);
	}


	ConnectedFragment DirectedGraph::parse()
	{
		stack<ConnectedFragment> operands;
		stack<size_t> operators;
		operators.push('\0');//the start operator
		parse_result = REGEX_PARSE_NOT_FOUND;
		parse_index = 0;
		while (parse_result == REGEX_PARSE_NOT_FOUND)
		{
			switch (pattern[parse_index])
			{
			case '(':
				if (get_priority(operators.top(), '(') < 0)
				{
					operators.push('(');
					parse_index++;
				}
				else
				{
					operate(operators.top(), operands);
					operators.pop();
				}
				break;
			case ')':
				if (operators.empty() || operators.top() == '\0' || operators.top() == '|')
					parse_result = REGEX_PARSE_MISS_LEFT_BRACKET;
				else if (operators.top() == '(')
				{
					operators.pop();
					parse_index++;
				}
				else
				{
					operate(operators.top(), operands);
					operators.pop();
				}
				break;
			case '|':
				if (get_priority(operators.top(), '|') < 0)
				{
					operators.push('|');
					parse_index++;
				}
				else 
				{
					operate(operators.top(), operands);
					operators.pop();
				}
				break;
			case '\0':
				if (operators.top() == '(') parse_result = REGEX_PARSE_MISS_RIGHT_BRACKET;
				else if (operands.size() == 1 && operators.top() == '\0')
				{
					operators.pop();
					parse_result = REGEX_PARSE_OK;
				}
				else
				{
					operate(operators.top(), operands);
					operators.pop();
				}
				break;
			default:
				DirectedEdge edge(pattern[parse_index], edges.size());
				edges.push_back(edge);
				operands.push(ConnectedFragment(edge.get_id(), edge.get_id()));
				parse_index++;
				break;
			}
		}
		return operands.top();
	}







	/*
	------------------------the bad code------------------------------------
	2016-10-17 15:21  T_T T_T T_T o(¦á¦ä¦á)o
	RegexParseCode DirectedGraph::compile(const char *pattern)
	{
		//check pattern
		if (pattern == NULL) return (parse_result = REGEX_PARSE_PATTERN_IS_NULL);
		this->pattern = pattern;
		parse_index = 0;
		//add the start node
		DirectedNode start_node;
		start_node.set_id(0);
		nodes.push_back(start_node);

		size_t s = 0,e=0;
		if ((parse_result = parse(s, e)) != REGEX_PARSE_OK) return parse_result;

		//the end node
		DirectedNode end_node;
		end_node.set_id(nodes.size());
		end_node.set_final(true);
		//connect e and end node by sigma edge
		DirectedEdge sigma_edge(e,end_node.get_id(),edges.size());
		nodes[e].add_out_edge(sigma_edge.get_id());
		end_node.add_in_edge(sigma_edge.get_id());
		//save end node and sigma edge
		edges.push_back(sigma_edge);
		nodes.push_back(end_node);
		return parse_result = REGEX_PARSE_OK;
	}
	RegexParseCode DirectedGraph::parse(size_t & s, size_t & e)
	{
		switch (pattern[parse_index])
		{
		case '\0':
			return REGEX_PARSE_OK;
		case '(':
			return parse_group(s, e);
		case ')':
			return REGEX_PARSE_GET_RIGHT_BRACKET;
		case '|':
			return parse_or(s, e);
		default:
			return parse_and(s,e);
		}
	}
	RegexParseCode DirectedGraph::parse_group(size_t & s, size_t & e)
	{
		assert(pattern[parse_index] == '(');
		parse_index++;


		size_t group_s = s;
		for (RegexParseCode code = parse(s, e); code != REGEX_PARSE_GET_RIGHT_BRACKET; code = parse(s, e))
		{
			if (code == REGEX_PARSE_OK) return REGEX_PARSE_MISS_RIGHT_BRACKET;
		}
		s = group_s;
		parse_index++;
		return parse(s, e);
	}
	RegexParseCode DirectedGraph::parse_and(size_t & s, size_t & e)
	{
		assert(!is_special_char(pattern[parse_index]));
		for (char ch = pattern[parse_index]; !is_special_char(ch); ch = pattern[++parse_index])
		{
			DirectedNode node;
			node.set_id(nodes.size());
			DirectedEdge edge(ch, e,node.get_id(),edges.size());
			nodes[e].add_out_edge(edge.get_id());
			node.add_in_edge(edge.get_id());
			edges.push_back(edge);
			nodes.push_back(node);
			s = e;
			e = node.get_id();
		}
		return parse(s,e);
	}
	RegexParseCode DirectedGraph::parse_or(size_t & s, size_t & e)
	{
		assert(pattern[parse_index] == '|');
		return REGEX_PARSE_OK;
	}
	*/
}
