#pragma once
#include "DirectedGraph.h"
#include "Matcher.h"

namespace  anyun_regex
{
	class Replacer
	{
	public:
		virtual string replace_match(const Matcher &matcher) const = 0;
	};

	//the common replacer object,no replace it
	class CommonReplacer:public Replacer
	{
	public:
		explicit CommonReplacer(const string &repalce_str);
		string replace_match(const Matcher &matcher) const override;
	private:
		string new_string;
	};
	string replace(const char * pattern, const string & new_string, const string & text, size_t offset = 0);
	string replace(const char * pattern, const char * new_string, const string & text, size_t offset = 0);
	string replace(const string &pattern, const string &new_string, const string &text, size_t offset = 0);
	string replace(const string &pattern, const Replacer &repalcer, const string &text, size_t offset = 0);
	string replace(const NFA &pattern, const string &new_string, const string &text, size_t offset = 0);
	string replace(const NFA &pattern, const Replacer &repalcer, const string &text, size_t offset = 0);
}

