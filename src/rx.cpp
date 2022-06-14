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
const string VERSION_STRING = "rx 2.81";

// options flags
const unsigned char VERBOSE       = 0x01;
const unsigned char IGNORE_CASE   = 0x02;
const unsigned char SINGLE_MATCH  = 0x04;
const unsigned char PRETTY_PRINT  = 0x08;
const unsigned char EXTENDED_REGX = 0x10;
const unsigned char REGEX_OPTIONS = 0x12;
const unsigned char FROM_FILE     = 0x20;
const unsigned char DEFAULTS = PRETTY_PRINT | EXTENDED_REGX;

// set defaults
unsigned char OPTION_FLAGS = DEFAULTS;
regex::flag_type REGX_FLAGS = regex::basic;

static struct option long_options[] =
{
	{"verbose", no_argument, 0, 'v'},
	{"help", no_argument, 0, 'h'},
	{"ignore_case", no_argument, 0, 'i'},
	{"single", no_argument, 0, 's'},
	{"pretty", no_argument, 0, 'P'},        //default
	{"no-pretty", no_argument, 0, 'p'},
	{"version", no_argument, 0, 'r'},
	{"not_extended", no_argument, 0, 'e'}, 
	{"extended", no_argument, 0, 'E'},      //default
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

void print_match_header(const string& pattern, const string& src, int count, int len)
{
	if(OPTION_FLAGS & PRETTY_PRINT)
	{
		if(len > 1) cout << count <<  ": "; // input number / count
		cout << FMT_FG_RED << ((OPTION_FLAGS  & SINGLE_MATCH) ? "Single Match Pattern: " : "Match Pattern: ") << FMT_RESET
			 << "'" << FMT_FG_YELLOW << pattern << FMT_RESET << "'"
			 << " -> "
			 << FMT_FG_RED << "Input: " << FMT_RESET
			 << "'" << FMT_FG_YELLOW << src << FMT_RESET << "'";
	}
}

int regx_match(const vector<string>& exp_text, const vector<string>& search_text)
{
	int exp_text_len = exp_text.size();
	// for each exp
	for(int i = 0; i < exp_text_len; ++i)
	{
		int search_text_len = search_text.size();
		// for each input
		for (int j = 0; j < search_text_len; ++j)
		{
			print_match_header(exp_text[i], search_text[j], j+1, search_text_len);
			string bash_stdio = search_text[j];
			REGX_FLAGS = (OPTION_FLAGS & IGNORE_CASE) != 0 ? REGX_FLAGS|regex::icase : REGX_FLAGS;

			regex src_epx;
			try
			{
				src_epx = regex(exp_text[i], REGX_FLAGS);
			}
			catch(regex_error& e)
			{
				cerr << "exception caught: " << e.what() << '\n';
				cerr << "error of type " << e.code() << " was unhandled\n";
			} 

			auto begin = sregex_iterator(search_text[j].begin(), search_text[j].end(), src_epx, std::regex_constants::match_default);
			auto end = sregex_iterator(); 
			int match_i = 0;
			// for each match
			for (sregex_iterator iter = begin; iter != end; ++iter, ++match_i)
			{
				string CURRENT_FG_COLOR(match_i % 2 ? FMT_FG_CYAN + FMT_UNDERLINE : FMT_FG_GREEN + FMT_UNDERLINE);
				smatch match = *iter;

				int pos = match.position() + match_i * (CURRENT_FG_COLOR.length() + FMT_RESET.length());
				int search_text_len = match.length();
				if ((OPTION_FLAGS & SINGLE_MATCH) && (iter != begin || pos != 0 || search_text[j].length() != (size_t)search_text_len))
				{
					begin = end;
					break;
				}

				if(OPTION_FLAGS & PRETTY_PRINT)
				{
					// set bash green start postion￼
					bash_stdio.insert(pos, CURRENT_FG_COLOR);
					// reset bash color position
					pos += CURRENT_FG_COLOR.length() + search_text_len;
					bash_stdio.insert(pos, FMT_RESET);
				}
				else
				{
					cout << (match_i+1) << "\t" << search_text[j].substr(match.position(), match.length()) 
						<< '\t' << match.position() << '\t' << match.length() << endl;
				}
			}

			if(OPTION_FLAGS & PRETTY_PRINT)
			{
				cout << endl << "Found " << distance(begin, end) << " matches:" << endl;
				cout << bash_stdio << endl;
			}
		}
	}
	return 0;
}

int parse_options(int argc, char* argv[])
{
	vector<string> exp_text;
	vector<string> search_text(argv, argv + argc);

	int opt = 0;
	int option_index = 0;
	optind = 0;
	while ((opt = getopt_long(argc, argv, "hvispPreEo:f:", long_options, &option_index)) != -1)
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
		case 'f':
		{
			OPTION_FLAGS |= FROM_FILE;
			if(argc != optind)
			{
				ifstream exp_file;
				exp_file.open(optarg, ios::in);
				if(exp_file.is_open())
				{
					string line;
					exp_file.clear();
					while(getline(exp_file, line))
					{
						exp_text.push_back(line);
						cout << line << endl;
					}
					exp_file.close(); 	
				}
			}
			else
			{
				ifstream search_file;
				search_file.open(optarg, ios::in); 
				if (search_file.is_open())
				{   
					string line;
					search_text.clear();
					while(getline(search_file, line))
					{
						search_text.push_back(line);
					}
					search_file.close(); 
				}
				else
				{
					cerr << "Error: invalid path with file option" << endl;
					return -1;
				}
			}
			break;
		}
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

	exp_text.push_back(argv[optind]);			
	if((OPTION_FLAGS & FROM_FILE) == 0)
	{
		search_text.assign(argv+(optind+1), argv + argc);
	}
	return regx_match(exp_text, search_text);
}
