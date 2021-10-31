#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <stdexcept>
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
		{"pretty", no_argument, 0, 'P'}, //default
		{"no-pretty", no_argument, 0, 'p'},
		{"version", no_argument, 0, 'r'},
		{"not_extended", no_argument, 0, 'e'}, 
		{"extended", no_argument, 0, 'E'}, //default
		{"options", no_argument, 0, 'o'} //default
	};

map<string, regex::flag_type> regex_flags =
	{
		{"ECMAScript", regex::ECMAScript}, 
		{"basic", regex::basic},
		{"extended", regex::extended},
		{"awk", regex::awk},
		{"grep", regex::grep}, 
		{"egrep", std::regex::egrep},
		{"icase", regex::icase},
		{"nosubs", regex::nosubs},
		{"optimize", regex::optimize},
		{"collate", regex::collate}
	};

map<string, std::regex_constants::match_flag_type>  match_flags =
	{
		{"match_default", std::regex_constants::match_default},
		{"match_not_bol",  std::regex_constants::match_not_bol},
		{"match_not_eol", std::regex_constants::match_not_eol},
		{"match_not_bow", std::regex_constants::match_not_bow},
		{"match_not_eow", std::regex_constants::match_not_eow}, 
		{"match_any", std::regex_constants::match_any},
		{"match_not_null", std::regex_constants::match_not_null},
		{"match_continuous", std::regex_constants::match_continuous},
		{"match_prev_avail", std::regex_constants::match_prev_avail},
		{"format_default", std::regex_constants::format_default},
		{"format_sed", std::regex_constants::format_sed},
		{"format_no_copy", std::regex_constants::format_no_copy},
		{"format_first_only", std::regex_constants::format_first_only}
	};


void print_help()
{
	cout << "Usage: "  
		 << FMT_BOLD << "rx" << FMT_RESET << " "
		 << FMT_UNDERLINE << "[OPTION]..." << FMT_RESET << " "
		 << FMT_UNDERLINE << "PATTERN" << FMT_RESET << " "
		 << FMT_UNDERLINE << "INPUT..." << FMT_RESET << endl;
}

void print_match_header(const string& pattern, const string& src, int count)
{
	if(OPTION_FLAGS  & PRETTY_PRINT)
	{
		cout << count << ": "; // input number / count
		cout << FMT_FG_RED << ((OPTION_FLAGS  & SINGLE_MATCH) ? "Single Match Pattern: " : "Match Pattern: ") << FMT_RESET
			 << "'" << FMT_FG_YELLOW << pattern << FMT_RESET << "'"
			 << " -> "
			 << FMT_FG_RED << "Input: " << FMT_RESET
			 << "'" << FMT_FG_YELLOW << src << FMT_RESET << "'";
	}
}

void print_version()
{
	cout << VERSION_STRING << endl;
}

int regx_match(int count, char* args[])
{
	string src;
	string exp(args[0]);
	
	// for each input
	for (int input_i = 1; input_i < count; ++input_i)
	{
		src = args[input_i];
		print_match_header(exp, src, input_i);
		string bash_stdio = src;
		REGX_FLAGS = (OPTION_FLAGS & IGNORE_CASE) != 0 ? REGX_FLAGS|regex::icase : REGX_FLAGS;
		regex src_epx(exp, REGX_FLAGS);

		auto begin = sregex_iterator(src.begin(), src.end(), src_epx);
		auto end = sregex_iterator(); 
		int match_i = 0;
		// for each match
		for (sregex_iterator iter = begin; iter != end; ++iter, ++match_i)
		{
			string CURRENT_FG_COLOR( match_i % 2 ? FMT_FG_CYAN + FMT_UNDERLINE : FMT_FG_GREEN + FMT_UNDERLINE );
			smatch match = *iter;
			int pos = match.position() + match_i * (CURRENT_FG_COLOR.length() + FMT_RESET.length());
			int len = match.length();
			if ( (OPTION_FLAGS & SINGLE_MATCH) && (iter != begin || pos != 0 || src.length() != (size_t)len) )
			{
				begin = end;
				break;
			}

			if(OPTION_FLAGS & PRETTY_PRINT)
			{
				// set bash green start postion￼
				bash_stdio.insert(pos, CURRENT_FG_COLOR);
				// reset bash color position
				pos += CURRENT_FG_COLOR.length() + len;
				bash_stdio.insert(pos, FMT_RESET);
			}
			else
			{
				cout << endl << (match_i+1) << "\t" << src.substr(match.position(), match.length()) 
					 << '\t' << match.position() << '\t' << match.length() << endl;
			}
        }

		if(OPTION_FLAGS & PRETTY_PRINT)
		{
			cout << endl << "Found " << distance(begin, end) << " matches:" << endl;
			cout << bash_stdio << endl;
		}
	}
	return 0;
}

int parse_options(int argc, char* argv[])
{
	int opt = 0;
	int option_index = 0;

	optind = 0;
	opt = getopt_long(argc, argv, "hvispPreEo", long_options, &option_index);
	while (opt != -1)
	{
		switch (opt)
		{
		case 'h':
			print_help();
			return 0;
		case 'v':
			OPTION_FLAGS |= VERBOSE;
			break;
		case 'i':
			OPTION_FLAGS |= IGNORE_CASE;
			break;
		case 's':
			OPTION_FLAGS |= SINGLE_MATCH;
			break;
		case 'P':
			OPTION_FLAGS |= PRETTY_PRINT;
			break;
		case 'p':
			OPTION_FLAGS &= ~PRETTY_PRINT;
			break;
		case 'E':
			OPTION_FLAGS |= EXTENDED_REGX;
			break;
		case 'e':
			OPTION_FLAGS &= ~EXTENDED_REGX;
			break;
		case 'r':
			print_version();
			return 0;
		case 'o':
		{
			string sz_opt = argv[optind];
			string::size_type sz_beg = 0;
			string::size_type sz_end = 0;	
			
			while(sz_end != string::npos) 
			{
				sz_end = sz_opt.find('|', sz_beg);	
				string split = sz_opt.substr(sz_beg, sz_end-sz_beg);
				sz_beg = sz_end+1;

				try
				{
					// DEBUG! throw std::out_of_range("Test");
					REGX_FLAGS |= regex_flags.at(split);
				}
				catch(std::out_of_range const&)
				{
					cerr << "Exception: Unexpected option, -h for help" << endl;
					return -1;
				}
			}
			++optind;
			break;
		}
		default: // unknown option before args
			cerr << "Unexpected option, -h for help" << endl;
			return -1;
		}
		opt = getopt_long(argc, argv, "hvispPreEo", long_options, &option_index);
	}

	if (argc <= DEFAULT_ARGC) // not correct number of args
	{
		cerr << "Expected argument after options, -h for help" << endl;
		return -1;
	}
	
	if (OPTION_FLAGS & VERBOSE)
	{
		print_help();
	}

	argc -= optind;
	argv += optind;

	return regx_match(argc, argv);
}
