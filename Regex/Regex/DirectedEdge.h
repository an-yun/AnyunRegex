#ifndef DIRECTED_EDGE
#define DIRECTED_EDGE

namespace anyun_regex
{
	class TransactionCondition
	{
	private:
		char ch;
		int start_index;
		int end_index;
		bool is_char;
	public:
		TransactionCondition(int start, int end);
		TransactionCondition(char ch);
		bool match(int ch);
	};
	class DirectedNode;
	class DirectedEdge
	{
	public:
		DirectedEdge();
		DirectedEdge(const char *);
		DirectedEdge(char);
		DirectedEdge(char ch,DirectedNode *s,DirectedNode *e);
		~DirectedEdge();
		
		void set_start_node(DirectedNode *node);
		void set_end_node(DirectedNode *node);


	private:
		DirectedNode *start;
		DirectedNode *end;
		TransactionCondition *condition;
	};
}

#endif
