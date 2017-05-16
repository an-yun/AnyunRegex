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


	class Matcher
	{
		friend class NFA;
		friend class SingleCharDirectedEdge;
		friend class RepeatCountDirectedNode;
		friend class GroupReferenceDirectedge;
	public:
		virtual ~Matcher()
		{
		}
		virtual bool match() = 0;
		virtual bool match(size_t start, size_t end) = 0;
		virtual bool search() = 0;
		virtual bool search(size_t offset) = 0;
		virtual pair<size_t, size_t> get_group(size_t group_index = 0);

		virtual size_t start(size_t index = 0) const = 0;
		virtual size_t end(size_t index = 0) const = 0;
		virtual string group(size_t index = 0) const = 0;
		virtual string group(string group_name) const = 0;
		virtual size_t group_index(string group_name)const = 0;
		virtual size_t group_count() const = 0;

		virtual void set_cursor(size_t cursor);
		virtual void set_content(const string &text, const string &pattern);
		virtual void set_text(const string &text);
		virtual void set_pattern(const string&pattern) = 0;
		virtual size_t current_cursor() const;
		virtual void next();
		virtual void back();

	protected:
		string text;
		size_t cursor;
		vector<pair<size_t, size_t>> groups;
		void set_groups(size_t groups_size);

		virtual pair<size_t, size_t> get_groups_node(size_t group_id) = 0;

	private:

	};

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
		void set_pattern(DirectedGraphPoint digraph);

		bool search() override;
		bool search(size_t offset) override;
		bool match() override;
		bool match(size_t start, size_t end) override;

		size_t start(size_t index = 0) const override;
		size_t end(size_t index = 0) const override;
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

		void set_nfa(NFA nfa);
		//NFAMatcher(const string &text, const NFA &nfa, size_t offset=0);
	};
	typedef shared_ptr<NFAMatcher> NFAMatcherPoint;
}
#endif // !MATCHER_H

