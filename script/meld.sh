#!/usr/bin/bash

FILE='meld.sh'
VERSION='version 0.1'
FILE_DATE='03-29-2021'

AUTHOR='<AUTHOR>'
EMAIL='<EMAIL>'
WWW='<WWW>'

FMT_FG_RED='\e[31m'
FMT_RESET='\e[0m'
PRINT_RED_DEBUG=${FMT_FG_RED}DEBUG${FMT_RESET}
DATE=$(date "+%H:%M:%S:%s")

# USER SETTING
DEBUG_MSG="$PRINT_RED_DEBUG: "
VERBOSE=1
DEBUG=1
# END

echo ${VERBOSE:+"File - $FILE"}.
echo ${VERBOSE:+"Version - $VERSION"}.
echo ${VERBOSE:+"Date - $FILE_DATE"}.
echo ${VERBOSE:+"Author - $AUTHOR"}.
echo ${VERBOSE:+"Email - $EMAIL"}.
echo ${VERBOSE:+"WWW - $WWW"}.

function PRINT_DEBUG
{
    MSG=${DEBUG_MSG}$1
    echo -e ${DEBUG:+"$MSG"}
}
PRINT_DEBUG "$FILE -> Running... @ $DATE"

# YOUR CODE
LIDX=$1
RIDX=$2
NAME=/home/brian/src/rx/src/$3
EXEC=meld

/home/brian/src/script/git/git_diff.sh "$NAME" "$LIDX" "$RIDX" meld

PRINT_DEBUG "$FILE -> Exiting. @ $DATE"
