
touch Money.h MoneyTest.h MoneyTest.cpp
aclocal -I /usr/share/aclocal
autoconf
automake -a
touch NEWS README AUTHORS ChangeLog # To make automake happy
./configure
make check