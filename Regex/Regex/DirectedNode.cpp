#include "DirectedNode.h"

namespace anyun_regex
{
	DirectedNode::DirectedNode(size_t id, bool is_final):id(id), is_final_node(is_final),out_edges(), in_edges()
	{
	}
	DirectedNode::DirectedNode(bool is_final): is_final_node(is_final),out_edges(),in_edges()
	{
	}
	DirectedNode::~DirectedNode()
	{
		
	}
	const vector<size_t>& anyun_regex::DirectedNode::get_out_edges()
	{
		return out_edges;
	}

	const vector<size_t>& DirectedNode::get_in_edges()
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

	size_t DirectedNode::get_id()
	{
		return id;
	}

	void DirectedNode::add_out_edge(size_t out_edge_id)
	{
		out_edges.push_back(out_edge_id);
	}

	void DirectedNode::add_in_edge(size_t in_edge_id)
	{
		in_edges.push_back(in_edge_id);
	}

	bool DirectedNode::is_final()
	{
		return is_final_node;
	}

	void DirectedNode::set_final(bool f)
	{
		is_final_node = f;
	}

	void DirectedNode::set_id(size_t id)
	{
		this->id = id;
	}


}
