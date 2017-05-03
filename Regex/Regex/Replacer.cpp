#include "Replacer.h"
namespace  anyun_regex
{
	CommonReplacer::CommonReplacer(const string & repalce_str):new_string(repalce_str)
	{
	}
	string anyun_regex::CommonReplacer::replace_match(const Matcher & matcher) const
	{
		return new_string;
	}
	string replace(const char * pattern, const string & new_string, const string & text, size_t offset)
	{
		return replace(NFA(pattern), CommonReplacer(new_string), text, offset);
	}

	string replace(const char * pattern, const char * new_string, const string & text, size_t offset)
	{
		return replace(NFA(pattern), CommonReplacer(new_string), text, offset);
	}

	string replace(const string & pattern, const string & new_string, const string & text, size_t offset)
	{
		return replace(NFA(pattern),CommonReplacer(new_string),text,offset);
	}
	string replace(const string & pattern, const Replacer & repalcer, const string & text, size_t offset)
	{
		return replace(NFA(pattern), repalcer, text, offset);
	}
	string replace(const NFA & pattern, const string & new_string, const string & text, size_t offset)
	{
		return replace(pattern, CommonReplacer(new_string), text, offset);
	}
	string replace(const NFA & pattern, const Replacer & repalcer, const string & text, size_t offset)
	{
		NFAMatcher matcher;
		matcher.set_content(text, pattern);
		matcher.set_cursor(offset);
		string result_str;
		size_t position = 0;
		while (matcher.search())
		{
			pair<size_t, size_t> total_group = matcher.get_group();
			result_str += text.substr(position, total_group.first - position);
			result_str += repalcer.replace_match(matcher);
			position = total_group.second;
		}
		size_t text_length = text.length();
		if (position < text_length)
			result_str += text.substr(position, text_length - position);
		return result_str;
	}
}
