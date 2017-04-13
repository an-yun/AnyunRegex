#include "DirectedEdge.h"

namespace anyun_regex
{


	inline bool is_special_char(size_t ch)
	{
		return is_char_in(ch, SINGLE_SPECAIL_CAHRS, SINGLE_SPECAIL_CAHR_SIZE);
	}

	inline bool is_upper_case(size_t ch)
	{
		return ch >= UPPER_A && ch <= UPPER_Z;
	}

	inline bool is_lower_case(size_t ch)
	{
		return ch >= LOWER_A && ch <= LOWER_Z;
	}

	inline bool is_letter(size_t ch)
	{
		return is_lower_case(ch) || is_upper_case(ch);
	}

	inline bool is_num(size_t ch)
	{
		return ch >= ZERO && ch <= NINE;
	}

	inline bool is_alpnum(size_t ch)
	{
		return is_letter(ch) || is_num(ch);
	}

	inline bool is_blank(size_t ch)
	{
		return is_char_in(ch,BLANK_CHARS,sizeof(BLANK_CHARS)/sizeof(char));
	}



	inline bool is_char_in(size_t ch, const char * str, size_t length)
	{
		for (size_t i = 0; i < length; i++)
			if (ch == str[i])return true;
		return false;
	}

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

	size_t SigmaDirectedEdge::accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const
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

	size_t SingleCharDirectedEdge::accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const
	{
		return index < matcher.text.length() && condition->match(text[index]) ? 1 : static_cast<unsigned>(-1);
	}

	DirectedEdge * SingleCharDirectedEdge::copy() const
	{
		return new SingleCharDirectedEdge(*this);
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

	size_t LineStartDirectedEdge::accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const
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

	size_t LineEndDirectedEdge::accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const
	{
		return (index == text.size() || (index < text.size() && text[index] == '\n')) ? 0 : static_cast<unsigned>(-1);
	}

	DirectedEdge * LineEndDirectedEdge::copy() const
	{
		return new LineEndDirectedEdge(*this);
	}

	Matcher::Matcher(string text, size_t cursor, size_t group_size) :text(text), cursor(cursor), groups(group_size)
	{
	}

	CountDirectedEdge::CountDirectedEdge(size_t id)
		: DirectedEdge(id)
	{
	}

	DirectedEdgeType CountDirectedEdge::get_type() const
	{
		return COUNT_DIRECTEDEDGE;
	}

	size_t CountDirectedEdge::accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const
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
		:DirectedEdge(id, s_id, e_id)
	{
	}

	DirectedEdgeType RepeatDirectedge::get_type() const
	{
		return REPEAT_DIRECTEDEDGE;
	}

	size_t RepeatDirectedge::accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const
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

	size_t GroupReferenceDirectedge::accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const
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

	size_t WordBoundaryDirectedEdge::accept(const string & text, size_t index, Matcher & matcher, TrackRecord & track_record) const
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

	size_t ElementDirectedge::accept(const string & text, size_t index, Matcher & matcher, TrackRecord & track_record) const
	{
		return original_edge->accept(text,index,matcher,track_record)==static_cast<size_t>(-1)?0: static_cast<size_t>(-1);
	}

	DirectedEdge * ElementDirectedge::copy() const
	{
		return new ElementDirectedge(*this);
	}

}
