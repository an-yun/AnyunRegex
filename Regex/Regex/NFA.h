#ifndef NFA_H
#define NFA_H

#include <algorithm>
#include <string>
#include <list>
#include <set>
#include <queue>
#include <iterator>
#include "DirectedGraph.h"

namespace anyun_regex
{
	using std::string;
	using std::list;
	using std::queue;
	using std::set;
	using std::back_inserter;
	using std::copy;
	class NFA
	{
	public:
		typedef size_t postoin_type;

		NFA();
		NFA(const char *pattern);
		NFA(const string & pattern);
		~NFA();

		bool find();
		void match(const char * text,postoin_type offset =0);
		char* get_match(char *match);
		size_t get_match_start();
		size_t get_match_end();
		const char *get_pattern();


	private:
		DirectedGraph digraph;
		list<size_t> start_state;
		const char* text;
		size_t match_start;
		size_t match_end;
		postoin_type offset;
		bool start_is_final;
		bool is_find;

		void get_sigma_closure(list<size_t> &source,bool &is_find);
		void get_next_state(list<size_t> & state, char ch,bool &is_find);
	};

}

#endif // !NFA