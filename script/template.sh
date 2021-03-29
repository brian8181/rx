#!/usr/bin/bash

FILE='<FILE NAME>.sh'
VERSION='<VERSION.SUBVERSION>'
FILE_DATE='<DATE>'

AUTHOR='Brian Preston'
EMAIL='brian8181@gmail.com'
GITHUB='https://github.com/brian8181'

FMT_FG_RED='\e[31m'
FMT_RESET='\e[0m'
DATE=$(date "+%H:%M:%S:%s")
EXEC_PARAMS=${FILE%%.*}
VERBOSE=1
DEBUG=1

echo ${VERBOSE:+"File - $FILE"}.
echo ${VERBOSE:+"Version - $VERSION"}.
echo ${VERBOSE:+"Date - $FILE_DATE"}.
echo ${VERBOSE:+"Author - $AUTHOR"}.
echo ${VERBOSE:+"Email - $EMAIL"}.
echo ${VERBOSE:+"GITHUB - $GITHUB"}.

echo -e "${DEBUG:+${FMT_FG_RED}DEBUG${FMT_RESET} - $FILE -> Running... @ $DATE}".

# YOUR CODE GOES HERE

# END

echo -e "${DEBUG:+${FMT_FG_RED}DEBUG${FMT_RESET} - $FILE -> Exiting. @ $DATE}".
