#!/bin/bash

echo "Testing..."
../build/rx abc abc abc abc
echo "Testing..."
../build/rx abc abcxabc abcxabcyabc abcxabcabcyabcabczabc
echo "0000063: Pipe Causes Segmentation Fault"
echo abcxabcyabc | ../build/rx abc abc
echo "TESTING INPUT-> ../build/rx -o 'basic|awk|grep|icase' abc ABC" 
../build/rx -o 'basic|awk|grep|icase' abc ABC
echo "TESTING INPUT-> ../build/rx -o 'icase' abc ABCxabcxABC"
../build/rx -o 'icase' abc ABCxabcxABC
echo "TESTING INPUT-> ../build/rx -o 'basic|awk|grep|icase' abc ABCxabcxABC ABCvabcvABCs" 
../build/rx -o 'basic|awk|grep|icase' abc ABCxabcxABC ABCvabcvABCs
echo "TESTING INPUT-> ../build/rx -o 'basic|awk|grep' abc ABCxabcxABC ABCvabcvABCs" 
../build/rx -o 'basic|awk|grep' abc ABCxabcxABC ABCvabcvABCs
echo "TESTING INPUT-> ./rx abc -f ../test/fopt.txt"
../build/rx abc -f ../test/fopt.txt
echo "TESTING INPUT-> ./rx abc -x ../test/exp_fopt.txt abcxabcxyzedf"
../build/rx abc -x ../test/exp_fopt.txt abcxabcxyzedf
echo "TESTING INPUT-> ./rx abc -x ../test/exp_fopt.txt -f ../test/search_fopt.txt"
../build/rx abc -x ../test/exp_fopt.txt -f ../test/search_fopt.txt
echo "TESTING email ..."
../build/rx \([a-z0-9_\.-]+\)@\([a-z0-9_\.-]+\)\\.\([a-z\]\{2,6\}\)$ brian@abc.com