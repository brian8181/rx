#fail
./rx -s "*ab*c{2}" "abccxxxabcc"

./rx -vs "a*b*c{2}" "abccxxxabcc"

#pass
../rx "(abc)*" abcXXabc
../rx \(abc\)* abcabc
../rx "(abc)*" abcabcabc

./rx -v -s "a*b*c{2}" "abccxxxabcc"

