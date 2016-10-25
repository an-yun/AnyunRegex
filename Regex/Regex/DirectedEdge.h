#ifndef DIRECTED_EDGE_H
#define DIRECTED_EDGE_H
#include<vector>
#include<string>
#include<memory>
namespace anyun_regex
{
	using std::vector;
	using std::string;
	using std::shared_ptr;
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

	class CharCondition:public Condition
	{
	public:
		CharCondition(size_t ch);
		bool match(size_t ch)  const override;
	private:
		size_t ch;
	};

	class RangeCondition :public Condition
	{
	public :
		RangeCondition(size_t from, size_t to);
		bool match(size_t ch) const override;
	private:
		size_t from;
		size_t to;
	};

	class ComplmentCondtion :public Condition
	{
	public:
		ComplmentCondtion(ConditionPoint condition_ptr);
		bool match(size_t ch) const override;
	private:
		ConditionPoint original_condition;
	};

	class OrCondtion :public Condition
	{
	public:
		OrCondtion(ConditionPoint lhs,ConditionPoint rhs);
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
		REPEAT_COUNT_DIRECTEDEDGE
	};

	class Matcher
	{
		friend class SingleCharDirectedEdge;
		friend class RepeatCountDirectedEdge;
	public:
		virtual bool find() = 0;
		virtual bool find(size_t offset) = 0;

		virtual string group(size_t index = 0) const = 0;
		virtual string group(string group_name) const = 0;
		virtual size_t group_count() const = 0;

	protected:
		string text;
		size_t cursor;
		virtual size_t peek() = 0;
		virtual size_t next() = 0;
		virtual size_t back() = 0;

		virtual size_t get_edge_pass_count(size_t edge_id) const = 0;
		virtual size_t get_node_pass_count(size_t node_id) const = 0;
		virtual void add_edge_pass_count(size_t edge_id) = 0;
		virtual void add_node_pass_count(size_t node_id) = 0;

		Matcher(string text, size_t cursor = 0);
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

		virtual bool accept(const string &text, size_t index, Matcher &matcher) const = 0 ;

		virtual ~DirectedEdge();	//the virtual destructor
	private:
		size_t id;
		size_t start_id;
		size_t end_id;
	};

	typedef shared_ptr<DirectedEdge> DirectedEdgePoint;

	class SigmaDirectedEdge:public DirectedEdge
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

	class RepeatCountDirectedEdge :public DirectedEdge
	{
	public:
		RepeatCountDirectedEdge(size_t id, size_t count_edge_id =0, size_t left =0,size_t right = UINT_MAX);
		DirectedEdgeType get_type() const override;
		bool accept(const string &text, size_t index, Matcher &matcher) const override;
	private:
		size_t count_edge_id;
		size_t left;
		size_t right;
	};
}

#endif
