#! /usr/bin/bash

ROOT=/home/brian/src/rx
FULL_NAME=$ROOT/src/$1
NAME=src/$1
LIDX=$2
RIDX=$3

echo "Debug: ROOT:$ROOT NAME:${FULL_NAME##/*/} FULL_NAME:$FULL_NAME LIDX:$LIDX RIDX:$RIDX"

LHASH=$(./hist.sh $FULL_NAME | egrep "^\s{4,5}$LIDX\s" | cut -d'|' -f2)
RHASH=$(./hist.sh $FULL_NAME | egrep "^\s{4,5}$RIDX\s" | cut -d'|' -f2)

echo "Debug: LHASH:$LHASH RHASH:$RHASH"
./diff.sh "$FULL_NAME" "$LHASH" "$RHASH" -y



