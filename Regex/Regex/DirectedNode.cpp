#include "DirectedNode.h"

namespace anyun_regex
{
	DirectedNode::DirectedNode(size_t id):id(id),out_edges(), in_edges()
	{
	}

	DirectedNode::~DirectedNode()
	{
		
	}
	const vector<size_t>& anyun_regex::DirectedNode::get_out_edges() const
	{
		return out_edges;
	}

	const vector<size_t>& DirectedNode::get_in_edges() const
	{
		return in_edges;
	}

	size_t DirectedNode::out_edges_num() const
	{
		return out_edges.size();
	}

	size_t DirectedNode::in_edges_num() const
	{
		return in_edges.size();
	}

	size_t DirectedNode::get_id() const
	{
		return id;
	}


	DirectedNodeType DirectedNode::get_type() const
	{
		return DIRECTEDNODE;
	}

	void DirectedNode::add_out_edge(size_t out_edge_id)
	{
		out_edges.push_back(out_edge_id);
	}

	void DirectedNode::add_in_edge(size_t in_edge_id)
	{
		in_edges.push_back(in_edge_id);
	}


	void DirectedNode::set_id(size_t id)
	{
		this->id = id;
	}


	StartDirectedNode::StartDirectedNode(size_t id):DirectedNode(id)
	{
	}


	DirectedNodeType StartDirectedNode::get_type() const
	{
		return START_DIRECTEDNODE;
	}

	EndDirectedNode::EndDirectedNode(size_t id) :DirectedNode(id)
	{
	}


	DirectedNodeType EndDirectedNode::get_type() const
	{
		return END_DIRECTEDNODE;
	}

	RepeatCountDirectedNode::RepeatCountDirectedNode(size_t id, size_t left, size_t right)
		:DirectedNode(id),left(left),right(right),lazy_match(false)
	{
	}

	DirectedNodeType RepeatCountDirectedNode::get_type() const
	{
		return REPEAT_COUNT_DIRECTEDNODE;
	}

	int RepeatCountDirectedNode::accept_count(size_t count)
	{
		if (count < left) return -1;
		if( count>= left && count < right) return 0;
		if (count == right) return 1;
		return 2;
	}

	bool RepeatCountDirectedNode::is_lazy()
	{
		return lazy_match;
	}

	void RepeatCountDirectedNode::set_lazy(bool is_lazy)
	{
		lazy_match = is_lazy;
	}

}
