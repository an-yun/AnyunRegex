#ifndef DIRECTED_EDGE_H
#define DIRECTED_EDGE_H
#include<vector>
#include<map>
#include <string>
#include<utility>
#include<memory>
namespace anyun_regex
{
	typedef unsigned size_t;
	using std::vector;
	using std::string;
	using std::map;
	using std::shared_ptr;
	using std::pair;

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
		GROUP_REFERENCE_DIRECTEDGE
	};

	class Matcher
	{
		friend class NFA;
		friend class SingleCharDirectedEdge;
		friend class RepeatCountDirectedNode;
		friend class GroupReferenceDirectedge;
	public:
		virtual bool find() = 0;
		virtual bool find(size_t offset) = 0;

		virtual string group(size_t index = 0) const = 0;
		virtual string group(string group_name) const = 0;
		virtual size_t group_count() const = 0;

	protected:
		string text;
		size_t cursor;
		vector<pair<size_t, size_t>> groups;
		map<string, size_t> name_groups;
		map<size_t, size_t> repeat_node_count;
		virtual size_t current_cursor() const;
		virtual void next() ;
		virtual void back();


		Matcher(string text, size_t cursor = 0,size_t group_size = 1 );
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

		virtual bool accept(const string &text, size_t index, Matcher &matcher) const = 0;

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
		bool accept(const string &text, size_t index, Matcher &matcher) const override;
	};

	class SingleCharDirectedEdge :public DirectedEdge
	{
	public:
		SingleCharDirectedEdge(size_t ch, size_t id, size_t s_id = 0, size_t  e_id = 0);
		SingleCharDirectedEdge(size_t start, size_t end, size_t id, bool complementary = false, size_t s_id = 0, size_t  e_id = 0);
		SingleCharDirectedEdge(ConditionPoint condition, size_t id, size_t s_id = 0, size_t  e_id = 0);

		DirectedEdgeType get_type() const override;
		bool accept(const string &text, size_t index, Matcher &matcher) const override;
	private:
		ConditionPoint condition;
	};

	class LineStartDirectedEdge :public DirectedEdge
	{
	public:
		LineStartDirectedEdge(size_t id);
		DirectedEdgeType get_type() const override;
		bool accept(const string &text, size_t index, Matcher &matcher) const override;
	};

	class LineEndDirectedEdge :public DirectedEdge
	{
	public:
		LineEndDirectedEdge(size_t id);
		DirectedEdgeType get_type() const override;
		bool accept(const string &text, size_t index, Matcher &matcher) const override;
	};

	class CountDirectedEdge :public DirectedEdge
	{
	public:
		CountDirectedEdge(size_t id);
		DirectedEdgeType get_type() const override;
		bool accept(const string &text, size_t index, Matcher &matcher) const override;
	private:

	};

	class RepeatDirectedge :public DirectedEdge
	{
	public:
		RepeatDirectedge(size_t id, size_t s_id = 0, size_t e_id = 0);

		DirectedEdgeType get_type() const override;
		bool accept(const string &text, size_t index, Matcher &matcher) const override;
	};

	class GroupReferenceDirectedge :public DirectedEdge
	{
	public:
		GroupReferenceDirectedge(size_t id, size_t group_id, size_t s_id = 0, size_t e_id = 0);

		DirectedEdgeType get_type() const override;
		bool accept(const string &text, size_t index, Matcher &matcher) const override;
	private:
		size_t reference_id;
	};
}

#endif
