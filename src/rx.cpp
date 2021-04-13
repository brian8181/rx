#include <iostream>
#include <string>
#include <regex>
#include <getopt.h>
#include "rx.hpp"

using namespace std;

static struct option long_options[] =
{
		{"verbose", no_argument, 0, 'v'},
		{"help", no_argument, 0, 'h'},
		{"ignore_case", no_argument, 0, 'i'},
		{"single", no_argument, 0, 's'}
};

void print_help()
{
	cout << "\n"
		 << FMT_BOLD << "rx" << FMT_RESET << " "
		 << FMT_UNDERLINE << "PATTERN" << FMT_RESET << " "
		 << FMT_UNDERLINE << "INPUT" << FMT_RESET << "\n\n";
}

void print_match_header(const string &pattern, const string &src)
{
	cout << FMT_FG_RED << "pattern: " << FMT_RESET
		 << "\"" << FMT_FG_YELLOW << pattern << FMT_RESET << "\""
		 << " -> "
		 << FMT_FG_RED << "input: " << FMT_RESET
		 << "\"" << FMT_FG_YELLOW << src << FMT_RESET << "\""
		 << "\n\n";
}

int parse_options(int argc, char *argv[])
{
	int opt = 0;
	int option_index = 0;
	bool verbose_flag = false;
	bool ignore_case_flag = false;
	bool single_flag = false;

	optind = 0;
	while ((opt = getopt_long(argc, argv, "hvis", long_options, &option_index)) != -1)
	{
		switch (opt)
		{
		case 'h':
			print_help();
			return EXIT_SUCCESS;
		case 'v':
			verbose_flag = true;
			break;
		case 'i':
			ignore_case_flag = true;
			break;
		case 's':
			single_flag = true;
			break;
		default: // unknown option before args
			{
				cerr << "Unexpected option, -h for help\n";
				return EXIT_FAILURE;
			}
		}
	}

	if (argc <= 2) // not correct number of args
	{
		cerr << "Expected argument after options, -h for help\n";
		return EXIT_FAILURE;
	}
	
	if (verbose_flag)
	{
		print_help();
	}

	int current_idx = optind + 1;
	string src;
	string exp(argv[optind]);
	
	if (verbose_flag)
	{
		print_help();
	}
	
	for (int i = current_idx; i < argc; ++i)
	{
		src = argv[i];
		// print command inputs
		print_match_header(exp, src);

		volatile int idx = 0;
		string bash_str = src;
		regex::flag_type regex_opt = regex::ECMAScript|regex::grep|regex::extended;
		regex_opt = ignore_case_flag ? regex_opt|regex::icase : regex_opt;
		regex src_epx(exp, regex_opt);
		auto begin = sregex_iterator(src.begin(), src.end(), src_epx);
		auto end = sregex_iterator();

		for (sregex_iterator iter = begin; iter != end; ++iter)
		{
			string CURRENT_FG_COLOR( idx % 2 ? FMT_FG_CYAN + FMT_UNDERLINE : FMT_FG_GREEN + FMT_UNDERLINE );
			smatch match = *iter;
			int pos = match.position() + (idx * (CURRENT_FG_COLOR.length() + FMT_RESET.length()));
			int len = match.length();

			if ( single_flag && (iter != begin || pos != 0 || src.length() != (size_t)len) )
			{
				begin = end;
				break;
			}
		
			// set bash green start postion
			bash_str.insert(pos, CURRENT_FG_COLOR);

			// reset bash color position
			pos = pos + CURRENT_FG_COLOR.length() + len;
			bash_str.insert(pos, FMT_RESET);

			cout << idx << ": " << src.substr(match.position(), match.length()) << endl;
			++idx;
		}

		cout << "\nFound " << std::distance(begin, end) << " matches:\n";
		cout << bash_str << "\n\n";
	}
	
	// print single match message
	if (single_flag)
	{
	    cout << FMT_FG_YELLOW << "Single Match Mode" << FMT_RESET << endl;
	}

	return EXIT_SUCCESS;
}
