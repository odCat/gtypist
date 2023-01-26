## This file is part of GNU Typist
##
## Copyright (C) 2001, 2002, 2003 Simon Baldwin (simonb@sco.com)
## Copyright (C) 2003, 2004, 2008, 2009, 2011, 2012, 2013, 2014, 2016,
##               2017, 2018, 2019, 2020
##               Michael Opdenacker, Hynek Hanke, Paul Goins, Tim Marston,
##               Mihai Gătejescu
## Copyright (C) 2021, 2022, 2023 Felix Natter, Mihai Gătejescu
##
## GNU Typist is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## GNU Typist is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with GNU Typist.  If not, see <http://www.gnu.org/licenses/>.

## Process this file with automake to produce Makefile.in

info_TEXINFOS=gtypist.texi gtypist.cs.texi gtypist.es.texi
gtypist_TEXINFOS=gpl.texi fdl.texi

EXTRA_DIST=gtypist.html gtypist.cs.html gtypist.es.html

html_docs=gtypist.html gtypist.cs.html gtypist.es.html

.texi.html:
	$(MAKEINFO) --html --no-split --no-headers -o gtypist.html gtypist.texi
	$(MAKEINFO) --html --no-split --no-headers -o gtypist.cs.html gtypist.cs.texi
	$(MAKEINFO) --html --no-split --no-headers -o gtypist.es.html gtypist.es.texi

all: info html

.PHONY: html
html: version.texi version2.texi version3.texi $(html_docs)

