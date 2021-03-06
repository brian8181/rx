AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = rx
#EXTRA_PROGRAMS = rx_test

#rx_SOURCES = src/main.cpp src/rx.cpp src/rx.hpp src/rx_test.cpp src/rx_test.hpp
rx_SOURCES = src/main.cpp src/rx.cpp src/rx.hpp

rx_LDADD = $(LDADD) $(DEPS_LIBS) $(ICONV_LIB) $(DL_LIBS)


#distdir = $(PACKAGE)-$(VERSION)

# EXTRA_DIST = README
# dist-hook:
#     chmod u+w $(distdir)/README
#     echo "Distribution date: `date`" >> $(distdir)/README

#         rm -f $(distdir)/doc/HACKING
# rx_test_SOURCES = src/rx_test.cpp src/rx_test.hpp

#man1_MANS = rx.1

#check_PROGRAMS = rx_test
#rx_test_program_SOURCES = src/rx_test.cpp src/rx_test.hpp

ACLOCAL_AMFLAGS = -I m4



