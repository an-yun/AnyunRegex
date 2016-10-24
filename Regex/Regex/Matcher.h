#ifndef MATCHER
#define MATCHER
#include <vector>
#include <map>
#include <string>
#include "NFA.h"

namespace anyun_regex {
	using std::vector;
	using std::map;
	using std::string;

	class Matcher
	{
		friend class SingleCharDirectedEdge;
	public:
		virtual bool find() =0;
		virtual bool find(size_t offset)= 0;

		virtual string group(size_t index = 0) const = 0;
		virtual string group(string group_name) const = 0;
		virtual size_t group_count() const = 0;

	protected:
		string text;
		size_t cursor;
		virtual size_t peek() = 0;
		virtual size_t next() = 0;
		virtual size_t back() = 0;

		virtual size_t get_edge_pass_count(size_t edge_id) const = 0 ;
		virtual size_t get_node_pass_count(size_t node_id) const = 0;
		virtual void set_edge_pass_count(size_t edge_id,size_t count) = 0;
		virtual void set_node_pass_count(size_t node_id,size_t count) = 0;

		Matcher(string text, size_t cursor = 0);
	private:

	};

	class NFAMatcher :public Matcher
	{
		friend class NFA;
	public:
		bool find() override;
		bool find(size_t offset) override;

		string group(size_t index = 0) const override;
		string group(string group_name) const override;

		size_t group_count() const override;

	protected:

		size_t peek() override;
		size_t next() override;
		size_t back() override;

		size_t get_edge_pass_count(size_t edge_id) const override ;
		size_t get_node_pass_count(size_t node_id) const override;
		void set_edge_pass_count(size_t edge_id, size_t count) override;
		void set_node_pass_count(size_t node_id, size_t count) override;
	private:
		NFA nfa;
		vector<string> groups;
		map<string, size_t> name_groups;
		vector<size_t> edges_count;
		vector<size_t> nodes_count;
	};
}
#endif // !MATCHER

