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
	bool SigmaDirectedEdge::accept(const string & text, size_t index, Matcher & matcher, State& state) const
	{
		return false;
	}
	DirectedEdgeType SingleCharDirectedEdge::get_type() const
	{
		return SINGLE_CHAR_DIRECTEDEDGE;
	}

	bool SingleCharDirectedEdge::accept(const string & text, size_t index, Matcher & matcher, State& state) const
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
		: DirectedEdge(id, s_id, e_id),condition(condition)
	{
	}


	LineStartDirectedEdge::LineStartDirectedEdge(size_t id):DirectedEdge(id)
	{
	}

	DirectedEdgeType LineStartDirectedEdge::get_type() const
	{
		return LINE_START_DIRECTEDEDGE;
	}

	bool LineStartDirectedEdge::accept(const string & text, size_t index, Matcher & matcher, State& state) const
	{
		return index == string::npos || text[index] == '\n';
	}

	LineEndDirectedEdge::LineEndDirectedEdge(size_t id)
		:DirectedEdge(id)
	{
	}

	DirectedEdgeType LineEndDirectedEdge::get_type() const
	{
		return LINE_END_DIRECTEDEDGE;
	}

	bool LineEndDirectedEdge::accept(const string & text, size_t index, Matcher & matcher, State& state) const
	{
		return index == text.size()-1 || text[index+1] == '\n';
	}

	Matcher::Matcher(string text,size_t cursor,size_t group_size):text(text),cursor(cursor),groups(group_size)
	{
	}

	CountDirectedEdge::CountDirectedEdge(size_t id)
		:DirectedEdge(id)
	{
	}

	DirectedEdgeType CountDirectedEdge::get_type() const
	{
		return COUNT_DIRECTEDEDGE;
	}

	bool CountDirectedEdge::accept(const string & text, size_t index, Matcher & matcher, State& state) const
	{
		return false;
	}

	size_t Matcher::current_cursor() const
	{
		return cursor;
	}


	void Matcher::next()
	{
		cursor++;
	}

	void Matcher::back()
	{
		cursor--;
	}

	RepeatDirectedge::RepeatDirectedge(size_t id, size_t s_id, size_t e_id)
		:DirectedEdge(id,s_id,e_id)
	{
	}

	DirectedEdgeType RepeatDirectedge::get_type() const
	{
		return REPEAT_DIRECTEDEDGE;
	}

	bool RepeatDirectedge::accept(const string & text, size_t index, Matcher & matcher, State& state) const
	{
		return false;
	}

	GroupReferenceDirectedge::GroupReferenceDirectedge(size_t id, size_t group_id, size_t s_id, size_t e_id) 
		:DirectedEdge(id, s_id, e_id),reference_id(group_id)
	{
	}

	DirectedEdgeType GroupReferenceDirectedge::get_type() const
	{
		return GROUP_REFERENCE_DIRECTEDGE;
	}

	bool GroupReferenceDirectedge::accept(const string & text, size_t index, Matcher & matcher, State& state) const
	{
		pair<size_t, size_t> reference_group = matcher.get_groups_node(reference_id);
		bool result = false;
		for(State::iterator st_b = state.begin(),st_e = state.end();st_b != st_e && (!result);st_b++)
		{
			result = true;
			TrackRecode &track_recode = (*st_b).second;
			size_t length = track_recode[reference_group.second] - track_recode[reference_group.first];
			string group_str = text.substr(track_recode[reference_group.first]+1, length);
			for (size_t i = 0; i < length; i++)
				if (group_str[i] != text[index + i])
				{
					result = false;
					break;
				}
			//more the cursor
			if (result)
			{
				matcher.cursor += length - 1;
				return true;
			}
		}
		return false;
	}

}
