/*
 * GNU Typist  - interactive typing tutor program for UNIX systems
 *
 * Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003
 * 				 Simon Baldwin (simonb@sco.com)
 * Copyright (C) 2003, 2008, 2009, 2010, 2011, 2012, 2013, 2014
 *               2016, 2017, 2018, 2019, 2020
 *               Hynek Hanke, Paul Goind, Mihai Gătejescu
 * Copyright (C) 2021, 2022, 2023 Felix Natter, Mihai Gătejescu
 *
 * GNU Typist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNU Typist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Typist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ERROR_H
#define ERROR_H

extern void fatal_error (const char *message, const char *line);
extern char *argv0;

#endif /* !ERROR_H */
