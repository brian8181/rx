#ifndef _RX_HPP
#define _RX_HPP

// constants
const int BUFFER_LEN = 0xFF;
const int DEFAULT_ARGC = 2;
const int EVENS_ONLY = 2;

// Version string
const string& VERSION_STRING = "rx 0.0.1";

// Options Flags
const unsigned char VERBOSE = 0x1;
const unsigned char IGNORE_CASE = 0x2;
const unsigned char SINGLE_MATCH = 0x4;
const unsigned char PRETTY_PRINT = 0x8;

const unsigned char DEFAULTS = PRETTY_PRINT;
unsigned char option_flags = DEFAULTS; 

int regx_match(int count, char* args[], const unsigned char& options);

#endif
