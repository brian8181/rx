echo "Standard test 1:"
../build/rx abc abc

echo "Ignore Case 1:"
../build/rx -i abc ABC

echo "Ignore Case 2:"
../build/rx -i ABC abc

echo "Ignore Case 3:"
../build/rx -i abc ABCabc abcxABCxabc ABCyabcyABC


