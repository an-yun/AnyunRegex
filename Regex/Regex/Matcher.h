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
		static NFAMatcher match(const string &text, const NFA &nfa, size_t offset = 0);
		bool find() override;
		bool find(size_t offset) override;

		string group(size_t index = 0) const override;
		string group(string group_name) const override;

		size_t group_count() const override;

	protected:
		virtual pair<size_t, size_t> get_groups_node(size_t group_id) override;

	private:
		NFA nfa;

		bool is_find;
		size_t text_length;

		NFAMatcher(const string &text, const NFA &nfa, size_t offset);
	};
}
#endif // !MATCHER_H

