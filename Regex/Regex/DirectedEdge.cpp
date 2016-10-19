#include "DirectedEdge.h"

namespace anyun_regex
{
	DirectedEdge::DirectedEdge(size_t id,bool is_dot) : id(id),condition(is_dot) {}
	DirectedEdge::DirectedEdge(size_t s_id, size_t e_id, size_t id):id(id), start_id(s_id), end_id(e_id)
	{
	}
	DirectedEdge::DirectedEdge(const char *str, size_t id): id(id)
	{

	}
	DirectedEdge::DirectedEdge(char ch, size_t id) : id(id)
	{
		//for the dot char
		if (ch == '.')condition = TransactionCondition(true);
		else condition = TransactionCondition(ch);
	}
	DirectedEdge::DirectedEdge(char ch, size_t s_id, size_t  e_id, size_t id) : id(id), start_id(s_id), end_id(e_id),condition(ch)
	{

	}
	DirectedEdge::~DirectedEdge()
	{
	}

	void DirectedEdge::set_start_node(size_t  node_id)
	{
		start_id = node_id;
	}

	void DirectedEdge::set_end_node(size_t node_id)
	{
		end_id = node_id;
	}

	size_t DirectedEdge::get_start_node_id()
	{
		return start_id;
	}

	size_t DirectedEdge::get_end_node_id()
	{
		return end_id;
	}
	
	bool DirectedEdge::is_sigma_edge()
	{
		return condition.flag == -1;
	}
	bool DirectedEdge::accept(char ch)
	{
		return condition.match(ch);
	}
	size_t DirectedEdge::get_id()
	{
		return id;
	}
	/*
	if is_dot is true which means the condition can accept any char
	else is sigma condition,namely sigma(the empty edge),not accept any char
	
	*/
	TransactionCondition::TransactionCondition(bool is_dot)
	{
		if (is_dot)flag = 2;
		else flag = -1;
	}
	TransactionCondition::TransactionCondition(char ch) :flag(0) 
	{
		condition.ch = ch;
	}
	TransactionCondition::TransactionCondition(int start, int end):flag(1)
	{
		condition.range.start_index = start;
		condition.range.end_index = end;
	}

	bool TransactionCondition::match(int ch)
	{
		switch (flag)
		{
		case -1:
			return false;
		case 0:
			return condition.ch == ch;
		case 1:
			return ch >= condition.range.start_index && ch <= condition.range.end_index;
		case 2:
			return true;
		default:
			return false;
		}
	}
}
