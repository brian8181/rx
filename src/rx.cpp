#include <iostream>
#include <string>
#include <regex>
#include <getopt.h>
#include "main.hpp"
#include "rx.hpp"

using namespace std;

static struct option long_options[] =
	{
		{"verbose", no_argument, 0, 'v'},
		{"help", no_argument, 0, 'h'},
		{"ignore_case", no_argument, 0, 'i'},
		{"single", no_argument, 0, 's'},
		{"pretty", no_argument, 0, 'P'},//default
		{"no-pretty", no_argument, 0, 'p'}
	};

void print_help()
{
	cout << "Usage: "  
		<< FMT_BOLD << "rx" << FMT_RESET << " "
		<< FMT_UNDERLINE << "[OPTION]..." << FMT_RESET << " "
		<< FMT_UNDERLINE << "PATTERN" << FMT_RESET << " "
		<< FMT_UNDERLINE << "INPUT..." << FMT_RESET << endl;
}

void print_match_header(const string &pattern, const string &src)
{
	if(option_flags & PRETTY_PRINT)
	{
		cout << endl 
			<< FMT_FG_RED << ((option_flags & SINGLE_MATCH) ? "Single Match Pattern: " : "Match Pattern: ") << FMT_RESET
			<< "'" << FMT_FG_YELLOW << pattern << FMT_RESET << "'"
			<< " -> "
			<< FMT_FG_RED << "Input: " << FMT_RESET
			<< "'" << FMT_FG_YELLOW << src << FMT_RESET << "'"
			<< endl;
	}
	else
	{
		cout << ((option_flags & SINGLE_MATCH) ? "Single Match Pattern: " : "Match Pattern: ") 
			<< "'" << pattern  << "'"
			<< " -> "
			<< "Input: " 
			<< "'" << src << "'"
			<< endl;
	}
}

int regx_match(int count, char* args[], const unsigned char& options)
{
	string src;
	string exp(args[0]);
	
	// for each input
	for (int input_i = 1; input_i < count; ++input_i)
	{
		src = args[input_i];
		print_match_header(exp, src);
		string bash_stdio = src;
		regex::flag_type regex_opt = regex::ECMAScript|regex::grep|regex::extended;
		regex_opt = (options & IGNORE_CASE) != 0 ? regex_opt|regex::icase : regex_opt;
		regex src_epx(exp, regex_opt);
		
		auto begin = sregex_iterator(src.begin(), src.end(), src_epx);
		auto end = sregex_iterator(); 
		int match_i = 0;
		// for each match
		for (sregex_iterator iter = begin; iter != end; ++iter, ++match_i)
		{
			string CURRENT_FG_COLOR( match_i % EVENS_ONLY ? FMT_FG_CYAN + FMT_UNDERLINE : FMT_FG_GREEN + FMT_UNDERLINE );
			smatch match = *iter;
			int pos = match.position() + match_i * (CURRENT_FG_COLOR.length() + FMT_RESET.length());
			int len = match.length();
			
			if ( (options & SINGLE_MATCH) && (iter != begin || pos != 0 || src.length() != (size_t)len) )
			{
				begin = end;
				break;
			}

			if(options & PRETTY_PRINT)
			{
				// set bash green start postion￼
				bash_stdio.insert(pos, CURRENT_FG_COLOR);
				// reset bash color position
				pos += CURRENT_FG_COLOR.length() + len;
				bash_stdio.insert(pos, FMT_RESET);
				cout << (match_i+1) << ": " << src.substr(match.position(), match.length()) << endl;
			}
			else
			{
				cout << (match_i+1) << "\t" << src.substr(match.position(), match.length()) 
					<< '\t' << match.position() << '\t' << match.length() << endl;
			}
		}

		cout << "\nFound " << std::distance(begin, end) << " matches:\n";
		cout << bash_stdio << "\n\n";
	}
	return 0;
}

int parse_options(int argc, char* argv[])
{
	int opt = 0;
	int option_index = 0;
	
	optind = 0;
	opt = getopt_long(argc, argv, "hvispP", long_options, &option_index);
	while (opt != -1)
	{
		switch (opt)
		{
		case 'h':
			print_help();
			return 0;
		case 'v':
			option_flags |= VERBOSE;
			break;
		case 'i':
			option_flags |= IGNORE_CASE;
			break;
		case 's':
			option_flags |= SINGLE_MATCH;
			break;
		case 'P':
			option_flags |= PRETTY_PRINT;
			break;
		case 'p':
			option_flags &= ~PRETTY_PRINT;
			break;
		default: // unknown option before args
			cerr << "Unexpected option, -h for help\n";
			return -1;
		}
		opt = getopt_long(argc, argv, "hvispP", long_options, &option_index);
	}

	if (argc <= DEFAULT_ARGC) // not correct number of args
	{
		cerr << "Expected argument after options, -h for help\n";
		return 0;
	}
	
	if (option_flags & VERBOSE)
	{
		print_help();
	}

	argc -= optind;
	argv += optind;

	return regx_match(argc, argv, option_flags);
}
