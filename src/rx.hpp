#ifndef _RX_HPP
#define _RX_HPP

#include <regex>
#include <string>

// constants
const int BUFFER_LEN   = 0xFF;
const int DEFAULT_ARGC = 2;
const string VERSION_STRING = "rx 0.0.1";

// options flags
const unsigned char VERBOSE       = 0x01;
const unsigned char IGNORE_CASE   = 0x02;
const unsigned char SINGLE_MATCH  = 0x04;
const unsigned char PRETTY_PRINT  = 0x08;
const unsigned char EXTENDED_REGX = 0x10;
const unsigned char DEFAULTS = PRETTY_PRINT | EXTENDED_REGX;

// Set Defaults
unsigned char OPTION_FLAGS = DEFAULTS;
std::regex::flag_type REGX_FLAGS = std::regex::basic;

// parse function
int parse_options(int argc, char* argv[]);
// match function
int regx_match(int count, char* args[]);

#endif
