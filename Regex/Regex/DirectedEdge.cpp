#include "DirectedEdge.h"

namespace anyun_regex
{
	Condition::~Condition()
	{
	}
	bool DotCondition::match(size_t ch) const
	{
		return true;
	}
	SingleCharCondition::SingleCharCondition(size_t ch):ch(ch)
	{
	}
	bool SingleCharCondition::match(size_t ch) const
	{
		return this->ch == ch;
	}
	RangeCondition::RangeCondition(size_t from, size_t to):from(from),to(to)
	{
	}
	bool RangeCondition::match(size_t ch) const
	{
		return ch >= from && ch <= to;
	}
	ComplmentCondtion::ComplmentCondtion(ConditionPoint condition_ptr):original_condition(condition_ptr)
	{
	}
	bool ComplmentCondtion::match(size_t ch) const
	{
		return !original_condition->match(ch);
	}
	OrCondtion::OrCondtion(ConditionPoint lhs, ConditionPoint rhs)
	{
		conditions.push_back(lhs);
		conditions.push_back(rhs);
	}
	OrCondtion::OrCondtion(vector<ConditionPoint> conditions):conditions(conditions)
	{
	}
	bool OrCondtion::match(size_t ch) const
	{
		for (vector<ConditionPoint>::const_iterator b = conditions.cbegin(), e = conditions.cend(); b != e; b++)
			if ((*b)->match(ch))return true;
		return false;
	}
	DirectedEdge::DirectedEdge(size_t id)
		:id(id),start_id(0),end_id(0),is_sigma(true)
	{
	}
	DirectedEdge::DirectedEdge(char ch, size_t id,size_t s_id, size_t e_id)
		: id(id), start_id(s_id), end_id(e_id), is_sigma(false)
	{
		if (ch == '.')condition.reset(new DotCondition());
		else condition.reset(new SingleCharCondition(ch));
	}
	DirectedEdge::DirectedEdge(char start,char end, size_t id, bool complementary,size_t s_id, size_t e_id)
		:id(id), start_id(s_id), end_id(e_id), is_sigma(false)
	{
		ConditionPoint range_condition(new RangeCondition(start, end));
		if (complementary) condition.reset(new ComplmentCondtion(range_condition));
		else condition = range_condition;
	}

	DirectedEdge::DirectedEdge(ConditionPoint condition, size_t id, size_t s_id, size_t e_id) 
		: id(id), start_id(s_id), end_id(e_id), is_sigma(false),condition(condition)
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


	size_t DirectedEdge::get_start_node_id() const
	{
		return start_id;
	}

	size_t DirectedEdge::get_end_node_id() const
	{
		return end_id;
	}

	bool DirectedEdge::is_sigma_edge() const
	{
		return is_sigma;
	}
	bool DirectedEdge::accept(char ch) const
	{
		return !is_sigma && condition->match(ch);
	}
	size_t DirectedEdge::get_id() const
	{
		return id;
	}
}
