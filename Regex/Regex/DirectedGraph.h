#ifndef DIRECTED_GRAPH
#define DIRECTED_GRAPH
#include <vector>

#include "DirectedNode.h"
#include "DirectedEdge.h"

namespace anyun_regex
{
	class DirectedGraph
	{
	public:
		DirectedGraph();
		DirectedGraph(const char *pattern);
		~DirectedGraph();
		
		size_t v();

	private:
		const char *pattern;
		DirectedNode *start_node;
		DirectedNode *end_node;
		vector<DirectedNode*> nodes;

		void compile();
	};
}

#endif