# Autoconf requirements
# Initialize, but use more options.  Note parameters brackets and whitespace.
AC_INIT([rx], [0.01], [brian8181@gmail.com], [rx], [http://brian8181.com])

# Force autoconf to be at least this version number:
AC_PREREQ([2.68])
# Safety check - list a source file that wouldn't be in other directories:
AC_CONFIG_SRCDIR([src/main.cpp])
# Put configuration results here, so we can easily #include them:
AC_CONFIG_HEADERS([config.h])
# Put autotools auxiliary files in a subdir, so they don't clutter top dir:
AC_CONFIG_AUX_DIR([build-aux])

# ======================================
# Check for various headers and settings
# ======================================
AC_CHECK_HEADERS([netinet/in.h])

AC_CONFIG_MACRO_DIRS([m4])
# AC_CHECK_FUNCS([memset])
# AC_CHECK_HEADERS([netinet/in.h])
AC_CHECK_HEADER_STDBOOL
AC_PROG_INSTALL
#AC_CONFIG_MACRO_DIRS



# Enable "automake" to simplify creating makefiles:
AM_INIT_AUTOMAKE([])
AC_CONFIG_FILES([Makefile])
AC_PROG_CXX
AC_PROG_CPP

# Perhaps check for: (more) programs, libraries, header files, types,
# structures, compiler characteristics, library functions, system services.

# Do final output.
AC_OUTPUT
