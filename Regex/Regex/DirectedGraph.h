#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H
#include <vector>
#include "DirectedNode.h"
#include "DirectedEdge.h"

namespace anyun_regex
{
	class DirectedGraph
	{
		friend class NFA;
	public:
		DirectedGraph();
		DirectedGraph(const char *pattern);
		~DirectedGraph();
		
		size_t v();

	private:
		const char * pattern;
		size_t start_node_id;
		size_t end_node_id;
		vector<DirectedNode> nodes;
		vector<DirectedEdge> edges;

		void compile();
	};
}

#endif