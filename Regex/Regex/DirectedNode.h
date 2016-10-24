#ifndef DIRECTED_NODE_H
#define DIRECTED_NODE_H
#include <vector>
#include <memory>
#include "DirectedEdge.h"

namespace anyun_regex
{
	using std::vector;
	using std::shared_ptr;
	class Matcher;

	enum DirectedNodeType
	{
		DIRECTEDNODE,
		START_DIRECTEDNODE,
		END_DIRECTEDNODE
	};
	class DirectedNode
	{
		friend class DirectedGraph;
	public:
		DirectedNode(size_t id = 0);
		virtual ~DirectedNode();

		const vector<size_t> & get_out_edges() const;
		const vector<size_t> & get_in_edges() const;
		size_t out_edges_num() const;
		size_t in_edges_num() const;
		size_t get_id() const;

		virtual void action(Matcher &matcher) const;
		virtual DirectedNodeType get_type() const;

	private:
		size_t id;	//the id of this node in digraph
		vector<size_t> out_edges;
		vector<size_t> in_edges;

		void set_id(size_t id);
		void add_out_edge(size_t out_edge_id);
		void add_in_edge(size_t in_edge_id);
	};

	typedef shared_ptr<DirectedNode> DirectedNodePoint;

	class StartDirectedNode:public DirectedNode
	{
	public:
		StartDirectedNode(size_t id = 0);

		void action(Matcher &matcher) const override;
		DirectedNodeType get_type() const override;
	private:

	};

	class EndDirectedNode :public DirectedNode
	{
	public:
		EndDirectedNode(size_t id = 0);

		void action(Matcher &matcher) const override;
		DirectedNodeType get_type() const override;
	private:

	};
}

#endif