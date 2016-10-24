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

	CharCondition::CharCondition(size_t ch):ch(ch)
	{
	}

	bool CharCondition::match(size_t ch) const
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


	DirectedEdge::DirectedEdge(size_t id, size_t s_id, size_t e_id):id(id),start_id(s_id),end_id(e_id)
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


	size_t DirectedEdge::get_start_node_id(const Matcher &matcher) const
	{
		return start_id;
	}

	size_t DirectedEdge::get_end_node_id(const Matcher &matcher) const
	{
		return end_id;
	}

	size_t DirectedEdge::get_id() const
	{
		return id;
	}

	DirectedEdge::~DirectedEdge()
	{
	}



	SigmaDirectedEdge::SigmaDirectedEdge(size_t id, size_t s_id, size_t e_id) 
		:DirectedEdge(id, s_id, e_id)
	{
	}

	DirectedEdgeType SigmaDirectedEdge::get_type() const
	{
		return SIGMA_DIRECTEDEDGE;
	}
	bool SigmaDirectedEdge::accept(const string & text, size_t index, Matcher & matcher) const
	{
		return false;
	}
	DirectedEdgeType SingleCharDirectedEdge::get_type() const
	{
		return SINGLE_CHAR_DIRECTEDEDGE;
	}

	bool SingleCharDirectedEdge::accept(const string & text, size_t index, Matcher & matcher) const
	{
		return condition->match(text[index]);
	}


	SingleCharDirectedEdge::SingleCharDirectedEdge(size_t ch, size_t id, size_t s_id, size_t e_id)
		:DirectedEdge(id, s_id, e_id)
	{
		if (ch == '.')condition.reset(new DotCondition());
		else condition.reset(new CharCondition(ch));
	}
	SingleCharDirectedEdge::SingleCharDirectedEdge(size_t start, size_t end, size_t id, bool complementary, size_t s_id, size_t e_id)
		: DirectedEdge(id, s_id, e_id)
	{
		ConditionPoint range_condition(new RangeCondition(start, end));
		if (complementary) condition.reset(new ComplmentCondtion(range_condition));
		else condition = range_condition;
	}

	SingleCharDirectedEdge::SingleCharDirectedEdge(ConditionPoint condition, size_t id, size_t s_id, size_t e_id) 
		: DirectedEdge(id, s_id, e_id)
	{
	}


}
