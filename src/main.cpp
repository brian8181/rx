#include "rx.hpp"
#include "../config.h"
#include <iostream>

#define BUFFERSIZE 100

int main(int argc, char *argv[])
{
    // char buffer[BUFFERSIZE];
    // int ret = scanf("%s", buffer);
    // cout << buffer << endl;
   
    return parse_options(argc, argv);
}
