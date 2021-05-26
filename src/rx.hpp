#ifndef _RX_HPP
#define _RX_HPP

#include <string>
#include <getopt.h>
#include "bash_color.h"

// functions
void print_help();
void print_match_header(const string &pattern, const string &src, const bool single_flag, const bool pretty_flag);
int parse_options(int argc, char *argv[]);
// constants
const int BUFFER_LEN = 0xFF;
const int DEFAULT_ARGC = 2;

#endif