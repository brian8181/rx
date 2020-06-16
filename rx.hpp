#ifndef _RX_H
#define _RX_H

#include <string>
#include <getopt.h>

using namespace std;

// shell color constants
const string FMT_FG_GREEN = "\e[32m";
const string FMT_UNDERLINE = "\e[4m";
const string FMT_BOLD = "\e[1m";
const string FMT_RESET = "\e[0m";
const string CURRENT_FG_COLOR = FMT_FG_GREEN + FMT_UNDERLINE;

void print_help();
int parse_options(int argc, char *argv[]);
int add(int a, int b);

const int DEFAULT_ARGC = 2;

#endif
