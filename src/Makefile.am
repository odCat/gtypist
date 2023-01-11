# This file is part of GNU Typist
#
# Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003
#               Simon Baldwin (simonb@sco.com)
# Copyright (C) 2003, 2004, 2008, 2009, 2011, 2012, 2013, 2014, 2016
#               2017, 2018, 2019, 2020
#               Hynek Hanke, Tim Marston, Felix Natter, Mihai Gătejescu
# Copyright (C) 2021, 2022, 2023 Felix Natter, Mihai Gătejescu
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

## Process this file with automake to produce Makefile.in

#
#	NOTE:  this file will probably be changed by gettextize, so don't
#	commit changed version into CVS.
#



bin_PROGRAMS = gtypist
gtypist_SOURCES = gtypist.c cursmenu.c script.c error.c getopt.c getopt1.c		\
	infoview.c speedbox.c banner.c cmdline.c cursmenu.h error.h getopt.h		\
	gettext.h gtypist.h script.h utf8.c utf8.h infoview.h speedbox.h banner.h	\
	cmdline.h cmdline.ggo
gtypist_LDADD = @LIBINTL@ @LIBICONV@

AM_CPPFLAGS = -I../intl \
  -DDATADIR=\"$(pkgdatadir)\" \
  -DLOCALEDIR=\"$(datadir)/locale\"

# build cmdline.{c,h} from cmdline.ggo

cmdline.c cmdline.h: cmdline.ggo
	gengetopt < $<

gtypist.c: cmdline.h

# GEN_MAN is a shell command that generates the man page

man_MANS = gtypist.1

GEN_MAN=@GEN_MAN@

gtypist.1: gtypist.c gtypist
	if (test ! -e gtypist.1) then $(GEN_MAN); fi

CLEANFILES = gtypist.1
