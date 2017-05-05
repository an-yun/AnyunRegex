#include "DirectedEdge.h"

namespace anyun_regex
{

	Condition::~Condition()
	{
	}

	bool DotCondition::match(size_t ch) const
	{
		return ch != '\n';
	}


	CharCondition::CharCondition(size_t ch) :ch(ch)
	{
	}

	bool CharCondition::match(size_t ch) const
	{
		return this->ch == ch;
	}

	RangeCondition::RangeCondition(size_t from, size_t to) :from(from), to(to)
	{
	}

	bool RangeCondition::match(size_t ch) const
	{
		return ch >= from && ch <= to;
	}

	ComplmentCondtion::ComplmentCondtion(ConditionPoint condition_ptr) :original_condition(condition_ptr)
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

	OrCondtion::OrCondtion(vector<ConditionPoint> conditions) :conditions(conditions)
	{
	}

	bool OrCondtion::match(size_t ch) const
	{
		for (vector<ConditionPoint>::const_iterator b = conditions.cbegin(), e = conditions.cend(); b != e; b++)
			if ((*b)->match(ch))return true;
		return false;
	}


	DirectedEdge::DirectedEdge(size_t id, size_t s_id, size_t e_id) 
	:id(id), start_id(s_id), end_id(e_id)
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

	size_t SigmaDirectedEdge::accept(const string & text, size_t index, Matcher & matcher, TrackRecord & track_record)
	{
		return 0;
	}
	DirectedEdge * SigmaDirectedEdge::copy() const
	{
		return new SigmaDirectedEdge(*this);
	}
	DirectedEdgeType SingleCharDirectedEdge::get_type() const
	{
		return SINGLE_CHAR_DIRECTEDEDGE;
	}

	size_t SingleCharDirectedEdge::accept(const string & text, size_t index, Matcher & matcher, TrackRecord & track_record)
	{
		return index < matcher.text.length() && condition->match(text[index]) ? 1 : static_cast<unsigned>(-1);
	}

	DirectedEdge * SingleCharDirectedEdge::copy() const
	{
		return new SingleCharDirectedEdge(*this);
	}


	SingleCharDirectedEdge::SingleCharDirectedEdge(size_t ch, size_t id, size_t s_id, size_t e_id)
		:DirectedEdge(id, s_id, e_id),condition(new CharCondition(ch))
	{
	}

	SingleCharDirectedEdge::SingleCharDirectedEdge(size_t start, size_t end, size_t id, bool complementary, size_t s_id, size_t e_id)
		: DirectedEdge(id, s_id, e_id)
	{
		ConditionPoint range_condition(new RangeCondition(start, end));
		if (complementary) condition.reset(new ComplmentCondtion(range_condition));
		else condition = range_condition;
	}

	SingleCharDirectedEdge::SingleCharDirectedEdge(ConditionPoint condition, size_t id, size_t s_id, size_t e_id)
		: DirectedEdge(id, s_id, e_id), condition(condition)
	{
	}




	LineStartDirectedEdge::LineStartDirectedEdge(size_t id) : DirectedEdge(id)
	{
	}

	DirectedEdgeType LineStartDirectedEdge::get_type() const
	{
		return LINE_START_DIRECTEDEDGE;
	}

	size_t LineStartDirectedEdge::accept(const string & text, size_t index, Matcher & matcher, TrackRecord & track_record)
	{
		return (index == 0 || text[index-1] == '\n') ? 0 : static_cast<unsigned>(-1);
	}

	DirectedEdge * LineStartDirectedEdge::copy() const
	{
		return new LineStartDirectedEdge(*this);
	}

	LineEndDirectedEdge::LineEndDirectedEdge(size_t id)
		:DirectedEdge(id)
	{
	}

	DirectedEdgeType LineEndDirectedEdge::get_type() const
	{
		return LINE_END_DIRECTEDEDGE;
	}

	size_t LineEndDirectedEdge::accept(const string & text, size_t index, Matcher & matcher, TrackRecord & track_record)
	{
		return (index == text.size() || (index < text.size() && text[index] == '\n')) ? 0 : static_cast<unsigned>(-1);
	}

	DirectedEdge * LineEndDirectedEdge::copy() const
	{
		return new LineEndDirectedEdge(*this);
	}


	CountDirectedEdge::CountDirectedEdge(size_t id)
		: DirectedEdge(id)
	{
	}

	DirectedEdgeType CountDirectedEdge::get_type() const
	{
		return COUNT_DIRECTEDEDGE;
	}

	size_t CountDirectedEdge::accept(const string & text, size_t index, Matcher & matcher, TrackRecord & track_record)
	{
		return static_cast<unsigned>(-1);
	}

	DirectedEdge * CountDirectedEdge::copy() const
	{
		return new CountDirectedEdge(*this);
	}

	pair<size_t, size_t> Matcher::get_group(size_t group_index)
	{
		return groups[group_index];
	}


	RepeatDirectedge::RepeatDirectedge(size_t id, size_t s_id, size_t e_id)
		:DirectedEdge(id, s_id, e_id)
	{
	}

	DirectedEdgeType RepeatDirectedge::get_type() const
	{
		return REPEAT_DIRECTEDEDGE;
	}

	size_t RepeatDirectedge::accept(const string & text, size_t index, Matcher & matcher, TrackRecord & track_record)
	{
		return static_cast<unsigned>(-1);
	}

	DirectedEdge * RepeatDirectedge::copy() const
	{
		return new RepeatDirectedge(*this);
	}

	GroupReferenceDirectedge::GroupReferenceDirectedge(size_t id, size_t group_id, size_t s_id, size_t e_id)
		:DirectedEdge(id, s_id, e_id), reference_id(group_id)
	{
	}

	DirectedEdgeType GroupReferenceDirectedge::get_type() const
	{
		return GROUP_REFERENCE_DIRECTEDGE;
	}

	size_t GroupReferenceDirectedge::accept(const string & text, size_t index, Matcher & matcher, TrackRecord & track_record)
	{
		//here should be move ?
		//if (index >= matcher.text.length()) return static_cast<unsigned>(-1);
		pair<size_t, size_t> reference_group = matcher.get_groups_node(reference_id);
		size_t length = track_record[reference_group.second].first - track_record[reference_group.first].first;
		string group_str = text.substr(track_record[reference_group.first].first, length);
		for (size_t i = 0; i < length; i++)
			if (group_str[i] != text[index + i])
				return static_cast<unsigned>(-1);
		//then shouldn't move the cursor
		return length;
	}

	DirectedEdge * GroupReferenceDirectedge::copy() const
	{
		return new GroupReferenceDirectedge(*this);
	}

	WordBoundaryDirectedEdge::WordBoundaryDirectedEdge(size_t id):DirectedEdge(id)
	{

	}

	DirectedEdgeType WordBoundaryDirectedEdge::get_type() const
	{
		return WORD_BOUNDARY_DIRECTEDEDGE;
	}

	size_t WordBoundaryDirectedEdge::accept(const string & text, size_t index, Matcher & matcher, TrackRecord & track_record)
	{
		//word start
		if ((index == 0 || is_blank(text[index - 1])) && !is_blank(text[index])) return 0;
		//word end
		if ((index == text.size() || is_blank(text[index])) && !is_blank(text[index-1])) return 0;
		return static_cast<unsigned>(-1);
	}

	DirectedEdge * WordBoundaryDirectedEdge::copy() const
	{
		return new WordBoundaryDirectedEdge(*this);
	}

	ElementDirectedge::ElementDirectedge(size_t id, DirectedEdgePoint original_edge)
		:DirectedEdge(id),original_edge(original_edge)
	{
	}

	DirectedEdgeType ElementDirectedge::get_type() const
	{
		return ELEMENT_DIRECTEDGE;
	}

	size_t ElementDirectedge::accept(const string & text, size_t index, Matcher & matcher, TrackRecord & track_record)
	{
		return original_edge->accept(text,index,matcher,track_record)==static_cast<size_t>(-1)?0: static_cast<size_t>(-1);
	}

	DirectedEdge * ElementDirectedge::copy() const
	{
		return new ElementDirectedge(*this);
	}

	PLAZeroAssertionDirectedge::PLAZeroAssertionDirectedge(size_t id, const string &pattern)
		:DirectedEdge(id)
	{
		//lazy implement
		sub_exp_matcher.set_pattern(pattern+".*");
	}

	DirectedEdgeType PLAZeroAssertionDirectedge::get_type() const
	{
		return PLA_ZERO_ASSERTION_DIRECTEDGE;
	}

	size_t PLAZeroAssertionDirectedge::accept(const string & text, size_t index, Matcher & matcher, TrackRecord & track_record)
	{
		sub_exp_matcher.set_text(text);
		return sub_exp_matcher.match(index,text.length())?0: static_cast<size_t>(-1);
	}

	DirectedEdge * PLAZeroAssertionDirectedge::copy() const
	{
		return new PLAZeroAssertionDirectedge(*this);
	}

}
