#! /usr/bin/bash

ROOT=/home/brian/src/rx
FULL_NAME=$ROOT/$NAME
NAME=$1
LIDX=$2
RIDX=$3

# lanch diff in diff
EXEC_PARAMS="diff -y"

./generic_diff.sh $NAME $LIDX $RIDX "$EXEC_PARAMS"