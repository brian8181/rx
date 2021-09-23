#include <iostream>
#include <string>
#include <regex>
#include <getopt.h>
#include "main.hpp"
#include "rx.hpp"
#include <vector>
#include <map>

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
		cout << count << ": ";
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
		regex::flag_type regex_opt = regex::extended;
		regex_opt = (OPTION_FLAGS & IGNORE_CASE) != 0 ? regex_opt|regex::icase : regex_opt;
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
			//cout << endl << (input_i) << ": ";
			cout << "\nFound " << std::distance(begin, end) << " matches:\n";
			cout << bash_stdio << "\n";
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
			OPTION_FLAGS |= PRETTY_PRINT;
			break;
		case 'p':
			OPTION_FLAGS &= ~PRETTY_PRINT;
			break;
		case 'E':
			OPTION_FLAGS |= EXTENDED_REGX;
			break;
		case 'e':
			print_version();
			return 0;
		case 'r':
			print_version();
			return 0;
		case 'o':
		{
			//OPTION_FLAGS |= REGEX_OPTIONS;
			//regex::flag_type regex_opt = *argv[optind];
			// cout << regex_opt;
			// regx_match.
			// memcpy(regex_opt, argv, sizeof(char));
			// char* argv[sizeof(char*) * optind];

			std::string arg = (string)argv[optind];
			//cin >> (string)argv[optind] >> options_flags;
			//unsigned int pos;
			std::size_t s = arg.find('|', 0);
			while(s != std::string::npos)
			{
				string opts; 
				vector<string> str_options;
				std::string skey = arg.substr(0, s-1);
				unsigned int key = enum_map[skey];
				//std::regex_constants::syntax_option_type id = (std::regex_constants::syntax_option_type)enum_map[key];
				switch(key)
				{
				// 	case ECMAScript:
				// 		str_options.push_front("ECMAScript");
				// 		opts.insert("ECMAScript", enum_map[ECMAScript]);
				// 		break;
				// 	case basic: 
				// 		//str_options.push_front("basic");
				// 		opts.insert(basic);
				// 		break;
				// 	// case: extended:
					// 	str_options.push_front("extendee"); 
					// 	opts.insert("extended", enum_map[basic]);
					// 	break;
					// case: awk:        
					// 	//str_options.insert(extended);   
					// 	opts.insert("extended", enum_map[basic]);
					// 	break;
					// case: grep: 
					// 	//str_options.insert(extended);   
					// 	opts.insert("extended", enum_map[basic]);    
					// 	break;
					// case: egrep:      
					// 	//str_options.push_front(extended);   
					// 	opts.insert("extended", enum_map[basic]);
				};
				s = arg.find('|', s);
			}
			break;
		}
		default: // unknown option before args
			cerr << "Unexpected option, -h for help\n";
			return -1;
		}
		opt = getopt_long(argc, argv, "hvispPreEo", long_options, &option_index);
	}

	if (argc <= DEFAULT_ARGC) // not correct number of args
	{
		cerr << "Expected argument after options, -h for help\n";
		return 0;
	}
	
	if (OPTION_FLAGS & VERBOSE)
	{
		print_help();
	}

	argc -= optind;
	argv += optind;

	return regx_match(argc, argv);
}
