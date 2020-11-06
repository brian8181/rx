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
    char buffer[255];
    struct termios t;
    if (tcgetattr(STDIN_FILENO, &t) < 0)
    {   
        scanf("%s", (char*)&buffer);
        //fprintf(stderr, "Read: %s\n", (char*)&buffer);

        char* argv_tmp[255];
        //argv_tmp = argv;
		//argv_tmp[0] = argv[0];

        for(int i =0; i < argc; ++i)
        {
            argv_tmp[i] = argv[i];
        }

        argv_tmp[argc] = buffer;

        argc++;
        //argv[0] = argv_tmp[0];
        return parse_options(argc, argv_tmp);
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
