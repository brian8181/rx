#!/usr/bin/bash

FILE='git_generic.sh'
VERSION='0.1'
DATE='03-28-2012'

AUTHOR='Brian Preston'
EMAIL='brian8181@gmail.com'
GITHUB='https://github.com/brian8181'

VERBOSE=$5
#DEBUG=1

echo ${VERBOSE:+"File - $FILE"}
echo ${VERBOSE:+"Version - $VERSION"}
echo ${VERBOSE:+"Date - $DATE"}
echo ${VERBOSE:+"Author - $AUTHOR"}
echo ${VERBOSE:+"Email - $EMAIL"}
echo ${VERBOSE:+"GITHUB - $GITHUB"}

ROOT=/home/brian/src/rx
FULL_NAME=$ROOT/src/$1
NAME=src/$1
LIDX=$2
RIDX=$3
EXEC_PARAMS="$4"

LHASH=$(~/script/git/git_hist.sh $FULL_NAME | egrep "^\s{4,5}$LIDX\s" | cut -d'|' -f'2 13' | sed s/\|/~/)
RHASH=$(~/script/git/git_hist.sh $FULL_NAME | egrep "^\s{4,5}$RIDX\s" | cut -d'|' -f'2 13' | sed s/\|/~/)

EXEC="/home/brian/src/script/git/git_diff.sh"
$EXEC "$FULL_NAME" "$LHASH" "$RHASH" "$EXEC_PARAMS"
