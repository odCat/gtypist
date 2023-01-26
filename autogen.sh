#!/bin/sh
### autogen.sh - tool to help build GNU Typist from a repository checkout

# Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003
#               Simon Baldwin (simonb@sco.com)
# Copyright (C) 2003, 2004, 2008, 2009, 2011, 2012, 2013, 2014, 2016,
#               2017, 2018, 2019, 2020
#               Michael Opdenacker, Hynek Hanke, Dmitry Rutsky, Paul Goins,
#               Tim Marston, Felix Natter
# Copyright (C) 2021, 2022, 2023 Felix Natter, Mihai Gătejescu

# This file if a part of GNU Typist

# GNU Typist is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# GNU Typist is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with GNU Typist.  If not, see <http://www.gnu.org/licenses/>.

### Commentary

# Run this program to build the configuration
# files for GNU Typist:
# [*/]Makefile.in, aclocal.m4, configure,
# config.h.in, config.sub, config.guess
# INSTALL, configure-w32, doc/gtypist.info, lessons/gtypist.typ
# (maybe more)

echo "Checking for required tools..."

(autoconf --version) < /dev/null > /dev/null 2>&1 || {
    echo
    echo "**Error**: You must have \`autoconf' installed"
    echo "Get ftp://ftp.gnu.org/gnu/autoconf/autoconf-2.57.tar.bz2"
    echo "(or a newer version if it is available)"
    exit 1
}

(automake --version) < /dev/null > /dev/null 2>&1 || {
    echo
    echo "**Error**: You must have \`automake' installed."
    echo "Get ftp://ftp.gnu.org/gnu/automake/automake-1.7.7.tar.bz2"
    echo "(or a newer version if it is available)"
    exit 1
}

(gettext --version) < /dev/null > /dev/null 2>&1 || {
    echo
    echo "**Error**: You must have \`gettext' installed."
    echo "Get ftp://ftp.gnu.org/gnu/gettext/gettext-0.12.1.tar.gz"
    echo "(or a newer version if it is available)"
    exit 1
}

(autopoint --version) < /dev/null > /dev/null 2>&1 || {
    echo
    echo "**Error**: You must have \`autopoint' (part of gettext) installed."
    echo "Get ftp://ftp.gnu.org/gnu/gettext/gettext-0.12.1.tar.gz"
    echo "(or a newer version if it is available)"
    exit 1
}

(help2man --version) < /dev/null > /dev/null 2>&1 || {
    echo
    echo "**Error**: You must have \`help2man' installed."
    echo "Get ftp://ftp.gnu.org/gnu/help2man/help2man_1.33.1.tar.gz"
    echo "(or a newer version if it is available)"
    exit 1
}

(makeinfo --version) < /dev/null > /dev/null 2>&1 || {
    echo
    echo "**Error**: You must have \`texinfo' installed."
    echo "Get ftp://ftp.gnu.org/gnu/texinfo/texinfo-4.6.tar.bz2"
    echo "(or a newer version if it is available)"
    exit 1
}

# Copy gettext.h from gettext install

gettext_exe=`which gettext`
gettext_bin=`dirname $gettext_exe`
gettext_home=`dirname $gettext_bin`
gettexth=$gettext_home/share/gettext/gettext.h
if [ ! -r "$gettexth" ]; then
   echo "Couldn't find gettext.h"
   echo "Looking for gettext.h in /usr/ ..."
   gettexth=`find /usr/ -name gettext.h -print`
fi
if [ ! -r "$gettexth" ]; then
    echo
    echo "**Error**: Can not find gettext.h on your system."
    echo "Get ftp://ftp.gnu.org/gnu/gettext/gettext-0.12.1.tar.gz"
    echo "(or a newer version if it is available)"
    exit 1
fi

echo "Copying gettext.h from $gettexth"
cp $gettexth src/

# Generate lesson menus
(gawk --version) < /dev/null > /dev/null 2>&1 || {
    echo
    echo "**Error**: The git version requires \`gawk' (awk won't do)."
    echo "This is needed to build lessons/gtypist.typ."
    echo "Write to bug-gtypist@gnu.org if you have problems with this."
    exit 1
}
echo "creating lessons/gtypist.typ..."
(cd lessons && gawk -f ../tools/typcombine q.typ r.typ t.typ v.typ u.typ d.typ c.typ m.typ s.typ n.typ > gtypist.typ)

VERSION=`./version.sh`

for file in configure-w32 INSTALL
  do
  echo "creating $file..."
  if test $file -nt ${file}.in; then
      echo "*** \"$file\" has been modified,"
      echo "but it is generated from ${file}.in."
      echo "Please apply the changes to ${file}.in instead."
      exit -1;
  fi
  sed "s/@VERSION/$VERSION/g" ${file}.in > $file
  # TODO: this causes cvs to think that ${file}.in was modified...
  # solution: use a "stamp" file for each $file ?
  touch ${file}.in
done

# Add gettext infrastructure.
echo "running autopoint..."
autopoint

# Build configuration files

echo "creating build configuration files..."
aclocal -I m4
autoheader
automake --add-missing

if [ $? != 0 ]; then
    echo ""
    echo "Automake wasn't able to generate the necessary files like"
    echo "config.sub, config.guess, etc. needed for compilation"
    echo "You can copy them from some other place, but it's better"
    echo "to investigate why automake --add-missing failed, so that"
    echo "it doesn't cause some obscure problems later."
    echo "After pressing ENTER, the process will continue, but"
    echo "you can use CONTROL-C to interrupt it."
    read
fi

autoconf
if [ $? != 0 ]; then
    echo -e \
    	"--------------------------------------------------------------------" \
    	"\nSomething was wrong, autoconf failed." \
	"\nConsult notes on how to build if from git in the README.git file," \
	"\nif you don't know how to resolve this."
    exit 1
fi


if test -z "$*"; then
    echo
    echo "**Warning**: I am going to run \`configure' with no arguments."
    echo "If you wish to pass any to it, please specify them on the"
    echo \'$0\'" command line."
fi

echo
echo running ./configure "$@"...
echo
./configure "$@"

# Run make

make

# Create the source packages

make dist

