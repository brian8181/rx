#### FAIL ####
../build/rx -s "*ab*c{2}" "abccxxxabcc"

../build/rx -vs "a*b*c{2}" "abccxxxabcc"

# invalid long option
../build/rx --babe abc abc

echo "abc!abc@abc$abc%abc^abc&abc*abc(abc)abc" | ../build/rx abc




#### PASS ####
../build/rx "(abc)*" abcXXabc
../build/rx \(abc\)* abcabc
../build/rx "(abc)*" abcabcabc

../build/rx -v -s "a*b*c{2}" "abccxxxabcc"


echo "Standard test 1:"
../build/rx abc abc abc abc
echo "Standard test 2:"
../build/rx abc abcxabc abcxabcyabc abcxabcabcyabcabczabc
echo "standard test 3"
echo abc | ../build/rx abc
echo "standard test 2"
echo 'abcxabc abcyabc' | ../build/rx abc

echo "TESTING INPUT-> ../build/rx -o 'basic|awk|grep|icase' abc abc" 
../build/rx -o 'basic|awk|grep|icase' abc abc

