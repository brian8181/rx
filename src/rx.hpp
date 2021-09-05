#ifndef _RX_HPP
#define _RX_HPP

#include <string>
#include <map>

using std::map;
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


int regx_match(int count, char* args[]);

//enum syntax_option_type
  //  {    // specify RE syntax rules
        const unsigned int ECMAScript = 0x00000001
        const unsigned int basic = 0x00000002;
        const unsigned int extended = 0x00000004;
        const unsigned int awk = 0x00000008;
        const unsigned int grep = 0x00000010;
        const unsigned int egrep = 0x00000020;
        const unsigned int gmask = 0x0000003F;
        const unsigned int icase = 0x00000100;
        const unsigned int nosubs = 0x00000200;
        const unsigned int optimize = 0x00000400;
        const unsigned int collate_ = 0x00000800
    //};

//syntax_option_type option_flags = DEFAULTS; 

std::map<std::string, unsigned int> enum_map = 
{{"ECMAScript", ECMAScript}, 
{"basic ", basic }
{"extended", extended}
{"awk", awk}
{"grep", grep}}
};


string ECMAScript = "ECMAScript";
string basic = "basic";
string extended = "extended";
string awk = "awk";

//m[1] = "test";
//m.insert(1, "s");
// std::pair<OS_type, string>(Windows, "Windows"),
// std::pai;r<OS_type, string>(Apple, "Apple"),
    
  

#endif
