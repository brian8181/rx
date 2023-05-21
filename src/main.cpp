#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>         /* for STDIN_FILENO */
#include <sys/select.h>     /* for pselect   */
#include <string>
#include <getopt.h>
#include "rx.hpp"
#include <signal.h>

int stdin_ready (int filedes)
{
	fd_set set;
	// struct timeval timeout2 = { .tv_sec = 0 };
	// sigset_t sset;
	// sigemptyset(&sset);
	// sigset_t origmask;
	// sigemptyset(&origmask);
	// pthread_sigmask(SIG_SETMASK, &sset, &origmask);
	// int ready = select(filedes + 1, &set, NULL, NULL, &timeout2);
	// pthread_sigmask(SIG_SETMASK, &origmask, NULL);
	// return ready;

	// declare/initialize zero timeout 
	struct timespec timeout = { .tv_sec = 0 };
	// initialize the file descriptor set
	FD_ZERO(&set);
	FD_SET(filedes, &set);
	// check stdin_ready is ready on filedes 
	return pselect(filedes + 1, &set, NULL, NULL, &timeout, NULL);
}

int main(int argc, char* argv[])
{
	try
	{
		char* argvtmp[(sizeof(char*) * argc)+1];
		if(stdin_ready(STDIN_FILENO))
		{
			std::string buffer;
			std::cin >> buffer;
			// add piped buffer to end of argv
			
			memcpy(argvtmp, argv, sizeof(char*) * argc);
			argvtmp[argc] = &buffer[0];
			argv = argvtmp;
			++argc;
			//return parse_options(argc, argv);
		}
		return parse_options(argc, argv);
	}
	catch(std::logic_error& ex)
	{
	 	std::cout << ex.what() << std::endl;
	}
}
