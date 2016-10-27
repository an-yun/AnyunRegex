#ifndef MATCHER_H
#define MATCHER_H
#include <vector>
#include <map>
#include <utility>
#include <string>
#include "NFA.h"

namespace anyun_regex {
	using std::vector;
	using std::map;
	using std::string;
	using std::pair;

	class NFAMatcher :public Matcher
	{
		friend class NFA;
	public:
		static NFAMatcher match(const string &text, const NFA &nfa, size_t offset = 0);
		bool find() override;
		bool find(size_t offset) override;

		string group(size_t index = 0) const override;
		string group(string group_name) const override;

		size_t group_count() const override;

	protected:

		size_t get_edge_pass_count(size_t edge_id) const override ;
		size_t get_node_pass_count(size_t node_id) const override;
		void add_edge_pass_count(size_t edge_id) override;
		void add_node_pass_count(size_t node_id) override;
	private:
		NFA nfa;

		vector<size_t> edges_count;
		vector<size_t> nodes_count;
		set<size_t> start_state;
		bool start_is_final;
		bool is_find;
		size_t text_length;

		NFAMatcher(const string &text, const NFA &nfa, size_t offset);
	};
}
#endif // !MATCHER_H

