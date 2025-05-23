// File Name:  src/rx.hpp
// Build Date: Tue May 20 22:29:39 CDT 2025
// Version:    0.1

#ifndef _RX_HPP
#define _RX_HPP

#include <string>
#include <vector>

using std::string;
using std::vector;

void print_version( );
void print_help( );
void print_match_header( const string& pattern, const string& src, int count, int len );
int parse_options( int argc, char* argv[] );
int regx_match( const vector<string>& exp_text, const vector<string>& search_text );

#endif
