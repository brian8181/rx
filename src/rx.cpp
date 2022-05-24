#include <iostream>
#include <stdlib.h>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <stdexcept>
#include <fstream>
#include <getopt.h>
#include "bash_color.hpp"
#include "rx.hpp"

using namespace std;

// constants
const int BUFFER_LEN = 0xFF;
const int DEFAULT_ARGC = 2;
const string VERSION_STRING = "rx 0.0.2";

// options flags
const unsigned char VERBOSE       = 0x01;
const unsigned char IGNORE_CASE   = 0x02;
const unsigned char SINGLE_MATCH  = 0x04;
const unsigned char PRETTY_PRINT  = 0x08;
const unsigned char EXTENDED_REGX = 0x10;
const unsigned char REGEX_OPTIONS = 0x12;
const unsigned char FROM_FILE     = 0x20;
const unsigned char DEFAULTS = PRETTY_PRINT | EXTENDED_REGX;

// Set Defaults
unsigned char OPTION_FLAGS = DEFAULTS;
regex::flag_type REGX_FLAGS = regex::basic;

static struct option long_options[] =
{
	{"verbose", no_argument, 0, 'v'},
	{"help", no_argument, 0, 'h'},
	{"ignore_case", no_argument, 0, 'i'},
	{"single", no_argument, 0, 's'},
	{"pretty", no_argument, 0, 'P'},       //default
	{"no-pretty", no_argument, 0, 'p'},
	{"version", no_argument, 0, 'r'},
	{"not_extended", no_argument, 0, 'e'}, 
	{"extended", no_argument, 0, 'E'},     //default
	{"options", no_argument, 0, 'o'},       //default
	{"file", required_argument, 0, 'f'}
};

map<std::string, regex::flag_type> regex_flags =
{
	{"ECMAScript", regex::ECMAScript}, 
	{"basic", regex::basic},
	{"extended", regex::extended},
	{"awk", regex::awk},
	{"grep", regex::grep}, 
	{"egrep", regex::egrep},
	{"icase", regex::icase},
	{"nosubs", regex::nosubs},
	{"optimize", regex::optimize},
	{"collate", regex::collate}
};

// map<std::string, regex_constants::match_flag_type>  match_flags =
// {
// 	{"match_default", regex_constants::match_default},
// 	{"match_not_bol",  regex_constants::match_not_bol},
// 	{"match_not_eol", regex_constants::match_not_eol},
// 	{"match_not_bow", regex_constants::match_not_bow},
// 	{"match_not_eow", regex_constants::match_not_eow}, 
// 	{"match_any", regex_constants::match_any},
// 	{"match_not_null", regex_constants::match_not_null},
// 	{"match_continuous", regex_constants::match_continuous},
// 	{"match_prev_avail", regex_constants::match_prev_avail},
// 	{"format_default", regex_constants::format_default},
// 	{"format_sed", regex_constants::format_sed},
// 	{"format_no_copy", regex_constants::format_no_copy},
// 	{"format_first_only", regex_constants::format_first_only}
// };

void print_version()
{
	cout << VERSION_STRING << endl;
}

void print_help()
{
	cout << "Usage: "  
		 << FMT_BOLD      << "rx"          << FMT_RESET << " "
		 << FMT_UNDERLINE << "[OPTION]..." << FMT_RESET << " "
		 << FMT_UNDERLINE << "PATTERN"     << FMT_RESET << " "
		 << FMT_UNDERLINE << "INPUT..."    << FMT_RESET << endl;
}

void print_match_header(const string& pattern, const string& src, int count)
{
	if(OPTION_FLAGS & PRETTY_PRINT)
	{
		cout << count << ": "; // input number / count
		cout << FMT_FG_RED << ((OPTION_FLAGS  & SINGLE_MATCH) ? "Single Match Pattern: " : "Match Pattern: ") << FMT_RESET
			 << "'" << FMT_FG_YELLOW << pattern << FMT_RESET << "'"
			 << " -> "
			 << FMT_FG_RED << "Input: " << FMT_RESET
			 << "'" << FMT_FG_YELLOW << src << FMT_RESET << "'";
	}
}

int regx_match(const string& exp, const vector<string>& search_text)
{
	int len = search_text.size();
	// for each input
	for (int i = 0; i < len; ++i)
	{
		print_match_header(exp, search_text[i], i+1);
		string bash_stdio = search_text[i];
		REGX_FLAGS = (OPTION_FLAGS & IGNORE_CASE) != 0 ? REGX_FLAGS|regex::icase : REGX_FLAGS;

		regex src_epx;
		try
		{
			src_epx = regex(exp, REGX_FLAGS);
		}
		catch(regex_error& e)
		{
			cerr << "exception caught: " << e.what() << '\n';
			cerr << "error of type " << e.code() << " was unhandled\n";
		} 

		auto begin = sregex_iterator(search_text[i].begin(), search_text[i].end(), src_epx, std::regex_constants::match_default);
		auto end = sregex_iterator(); 
		int match_i = 0;
		// for each match
		for (sregex_iterator iter = begin; iter != end; ++iter, ++match_i)
		{
			string CURRENT_FG_COLOR(match_i % 2 ? FMT_FG_CYAN + FMT_UNDERLINE : FMT_FG_GREEN + FMT_UNDERLINE);
			smatch match = *iter;

			int pos = match.position() + match_i * (CURRENT_FG_COLOR.length() + FMT_RESET.length());
			int len = match.length();
			if ((OPTION_FLAGS & SINGLE_MATCH) && (iter != begin || pos != 0 || search_text[i].length() != (size_t)len))
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
				cout << (match_i+1) << "\t" << search_text[i].substr(match.position(), match.length()) 
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
	while ((opt = getopt_long(argc, argv, "hvispPreEo:", long_options, &option_index)) != -1)
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
			OPTION_FLAGS |= REGEX_OPTIONS;
			string str_optarg = optarg;
			string::size_type sz_beg = 0;
			string::size_type sz_end = 0;	
			
			while(sz_end != string::npos) 
			{
				sz_end = str_optarg.find('|', sz_beg);	
				string split = str_optarg.substr(sz_beg, sz_end-sz_beg);
				sz_beg = sz_end+1;

				try
				{
					REGX_FLAGS |= regex_flags.at(split);
				}
				catch(out_of_range const& ex)
				{
					cerr << ex.what() << endl;
					cout << "Exception: Unexpected option, -h for help" << endl;
					return -1;
				}
			}
			break;
		}
		default: // unknown option before args
			cerr << "Unexpected option, -h for help" << endl;
			return -1;
		}
	}

	if (argc <= DEFAULT_ARGC) // not correct number of args
	{
		cerr << "Expected argument after options, -h for help" << endl;
		return -1;
	}

	vector<string> search_text(argv+(optind+1), argv + argc);	
	return regx_match(argv[optind], search_text);
}
