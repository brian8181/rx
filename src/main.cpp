#include <iostream>
#include <cstring>
#include <unistd.h>
#include <termios.h>
#include "rx.hpp"
#include "../config.h"

int
main(int argc, char* argv[])
{
    termios t;
    if (tcgetattr(STDIN_FILENO, &t) < 0)
    { 
        // get input from pipe
        char buffer[BUFFER_LEN]; // buffer for pipe  
        cin >> buffer;

        // add piped buffer to end of args
        // note: create array of char*, number of char* is argc
        // char* argv_tmp[] = new char* [argc];
        char* argv_tmp[BUFFER_LEN];
        memcpy(argv_tmp, argv, sizeof(char*) * argc);
        argv_tmp[argc] = buffer;

        //argv = &argv_tmp;
        return parse_options(++argc, argv_tmp);
    }
    return parse_options(argc, argv);
}

// output
// $ echo abc | ./rx abc
// pattern: "abc" -> input: "abc"

// 0: abc

// Found 1 matches:
// abc
