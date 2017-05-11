#ifndef NFA_H
#define NFA_H

#include <algorithm>
#include <string>
#include <list>
#include <set>
#include <utility>
#include <map>
#include <queue>
#include <stack>
#include <iterator>
#include <memory>

namespace anyun_regex
{
	using std::string;
	using std::list;
	using std::queue;
	using std::map;
	using std::pair;
	using std::set;
	using std::stack;
	using std::tuple;
	using std::back_inserter;
	using std::copy;
	using std::shared_ptr;

	// reach_node->(str_point,repeat_times)
	typedef map<size_t, pair<size_t, size_t>> TrackRecord;
	// current_node,track_record
	typedef pair<size_t, TrackRecord> OneState;
	typedef list<OneState> State;
	//we can use the stack to implement the lazy match
	typedef tuple<size_t, size_t, TrackRecord> OneSaveState;
	// node_id ,next_edge_index,trackrecode
	typedef stack<OneSaveState> SaveState;

	class DirectedGraph;
	typedef shared_ptr<DirectedGraph> DirectedGraphPoint;
	enum RegexParseCode;
	class Matcher;
	class NFA
	{
		friend class NFAMatcher;
	public:
		//explicit NFA(const char *pattern = "");
		explicit NFA(const string & pattern);
		explicit NFA();
		explicit NFA(DirectedGraphPoint digraph);
		~NFA();
		//recompline another pattern,success return true else false
		bool compile(const string &pattern);
		void set_digraph(DirectedGraphPoint diagraph);
		DirectedGraphPoint get_diagraph();
		RegexParseCode get_compile_result_code() const;
		string get_compile_message() const;
		string get_pattern() const;

		size_t group_size() const;
		size_t node_size() const;
		size_t edge_size() const;


	private:
		DirectedGraphPoint digraph;

		//the new disign for update
		void get_next_state(SaveState & state, const string &text, Matcher &matcher) const;

		//update the group node
		size_t update_group_node_record(TrackRecord& record, Matcher &matcher) const;
	};

}

#endif // !NFA