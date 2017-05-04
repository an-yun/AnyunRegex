#ifndef DIRECTED_EDGE_H
#define DIRECTED_EDGE_H
#include<vector>
#include<map>
#include <string>
#include<utility>
#include<memory>
#include <algorithm>
#include <list>
#include <utility>
#include <iterator>
#include <stack>
#include <tuple>

namespace anyun_regex
{
	using std::string;
	using std::list;
	using std::map;
	using std::pair;
	using std::back_inserter;
	using std::copy;
	using std::vector;
	using std::shared_ptr;
	using std::stack;
	using std::tuple;
	// reach_node->(str_point,repeat_times)
	typedef map<size_t, pair<size_t, size_t>> TrackRecord;
	// current_node,track_record
	typedef pair<size_t, TrackRecord> OneState;
	typedef list<OneState> State;
	//we can use the stack to implement the lazy match
	typedef tuple<size_t, size_t, TrackRecord> OneSaveState;
	// node_id ,next_edge_index,trackrecode
	typedef stack<OneSaveState> SaveState;

	const size_t ZERO = '0';
	const size_t NINE = '9';
	const size_t LOWER_A = 'a';
	const size_t LOWER_Z = 'z';
	const size_t UPPER_A = 'A';
	const size_t UPPER_Z = 'Z';
	const char BLANK_CHARS[] = " \n\t\r\f";
	const char SINGLE_SPECAIL_CAHRS[] = { '\0','(' ,')','[',']','{','}','|','*','+','?' ,'\\','^','$' };
	const char META_CHARS[] = { 'a','w','W','d','D','s','S'};
	static map<size_t, const char *> meta_string_map
	{
		{'a',"[a-zA-Z]"},
		{'w',"[a-zA-Z0-9_]" },
		{'W',"[^a-zA-Z0-9_]" },
		{'d',"[0-9]"},
		{'D',"[^0-9]" },
		{'s',"[\n\t\r\f ]" },
		{'S',"[^\n\t\r\f ]" },
	};
	const size_t SINGLE_SPECAIL_CAHR_SIZE = sizeof(SINGLE_SPECAIL_CAHRS) / sizeof(char);

	static bool is_char_in(size_t ch, const char * str, size_t length)
	{
		for (size_t i = 0; i < length; i++)
			if (ch == str[i])return true;
		return false;
	}

	static bool is_special_char(size_t ch)
	{
		return is_char_in(ch, SINGLE_SPECAIL_CAHRS, SINGLE_SPECAIL_CAHR_SIZE);
	}

	static bool is_meta_char(size_t ch)
	{
		return is_char_in(ch, META_CHARS, sizeof(META_CHARS) / sizeof(char));
	}

	static bool is_upper_case(size_t ch)
	{
		return ch >= UPPER_A && ch <= UPPER_Z;
	}

	static bool is_lower_case(size_t ch)
	{
		return ch >= LOWER_A && ch <= LOWER_Z;
	}

	static bool is_letter(size_t ch)
	{
		return is_lower_case(ch) || is_upper_case(ch);
	}

	static bool is_num(size_t ch)
	{
		return ch >= ZERO && ch <= NINE;
	}

	static bool is_alpnum(size_t ch)
	{
		return is_letter(ch) || is_num(ch);
	}

	static bool is_blank(size_t ch)
	{
		return is_char_in(ch, BLANK_CHARS, sizeof(BLANK_CHARS) / sizeof(char));
	}




	class Condition
	{
	public:
		virtual bool match(size_t ch) const = 0;
		virtual ~Condition();						//the virtual destrutor
	};

	typedef shared_ptr<Condition> ConditionPoint;

	//match any char
	class DotCondition :public Condition
	{
	public:
		bool match(size_t ch) const override;
	};

	class CharCondition :public Condition
	{
	public:
		explicit CharCondition(size_t ch);
		bool match(size_t ch)  const override;
	private:
		size_t ch;
	};

	class RangeCondition :public Condition
	{
	public:
		RangeCondition(size_t from, size_t to);
		bool match(size_t ch) const override;
	private:
		size_t from;
		size_t to;
	};

	class ComplmentCondtion :public Condition
	{
	public:
		explicit ComplmentCondtion(ConditionPoint condition_ptr);
		bool match(size_t ch) const override;
	private:
		ConditionPoint original_condition;
	};

	class OrCondtion :public Condition
	{
	public:
		OrCondtion(ConditionPoint lhs, ConditionPoint rhs);
		OrCondtion(vector<ConditionPoint> conditions);
		bool match(size_t ch) const override;
	private:
		vector<ConditionPoint> conditions;
	};

	enum DirectedEdgeType
	{
		SIGMA_DIRECTEDEDGE,
		SINGLE_CHAR_DIRECTEDEDGE,
		LINE_START_DIRECTEDEDGE,
		LINE_END_DIRECTEDEDGE,
		REPEAT_DIRECTEDEDGE,
		COUNT_DIRECTEDEDGE,
		GROUP_REFERENCE_DIRECTEDGE,
		WORD_BOUNDARY_DIRECTEDEDGE,
		ELEMENT_DIRECTEDGE,
		PLA_ZERO_ASSERTION_DIRECTEDGE
	};

	class DirectedGraph;
	typedef shared_ptr<DirectedGraph> DirectedGraphPoint;
	class NFAMatcher;
	typedef shared_ptr<NFAMatcher> NFAMatcherPoint;
	class Matcher
	{
		friend class NFA;
		friend class SingleCharDirectedEdge;
		friend class RepeatCountDirectedNode;
		friend class GroupReferenceDirectedge;
	public:
		virtual ~Matcher()
		{
		}
		virtual bool match() =0;
		virtual bool match(size_t start, size_t end) = 0;
		virtual bool search() = 0;
		virtual bool search(size_t offset) = 0;
		virtual pair<size_t, size_t> get_group(size_t group_index = 0);

		virtual string group(size_t index = 0) const = 0;
		virtual string group(string group_name) const = 0;
		virtual size_t group_index(string group_name)const = 0;
		virtual size_t group_count() const = 0;

		virtual void set_cursor(size_t cursor);

	protected:
		string text;
		size_t cursor;
		vector<pair<size_t, size_t>> groups;
		void set_groups(size_t groups_size);
		virtual void set_content(const string &text,const string &pattern);
		virtual void set_text(const string &text);
		virtual void set_pattern(const string&pattern) = 0;
		virtual size_t current_cursor() const;
		virtual void next();
		virtual void back();
		virtual pair<size_t, size_t> get_groups_node(size_t group_id) = 0;

	private:

	};

	class DirectedEdge
	{
	public:

		DirectedEdge(size_t id, size_t s_id = 0, size_t e_id = 0);
		size_t get_id() const;
		virtual DirectedEdgeType get_type() const = 0;

		virtual void set_start_node(size_t node_id);
		virtual void set_end_node(size_t node_id);
		virtual size_t get_start_node_id() const;
		virtual size_t get_end_node_id() const;

		virtual size_t accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const = 0;
		virtual DirectedEdge* copy() const = 0;
		virtual ~DirectedEdge();	//the virtual destructor
	private:
		size_t id;
		size_t start_id;
		size_t end_id;
	};

	typedef shared_ptr<DirectedEdge> DirectedEdgePoint;

	class SigmaDirectedEdge :public DirectedEdge
	{
	public:
		SigmaDirectedEdge(size_t id, size_t s_id = 0, size_t e_id = 0);

		DirectedEdgeType get_type() const override;
		size_t accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const override;
		DirectedEdge* copy() const override;
	};

	class SingleCharDirectedEdge :public DirectedEdge
	{
	public:
		SingleCharDirectedEdge(size_t ch, size_t id, size_t s_id = 0, size_t  e_id = 0);
		SingleCharDirectedEdge(size_t start, size_t end, size_t id, bool complementary = false, size_t s_id = 0, size_t  e_id = 0);
		SingleCharDirectedEdge(ConditionPoint condition, size_t id, size_t s_id = 0, size_t  e_id = 0);

		DirectedEdgeType get_type() const override;
		size_t accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const override;
		DirectedEdge* copy() const override;
	private:
		ConditionPoint condition;
	};

	class LineStartDirectedEdge :public DirectedEdge
	{
	public:
		LineStartDirectedEdge(size_t id);
		DirectedEdgeType get_type() const override;
		size_t accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const override;
		DirectedEdge* copy() const override;
	};

	class LineEndDirectedEdge :public DirectedEdge
	{
	public:
		LineEndDirectedEdge(size_t id);
		DirectedEdgeType get_type() const override;
		size_t accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const override;
		DirectedEdge* copy() const override;
	};

	class WordBoundaryDirectedEdge :public DirectedEdge
	{
	public:
		WordBoundaryDirectedEdge(size_t id);
		DirectedEdgeType get_type() const override;
		size_t accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const override;
		DirectedEdge* copy() const override;
	};

	class CountDirectedEdge :public DirectedEdge
	{
	public:
		CountDirectedEdge(size_t id);
		DirectedEdgeType get_type() const override;
		size_t accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const override;
		DirectedEdge* copy() const override;
	private:

	};

	class RepeatDirectedge :public DirectedEdge
	{
	public:
		RepeatDirectedge(size_t id, size_t s_id = 0, size_t e_id = 0);

		DirectedEdgeType get_type() const override;
		size_t accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const override;
		DirectedEdge* copy() const override;
	};

	class GroupReferenceDirectedge :public DirectedEdge
	{
	public:
		GroupReferenceDirectedge(size_t id, size_t group_id, size_t s_id = 0, size_t e_id = 0);

		DirectedEdgeType get_type() const override;
		size_t accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const override;
		DirectedEdge* copy() const override;
	private:
		size_t reference_id;
	};

	class ElementDirectedge :public DirectedEdge
	{
	public:
		ElementDirectedge(size_t id, DirectedEdgePoint original_edge);

		DirectedEdgeType get_type() const override;
		size_t accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const override;
		DirectedEdge* copy() const override;
	private:
		DirectedEdgePoint original_edge;
	};

	/*
	 * 
	 *Positive Lookahead Zero-Length Assertions 零宽度正预测先行断言
	 *(?=exp)
	 *对应的边
	 */
	class PLAZeroAssertionDirectedge :public DirectedEdge
	{
	public:
		PLAZeroAssertionDirectedge(size_t id, const string &pattern);

		DirectedEdgeType get_type() const override;
		size_t accept(const string& text, size_t index, Matcher& matcher, TrackRecord& track_record) const override;
		DirectedEdge* copy() const override;
	private:
		NFAMatcherPoint matcher;
	};
}

#endif
