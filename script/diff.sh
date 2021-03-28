ROOT=/home/brian/src/rx
FULL_NAME=$ROOT/$NAME
NAME=$1
LIDX=$2
RIDX=$3
#EXEC=~/script/git/generic_diff.sh
EXEC_PARAMS="diff -y"

./generic_diff.sh $NAME $LIDX $RIDX "$EXEC_PARAMS"
