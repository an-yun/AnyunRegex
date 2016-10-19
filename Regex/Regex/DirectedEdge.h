#ifndef DIRECTED_EDGE_H
#define DIRECTED_EDGE_H
#include<vector>


namespace anyun_regex
{
	using std::vector;
	class TransactionCondition
	{
		friend class DirectedEdge;
	private:
		union {
			char ch;
			struct
			{
				int start_index;
				int end_index;
			}range;
		}condition;
		/*
		the flag:
		-1 represent sigma conditon
		0 represent single char
		1 represent a range
		2 represent can accept any char
		*/
		int flag;
	public:
		TransactionCondition(char ch);
		TransactionCondition(bool is_dot = false);
		TransactionCondition(int start, int end);
		bool match(int ch);
	};
	class DirectedEdge
	{

	public:
		DirectedEdge(size_t id,bool is_dot = false);
		DirectedEdge(size_t s_id, size_t  e_id, size_t id);
		DirectedEdge(const char *str, size_t id);
		DirectedEdge(char ch,size_t id);
		DirectedEdge(char ch,size_t s_id, size_t  e_id,size_t id);
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
		TransactionCondition condition;

	};
}

#endif
