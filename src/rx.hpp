#ifndef _RX_HPP
#define _RX_HPP

#include <string>
//std::regex_constants;

// constants
const int BUFFER_LEN   = 0xFF;
const int DEFAULT_ARGC = 2;
const int EVENS_ONLY   = 2;

// version string
const std::string VERSION_STRING = "rx 0.0.1";

// options flags
const unsigned char VERBOSE       = 0x01;
const unsigned char IGNORE_CASE   = 0x02;
const unsigned char SINGLE_MATCH  = 0x04;
const unsigned char PRETTY_PRINT  = 0x08;
const unsigned char EXTENDED_REGX = 0x10;
const unsigned char REGEX_OPTIONS = 0x12;

const unsigned char DEFAULTS = PRETTY_PRINT | EXTENDED_REGX;
unsigned char option_flags = DEFAULTS; 

int regx_match(int count, char* args[]);

#endif
