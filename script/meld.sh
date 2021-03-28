#!/usr/bin/bash

FILE='meld.sh'
VERSION='0.1'
FILE_DATE='03-28-2012'

AUTHOR='Brian Preston'
EMAIL='brian8181@gmail.com'
GITHUB='https://github.com/brian8181'

VERBOSE=1
DEBUG=1
FMT_FG_RED='\e[31m'
FMT_RESET='\e[0m'

echo ${VERBOSE:+"File - $FILE"}
echo ${VERBOSE:+"Version - $VERSION"}
echo ${VERBOSE:+"Date - $FILE_DATE"}
echo ${VERBOSE:+"Author - $AUTHOR"}
echo ${VERBOSE:+"Email - $EMAIL"}
echo ${VERBOSE:+"GITHUB - $GITHUB"}

DATE=$(date "+%H:%M:%S:%s")
ROOT=/home/brian/src/rx
FULL_NAME=$ROOT/$NAME
NAME=$1
LIDX=$2
RIDX=$3

echo -e "${DEBUG:+${FMT_FG_RED}DEBUG${FMT_RESET} - Root=\"$ROOT\" FULL_NAME=\"$FULL_NAME\" NAME=\"$NAME\"}"
echo -e "${DEBUG:+${FMT_FG_RED}DEBUG${FMT_RESET} - LIDX=\"$LIDX\"  RIDX=\"$RIDX\"}"

# lanch diff in meld
EXEC_PARAMS="meld"

echo -e "${DEBUG:+${FMT_FG_RED}DEBUG${FMT_RESET} - $FILE -> Running... @ $DATE}"

# YOUR CODE GOES HERE
/home/brian/src/rx/script/generic_diff.sh "$NAME" "$LIDX" $RIDX "$EXEC_PARAMS" -verbose=1

echo -e "${DEBUG:+${FMT_FG_RED}DEBUG${FMT_RESET} - $FILE -> Exiting. @ $DATE}"
