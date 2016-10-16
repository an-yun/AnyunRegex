#include "DirectedGraph.h"

namespace anyun_regex
{
	DirectedGraph::DirectedGraph()
	{
		pattern = "";
		nodes.push_back(new DirectedNode(true));
		start_node = end_node = nodes[0];
	}
	DirectedGraph::DirectedGraph(const char * pattern)
	{
		this->pattern = pattern;
		compile();
	}
	DirectedGraph::~DirectedGraph()
	{
		for (size_t i = 0; i < nodes.size(); i++)	//release memory
			delete nodes[i];
	}
	size_t DirectedGraph::v()
	{
		return nodes.size();
	}
	void DirectedGraph::compile()
	{
		start_node = new DirectedNode();
		nodes.push_back(start_node);
		DirectedNode *state = start_node;

		for (size_t index = 0; pattern[index] != '\0'; index++)
		{
			char ch = pattern[index];

			//simple transaction
			DirectedNode *next = new DirectedNode();
			nodes.push_back(next);
			DirectedEdge *edge = new DirectedEdge(ch, state, next);
			state->add_out_edge(edge);
			next->add_in_edge(edge);
			state = next;
		}

		end_node = state;
		end_node->set_final(true);
	}
}
