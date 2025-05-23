// File Name:  src/rx.cpp
// Build Date: Tue May 20 22:29:39 CDT 2025
// Version:    0.1

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

using std::string;
using std::vector;
using std::map;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::regex;

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
	{"pretty", no_argument, 0, 'P'},        //default
	{"no-pretty", no_argument, 0, 'p'},
	{"version", no_argument, 0, 'r'},
	{"not_extended", no_argument, 0, 'e'},
	{"extended", no_argument, 0, 'E'},      //default
	{"options", required_argument, 0, 'o'}, //default
	{"file", required_argument, 0, 'f'},
	{"regex_file", required_argument, 0, 'x'}
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
	{"collate", regex::collate},//
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

void print_match_header( const string& pattern, const string& src, int count, int len )
{
	if( OPTION_FLAGS & PRETTY_PRINT )
	{
		if( len > 1 ) cout << count << ": "; // input number / count
		cout << FMT_FG_RED << ( ( OPTION_FLAGS & SINGLE_MATCH ) ? "Single Match Pattern: " : "Match Pattern: " ) << FMT_RESET
			<< "'" << FMT_FG_YELLOW << pattern << FMT_RESET << "'"
			<< " -> "
			<< FMT_FG_RED << "Input: " << FMT_RESET
			<< "'" << FMT_FG_YELLOW << src << FMT_RESET << "'";
	}
}

int regx_match( const vector<string>& exp_text, const vector<string>& search_text )
{
	int exp_text_len = exp_text.size();
	// for each exp
	for( int i = 0; i < exp_text_len; ++i )
	{
		int search_text_len = search_text.size();
		// for each input
		for( int j = 0; j < search_text_len; ++j )
		{
			print_match_header( exp_text[i], search_text[j], j + 1, search_text_len );
			string bash_stdio = search_text[j];
			REGX_FLAGS = ( OPTION_FLAGS & IGNORE_CASE ) != 0 ? REGX_FLAGS | regex::icase : REGX_FLAGS;

			regex src_epx;
			try
			{
				src_epx = regex( exp_text[i], REGX_FLAGS );
			}
			catch( regex_error& e )
			{
				cerr << "exception caught: " << e.what() << '\n';
				cerr << "error of type " << e.code() << " was unhandled\n";
			}

			auto begin = sregex_iterator( search_text[j].begin(), search_text[j].end(), src_epx, std::regex_constants::match_default );
			auto end = sregex_iterator();
			int match_i = 0;
			// for each match
			for( sregex_iterator iter = begin; iter != end; ++iter, ++match_i )
			{
				string CURRENT_FG_COLOR( match_i % 2 ? FMT_FG_CYAN + FMT_UNDERLINE : FMT_FG_GREEN + FMT_UNDERLINE );
				smatch match = *iter;

				int pos = match.position() + match_i * ( CURRENT_FG_COLOR.length() + FMT_RESET.length() );
				int search_text_len = match.length();
				if( ( OPTION_FLAGS & SINGLE_MATCH ) && ( iter != begin || pos != 0 || search_text[j].length() != (size_t)search_text_len ) )
				{
					begin = end;
					break;
				}

				if( OPTION_FLAGS & PRETTY_PRINT )
				{
					// set bash green start postion
					bash_stdio.insert( pos, CURRENT_FG_COLOR );
					// reset bash color position
					pos += CURRENT_FG_COLOR.length() + search_text_len;
					bash_stdio.insert( pos, FMT_RESET );
					pos += FMT_RESET.length();

					if( OPTION_FLAGS & GROUPS )
					{
						int len = match.size();
						for( int i = 1; i < len; ++i )
						{
							if( match[i].matched )
							{
								ostringstream ss;
								ss << "\n\t" << i << ": " << FMT_FG_RED << "Submatch: " << FMT_RESET << FMT_FG_GREEN << match[i].str() << FMT_RESET;
								bash_stdio.insert( pos, ss.str() );
								pos += ss.str().size();
							}
						}
					}
				}
				else
				{
					cout << ( match_i + 1 ) << "\t" << search_text[j].substr( match.position(), match.length() )
						<< '\t' << match.position() << '\t' << match.length() << endl;
				}
			}

			if( OPTION_FLAGS & PRETTY_PRINT )
			{
				cout << endl << "Found " << distance( begin, end ) << " matches:" << endl;
				cout << bash_stdio << endl;
			}
		}
	}
	return 0;
}

int parse_options( int argc, char* argv[] )
{
	vector<string> exp_text;
	vector<string> search_text;

	int opt = 0;
	int option_index = 0;
	optind = 0;
	while( ( opt = getopt_long( argc, argv, "hvispgPreEo:x:f:", long_options, &option_index ) ) != -1 )
	{
		switch( opt )
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
			search_file.open( optarg, ios::in );
			if( search_file.is_open() )
			{
				string line;
				search_text.clear();
				while( getline( search_file, line ) )
				{
					search_text.push_back( line );
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
			exp_file.open( optarg, ios::in );
			if( exp_file.is_open() )
			{
				string line;
				exp_text.clear();
				while( getline( exp_file, line ) )
				{
					exp_text.push_back( line );
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

			while( sz_end != string::npos )
			{
				sz_end = str_optarg.find( '|', sz_beg );
				string split = str_optarg.substr( sz_beg, sz_end - sz_beg );
				sz_beg = sz_end + 1;

				try
				{
					REGX_FLAGS |= regex_flags.at( split );
				}
				catch( out_of_range const& ex )
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
		//return 0;
	}

	if( argc <= DEFAULT_ARGC ) // not correct number of args
	{
		cerr << "Expected argument after options, -h for help" << endl;
		return -1;
	}

	if( !( ( OPTION_FLAGS & SEARCH_FROM_FILE ) && ( OPTION_FLAGS & REGEX_FROM_FILE ) ) )
	{
		if( OPTION_FLAGS & SEARCH_FROM_FILE )
		{
			exp_text.assign( argv + ( optind ), argv + ( optind + 1 ) );
		}
		else if( OPTION_FLAGS & REGEX_FROM_FILE )
		{
			search_text.assign( argv + optind, argv + argc );
		}
		else
		{
			exp_text.assign( argv + optind, argv + ( optind + 1 ) );
			search_text.assign( argv + ( optind + 1 ), argv + argc );
		}
	}

	return regx_match( exp_text, search_text );
}
