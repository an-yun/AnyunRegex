#include "DirectedGraph.h"

namespace anyun_regex
{
	DirectedGraph::DirectedGraph()
	{
		pattern = "";
		nodes.push_back(DirectedNode(0,true));
		start_node_id = end_node_id = 0;
	}
	DirectedGraph::DirectedGraph(const char * pattern):pattern(pattern)
	{
		compile();
	}
	DirectedGraph::~DirectedGraph()
	{
		
	}
	size_t DirectedGraph::v()
	{
		return nodes.size();
	}
	void DirectedGraph::compile()
	{
		nodes.push_back(DirectedNode());
		nodes.back().set_id(0);
		start_node_id = 0;
		size_t state = 0;
		for (size_t index = 0; pattern[index] != '\0'; index++)
		{
			char ch = pattern[index];

			//simple transaction
			DirectedNode next(nodes.size());
			DirectedEdge edge(ch, state, next.get_id(),edges.size());
			nodes[state].add_out_edge(edge.get_id());
			next.add_in_edge(edge.get_id());
			nodes.push_back(next);
			edges.push_back(edge);
			state = next.get_id();
		}

		end_node_id = state;
		nodes[end_node_id].set_final(true);
	}
}
