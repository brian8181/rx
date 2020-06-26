# Process this file with autoconf to produce a configure script.

AC_INIT([rx], [1.0], [brian8181@gmail.com])
AC_PREREQ([2.68])

# Enable "automake" to simplify creating makefiles:
AM_INIT_AUTOMAKE([1.11 -Wall -Werror])

AC_CONFIG_SRCDIR([src/main.cpp])


# Put configuration results here, so we can easily #include them:
AC_CONFIG_HEADERS([config.h])
# Put autotools auxiliary files in a subdir, so they don't clutter top dir:
AC_CONFIG_AUX_DIR([build-aux])

#AC_CONFIG_MACRO_DIRS([m4])


# Checks for programs.
AC_PROG_CXX
#AC_PROG_CC

# Checks for libraries.
# LT_INIT
# AC_ENABLE_SHARED
# AC_DISABLE_STATIC
# AC_PROG_LIBTOOL(libtool)

# Checks for typedefs, structures, and compiler characteristics.
# AC_HEADER_STDBOOL
# AC_C_INLINE
# AC_TYPE_SIZE_T

# Output Makefile files.
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
