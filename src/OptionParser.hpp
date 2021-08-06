#ifndef _OPTION_PARSER_HPP
#define _OPTION_PARSER_HPP

#include <string>
#include <getopt.h>
#include "bash_color.h"

class OptionParser 
{

public: 

    OptionParser();
    // functions
    void print_help();
    void print_match_header(const string& pattern, const string& src, const bool single_flag, const bool pretty_flag);
    int parse_options(int argc, char* argv[], const unsigned char& options);

protected:

    const unsigned char options;

};

#endif
