#ifndef _RX_HPP
#define _RX_HPP

#include <string>
#include <map>
#include <vector>
#include <regex>


using std::map;
using std::string;

//using std::regex_constants;

// constants
const int BUFFER_LEN   = 0xFF;
const int DEFAULT_ARGC = 2;
const int EVENS_ONLY   = 2;
const string VERSION_STRING = "rx 0.0.1";

// options flags
const unsigned char VERBOSE       = 0x01;
const unsigned char IGNORE_CASE   = 0x02;
const unsigned char SINGLE_MATCH  = 0x04;
const unsigned char PRETTY_PRINT  = 0x08;
const unsigned char EXTENDED_REGX = 0x10;
const unsigned char REGEX_OPTIONS = 0x20;
const unsigned char DEFAULTS = PRETTY_PRINT | EXTENDED_REGX;
unsigned char OPTION_FLAGS = DEFAULTS;
std::regex::flag_type REGX_FLAGS = std::regex::basic;

std::map<std::string, std::regex::flag_type> enum_map =
{
    {"ECMAScript", std::regex::ECMAScript}, 
    {"basic", std::regex::basic},
    {"extended", std::regex::extended},
    {"awk", std::regex::awk},
    {"grep", std::regex::grep}, 
    {"egrep", std::regex::egrep},
    {"icase", std::regex::icase},
    {"nosubs", std::regex::nosubs},
    {"optimize", std::regex::optimize},
    {"collate", std::regex::collate}
};


// match function
int regx_match(int count, char* args[]);

#endif
