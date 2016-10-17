#ifndef DIRECTED_NODE_H
#define DIRECTED_NODE_H
#include <vector>
#include "DirectedEdge.h"

namespace anyun_regex
{
	using std::vector;
	class DirectedNode
	{
		friend class DirectedGraph;
	public:
		DirectedNode(size_t id,bool is_final = false);
		DirectedNode(bool is_final = false);
		~DirectedNode();

		const vector<size_t> & get_out_edges();
		const vector<size_t> & get_in_edges();
		size_t out_edges_num();
		size_t in_edges_num();
		size_t get_id();
		bool is_final();

	private:
		size_t id;	//the id of this node in digraph
		bool is_final_node;
		vector<size_t> out_edges;
		vector<size_t> in_edges;

		void set_id(size_t id);
		void set_final(bool f);
		void add_out_edge(size_t out_edge_id);
		void add_in_edge(size_t in_edge_id);
	};
}

#endif