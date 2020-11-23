#ifndef _RX_HPP
#define _RX_HPP

#include <string>
#include <getopt.h>

using namespace std;

// shell color constants
const string FMT_FG_GREEN = "\033[32m";
const string FMT_FG_RED = "\033[31m";
const string FMT_FG_YELLOW = "\033[33m";
const string FMT_UNDERLINE = "\033[4m";
const string FMT_BOLD = "\033[1m";
const string FMT_RESET = "\033[0m";
const string CURRENT_FG_COLOR = FMT_FG_GREEN + FMT_UNDERLINE;

// functions
int parse_options(int argc, char *argv[]);
void print_help();

// constants
const int BUFFER_LEN = 0xFF;
const int DEFAULT_ARGC = 2;

#endif
