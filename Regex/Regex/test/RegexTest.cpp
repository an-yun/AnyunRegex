#include "RegexTest.h"

namespace anyun_regex
{
	LibraryRegex::LibraryRegex()
	{
	}


	int test_exameple()
	{
		std::string s = "Some people, when confronted with a problem, think "
			"\"I know, I'll use regular expressions.\" "
			"Now they have two problems.";

		std::regex self_regex("REGULAR EXPRESSIONS",
			std::regex_constants::ECMAScript | std::regex_constants::icase);
		if (std::regex_search(s, self_regex)) {
			std::cout << "Text contains the phrase 'regular expressions'\n";
		}

		std::regex word_regex("(\\S+)");
		auto words_begin =
			std::sregex_iterator(s.begin(), s.end(), word_regex);
		auto words_end = std::sregex_iterator();

		std::cout << "Found "
			<< std::distance(words_begin, words_end)
			<< " words\n";

		const int N = 6;
		std::cout << "Words longer than " << N << " characters:\n";
		for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
			std::smatch match = *i;
			std::string match_str = match.str();
			if (match_str.size() > N) {
				std::cout << "  " << match_str << '\n';
			}
		}

		std::regex long_word_regex("(\\w{7,})");
		std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
		std::cout << new_s << '\n';
		return 0;
	}

	int test_files()
	{
		string parent_path = "../testfiles/";
		string test_files[] = { "and_test_case.txt" ,"or_test_case.txt" ,"dot_test_case.txt" ,"question_mark_test_case.txt" };
		ifstream input;
		for (size_t i = 0; i < sizeof(test_files) / sizeof(string); i++)
		{
			input.open(parent_path+test_files[i]);
			if (input.bad())
			{
				std::cout << parent_path +test_files[i] << " file error!" << std::endl;
				return 0;
			}
			cout << "-------------------------------------" << test_files[i] << "-----------------------------------------------------" << endl;
			size_t case_num;
			string str;
			while (input >> case_num)
			{
				input >> str;
				NFA nfa(str.substr(1, str.size() - 2));
				cout << "grep " << nfa.get_pattern() << endl;
				string line;
				getline(input, line);
				getline(input, line);
				for (unsigned line_no = 1; line_no <= case_num; getline(input, line)) {
					nfa.match(line.c_str());
					if (nfa.find())
						cout << line << std::endl;
					line_no++;
				}
				cout << endl;
			}
			input.close();
		}
		return 0;
	}
}
