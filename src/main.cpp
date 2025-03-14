#include <iostream>
#include <cstring>
#include <string>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>         /* for STDIN_FILENO */
#include <sys/select.h>     /* for pselect   */

#include <getopt.h>
#include "rx.hpp"

int stdin_ready (int filedes)
{
	fd_set set;
	// declare/initialize zero timeout
#ifndef CYGWIN
	//struct timespec timeout = { .tv_sec = 0 };
#else
	struct timeval timeout = { .tv_sec = 0 };
#endif
	// initialize the file descriptor set
	FD_ZERO(&set);
	FD_SET(filedes, &set);

	// check stdin_ready is ready on filedes
#ifndef CYGWIN
		return pselect(filedes + 1, &set, NULL, NULL, &timeout, NULL);
#else
		return select(filedes + 1, &set, NULL, NULL, &timeout);
#endif
}

int main(int argc, char* argv[])
{
	try
	{
		if(stdin_ready(STDIN_FILENO))
		{
			std::string buffer;
			std::cin >> buffer;
			// add piped buffer to end of argv
			char* argvtmp[sizeof(char*) * argc+1];
			memcpy(argvtmp, argv, sizeof(char*) * argc);
			argvtmp[argc] = &buffer[0];
			argv = argvtmp;
			++argc;
		}
		return parse_options(argc, argv);
	}
	catch(std::logic_error& ex)
	{
	 	std::cout << ex.what() << std::endl;
	}
}
