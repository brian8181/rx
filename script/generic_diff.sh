ROOT=/home/brian/src/rx
FULL_NAME=$ROOT/src/$1
NAME=src/$1
LIDX=$2
RIDX=$3
EXEC=~/script/git/git_diff.sh
EXEC_PARAMS="$4"

echo "Debug: ROOT:$ROOT NAME:${FULL_NAME##/*/} FULL_NAME:$FULL_NAME LIDX:$LIDX RIDX:$RIDX"

LHASH=$(~/script/git/git_hist.sh $FULL_NAME | egrep "^\s{4,5}$LIDX\s" | cut -d'|' -f'2 13' | sed s/\|/~/)
RHASH=$(~/script/git/git_hist.sh $FULL_NAME | egrep "^\s{4,5}$RIDX\s" | cut -d'|' -f'2 13' | sed s/\|/~/)


echo "Debug: EXEC:"$EXEC" $NAME-LHASH:$LHASH $NAME-RHASH:$RHASH"

$EXEC $FULL_NAME $LHASH $RHASH "$EXEC_PARAMS"
