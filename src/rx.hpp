#ifndef _RX_HPP
#define _RX_HPP

#include <regex>

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
<<<<<<< HEAD
//const unsigned char REGEX_OPTIONS = 0x20;
=======
>>>>>>> 3737389ece3a4e5b32edb84d8d0872fa34e95483
const unsigned char DEFAULTS = PRETTY_PRINT | EXTENDED_REGX;

// Set Defaults
unsigned char OPTION_FLAGS = DEFAULTS;
std::regex::flag_type REGX_FLAGS = std::regex::basic;

// match function
int regx_match(int count, char* args[]);


// syntax_option_type icase = /*unspecified*/;
// syntax_option_type nosubs = /*unspecified*/;
// syntax_option_type optimize = /*unspecified*/;
// syntax_option_type collate = /*unspecified*/;
// syntax_option_type ECMAScript = /*unspecified*/;
// syntax_option_type basic = /*unspecified*/;
// syntax_option_type extended = /*unspecified*/;
// syntax_option_type awk = /*unspecified*/;
// syntax_option_type grep = /*unspecified*/;
// syntax_option_type egrep = /*unspecified*/;
// syntax_option_type multiline = /*unspecified*/;

#endif
