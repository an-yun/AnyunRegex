#include "DirectedGraph.h"

namespace anyun_regex
{
#define PRE_PROCESS_PATTERN_ERROR(assgin,code)  \
			do {								\
				(assgin) = (code);				\
				return "" ;						\
			} while(0)

#define PARSE_ERROR(assgin,code)		\
			do {								\
				(assgin) = (code);				\
				return ConnectedFragment(0,0);	\
			} while(0)

#define DEFAULT_SINGLE_CHAR_PROCESS(ch)				\
	do{												\
		add_single_char_edge(ch, operands);			\
		parse_index++;								\
	}while(0)

	/*
	-----------------------these code can be used again------------------------------------
	2016-10-18 10:23
	*/
	const char DirectedGraph::SINGLE_SPECAIL_CAHRS[] = { '\0','(' ,')','[',']','{','}','|','*','+','?' ,'\\','^','$' };
	const size_t DirectedGraph::SINGLE_SPECAIL_CAHR_SIZE = sizeof(DirectedGraph::SINGLE_SPECAIL_CAHRS) / sizeof(char);
	inline bool DirectedGraph::is_special_char(size_t ch)
	{
		return is_char_in(ch, SINGLE_SPECAIL_CAHRS, SINGLE_SPECAIL_CAHR_SIZE);
	}

	bool DirectedGraph::is_upper_case(size_t ch)
	{
		return ch >= UPPER_A && ch <= UPPER_Z;
	}

	bool DirectedGraph::is_lower_case(size_t ch)
	{
		return ch >= LOWER_A && ch <= LOWER_Z;
	}

	bool DirectedGraph::is_letter(size_t ch)
	{
		return is_lower_case(ch) || is_upper_case(ch);
	}

	bool DirectedGraph::is_num(size_t ch)
	{
		return ch >= ZERO && ch <= NINE;
	}

	bool DirectedGraph::is_alpnum(size_t ch)
	{
		return is_letter(ch) || is_num(ch);
	}



	inline bool DirectedGraph::is_char_in(size_t ch, const char * str, size_t length)
	{
		for (size_t i = 0; i < length; i++)
			if (ch == str[i])return true;
		return false;
	}


	int DirectedGraph::get_priority(size_t op1, size_t op2)
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
		static vector<tuple<size_t, size_t, int>> priority_table =
		{
			{ '\0','\0', 0 },
			{ '\0','(', -1 },
			//{ '\0',')', 0 }miss left bracket
			{ '\0','|', -1 },
			{ '\0','.', -1 },
			{ '\0','?', -1 },
			{ '\0','*', -1 },
			{ '\0','+', -1},
			{ '\0','-', -1 },

			//{'(','\0'}  miss right bracket
			{'(','(',-1},
			{'(',')',0},
			{'(','|',-1},
			{'(','.',-1},
			{'(','?',-1},
			{'(','*',-1},
			{'(','+',-1},
			{ '(','-',-1 },

			{')','\0',1},
			{')','(',1},
			{')',')',1},
			{')','|',1},
			{')','.',1},
			{')','?',1},
			{')','*',1},
			{')','+',1},
			{ ')','-',1 },

			{'|','\0',1},
			{'|','(',-1},
			{'|',')',1},
			{'|','|',-1},
			{'|','.',-1},
			{'|','?',-1},
			{'|','*',-1},
			{'|','+',-1},
			{ '|','-',-1 },

			{'.','\0',1},
			{'.','(',-1},
			{'.',')',1},
			{'.','|',1},
			{'.','.',1},
			{'.','?',-1},
			{'.','*',-1},
			{'.','+',-1},
			{ '.','-',-1 },

			{'?','\0',1},
			//{'?','('} miss concatenation  operator
			{'?',')',1},
			{'?','|',1},
			{'?','.',1},
			{'?','?',1},
			{'?','*',1},
			{'?','+',1},
			{ '?','-',1 },

			{'*','\0',1},
			//{'*','('} miss concatenation  operator
			{'*',')',1},
			{'*','|',1},
			{'*','.',1},
			{'*','?',1},
			{'*','*',1},
			{ '*','-',1 },

			{'+','\0',1},
			//{'+','('} miss concatenation  operator
			{'+',')',1},
			{'+','|',1},
			{'+','.',1},
			{'+','?',1},
			{'+','*',1},
			{'+','+',1},
			{ '+','-',1 },

			// - represent ??
			{ '-','\0',1 },
			//{'-','('} miss concatenation  operator
			{ '-',')',1 },
			{ '-','|',1 },
			{ '-','.',1 },
			{ '-','?',1 },
			{ '-','*',1 },
			{ '-','+',1 },
			{ '-','-',1 },
		};
		static map<size_t, map<size_t, int>> priority;
		if (priority.empty())
		{
			for (vector<tuple<size_t, size_t, int>>::iterator b = priority_table.begin(), e = priority_table.end(); b != e; b++)
			{
				size_t frist = std::get<0>(*b);
				size_t seconde = std::get<1>(*b);
				int p = std::get<2>(*b);
				priority[frist][seconde] = p;
			}
		}
		return priority[op1][op2];
	}

	void DirectedGraph::operate(size_t opt, stack<ConnectedFragment>& operands, stack<size_t>&operators)
	{
		switch (opt)
		{
		case '|':
		{
			vector<ConnectedFragment> fragments{ operands.top() };
			operands.pop();
			while (operators.top() == '|')
			{
				fragments.push_back(operands.top());
				operands.pop();
				operators.pop();
			}
			operands.push(merge_fragments(fragments,true));
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
			operators.pop();
			break;
		}
		case '?':
		{
			ConnectedFragment fra1 = operands.top();
			operands.pop();
			DirectedEdgePoint sigma_edge(new SigmaDirectedEdge(edges.size()));
			edges.push_back(sigma_edge);
			ConnectedFragment fra2(sigma_edge->get_id(), sigma_edge->get_id());
			operands.push(merge_fragments(fra1, fra2));
			operators.pop();
			break;
		}
		case '*':
		{
			ConnectedFragment fra1 = operands.top();
			operands.pop();
			//add self connect and push
			operands.push(self_connect_fragment(fra1));
			operators.pop();
			break;
		}
		case '+':
		{
			ConnectedFragment fra1 = operands.top();
			operands.pop();
			DirectedEdgePoint sigma_edge(new SigmaDirectedEdge(edges.size()));
			edges.push_back(sigma_edge);
			//the fra2
			ConnectedFragment fra2(sigma_edge->get_id(), sigma_edge->get_id());
			//reverse merge fra1 and fra2
			operands.push(reverse_merge_fragments(fra1, fra2));
			operators.pop();
			break;
		}
		case '-':
		{
			// for can be none lazy match
			ConnectedFragment fra1 = operands.top();
			operands.pop();
			DirectedEdgePoint sigma_edge(new SigmaDirectedEdge(edges.size()));
			edges.push_back(sigma_edge);
			ConnectedFragment fra2(sigma_edge->get_id(), sigma_edge->get_id());
			operands.push(merge_fragments(fra2, fra1));
			operators.pop();
			break;

		}
		case '0':
		{
			// for zero more lazy match
			ConnectedFragment fra1 = operands.top();
			operands.pop();
			//add self connect and push
			operands.push(self_connect_fragment(fra1, true));
			operators.pop();
			break;
		}
		case '1':
		{
			// for one more lazy match
			ConnectedFragment fra1 = operands.top();
			operands.pop();
			DirectedEdgePoint sigma_edge(new SigmaDirectedEdge(edges.size()));
			edges.push_back(sigma_edge);
			//the fra2
			ConnectedFragment fra2(sigma_edge->get_id(), sigma_edge->get_id());
			//reverse merge fra1 and fra2
			operands.push(reverse_merge_fragments(fra1, fra2,true));
			operators.pop();
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

	size_t DirectedGraph::get_start_node_id()
	{
		return start_node_id;
	}

	size_t DirectedGraph::get_end_node_id()
	{
		return end_node_id;
	}

	//rewite the follow bad code
	RegexParseCode DirectedGraph::compile(const string &pattern)
	{
		//the empty pattern
		edges.clear();
		nodes.clear();
		if (pattern.size() == 0)
		{
			this->pattern = "";
			nodes.push_back(DirectedNodePoint(new StartDirectedNode(0)));
			start_node_id = 0;
			nodes.push_back(DirectedNodePoint(new EndDirectedNode(1)));
			end_node_id = 1;
			DirectedEdgePoint sigma_edge(new SigmaDirectedEdge(0));
			edges.push_back(sigma_edge);
			connect_in_node_to_edge(0, 0);
			connect_out_node_to_edge(1, 0);
			groups.push_back(Group(0, 1));
			return (parse_result = REGEX_PARSE_OK);
		}
		this->pattern = pattern;
		//add the start node
		nodes.push_back(DirectedNodePoint(new StartDirectedNode(0)));
		groups.push_back(Group(0, 0));
		start_node_id = 0;
		//bgein to parse
		parse_result = REGEX_PARSE_OK;
		string pre_pattern = pre_process_pattern(this->pattern);
		if (parse_result != REGEX_PARSE_OK) return parse_result;
		ConnectedFragment fragment = parse(pre_pattern);
		if (parse_result == REGEX_PARSE_OK)
		{
			//add the end node
			DirectedNodePoint end_node(new EndDirectedNode(nodes.size()));
			nodes.push_back(end_node);
			end_node_id = end_node->get_id();
			groups[0].group_end_node = end_node->get_id();
			connect_in_node(0, fragment);
			connect_out_node(end_node->get_id(), fragment);
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
		edges[fragment.in_edge_id]->set_start_node(in_node_id);
		nodes[in_node_id]->add_out_edge(fragment.in_edge_id);
	}

	inline void DirectedGraph::connect_out_node(size_t out_node_id, const ConnectedFragment & fragment)
	{
		edges[fragment.out_edge_id]->set_end_node(out_node_id);
		nodes[out_node_id]->add_in_edge(fragment.out_edge_id);
	}

	inline size_t DirectedGraph::add_in_sigma_edge(size_t node_id)
	{
		//connect in  edge
		DirectedEdgePoint sigma_edge(new SigmaDirectedEdge(edges.size()));
		edges.push_back(sigma_edge);
		connect_out_node_to_edge(node_id, sigma_edge->get_id());
		return sigma_edge->get_id();  //return sigma_edge id
	}

	inline size_t DirectedGraph::add_out_sigma_edge(size_t node_id)
	{
		//connect out edges
		DirectedEdgePoint sigma_edge(new SigmaDirectedEdge(edges.size()));
		edges.push_back(sigma_edge);
		connect_in_node_to_edge(node_id, sigma_edge->get_id());
		return sigma_edge->get_id();  //return sigma_edge id
	}
	/*
	connect fragment to itself
	  <fra<
	 \     /
	->  O  ->
	*/
	ConnectedFragment DirectedGraph::self_connect_fragment(const ConnectedFragment & fragment, bool reverse)
	{
		//the selfnode
		DirectedNodePoint node(new DirectedNode(nodes.size()));
		nodes.push_back(node);
		if(reverse)
		{
			//add in and out edge
			size_t in_edge_id = add_in_sigma_edge(node->get_id());
			size_t out_edge_id = add_out_sigma_edge(node->get_id());
			//connect to itself
			connect_in_node(node->get_id(), fragment);
			connect_out_node(node->get_id(), fragment);
			return ConnectedFragment(in_edge_id, out_edge_id);
		}
		else
		{
			//connect to itself
			connect_in_node(node->get_id(), fragment);
			connect_out_node(node->get_id(), fragment);
			//add in and out edge
			size_t in_edge_id = add_in_sigma_edge(node->get_id());
			size_t out_edge_id = add_out_sigma_edge(node->get_id());
			return ConnectedFragment(in_edge_id, out_edge_id);
		}


		
	}
	/*
	connect fragment1 to fragment1
	->fra1->fra2->
	*/
	inline ConnectedFragment DirectedGraph::connect_fragments(const ConnectedFragment & fragment1, const ConnectedFragment & fragment2)
	{
		DirectedNodePoint node(new DirectedNode(nodes.size()));
		nodes.push_back(node);
		connect_out_node(node->get_id(), fragment1);
		connect_in_node(node->get_id(), fragment2);
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
		DirectedNodePoint in_node(new DirectedNode(nodes.size()));
		nodes.push_back(in_node);
		connect_in_node(in_node->get_id(), fragment1);
		connect_in_node(in_node->get_id(), fragment2);
		//connect out node
		DirectedNodePoint out_node(new DirectedNode(nodes.size()));
		nodes.push_back(out_node);
		connect_out_node(out_node->get_id(), fragment1);
		connect_out_node(out_node->get_id(), fragment2);
		//connect in and out edges
		size_t in_edge_id = add_in_sigma_edge(in_node->get_id());
		size_t out_edge_id = add_out_sigma_edge(out_node->get_id());

		return ConnectedFragment(in_edge_id, out_edge_id);
	}


	/*
	merge two or more fragments together
		 >fra1>
		/  .   \
	   /   .    \
	->O ->frai-> O->
	   \   .    /
		\  .   /
		 >fran>
	*/
	ConnectedFragment DirectedGraph::merge_fragments(const vector<ConnectedFragment>& fragments,bool reverse)
	{
		//the in node
		DirectedNodePoint in_node(new DirectedNode(nodes.size()));
		nodes.push_back(in_node);
		//the out node
		DirectedNodePoint out_node(new DirectedNode(nodes.size()));
		nodes.push_back(out_node);
		//connect 
		if(reverse)
		{

			for (vector<ConnectedFragment>::const_reverse_iterator b = fragments.crbegin(),e = fragments.crend();b!=e;b++)
			{
				connect_in_node(in_node->get_id(), *b);
				connect_out_node(out_node->get_id(), *b);
			}
		}
		else
		{
			for (vector<ConnectedFragment>::const_iterator b = fragments.cbegin(), e = fragments.cend(); b != e; b++)
			{
				connect_in_node(in_node->get_id(), *b);
				connect_out_node(out_node->get_id(), *b);
			}
		}
		
		//connect in and out edges
		size_t in_edge_id = add_in_sigma_edge(in_node->get_id());
		size_t out_edge_id = add_out_sigma_edge(out_node->get_id());

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
	inline ConnectedFragment DirectedGraph::reverse_merge_fragments(const ConnectedFragment & fragment1, const ConnectedFragment & fragment2, bool reverse)
	{
		//the in node
		DirectedNodePoint in_node(new DirectedNode(nodes.size()));
		nodes.push_back(in_node);
		//the out node
		DirectedNodePoint out_node(new DirectedNode(nodes.size()));
		nodes.push_back(out_node);
		size_t in_edge_id=0, out_edge_id=0;
		if(reverse)
		{
			//connect in and out edges
			in_edge_id = add_in_sigma_edge(in_node->get_id());
			out_edge_id = add_out_sigma_edge(out_node->get_id());
			//connect in node
			connect_in_node(in_node->get_id(), fragment1);
			connect_out_node(in_node->get_id(), fragment2);
			//connect out node
			connect_out_node(out_node->get_id(), fragment1);
			connect_in_node(out_node->get_id(), fragment2);
		}
		else
		{
			//connect in node
			connect_in_node(in_node->get_id(), fragment1);
			connect_out_node(in_node->get_id(), fragment2);
			//connect out node
			connect_out_node(out_node->get_id(), fragment1);
			connect_in_node(out_node->get_id(), fragment2);
			//connect in and out edges
			in_edge_id = add_in_sigma_edge(in_node->get_id());
			out_edge_id = add_out_sigma_edge(out_node->get_id());
		}


		return ConnectedFragment(in_edge_id, out_edge_id);
	}

	inline void DirectedGraph::connect_in_node_to_edge(size_t in_node_id, size_t edge_id)
	{
		edges[edge_id]->set_start_node(in_node_id);
		nodes[in_node_id]->add_out_edge(edge_id);
	}

	inline void DirectedGraph::connect_out_node_to_edge(size_t out_node_id, size_t edge_id)
	{
		edges[edge_id]->set_end_node(out_node_id);
		nodes[out_node_id]->add_in_edge(edge_id);
	}


	string DirectedGraph::pre_process_pattern(const string & p)
	{

		static const char end_and_no_connect_operators[] = { '\0',')','{','|','*','+','?' };
		static const char right_operators[] = { '*','+','?',']',')','}' ,'^','$' ,'\\' };
		static const char left_operatior[] = { '|','*','+','?','\0' };
		list<size_t> result;
		size_t size = p.size();
		stack<size_t> bracket_states;
		int bracket_count = 0;
		for (size_t i = 0; i < size; i++)
		{
			size_t current = p[i], next = p[i + 1];
			bool pre_is_left = (i == 0 ? true : is_char_in(p[i - 1], left_operatior, sizeof(left_operatior) / sizeof(char)));
			bool statest_empty = bracket_states.empty();
			bool current_is_special = is_special_char(current);
			bool current_qulifoer_operator = is_char_in(current, left_operatior, sizeof(left_operatior) / sizeof(char));
			bool current_is_right = is_char_in(current, right_operators, sizeof(right_operators) / sizeof(char));
			bool next_is_other = is_char_in(next, end_and_no_connect_operators, sizeof(end_and_no_connect_operators) / sizeof(char));
			result.push_back(current);
			if (pre_is_left && current_qulifoer_operator)
				PRE_PROCESS_PATTERN_ERROR(parse_result, REGEX_PARSE_ILLEGAL_QUALIFIER_CHAR);
			switch (current)
			{
			case '(':
				if (next == '?')
				{
					i++;
					current = p[i], next = p[i + 1];
					result.push_back(current);
					if (next == '<' || next == '\'')
					{
						//do something for name capture (?<group_name>##) or (?'group_name'##)
						i++;
						current = p[i], next = p[i + 1];
						result.push_back(current);
						char find_char = current == '\'' ? '\'' : '>';
						size_t end_group_name_position = p.find_first_of(find_char, ++i);
						//add expection handle to namecapture
						if (end_group_name_position == string::npos)
							PRE_PROCESS_PATTERN_ERROR(parse_result, REGEX_PARSE_MISS_END_CHAR_FOR_NAMECAPTURE);
						string group_name = p.substr(i, end_group_name_position - i);
						for (size_t ch : group_name) { result.push_back(ch); }
						result.push_back(p[end_group_name_position]);
						i = end_group_name_position;
					}

					else if (next == ':')
					{
						//don't capture this group (?:###)
						i++;
						current = p[i], next = p[i + 1];
						result.push_back(current);
					}
				}
				bracket_count++;
				break;
			case ')':
				if (bracket_count < 1)
					PRE_PROCESS_PATTERN_ERROR(parse_result, REGEX_PARSE_MISS_LEFT_BRACKET);
				else bracket_count--;
				break;
			case '[':
				if (statest_empty)
					bracket_states.push(1);
				else if (bracket_states.top() == 1)
					PRE_PROCESS_PATTERN_ERROR(parse_result, REGEX_PARSE_SQUARE_BRAKET_NESTED);
				else
					PRE_PROCESS_PATTERN_ERROR(parse_result, REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET);
				break;
			case ']':
				if (!statest_empty && bracket_states.top() == 1)
					bracket_states.pop();
				else if (!statest_empty && bracket_states.top() == 2)
					PRE_PROCESS_PATTERN_ERROR(parse_result, REGEX_PARSE_MISS_RIGHT_BRACES);
				else
					PRE_PROCESS_PATTERN_ERROR(parse_result, REGEX_PARSE_MISS_LEFT_SQUARE_BRACKET);
				break;
			case '{':
				if (statest_empty)
					bracket_states.push(2);
				else if (!statest_empty && bracket_states.top() == 1)
					PRE_PROCESS_PATTERN_ERROR(parse_result, REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET);
				else
					PRE_PROCESS_PATTERN_ERROR(parse_result, REGEX_PARSE_MISS_RIGHT_BRACES);
				break;
			case '}':
				if (!statest_empty && bracket_states.top() == 2)
					bracket_states.pop();
				else
					PRE_PROCESS_PATTERN_ERROR(parse_result, REGEX_PARSE_MISS_LEFT_BRACES);
				break;
			case '|':
				//handle the error |* || |)
				if (next_is_other)
					PRE_PROCESS_PATTERN_ERROR(parse_result, REGEX_PARSE_ILLEGAL_CHAR_AFTER_OR);
				break;
			case '\\':
				if (next == 'N')
					PRE_PROCESS_PATTERN_ERROR(parse_result, REGEX_PARSE_ILLEGAL_ESCAPE_CHAR);
				result.push_back(next);
				i++;
				next = p[i + 1];
				next_is_other = is_char_in(next, end_and_no_connect_operators, sizeof(end_and_no_connect_operators) / sizeof(char));
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
		if (!bracket_states.empty())
		{
			if (bracket_states.top() == 1)
				PRE_PROCESS_PATTERN_ERROR(parse_result, REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET);
			else PRE_PROCESS_PATTERN_ERROR(parse_result, REGEX_PARSE_MISS_RIGHT_BRACES);
		}
		else if (bracket_count > 0)
			PRE_PROCESS_PATTERN_ERROR(parse_result, REGEX_PARSE_MISS_RIGHT_BRACKET);

		else return string(result.begin(), result.end());
	}

	ConnectedFragment DirectedGraph::parse(string p)
	{
		stack<ConnectedFragment> operands;
		stack<size_t> operators;
		stack<string> group_names;
		operators.push('\0');//the start operator
		parse_result = REGEX_PARSE_NOT_FOUND;
		size_t parse_index = 0;
		while (parse_result == REGEX_PARSE_NOT_FOUND)
		{
			/*
			now we have support () | . + * []
			next to support is ^ $ {}
			*/
			switch (p[parse_index])
			{
			case '\0':
				normal_priority_parse('\0', operators, operands, parse_index);
				if (operators.empty()) parse_result = REGEX_PARSE_OK;
				break;
			case '(':
				if (p[parse_index + 1] == '?')
				{
					parse_index++;
					if (p[parse_index + 1] == '<' || p[parse_index + 1] == '\'')
					{
						//do something for name capture (?<group_name>##) or (?'group_name'##)
						parse_index++;
						char find_char = p[parse_index] == '\'' ? '\'' : '>';
						size_t end_group_name_position = p.find_first_of(find_char, ++parse_index);
						string group_name = p.substr(parse_index, end_group_name_position - parse_index);
						// the stack will store like "?<group_name" or "?'group_name" 
						group_names.push(p.substr(parse_index - 2, 2) + group_name);
						parse_index = end_group_name_position;
					}
					else if (p[parse_index + 1] == ':')
					{
						//don't capture this group (?:###)
						group_names.push(":");
						parse_index++;
					}
				}
				else group_names.push("");
				normal_priority_parse('(', operators, operands, parse_index);
				break;
			case ')':
			{
				size_t temp = parse_index;
				normal_priority_parse(')', operators, operands, parse_index);
				//add group node
				if (temp != parse_index)
					add_group_node(operands, group_names);
				break;
			}
			case '^':
			{
				DirectedEdgePoint edge(new LineStartDirectedEdge(edges.size()));
				store_edge(edge, operands);
				parse_index++;
				break;
			}
			case '$':
			{
				DirectedEdgePoint edge(new LineEndDirectedEdge(edges.size()));
				store_edge(edge, operands);
				parse_index++;
				break;
			}
			case '[':
			{
				// to test

				//p parse_index
#define PARSE_OR_STRING(the_string,the_index)											\
				bool complementary = the_string[++the_index] == '^';/*is complementary?*/	\
				if (complementary)the_index++;												\
				if (p[the_index + 1] == ']')												\
					PARSE_ERROR(parse_result, REGEX_PARSE_SQUARE_BRAKET_IS_EMPTY);			\
				vector<ConditionPoint> conditions;											\
				if (!parse_or_condition(conditions, the_string, the_index))					\
					PARSE_ERROR(parse_result, REGEX_PARSE_ILLEGAL_CHAR_IN_SQUARE_BRAKET);	\
				ConditionPoint condition(new OrCondtion(conditions));						\
				if (complementary)condition.reset(new ComplmentCondtion(condition));		\
				DirectedEdgePoint edge(new SingleCharDirectedEdge(condition, edges.size()));\
				store_edge(edge, operands);													\
				assert(the_string[the_index] == ']');										\
				the_index++;
				PARSE_OR_STRING(p, parse_index);
				break;
			}
			case '{':
			{
				if (!parse_repeat_count_node(p, parse_index, operands))
					PARSE_ERROR(parse_result, REGEX_PARSE_ILLEGAL_REPEAT_COUNT);
				assert(p[parse_index] == '}');
				parse_index++;
				break;
			}

			case '|':
				//can here be more elegent
				normal_priority_parse('|', operators, operands, parse_index);
				break;
				//the escape 
			case '\\':
				switch (p[++parse_index])
				{
					//the dot \N means concatenation  operator
				case 'N':
					normal_priority_parse('.', operators, operands, parse_index);
					if (p[parse_index - 1] == '\\')parse_index--;
					break;
				case 't':
					DEFAULT_SINGLE_CHAR_PROCESS('\t');
					break;
				case 'n':
					DEFAULT_SINGLE_CHAR_PROCESS('\n');
					break;
				case 'r':
					DEFAULT_SINGLE_CHAR_PROCESS('\r');
					break;
				case 'f':
					DEFAULT_SINGLE_CHAR_PROCESS('\f');
					break;
				case 'w':
				{
					string d_string = "[a-zA-Z0-9_]";
					size_t d_index = 0;
					PARSE_OR_STRING(d_string, d_index);
					parse_index++;
					break;
				}
				case 'W':
				{
					string d_string = "[^a-zA-Z0-9_]";
					size_t d_index = 0;
					PARSE_OR_STRING(d_string, d_index);
					parse_index++;
					break;
				}
				case 'd':
				{
					string d_string = "[0-9]";
					size_t d_index = 0;
					PARSE_OR_STRING(d_string, d_index);
					parse_index++;
					break;
				}
				case 'D':
				{
					string d_string = "[^0-9]";
					size_t d_index = 0;
					PARSE_OR_STRING(d_string, d_index);
					parse_index++;
					break;
				}
				case 's':
				{
					string d_string = "[\n\t\r\f ]";
					size_t d_index = 0;
					PARSE_OR_STRING(d_string, d_index);
					parse_index++;
					break;
				}
				case 'S':
				{
					string d_string = "[^\n\t\r\f ]";
					size_t d_index = 0;
					PARSE_OR_STRING(d_string, d_index);
					parse_index++;
					break;
				}
				case 'b':
				{
					break;
				}
				case 'B':
				{
					break;
				}
				case '0':
					PARSE_ERROR(parse_result, REGEX_PARSE_ILLEGAL_GROUP_REFERENCE);
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				{
					DirectedEdgePoint directed_edge = parse_group_reference(p, parse_index);
					if (directed_edge == nullptr)PARSE_ERROR(parse_result, REGEX_PARSE_ILLEGAL_GROUP_REFERENCE);
					else store_edge(directed_edge, operands);
					parse_index++;
					break;
				}
				default:
					DEFAULT_SINGLE_CHAR_PROCESS(p[parse_index]);
					break;
				}
				break;
			case '?':
				if (p[parse_index + 1] == '?') //lazy match
				{
					parse_index++;
					normal_priority_parse('-', operators, operands, parse_index);
				}
				else normal_priority_parse('?', operators, operands, parse_index);
				break;
			case '*':
				if (p[parse_index + 1] == '?') //lazy match
				{
					parse_index++;
					normal_priority_parse('0', operators, operands, parse_index);
					//do something
				}
				else normal_priority_parse('*', operators, operands, parse_index);
				break;
			case '+':
				if (p[parse_index + 1] == '?') //lazy match
				{
					parse_index++;
					//do something
					normal_priority_parse('1', operators, operands, parse_index);
				}
				else normal_priority_parse('+', operators, operands, parse_index);
				break;
				//the single char
			default:
				DEFAULT_SINGLE_CHAR_PROCESS(p[parse_index]);
				break;
			}
		}
		assert(operators.empty());
		assert(operands.size() == 1);
		return operands.top();
	}

	//parse or condition in []
	inline bool DirectedGraph::parse_or_condition(vector<ConditionPoint>& conditions, const string & p, size_t & parse_index)
	{

		size_t current = p[parse_index], next = p[parse_index + 1];
		while (current != ']')
		{
			if (next == '-')
			{
				if (check_range(current, p[parse_index + 2]))
				{
					conditions.push_back(ConditionPoint(new RangeCondition(current, p[parse_index + 2])));
					parse_index += 3;
				}
				else return false;
			}
			else if (current == '\\')
			{
				if (is_special_char(next))
				{
					conditions.push_back(ConditionPoint(new CharCondition(next)));
					parse_index += 2;
				}
				else return false;
			}
			else if (is_special_char(current))
				return false;
			else
			{
				conditions.push_back(ConditionPoint(new CharCondition(current)));
				parse_index++;
			}
			current = p[parse_index], next = p[parse_index + 1];
		}
		return true;
	}

	DirectedEdgePoint DirectedGraph::parse_group_reference(const string & p, size_t & parse_index)
	{
		char *end_point = nullptr;
		const char *start = p.c_str() + parse_index;
		size_t capture_num = (size_t)strtol(start, &end_point, 10);
		if (capture_num == 0 || end_point == start || capture_num >= groups.size())
			return DirectedEdgePoint();
		return DirectedEdgePoint(new GroupReferenceDirectedge(edges.size(), capture_num));
	}

	//parse repeat count in {}
	bool DirectedGraph::parse_repeat_count_node(const string & p, size_t & parse_index, stack<ConnectedFragment>& operands)
	{
		assert(p[parse_index] == '{');
		char *end_point = nullptr;
		const char *start = p.c_str() + parse_index + 1;
		size_t from = static_cast<size_t>(strtol(start, &end_point, 10));
		if (end_point == start)
			return false;
		while ((*end_point) == ' ')end_point++;
		switch (*end_point)
		{
		case ',':
		{
			end_point++;
			while ((*end_point) == ' ')end_point++;
			if ((*end_point) == '}')// from to infinity
			{
				//the end node
				DirectedNodePoint repeat_node(new RepeatCountDirectedNode(nodes.size(), from));
				nodes.push_back(repeat_node);
				store_repeat_node(repeat_node, operands);
				parse_index = end_point - p.c_str();
				return true;
			}
			//from,to 
			start = end_point;
			size_t to = static_cast<size_t>(strtol(start, &end_point, 10));
			if (end_point == start || from > to)
				return false;
			//the end node
			DirectedNodePoint repeat_node(new RepeatCountDirectedNode(nodes.size(), from, to));
			nodes.push_back(repeat_node);
			store_repeat_node(repeat_node, operands);
			while ((*end_point) == ' ')end_point++;
			parse_index = end_point - p.c_str();
			return true;
		}
		case '}':// spcific one repeat count
		{
			//the end node
			DirectedNodePoint repeat_node(new RepeatCountDirectedNode(nodes.size(), from, from));
			nodes.push_back(repeat_node);
			store_repeat_node(repeat_node, operands);
			parse_index = end_point - p.c_str();
			return true;
		}
		default:
			return false;
		}

	}

	//check the range is right?
	bool DirectedGraph::check_range(size_t from, size_t to)
	{
		if (from < to)
		{
			if (is_num(from) && is_num(to)) return true;
			if (is_upper_case(from) && is_upper_case(to))return true;
			if (is_lower_case(from) && is_lower_case(to))return true;
			return false;
		}
		return false;
	}

	//add a single char edge
	inline void DirectedGraph::add_single_char_edge(size_t ch, stack<ConnectedFragment>& operands)
	{
		DirectedEdgePoint edge(new SingleCharDirectedEdge(ch, edges.size()));
		store_edge(edge, operands);
	}

	//store the edge
	inline void DirectedGraph::store_edge(DirectedEdgePoint edge, stack<ConnectedFragment>& operands)
	{
		edges.push_back(edge);
		operands.push(ConnectedFragment(edge->get_id(), edge->get_id()));
	}

	void DirectedGraph::store_repeat_node(DirectedNodePoint repeat_node, stack<ConnectedFragment>& operands)
	{
		//the repeat fragment
		ConnectedFragment repeat_fragment = operands.top();
		operands.pop();
		//the start node
		DirectedNodePoint repeat_start_node(new DirectedNode(nodes.size()));
		nodes.push_back(repeat_start_node);
		size_t the_start_node_id = add_in_sigma_edge(repeat_start_node->get_id());
		//the end_node id
		size_t repeat_node_id = repeat_node->get_id();
		//connect it
		connect_in_node(repeat_start_node->get_id(), repeat_fragment);
		connect_out_node(repeat_node_id, repeat_fragment);
		//repeat edge
		DirectedEdgePoint repeat_edge(new RepeatDirectedge(edges.size()));
		edges.push_back(repeat_edge);
		//connect the repeat position
		connect_out_node_to_edge(the_start_node_id, repeat_edge->get_id());
		//pass edge
		DirectedEdgePoint count_edge(new CountDirectedEdge(edges.size()));
		edges.push_back(count_edge);
		//connet to repeat node
		connect_in_node_to_edge(repeat_node_id, repeat_edge->get_id());
		connect_in_node_to_edge(repeat_node_id, count_edge->get_id());
		//save to stack
		operands.push(ConnectedFragment(the_start_node_id, count_edge->get_id()));
	}

	inline void DirectedGraph::add_group_node(stack<ConnectedFragment>& operands, stack<string> &group_names)
	{
		ConnectedFragment fragment = operands.top();
		operands.pop();
		//connect in node
		DirectedNodePoint in_node(new DirectedNode(nodes.size()));
		nodes.push_back(in_node);
		connect_in_node(in_node->get_id(), fragment);
		//connect out node
		DirectedNodePoint out_node(new DirectedNode(nodes.size()));
		nodes.push_back(out_node);
		connect_out_node(out_node->get_id(), fragment);

		string group_name = group_names.top();
		group_names.pop();
		if (group_name.length() == 0) //add one group and don't give it one name
		{
			//add group
			groups.push_back(Group(in_node->get_id(), out_node->get_id()));
		}
		else if (group_name.length() == 1)
		{
			if (group_name[0] == ':')
				; // don't capture the group
		}
		else
		{
			if (group_name[0] == '?')
			{
				if (group_name[1] == '<' || group_name[1] == '\'')
				{
					//add group
					groups.push_back(Group(in_node->get_id(), out_node->get_id()));
					// give the group name
					name_groups[group_name.substr(2)] = groups.size() - 1;
				}

			}
		}



		size_t in_edge_id = add_in_sigma_edge(in_node->get_id());
		size_t out_edge_id = add_out_sigma_edge(out_node->get_id());

		operands.push(ConnectedFragment(in_edge_id, out_edge_id));
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
			operate(operators.top(), operands, operators);
	}
}
