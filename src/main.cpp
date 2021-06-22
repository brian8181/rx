#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <termios.h>
#include "main.hpp"

using std::cin;
using std::string;

int main(int argc, char* argv[])
{
	termios t;
	if (tcgetattr(STDIN_FILENO, &t) < 0)
	{
		string buffer;
		cin >> buffer;
		// add piped buffer to end of argv
		char* argvtmp[sizeof(char*) * argc+1];
		memcpy(argvtmp, argv, sizeof(char*) * argc);
		argvtmp[argc] = &buffer[0];
		argv = argvtmp;
		return parse_options(++argc, argv);
	}
	return parse_options(argc, argv);
}
