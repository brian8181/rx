
#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([rx], [0.01], [brian8181@gmail.com], [rx], [https://github.com/brian8181])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP

# Initialize libtool
LT_PREREQ([2.2])
LT_INIT

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lcppunit':
AC_CHECK_LIB([CPPUNIT_TEST], [main])

# Checks for header files.
AC_CHECK_HEADERS([netinet/in.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

AM_INIT_AUTOMAKE
# Checks for library functions.
AC_CONFIG_FILES([Makefile
                  src/Makefile])
AC_OUTPUT
