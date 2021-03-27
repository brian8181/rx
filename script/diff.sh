#! /usr/bin/bash

FULL_NAME=$1
LHASH=$2
RHASH=$3
SIDE_BY_SIDE=$4

echo "Debug: FULL_NAME:$FULL_NAME LHASH:$LHASH RHASH:$RHASH"

# clean up
#  d0c8a1a7c57559fca3f93f9458011e65ce65cbfb.tmp   
#  4774cf3632d9047af8d0c1b77cd503d677e4eb3e.tmp
#MASK=[0-9a-f]??????????????????????????????????????[0-9a-f].tmp
#rm $MASK

~/script/git_diff.sh $FULL_NAME $LHASH $RHASH $SIDE_BY_SIDE

