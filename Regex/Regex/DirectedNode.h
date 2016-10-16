#ifndef DIRECTED_NODE
#define DIRECTED_NODE
#include <vector>
#include "DirectedEdge.h"

namespace anyun_regex
{
	using std::vector;
	class DirectedNode
	{
	public:

		DirectedNode(bool is_final = false);
		~DirectedNode();

		const vector<DirectedEdge *> & get_out_edges();
		const vector<DirectedEdge *> & get_in_edges();
		size_t out_edges_num();
		size_t in_edges_num();
		void add_out_edge(DirectedEdge * out_edge);
		void add_in_edge(DirectedEdge * in_edge);
		bool is_final();
		void set_final(bool f);
	private:
		vector<DirectedEdge *> out_edges;
		vector<DirectedEdge *> in_edges;
		bool is_final_node;
	};
}

#endif