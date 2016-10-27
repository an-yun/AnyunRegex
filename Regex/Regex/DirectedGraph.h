#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H
#include <map>
#include <vector>
#include <tuple>
#include <stack>
#include <list>
#include <string>
#include <memory>
#include <assert.h>
#include "DirectedNode.h"
#include "DirectedEdge.h"

namespace anyun_regex
{
	using std::map;
	using std::stack;
	using std::list;
	using std::string;
	using std::shared_ptr;
	using std::tuple;

	enum RegexParseCode {
		REGEX_PARSE_OK = 0,
		REGEX_PARSE_NOT_FOUND,
		REGEX_PARSE_PATTERN_IS_NULL,
		REGEX_PARSE_MISS_LEFT_BRACKET,
		REGEX_PARSE_MISS_RIGHT_BRACKET,
		REGEX_PARSE_MISS_LEFT_SQUARE_BRACKET,
		REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET,
		REGEX_PARSE_MISS_LEFT_BRACES,
		REGEX_PARSE_MISS_RIGHT_BRACES,
		REGEX_PARSE_ILLEGAL_CHAR_AFTER_OR,
		REGEX_PARSE_BRAKET_NESTED,
		REGEX_PARSE_SQUARE_BRAKET_NESTED,
		REGEX_PARSE_ILLEGAL_CHAR_IN_SQUARE_BRAKET,
		REGEX_PARSE_ILLEGAL_CHAR_IN_BRACES,
		REGEX_PARSE_SQUARE_BRAKET_IS_EMPTY,
		REGEX_PARSE_BRACES_IS_EMPTY
	};
	static const char *PARSE_RESULT_MESSAGE[] =
	{
		"REGEX_PARSE_OK",
		"REGEX_PARSE_NOT_FOUND",
		"REGEX_PARSE_PATTERN_IS_NULL",
		"REGEX_PARSE_MISS_LEFT_BRACKET",
		"REGEX_PARSE_MISS_RIGHT_BRACKET",
		"REGEX_PARSE_MISS_LEFT_SQUARE_BRACKET",
		"REGEX_PARSE_MISS_RIGHT_SQUARE_BRACKET",
		"REGEX_PARSE_MISS_LEFT_BRACES",
		"REGEX_PARSE_MISS_RIGHT_BRACES",
		"REGEX_PARSE_ILLEGAL_CHAR_AFTER_OR",
		"REGEX_PARSE_BRAKET_NESTED",
		"REGEX_PARSE_SQUARE_BRAKET_NESTED",
		"REGEX_PARSE_ILLEGAL_CHAR_IN_SQUARE_BRAKET",
		"REGEX_PARSE_ILLEGAL_CHAR_IN_BRACES",
		"REGEX_PARSE_SQUARE_BRAKET_IS_EMPTY",
		"REGEX_PARSE_BRACES_IS_EMPTY",
		nullptr
	};

	const size_t ZERO = '0';
	const size_t NINE = '9';
	const size_t LOWER_A = 'a';
	const size_t LOWER_Z = 'z';
	const size_t UPPER_A = 'A';
	const size_t UPPER_Z = 'Z';

	struct ConnectedFragment
	{
		size_t in_edge_id;
		size_t out_edge_id;
		ConnectedFragment(size_t i_id, size_t o_id) :in_edge_id(i_id), out_edge_id(o_id) {}
	};

	struct Group
	{
		size_t group_start_node;
		size_t group_end_node;
		Group(size_t group_start, size_t group_end) :group_start_node(group_start), group_end_node(group_end) {}
	};

	class DirectedGraph
	{
		friend class NFA;
#ifdef _DEBUG
		friend class DirectedGraphTest;
#endif // DEBUG
	public:

		static const char SINGLE_SPECAIL_CAHRS[];
		static const size_t SINGLE_SPECAIL_CAHR_SIZE;
		static bool is_special_char(size_t ch);
		static bool is_upper_case(size_t ch);
		static bool is_lower_case(size_t ch);
		static bool is_letter(size_t ch);
		static bool is_num(size_t ch);
		static bool is_alpnum(size_t ch);
		static bool is_char_in(size_t ch, const char *str, size_t length);

	public:
		DirectedGraph();
		DirectedGraph(const char *pattern);
		DirectedGraph(const string &pattern);
		~DirectedGraph();

		size_t v();



	private:
		string pattern;
		size_t start_node_id;
		size_t end_node_id;
		vector<DirectedNodePoint> nodes;
		vector<DirectedEdgePoint> edges;
		vector<Group> groups;
		RegexParseCode parse_result;
		
		static int get_priority(size_t op1,size_t op2);

		RegexParseCode compile(const string &pattern);
		void operate(size_t opt, stack<ConnectedFragment> &operands);
		void connect_in_node(size_t in_node_id, const ConnectedFragment &fragment);
		void connect_out_node(size_t out_node_id, const ConnectedFragment &fragment);
		size_t add_in_sigma_edge(size_t node_id);
		size_t add_out_sigma_edge(size_t node_id);
		/*
		connect fragment to itself
          <fra<
		 \     /
		->  O  ->

		*/
		ConnectedFragment self_connect_fragment(const ConnectedFragment &fragment);
		/*
		connect fragment1 to fragment1 
		->fra1->fra2->
		*/
		ConnectedFragment connect_fragments(const ConnectedFragment &fragment1, const ConnectedFragment &fragment2);
		/*
		merge fragment1 and  fragment2 together
		   
		   >fra1>
		  /      \
	   ->O        O->
		  \      /
		   >fra2>
		*/
		ConnectedFragment merge_fragments(const ConnectedFragment &fragment1, const ConnectedFragment &fragment2);
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
		ConnectedFragment merge_fragments(const vector<ConnectedFragment> &fragments);
		/*
		reverse merge fragment1 and  fragment2 together

		   >fra1>
		  /      \
	    ->O       O->
		  \      /
		   <fra2<
		*/
		ConnectedFragment reverse_merge_fragments(const ConnectedFragment &fragment1, const ConnectedFragment &fragment2);

		void connect_in_node_to_edge(size_t in_node_id, size_t edge_id);
		void connect_out_node_to_edge(size_t out_node_id, size_t edge_id);

		//pre_process_pattern add the dot \N (means concatenation  operator) to pattern
		string pre_process_pattern(const string &p);

		ConnectedFragment parse(string p);

		//parse or condition in []
		bool parse_or_condition(vector<ConditionPoint> &conditions, const string &p, size_t &parse_index);

		//check the range is right?
		bool check_range(size_t from,size_t to);

		//store the edge
		void store_edge(DirectedEdgePoint edge, stack<ConnectedFragment> &operands);

		//compare op's priority with operators.top()'s
		//accroding the result of  comparation to decide it should push or operate
		void normal_priority_parse(size_t op, stack<size_t> &operators, stack<ConnectedFragment>& operands, size_t &parse_index);
	};

	typedef shared_ptr<DirectedGraph> DirectedGraphPoint;
}

#endif