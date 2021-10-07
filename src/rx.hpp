#ifndef _RX_HPP
#define _RX_HPP

#include <string>
#include <map>
#include <vector>
#include <regex>


using std::map;
using std::string;
//using std::regex_constants;

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
const unsigned char REGEX_OPTIONS = 0x20;
const unsigned char DEFAULTS = PRETTY_PRINT | EXTENDED_REGX;


int regx_match(int count, char* args[]);

const unsigned int ECMAScript = 0x00000001;
const unsigned int basic      = 0x00000002;
const unsigned int extended   = 0x00000004;
const unsigned int awk        = 0x00000008;
const unsigned int grep       = 0x00000010;
const unsigned int egrep      = 0x00000020;
const unsigned int gmask      = 0x0000003F;
const unsigned int icase      = 0x00000100;
const unsigned int nosubs     = 0x00000200;
const unsigned int optimize   = 0x00000400;
const unsigned int collate  = 0x00000800;

// const unsigned int RXOPT_ECMAScript = 0x00000001;
// const unsigned int RXOPT_basic      = 0x00000002;
// const unsigned int RXOPT_extended   = 0x00000004;
// const unsigned int RXOPT_awk        = 0x00000008;
// const unsigned int RXOPT_grep       = 0x00000010;
// const unsigned int RXOPT_egrep      = 0x00000020;
// const unsigned int RXOPT_gmask      = 0x0000003F;
// const unsigned int RXOPT_icase      = 0x00000100;
// const unsigned int RXOPT_nosubs     = 0x00000200;
// const unsigned int RXOPT_optimize   = 0x00000400;
// const unsigned int RXOPT_collate   = 0x00000800;

unsigned int REGX_FLAGS = 0;
unsigned char OPTION_FLAGS = DEFAULTS;

//regex::flag_type t;

// std::map<std::string, regex::flag_type> enum_map = {
//     {"ECMAScript", regex::ECMAScript}, 
//     // {"basic ", regex::basic },
//     // {"extended", regex::extended},
//     // {"awk", regex::awk},
//     // {"grep", regex::grep}, 
//     // {"egrep", regex::egrep},
//     // {"icase", regex::icase},
//     // {"nosubs", regex::nosubs},
//     // {"optimize", regex::optimize},
//     // {"_collate", regex::collate_}
// };

std::map<std::string, int> enum_map = {
    {"ECMAScript", ECMAScript}, 
    {"basic ", basic },
    {"extended", extended},
    {"awk", awk},
    {"grep", grep}, 
    {"egrep", egrep},
    {"icase", icase},
    {"nosubs", nosubs},
    {"optimize", optimize},
    {"collate", collate}
};


string strECMAScript = "ECMAScript";
string strbasic = "basic";
string strextended = "extended";
string strawk = "awk";
  
  

#endif
