#include <iostream>
#include <stdlib.h>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <stack>
#include <utility>
#include <stdexcept>
#include <fstream>
#include <getopt.h>
#include "bash_color.hpp"
#include "rx.hpp"

using namespace std;

// constants
const int DEFAULT_ARGC = 2;
const string VERSION_STRING = "rx 2.90";

// options flags
const unsigned short VERBOSE = 0x01;
const unsigned short IGNORE_CASE = 0x02;
const unsigned short SINGLE_MATCH = 0x04;
const unsigned short PRETTY_PRINT = 0x08;
const unsigned short GROUPS = 0x10;
const unsigned short EXTENDED_REGX = 0x20;
const unsigned short REGEX_OPTIONS = 0x40;
const unsigned short SEARCH_FROM_FILE = 0x80;
const unsigned short REGEX_FROM_FILE = 0x100;
const unsigned short DEFAULTS = PRETTY_PRINT | EXTENDED_REGX;

// Set Defaults
unsigned short OPTION_FLAGS = DEFAULTS;
regex::flag_type REGX_FLAGS = regex::ECMAScript;

static struct option long_options[] =
	{
		{"verbose", no_argument, 0, 'v'},
		{"help", no_argument, 0, 'h'},
		{"icase", no_argument, 0, 'i'},
		{"single", no_argument, 0, 's'},
		{"groups", no_argument, 0, 'g'},
		{"pretty", no_argument, 0, 'P'}, // default
		{"no-pretty", no_argument, 0, 'p'},
		{"version", no_argument, 0, 'r'},
		{"not_extended", no_argument, 0, 'e'},
		{"extended", no_argument, 0, 'E'},		// default
		{"options", required_argument, 0, 'o'}, // default
		{"file", required_argument, 0, 'f'},
		{"regex_file", required_argument, 0, 'x'}};

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
		{"collate", regex::collate}, //
									 //{"multiline". regex::multiline} (since C++17)
};

void print_version()
{
	cout << VERSION_STRING << endl;
}

void print_help()
{
	cout << "Usage: "
		 << FMT_BOLD << "rx" << FMT_RESET << " "
		 << FMT_UNDERLINE << "[OPTION]..." << FMT_RESET << " "
		 << FMT_UNDERLINE << "PATTERN" << FMT_RESET << " "
		 << FMT_UNDERLINE << "INPUT..." << FMT_RESET << endl;
}

void print_match_header(const string &pattern, const string &src, int count, int len)
{
	if (OPTION_FLAGS & PRETTY_PRINT)
	{
		if (len > 1)
			cout << count << ": "; // input number / count
		cout << FMT_FG_RED << ((OPTION_FLAGS & SINGLE_MATCH) ? "Single Match Pattern: " : "Match Pattern: ") << FMT_RESET
			 << "'" << FMT_FG_YELLOW << pattern << FMT_RESET << "'"
			 << " -> "
			 << FMT_FG_RED << "Input: " << FMT_RESET
			 << "'" << FMT_FG_YELLOW << src << FMT_RESET << "'";
	}
}

int regx_match(const vector<string> &exp_text, const vector<string> &search_text)
{
	int exp_text_len = exp_text.size();
	// for each exp
	for (int i = 0; i < exp_text_len; ++i)
	{
		int search_text_len = search_text.size();
		// for each input
		for (int j = 0; j < search_text_len; ++j)
		{
			print_match_header(exp_text[i], search_text[j], j + 1, search_text_len);
			ostringstream oss;
			ostringstream oss2;
			ostringstream oss3;
			ostringstream oss4;

			REGX_FLAGS = (OPTION_FLAGS & IGNORE_CASE) != 0 ? REGX_FLAGS | regex::icase : REGX_FLAGS;
			regex src_epx;
			try
			{
				src_epx = regex(exp_text[i], REGX_FLAGS);
			}
			catch (regex_error &e)
			{
				cerr << "exception caught: " << e.what() << '\n';
				cerr << "error of type " << e.code() << " was unhandled\n";
			}

			auto begin = sregex_iterator(search_text[j].begin(), search_text[j].end(), src_epx, std::regex_constants::match_default);
			auto end = sregex_iterator();
			int match_i = 0;
			int prev_pos = 0;
			int curr_pos = 0;

			// for each match
			for (sregex_iterator iter = begin; iter != end; ++iter, ++match_i)
			{
				string CURRENT_FG_COLOR(match_i % 2 ? FMT_FG_CYAN + FMT_UNDERLINE : FMT_FG_GREEN + FMT_UNDERLINE);
				smatch match = *iter;

				if ((OPTION_FLAGS & SINGLE_MATCH) && (iter != begin || curr_pos != 0 || search_text[j].length() != (size_t)search_text_len))
				{
					begin = end;
					break;
				}

				if (OPTION_FLAGS & PRETTY_PRINT)
				{
					if (OPTION_FLAGS & GROUPS)
					{
						// BKP TESTING
						int len = match.size();
						stack<std::pair<ssub_match, string>> sub_match_stack;
						cout << endl;

						// testing
						ptrdiff_t p_pos = distance(match[0].first, match[1].second);;
						//ptrdiff_t p_len = distance(match[0].first, match[1].second);
						ptrdiff_t c_pos = distance(match[0].first, match[2].second);
						//ptrdiff_t c_len = distance(match[1].first, match[2].second);
						//size_t end = search_text[j].length();
						
						ptrdiff_t len_to_next = (c_pos - p_pos); // or end ? could be negative
						string snip = search_text[j].substr(p_pos, len_to_next);
						pair<ssub_match, string> match_pair(match[i], snip);
						sub_match_stack.push(match_pair);
	
						// struct SMatch
						// {
						// 	ssub_match ssmatch;
						// 	string sub_str;
						// };

						for (int i = 2; i < len; ++i)
						{
							if (match[i].matched)
							{
								//  auto sm = match[i];
								// same thing as below ?
								//  auto sz1 = match.position(i);
								//  auto pos1 = match.length(i);
								//  string sss1 = search_text[j].substr(pos1, sz1);
								//  cout << "*DEBUG* 1* " << sss1 << " : " << endl;
								
								// c_sz = distance(sm.first, sm.second);
								// p_pos = c_pos;
								// oss3 << "(" << snip;		
								
								// get unmatched test before match
								// oss3 << sss2;
								// p_pos = c_pos + sz2;
								// oss3 << "( " << CURRENT_FG_COLOR << sss2 << FMT_RESET;

								// string sss2 = search_text[j].substr(pos2, sz2);
								// oss2 << "(" << i << ":" << sss2 << ".";
								// cout << "*DEBUG* 2* " << sss2 << " : " << endl;
								// cout << "*DEBUG* 3* " << sm.str() << " : " << endl;
								
								// TODO
								c_pos = distance(match[0].first, match[i].first);
								len_to_next = (c_pos - p_pos); // or end
								string snip = search_text[j].substr(p_pos, len_to_next);
								pair<ssub_match, string> match_pair(match[i], snip);
								sub_match_stack.push(match_pair);
										
								while(c_pos < p_pos)
								{

									auto top = sub_match_stack.top();
									sub_match_stack.pop();
									auto next = sub_match_stack.top();
									sub_match_stack.pop();
									
									// push cat and add paren
									string cat = next.second + top.second + ")";
									pair<ssub_match, string> cat_pair(next.first, cat);
									sub_match_stack.push(cat_pair);

									// push current match
									pair<ssub_match, string> top_pair(match[i], "?");
									sub_match_stack.push(top_pair);

									p_pos = c_pos;
									c_pos = distance(match[0].first, sub_match_stack.top().first.first);
								}

								
							}
						}

						auto top = sub_match_stack.top();
						sub_match_stack.pop();
						if(!sub_match_stack.empty())
						{
							// ?
						}
						string last = top.first.str();
						cout << "Try:" << endl;
						cout << last;

						// ptrdiff_t len_to_end = distance(match[0].first, match[0].second) - c_pos;
						// string snip_to_end = search_text[j].substr(c_pos, len_to_end);
						// oss3 << "(" << snip_to_end;

						// cout << "unwind stack: " << endl;
						// oss4 << "unwind stack: " << endl;
						// while(!sub_match_stack.empty())
						// {
						// 	auto sm = sub_match_stack.top();
						// 	cout << sm.first.str() << endl;
						// 	sub_match_stack.pop();
							
						// 	sm.first.str().length();
						// 	c_pos = distance(match[0].first, sm.first.first);
						// 	len_to_next = (c_pos - p_pos); // or end
						// 	string snip = search_text[j].substr(p_pos, len_to_next);
						// 	p_pos = c_pos;
						// 	oss4 << "(" << snip;		
						// }

						// // BKP TESTING
						// cout << endl;
					}
					else
					{
						curr_pos = match.position();
						// get unmatched test before match
						oss << search_text[j].substr(prev_pos, curr_pos - prev_pos);
						// set prev_position
						prev_pos = curr_pos + match.length();
						oss << "( " << CURRENT_FG_COLOR << match.str() << FMT_RESET << " )";
					}
				}
				else
				{
					cout << (match_i + 1) << "\t" << search_text[j].substr(match.position(), match.length())
						 << '\t' << match.position() << '\t' << match.length() << endl;
				}
			}

			if (OPTION_FLAGS & PRETTY_PRINT)
			{
				cout << endl
					 << "Found " << distance(begin, end) << " matches:" << endl;
				// get unmatched test before match
				oss << search_text[j].substr(prev_pos, curr_pos - prev_pos);
				cout << oss.str() << endl;
				// testing
				cout << oss2.str() << endl;
				cout << oss3.str() << endl;
				cout << oss4.str() << endl;
			}
		}
	}
	return 0;
}

int parse_options(int argc, char *argv[])
{
	vector<string> exp_text;
	vector<string> search_text;

	int opt = 0;
	int option_index = 0;
	optind = 0;
	while ((opt = getopt_long(argc, argv, "hvispgPreEo:x:f:", long_options, &option_index)) != -1)
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
		case 'g':
			OPTION_FLAGS |= GROUPS;
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
			OPTION_FLAGS |= SEARCH_FROM_FILE;
			ifstream search_file;
			search_file.open(optarg, ios::in);
			if (search_file.is_open())
			{
				string line;
				search_text.clear();
				while (getline(search_file, line))
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
			break;
		}
		case 'x':
		{
			OPTION_FLAGS |= REGEX_FROM_FILE;
			ifstream exp_file;
			exp_file.open(optarg, ios::in);
			if (exp_file.is_open())
			{
				string line;
				exp_file.clear();
				while (getline(exp_file, line))
				{
					exp_text.push_back(line);
					// cout << line << endl;
				}
				exp_file.close();
			}
			else
			{
				cerr << "Error: invalid path with regex file option" << endl;
				return -1;
			}
			break;
		}
		case 'o':
		{
			REGX_FLAGS = regex_constants::basic;
			OPTION_FLAGS |= REGEX_OPTIONS;
			string str_optarg = optarg;
			string::size_type sz_beg = 0;
			string::size_type sz_end = 0;

			while (sz_end != string::npos)
			{
				sz_end = str_optarg.find('|', sz_beg);
				string split = str_optarg.substr(sz_beg, sz_end - sz_beg);
				sz_beg = sz_end + 1;

				try
				{
					REGX_FLAGS |= regex_flags.at(split);
				}
				catch (out_of_range const &ex)
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

	if (!((OPTION_FLAGS & SEARCH_FROM_FILE) && (OPTION_FLAGS & REGEX_FROM_FILE)))
	{
		if (OPTION_FLAGS & SEARCH_FROM_FILE)
		{
			exp_text.assign(argv + (optind), argv + (optind + 1));
		}
		else if (OPTION_FLAGS & REGEX_FROM_FILE)
		{
			search_text.assign(argv + optind, argv + argc);
		}
		else
		{
			exp_text.assign(argv + optind, argv + (optind + 1));
			search_text.assign(argv + (optind + 1), argv + argc);
		}
	}

	return regx_match(exp_text, search_text);
}
