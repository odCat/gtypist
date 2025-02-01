# Autoconf script for GNU Typist
# Process this file with autoconf to produce a configure script.

# Copyright (C) 2008, 2009, 2011, 2012, 2013, 2014, 2016,
#               2017, 2018, 2019, 2020
#               Felix Natter, Paul Goins, Tim Marston,
#               clutton, Mihai Gătejescu
# Copyright (C) 2021, 2022, 2023, 2025 Felix Natter, Mihai Gătejescu
#
# This file is a part of GNU Typist
#
# GNU Typist is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# GNU Typist is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Typist.  If not, see <http://www.gnu.org/licenses/>.

AC_INIT([GNU Typist],
        m4_bregexp(m4_include([version.sh]), [[0-9]+\.[0-9]+\.[0-9]+], [\&]),
        [bug-gtypist@gnu.org], [gtypist])
AM_INIT_AUTOMAKE([1.8.2 gnu dist-xz])
AC_CONFIG_SRCDIR([src/gtypist.c])
AM_CONFIG_HEADER([config.h])
AC_USE_SYSTEM_EXTENSIONS
AC_CANONICAL_HOST

# Checks for programs

AC_PROG_AWK
AC_PROG_CC
AC_ISC_POSIX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_YACC

# Set of available languages.

ALL_LINGUAS="cs de es eu fi fr nl pl ro ru tr zh_CN zh_TW"

# Checks for header files.

AC_HEADER_STDC
AC_CHECK_HEADERS([unistd.h alloca.h argz.h errno.h fcntl.h langinfo.h libintl.h limits.h locale.h malloc.h stddef.h stdio_ext.h stdlib.h string.h strings.h sys/param.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_C_VOLATILE
AC_TYPE_SIZE_T

# Checks for library functions.

AC_PROG_GCC_TRADITIONAL
AC_FUNC_ALLOCA
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_TYPE_SIGNAL
AC_FUNC_STRTOD
AC_CHECK_FUNCS([__argz_count __argz_next __argz_stringify dcgettext getcwd getwd mempcpy memset munmap nl_langinfo setlocale stpcpy strcasecmp strchr strcspn strdup strstr strtoul])

# check for libncursesw
case $host_os in
  *bsd* | darwin*)
    AC_DEFINE([OS_BSD], [1], [OS BSD's curses includes ncursesw])
    # check for courses.h
    AC_CHECK_HEADER(curses.h, [], [AC_MSG_ERROR(
      [curses.h header is missing: See INSTALL file for further information])])
    # check for libncursesw
    AC_CHECK_LIB(ncursesw, add_wch, [], [AC_MSG_ERROR(
      [ncursesw library is missing: See INSTALL file for further information])])
    ;;
  *)
    AC_CHECK_HEADER(ncursesw/ncurses.h, HAVE_NCURSESW_H=1)
    AC_CHECK_LIB(ncursesw, add_wch, HAVE_LIBNCURSESW=1)
    if test -n "$HAVE_NCURSESW_H" -a -n "$HAVE_LIBNCURSESW";  then
       LIBS="-lncursesw $LIBS"
    else
       echo -e "Error:  both library and header files for the ncursesw library\n"\
           "are required to build this package.  See INSTALL file for"\
           "further information. On Debian/Ubuntu you need to install libncursesw5-dev."
       exit 1;
    fi
    ;;
esac

AC_SEARCH_LIBS(cbreak, tinfo, [],
  [AC_MSG_ERROR([Can't find cbreak() in -lncursesw or -ltinfo])])


# iconv

AM_ICONV

# Internationalization macros

AM_GNU_GETTEXT_VERSION([0.18.2])
AM_GNU_GETTEXT(external)

# Manual page generation

GEN_MAN="help2man ./gtypist -o gtypist.1 -n 'a typing tutor with lessons for different keyboards and languages'"
AC_SUBST(GEN_MAN)

# This is necessary for tools/gtypist-mode.el

AM_PATH_LISPDIR

# Generate files

AC_CONFIG_FILES([lessons/Makefile tools/Makefile doc/Makefile src/Makefile
		Makefile po/Makefile.in m4/Makefile])
AC_OUTPUT
