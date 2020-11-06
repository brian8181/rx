#include "rx.hpp"
#include "../config.h"
#include <iostream>

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#define BUFFERSIZE 100

int
main(int argc, char* argv[])
{
    termios t;
    if (tcgetattr(STDIN_FILENO, &t) < 0)
    { 
        char buffer[255]; // buffer for pipe  
        scanf("%s", (char*)&buffer);

        char* argv_tmp[255];
        
        // can't I just assing the beg address?
        //argv_tmp = argv;
		//argv_tmp[0] = argv[0];

        for(int i =0; i < argc; ++i)
        {
            argv_tmp[i] = argv[i];
        }
        argv_tmp[argc] = buffer;

        //argv = &argv_tmp;
        return parse_options(++argc, argv_tmp);
    }
     
    return parse_options(argc, argv);
}

// 11052020 

// [brian@monster-island src]$ echo "t1" | ./rx
// Read: t1
// arg[0]: ./rx
// [brian@monster-island src]$ echo "t1" | ./rx abc
// Read: t1
// arg[0]: ./rx
// arg[1]: abc
