#include <iostream>
#include <string>
#include <regex>
#include <getopt.h>
#include "rx.hpp"
#include <stdio.h>

static struct option long_options[] =
    {
        {"verbose", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        {"single", no_argument, 0, 's'}
    };

void 
print_help()
{
    std::cout << "\n"
         << FMT_BOLD << "rx" << FMT_RESET << " "
         << FMT_UNDERLINE << "PATTERN" << FMT_RESET << " "
         << FMT_UNDERLINE << "INPUT" << FMT_RESET << "\n\n";
}
        

int parse_options(int argc, char *argv[])
{
    int opt = 0;
    int option_index = 0;
    bool verbose_flag = false;
    bool single_flag = false;

    optind = 0;
    while ((opt = getopt_long(argc, argv, "hvs", long_options, &option_index)) != -1)
    {
        switch (opt)
        {
        case 'h':
            print_help();
            return 0;
        case 'v':
            verbose_flag = true;
            break;
        case 's':
            single_flag = true;
            break;
        default: // unknown option before args
    	    {
        	    fprintf(stderr, "Unexpected option, -h for help\n");
            	return EXIT_FAILURE;
        	}
	    }
    }

    if (optind <= (argc - DEFAULT_ARGC)) // not correct number of args
    {
        fprintf(stderr, "Expected argument after options, -h for help\n");
        exit(EXIT_FAILURE);
    }

    // single mode: mockup
    if (single_flag)
    {
        cout << "Single Match Mode" << endl;
    }

    if (verbose_flag)
    {
        print_help();
    }

    int current_idx = optind + 1;
    string src;
    string exp(argv[optind]);

    for (int i = current_idx; i < argc; ++i)
    {
        src = argv[i];

        cout << "pattern: "
             << "\"" << exp << "\""
             << " -> "
             << "input: "
             << "\"" << src << "\""
             << "\n\n";

        int idx = 0;
        string bash_str = src;
        regex src_epx(exp);
        auto begin = sregex_iterator(src.begin(), src.end(), src_epx);
        auto end = sregex_iterator();

        for (sregex_iterator i = begin; i != end; ++i)
        {
            smatch match = *i;
            int pos = match.position() + (idx * (CURRENT_FG_COLOR.length() + FMT_RESET.length()));
            int len = match.length();

            // set bash green start postion
            bash_str.insert(pos, CURRENT_FG_COLOR);

            // reset bash color position
            pos = pos + CURRENT_FG_COLOR.length() + len;
            bash_str.insert(pos, FMT_RESET);

            cout << idx << ": " << src.substr(match.position(), match.length()) << endl;
            ++idx;
        }
        cout << "\nFound " << std::distance(begin, end) << " matches:\n";
        cout << bash_str << "\n\n";
    }
    return EXIT_SUCCESS;
}

