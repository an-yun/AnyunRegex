#include "DirectedEdge.h"

namespace anyun_regex
{
	DirectedEdge::DirectedEdge() :start(nullptr), end(nullptr) {}
	DirectedEdge::DirectedEdge(const char *)
	{

	}
	DirectedEdge::DirectedEdge(char ch)
	{
		condition = new TransactionCondition(ch);
	}
	DirectedEdge::DirectedEdge(char ch, DirectedNode *s, DirectedNode *e)
	{
		condition = new TransactionCondition(ch);
		start = s;
		end = e;
	}
	DirectedEdge::~DirectedEdge()
	{
		delete condition;
	}
	void DirectedEdge::set_start_node(DirectedNode * node)
	{
		start = node;
	}
	void DirectedEdge::set_end_node(DirectedNode * node)
	{
		end = node;
	}
	TransactionCondition::TransactionCondition(int start, int end)
	{
		start_index = start;
		end_index = end;
		is_char = false;
	}
	TransactionCondition::TransactionCondition(char ch) :ch(ch),is_char(true) {}
	bool TransactionCondition::match(int ch)
	{
		if (is_char) return ch == this->ch;
		else return ch >= start_index && ch <= end_index;
	}
}
