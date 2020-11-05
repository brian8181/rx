#include "rx.hpp"
#include "../config.h"
#include <iostream>

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#define BUFFERSIZE 100

int
main(int argc, char** argv)
{
    char buffer[10];
    struct termios t;
    if (tcgetattr(STDIN_FILENO, &t) < 0)
    {   
        scanf("%s", (char*)&buffer);
        fprintf(stderr, "Read: %s\n", (char*)&buffer);
    }
    else
    {
        //fprintf(stderr, "no pipe found \n");
        return parse_options(argc, argv);
    }

    for(int i = 0; i < argc; ++i)
    {
        printf("arg[%d]: %s\n", i, argv[i]);
    }
      
    return 0; 
    //return parse_options(argc, argv);
}

// 11052020 

// output 1

// [brian@monster-island src]$ echo "t1" | ./rx
// Read: t1
// arg[0]: ./rx
// [brian@monster-island src]$ echo "t1" | ./rx abc
// Read: t1
// arg[0]: ./rx
// arg[1]: abc

// ouput 2

// [brian@monster-island src]$ ./rx a{2}b{3}c{5} aabbbccccc
// pattern: "a{2}b{3}c{5}" -> input: "aabbbccccc"

// 0: aabbbccccc

// Found 1 matches:
// aabbbccccc

// [brian@monster-island src]$ echo "test" | ./rx a{2}b{3}c{5} aabbbccccc
// Read: test
// arg[0]: ./rx
// arg[1]: a{2}b{3}c{5}
// arg[2]: aabbbccccc
// [brian@monster-island src]$ echo "test" | ./rx a{2}b{3}c{5}
// Read: test
// arg[0]: ./rx
// arg[1]: a{2}b{3}c{5}
