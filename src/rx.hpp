#ifndef _RX_HPP
#define _RX_HPP

#include <string>
#include <getopt.h>
#include "bash_color.h"

// functions
int parse_options(int argc, char *argv[]);
void print_help();
// constants
const int BUFFER_LEN = 0xFF;
const int DEFAULT_ARGC = 2;

#endif
