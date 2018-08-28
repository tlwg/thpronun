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
AX_CXX_COMPILE_STDCXX_14
AM_PROG_LIBTOOL

# Checks for libraries.
PKG_CHECK_MODULES(LIBTHAI, libthai)
PKG_CHECK_MODULES(LIBDATRIE, datrie-0.2)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# Check commandline options
AC_ARG_ENABLE(debug,
              [AC_HELP_STRING([--enable-debug],
                              [enable assertion checks])],
              , enable_debug="no")
if test "x$enable_debug" = "xno"; then
  CPPFLAGS="$CPPFLAGS -DNDEBUG"
fi

AC_ARG_ENABLE(man,
              [AC_HELP_STRING([--disable-man],
                              [disable automatic manpage generation])])
if test "x$enable_man" != "xno"; then
  AC_PATH_PROG(HELP2MAN, help2man, false)
  if test "x$HELP2MAN" == "xfalse"; then
    AC_MSG_ERROR([You need help2man to generate manpage, or use --disable-man to skip.])
  fi
fi
AM_CONDITIONAL(ENABLE_MAN,test "x$enable_man" != "xno")

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
                 data/Makefile
                 parser/Makefile
                 parser/tests/Makefile
                 thpronun/Makefile
                 thpronun/tests/Makefile])
AC_OUTPUT
