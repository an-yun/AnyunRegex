#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H
#include <map>
#include <vector>
#include <stack>
#include <string>
#include <assert.h>
#include "DirectedNode.h"
#include "DirectedEdge.h"

namespace anyun_regex
{
	using std::map;
	using std::stack;
	using std::string;
	enum RegexParseCode {
		REGEX_PARSE_OK = 0,
		REGEX_PARSE_NOT_FOUND,
		REGEX_PARSE_PATTERN_IS_NULL,
		REGEX_PARSE_MISS_LEFT_BRACKET,
		REGEX_PARSE_MISS_RIGHT_BRACKET,
		REGEX_PARSE_GET_RIGHT_BRACKET,
		REGEX_PARSE_GET_INVALID_CHAR
	};
	struct ConnectedFragment
	{
		size_t in_edge_id;
		size_t out_edge_id;
		ConnectedFragment(size_t i_id, size_t o_id) :in_edge_id(i_id), out_edge_id(o_id) {}
	};
	class DirectedGraph
	{
		friend class NFA;
	public:
		DirectedGraph();
		DirectedGraph(const char *pattern);
		~DirectedGraph();
		/*
		static const char SINGLE_SPECAIL_CAHR[];
		static const size_t SINGLE_SPECAIL_CAHR_SIZE;
		static bool is_special_char(char ch);
		*/
		size_t v();

		RegexParseCode compile(const char *pattern);


	private:
		string pattern;
		size_t start_node_id;
		size_t end_node_id;
		vector<DirectedNode> nodes;
		vector<DirectedEdge> edges;
		RegexParseCode parse_result;
		size_t parse_index;
		
		static int get_priority(size_t op1,size_t op2);
		void operate(size_t opt, stack<ConnectedFragment> &operands);
		void connect_in_node(size_t in_node_id, const ConnectedFragment &fragment);
		void connect_out_node(size_t out_node_id, const ConnectedFragment &fragment);
		void connect_fragments(const ConnectedFragment &fragment1, const ConnectedFragment &fragment2);
		void connect_in_node_to_edge(size_t in_node_id, size_t edge_id);
		void connect_out_node_to_edge(size_t out_node_id, size_t edge_id);
		ConnectedFragment parse();
	};
}

#endif