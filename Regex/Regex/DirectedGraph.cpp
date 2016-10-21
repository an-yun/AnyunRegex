#include "DirectedGraph.h"

namespace anyun_regex
{
#define PRE_PROCESS_ERROR(assgin,code)  \
	do {								\
		(assgin) = (code);				\
		return "" ;						\
	} while(0)

	/*
	-----------------------these code can be used again------------------------------------
	2016-10-18 10:23
	*/
	const char DirectedGraph::SINGLE_SPECAIL_CAHRS[] = { '\0','(' ,')','[',']','{','}','|','*','+','?' };
	const size_t DirectedGraph::SINGLE_SPECAIL_CAHR_SIZE = sizeof(DirectedGraph::SINGLE_SPECAIL_CAHRS) / sizeof(char);
	inline bool DirectedGraph::is_special_char(size_t ch)
	{
		return is_char_in(ch, SINGLE_SPECAIL_CAHRS, SINGLE_SPECAIL_CAHR_SIZE);
	}

	inline bool DirectedGraph::is_char_in(size_t ch, const char * str, size_t length)
	{
		for (size_t i = 0; i < length; i++)
			if (ch == str[i])return true;
		return false;
	}

	int DirectedGraph::get_priority(size_t op1, size_t op2)
	{
		static map<size_t, map<size_t, int>> priority;
		if (priority.empty())
		{
			/*
			the priority table

			\metachar  (the escape char)
			( )、(?: )、(?= )、[ ]
			*、+、?、{n}、{n,}、{m,n}
			^、$
			concatenation  operator (I represent it here using .)
			|
			\0  (start or end)

			*/
			priority['\0']['\0'] = 0;
			priority['\0']['('] = -1;
			//priority['\0'][')'] miss left bracket
			priority['\0']['|'] = -1;
			priority['\0']['.'] = -1;
			priority['\0']['?'] = -1;
			priority['\0']['*'] = -1;
			priority['\0']['+'] = -1;

			//priority['(']['\0']  miss right bracket
			priority['(']['('] = -1;
			priority['('][')'] = 0;
			priority['(']['|'] = -1;
			priority['(']['.'] = -1;
			priority['(']['?'] = -1;
			priority['(']['*'] = -1;
			priority['(']['+'] = -1;

			priority[')']['\0'] = 1;
			priority[')']['('] = 1;
			priority[')'][')'] = 1;
			priority[')']['|'] = 1;
			priority[')']['.'] = 1;
			priority[')']['?'] = 1;
			priority[')']['*'] = 1;
			priority[')']['+'] = 1;

			priority['|']['\0'] = 1;
			priority['|']['('] = -1;
			priority['|'][')'] = 1;
			priority['|']['|'] = 1;
			priority['|']['.'] = -1;
			priority['|']['?'] = -1;
			priority['|']['*'] = -1;
			priority['|']['+'] = -1;

			priority['.']['\0'] = 1;
			priority['.']['('] = -1;
			priority['.'][')'] = 1;
			priority['.']['|'] = 1;
			priority['.']['.'] = 1;
			priority['.']['?'] = -1;
			priority['.']['*'] = -1;
			priority['.']['+'] = -1;

			priority['?']['\0'] = 1;
			//priority['?']['('] miss concatenation  operator
			priority['?'][')'] = 1;
			priority['?']['|'] = 1;
			priority['?']['.'] = 1;
			priority['?']['?'] = 1;
			priority['?']['*'] = 1;
			priority['?']['+'] = 1;

			priority['*']['\0'] = 1;
			//priority['*']['('] miss concatenation  operator
			priority['*'][')'] = 1;
			priority['*']['|'] = 1;
			priority['*']['.'] = 1;
			priority['*']['?'] = 1;
			priority['*']['*'] = 1;

			priority['+']['\0'] = 1;
			//priority['+']['('] miss concatenation  operator
			priority['+'][')'] = 1;
			priority['+']['|'] = 1;
			priority['+']['.'] = 1;
			priority['+']['?'] = 1;
			priority['+']['*'] = 1;
			priority['+']['+'] = 1;

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
			operands.push(merge_fragments(fra1, fra2));
			break;
		}
		//the dot . means concatenation  operator
		case '.':
		{
			ConnectedFragment fra2 = operands.top();
			operands.pop();
			ConnectedFragment fra1 = operands.top();
			operands.pop();
			operands.push(connect_fragments(fra1, fra2));
			break;
		}
		case '?':
		{
			ConnectedFragment fra1 = operands.top();
			operands.pop();
			DirectedEdge sigma_edge(edges.size());
			edges.push_back(sigma_edge);
			ConnectedFragment fra2(sigma_edge.get_id(), sigma_edge.get_id());
			operands.push(merge_fragments(fra1, fra2));
			break;
		}
		case '*':
		{
			ConnectedFragment fra1 = operands.top();
			operands.pop();
			//add self connect and push
			operands.push(self_connect_fragment(fra1));
			break;
		}
		case '+':
		{
			ConnectedFragment fra1 = operands.top();
			operands.pop();
			DirectedEdge sigma_edge(edges.size());
			edges.push_back(sigma_edge);
			//the fra2
			ConnectedFragment fra2(sigma_edge.get_id(), sigma_edge.get_id());
			//reverse merge fra1 and fra2
			operands.push(reverse_merge_fragments(fra1, fra2));
			break;
		}
		default:
			break;
		}
	}

	DirectedGraph::DirectedGraph()
	{
		compile("");
	}
	DirectedGraph::DirectedGraph(const char * pattern)
	{
		if (pattern == NULL) parse_result = REGEX_PARSE_PATTERN_IS_NULL;
		else compile(pattern);
	}
	DirectedGraph::DirectedGraph(const string & pattern)
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
	RegexParseCode DirectedGraph::compile(const string &pattern)
	{
		//the empty pattern
		if (pattern.size() == 0)
		{
			this->pattern = "";
			nodes.push_back(DirectedNode(0, true));
			start_node_id = end_node_id = 0;
			return (parse_result = REGEX_PARSE_OK);
		}
		this->pattern = pattern;
		//add the start node
		DirectedNode start_node;
		start_node.set_id(0);
		nodes.push_back(start_node);

		//bgein to parse
		parse_result = REGEX_PARSE_OK;
		string pre_pattern = pre_process_pattern(this->pattern);
		if (parse_result != REGEX_PARSE_OK) return parse_result;
		ConnectedFragment fragment = parse(pre_pattern);
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

	inline size_t DirectedGraph::add_in_sigma_edge(size_t node_id)
	{
		//connect in  edge
		DirectedEdge sigma_edge(edges.size());
		edges.push_back(sigma_edge);
		connect_out_node_to_edge(node_id, sigma_edge.get_id());
		return sigma_edge.get_id();  //return sigma_edge id
	}

	inline size_t DirectedGraph::add_out_sigma_edge(size_t node_id)
	{
		//connect out edges
		DirectedEdge sigma_edge(edges.size());
		edges.push_back(sigma_edge);
		connect_in_node_to_edge(node_id, sigma_edge.get_id());
		return sigma_edge.get_id();  //return sigma_edge id
	}
	/*
	connect fragment to itself
	  <fra<
	 \     /
	->  O  ->
	*/
	ConnectedFragment DirectedGraph::self_connect_fragment(const ConnectedFragment & fragment)
	{
		//the selfnode
		DirectedNode node(nodes.size());
		nodes.push_back(node);
		//connect to itself
		connect_in_node(node.get_id(), fragment);
		connect_out_node(node.get_id(), fragment);
		//add in and out edge
		size_t in_edge_id = add_in_sigma_edge(node.get_id());
		size_t out_edge_id = add_out_sigma_edge(node.get_id());

		return ConnectedFragment(in_edge_id, out_edge_id);
	}
	/*
	connect fragment1 to fragment1
	->fra1->fra2->
	*/
	inline ConnectedFragment DirectedGraph::connect_fragments(const ConnectedFragment & fragment1, const ConnectedFragment & fragment2)
	{
		DirectedNode node(nodes.size());
		nodes.push_back(node);
		connect_out_node(node.get_id(), fragment1);
		connect_in_node(node.get_id(), fragment2);
		return ConnectedFragment(fragment1.in_edge_id, fragment2.out_edge_id);
	}

	/*
	merge fragment1 and  fragment2 together

		>fra1>
	   /      \
	->O        O->
	   \      /
		>fra2>
	*/
	inline ConnectedFragment DirectedGraph::merge_fragments(const ConnectedFragment & fragment1, const ConnectedFragment & fragment2)
	{
		//connect in node
		DirectedNode in_node(nodes.size());
		nodes.push_back(in_node);
		connect_in_node(in_node.get_id(), fragment1);
		connect_in_node(in_node.get_id(), fragment2);
		//connect out node
		DirectedNode out_node(nodes.size());
		nodes.push_back(out_node);
		connect_out_node(out_node.get_id(), fragment1);
		connect_out_node(out_node.get_id(), fragment2);
		//connect in and out edges
		size_t in_edge_id = add_in_sigma_edge(in_node.get_id());
		size_t out_edge_id = add_out_sigma_edge(out_node.get_id());

		return ConnectedFragment(in_edge_id, out_edge_id);
	}

	/*
	reverse merge fragment1 and  fragment2 together

		>fra1>
	   /      \
	->O       O->
	   \      /
		<fra2<
	*/
	inline ConnectedFragment DirectedGraph::reverse_merge_fragments(const ConnectedFragment & fragment1, const ConnectedFragment & fragment2)
	{
		//connect in node
		DirectedNode in_node(nodes.size());
		nodes.push_back(in_node);
		connect_in_node(in_node.get_id(), fragment1);
		connect_out_node(in_node.get_id(), fragment2);
		//connect out node
		DirectedNode out_node(nodes.size());
		nodes.push_back(out_node);
		connect_out_node(out_node.get_id(), fragment1);
		connect_in_node(out_node.get_id(), fragment2);
		//connect in and out edges
		size_t in_edge_id = add_in_sigma_edge(in_node.get_id());
		size_t out_edge_id = add_out_sigma_edge(out_node.get_id());

		return ConnectedFragment(in_edge_id, out_edge_id);
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


	string DirectedGraph::pre_process_pattern(const string & p)
	{

		static const char end_and_no_connect_operators[] = { '\0',')','{','|','*','+','?', };
		static const char right_operators[] = { '*','+','?',']',')','}' };
		list<size_t> result;
		size_t size = p.size();
		stack<size_t> bracket_states;
		int bracket_count = 0;
		for (size_t i = 0; i < size; i++)
		{
			size_t current = p[i], next = p[i + 1];
			bool statest_empty = bracket_states.empty();
			bool current_is_special = is_special_char(current);
			bool current_is_right = is_char_in(current, right_operators, sizeof(right_operators) / sizeof(char));
			bool next_is_other = is_char_in(next, end_and_no_connect_operators, sizeof(end_and_no_connect_operators) / sizeof(char));
			result.push_back(current);
			switch (current)
			{
			case '(':
				bracket_count++;
				break;
			case ')':
				if (bracket_count < 1)
					PRE_PROCESS_ERROR(parse_result, REGEX_PARSE_MISS_LEFT_BRACKET);
				else bracket_count--;
				break;
			case '[':
				if (statest_empty)
					bracket_states.push(1);
				else
					PRE_PROCESS_ERROR(parse_result, REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET);
				break;
			case ']':
				if (!statest_empty && bracket_states.top() == 1)
					bracket_states.pop();
				else
					PRE_PROCESS_ERROR(parse_result, REGEX_PARSE_MISS_LEFT_SQUARE_BRACKET);
				break;
			case '{':
				if (statest_empty)
					bracket_states.push(2);
				else
					PRE_PROCESS_ERROR(parse_result, REGEX_PARSE_MISS_RIGHT_BRACKET);
				break;
			case '}':
				if (!statest_empty && bracket_states.top() == 2)
					bracket_states.pop();
				else
					PRE_PROCESS_ERROR(parse_result, REGEX_PARSE_MISS_LEFT_BRACKET);
				break;
			case '|':
				//handle the error |* || |)
				if (next_is_other)
					PRE_PROCESS_ERROR(parse_result, REGEX_PARSE_AFTER_OR_ILLEGAL);
				break;
			default:
				break;
			}
			//if next char is group end position or other operator ,not add concatenation operator,if not ,add it
			if (bracket_states.empty() && (!current_is_special || current_is_right) && !next_is_other)
			{
				result.push_back('\\');
				result.push_back('N');
			}

		}
		if (bracket_count > 0)
			PRE_PROCESS_ERROR(parse_result, REGEX_PARSE_MISS_RIGHT_BRACKET);
		return string(result.begin(), result.end());
	}

	ConnectedFragment DirectedGraph::parse(string p)
	{
		stack<ConnectedFragment> operands;
		stack<size_t> operators;
		operators.push('\0');//the start operator
		parse_result = REGEX_PARSE_NOT_FOUND;
		size_t parse_index = 0;
		while (parse_result == REGEX_PARSE_NOT_FOUND)
		{
			/*
			now we have support () | . + *
			next to support is []
			*/
			switch (p[parse_index])
			{
			case '\0':
				normal_priority_parse('\0', operators, operands, parse_index);
				if (operators.empty()) parse_result = REGEX_PARSE_OK;
				break;
			case '(':
				normal_priority_parse('(', operators, operands, parse_index);
				break;
			case ')':
				normal_priority_parse(')', operators, operands, parse_index);
				break;
			case '|':
				normal_priority_parse('|', operators, operands, parse_index);
				break;
			case '\\':
				switch (p[++parse_index])
				{
					//the dot \N means concatenation  operator
				case 'N':
					normal_priority_parse('.', operators, operands, parse_index);
					if (p[parse_index - 1] == '\\')parse_index--;
					break;
				default:
					parse_index++;
					break;
				}
				break;
			case '?':
				//to test
				normal_priority_parse('?', operators, operands, parse_index);
				break;
			case '*':
				//to test
				normal_priority_parse('*', operators, operands, parse_index);
				break;
			case '+':
				//to test
				normal_priority_parse('+', operators, operands, parse_index);
				break;
				//the single char
			default:
				DirectedEdge edge(p[parse_index], edges.size());
				edges.push_back(edge);
				operands.push(ConnectedFragment(edge.get_id(), edge.get_id()));
				parse_index++;
				break;
			}
		}
		return operands.top();
	}

	/*
	compare op's priority with operators.top()'s
	accroding the result of  comparation to decide it should push or operate
	*/
	inline void DirectedGraph::normal_priority_parse(size_t op, stack<size_t>& operators, stack<ConnectedFragment>& operands, size_t &parse_index)
	{
		int compare = get_priority(operators.top(), op);
		if (compare < 0)
		{
			operators.push(op);
			parse_index++;
		}
		else if (compare == 0)
		{
			operators.pop();
			parse_index++;
		}
		else
		{
			operate(operators.top(), operands);
			operators.pop();
		}
	}
}
