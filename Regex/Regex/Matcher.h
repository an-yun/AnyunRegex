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
		friend class GroupReferenceDirectedge;
	public:
		static bool search(const string &text, NFAMatcher& search_result,const string &pattern, size_t offset = 0);
		static bool search(const string &text, NFAMatcher& search_result, const NFA &nfa, size_t offset = 0);
		static bool match(const string&text, NFAMatcher& match_result, const string&pattern,size_t offset=0);
		static bool match(const string&text, NFAMatcher& match_result, const NFA &nfa, size_t offset = 0);
		static bool match(const string&text, NFAMatcher& match_result, const string&pattern, size_t start,size_t end);
		static bool match(const string&text, NFAMatcher& match_result, const NFA &nfa, size_t start, size_t end);

		NFAMatcher();
		void set_content(const string&text, const string &pattern) override;
		void set_content(const string&text, const NFA &nfa);
		void set_text(const string &text) override;
		void set_pattern(const string &pattern) override;

		bool search() override;
		bool search(size_t offset) override;
		bool match() override;
		bool match(size_t start, size_t end) override;


		string group(size_t index = 0) const override;
		string group(string group_name) const override;
		size_t group_index(string group_name) const override;
		size_t group_count() const override;

	protected:
		virtual pair<size_t, size_t> get_groups_node(size_t group_id) override;

	private:
		NFA nfa;

		bool is_find;
		size_t text_length;
		bool has_set;

		void set_nfa(NFA nfa);
		//NFAMatcher(const string &text, const NFA &nfa, size_t offset=0);
	};
}
#endif // !MATCHER_H

