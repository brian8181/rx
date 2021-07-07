#### FAIL ####
./rx -s "*ab*c{2}" "abccxxxabcc"

./rx -vs "a*b*c{2}" "abccxxxabcc"

# invalid long option
./rx --babe abc abc

echo "abc!abc@abc$abc%abc^abc&abc*abc(abc)abc" | ./rx abc




#### PASS ####
../rx "(abc)*" abcXXabc
../rx \(abc\)* abcabc
../rx "(abc)*" abcabcabc

./rx -v -s "a*b*c{2}" "abccxxxabcc"

