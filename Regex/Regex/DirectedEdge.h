#ifndef DIRECTED_EDGE_H
#define DIRECTED_EDGE_H
#include<vector>
#include<memory>

namespace anyun_regex
{
	using std::vector;
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

	class SingleCharCondition:public Condition
	{
	public:
		SingleCharCondition(size_t ch);
		bool match(size_t ch) const override;
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


	class DirectedEdge
	{
	public:
		//the default sigma edge
		DirectedEdge(size_t id);
		DirectedEdge(char ch, size_t id,size_t s_id =0, size_t  e_id=0);
		DirectedEdge(char start, char end , size_t id,  bool complementary = false, size_t s_id = 0, size_t  e_id = 0);
		DirectedEdge(ConditionPoint condition, size_t id, size_t s_id = 0, size_t  e_id = 0);
		~DirectedEdge();
		
		void set_start_node(size_t node_id);
		void set_end_node(size_t node_id);
		size_t get_start_node_id();
		size_t get_end_node_id();
		bool is_sigma_edge();
		bool accept(char ch);
		size_t get_id();

	private:
		size_t id;
		size_t start_id;
		size_t end_id;
		bool is_sigma;
		ConditionPoint condition;

	};
}

#endif
