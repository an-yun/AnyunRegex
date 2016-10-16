#include "DirectedNode.h"

namespace anyun_regex
{
	DirectedNode::DirectedNode(bool is_final = false):out_edges(),in_edges(),is_final_node(is_final)
	{
	}
	DirectedNode::~DirectedNode()
	{
		for (size_t i = 0; i < out_edges.size(); i++)  //only release out_edges memory
			delete out_edges[i];
	}
	const vector<DirectedEdge*>& anyun_regex::DirectedNode::get_out_edges()
	{
		return out_edges;
	}

	const vector<DirectedEdge*>& DirectedNode::get_in_edges()
	{
		return in_edges;
	}

	size_t DirectedNode::out_edges_num()
	{
		return out_edges.size();
	}

	size_t DirectedNode::in_edges_num()
	{
		return in_edges.size();
	}

	void DirectedNode::add_out_edge(DirectedEdge * out_edge)
	{
		out_edges.push_back(out_edge);
	}

	void DirectedNode::add_in_edge(DirectedEdge * in_edge)
	{
		in_edges.push_back(in_edge);
	}

	bool DirectedNode::is_final()
	{
		return is_final_node;
	}

	void DirectedNode::set_final(bool f)
	{
		is_final_node = f;
	}


}
