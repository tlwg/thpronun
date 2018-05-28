#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([thpronun],
        m4_esyscmd([build-aux/git-version-gen]),
        [theppitak@gmail.com])
AC_CONFIG_SRCDIR([sylstring/sylcomp.h])
AC_CONFIG_AUX_DIR(build-aux)
AC_CONFIG_MACRO_DIRS([m4])

AM_INIT_AUTOMAKE(dist-xz no-dist-gzip)

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AM_PROG_LIBTOOL

# Checks for libraries.
PKG_CHECK_MODULES(LIBTHAI, libthai)
PKG_CHECK_MODULES(LIBDATRIE, datrie-0.2)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 thortho/Makefile
                 thortho/tests/Makefile
                 sylstring/Makefile
                 sylstring/tests/Makefile
                 lattice/Makefile
                 lattice/tests/Makefile
                 output/Makefile
                 output/tests/Makefile
                 dict/Makefile
                 dict/tests/Makefile
                 parser/Makefile
                 parser/tests/Makefile
                 thpronun/Makefile])
AC_OUTPUT
