/*
 * GNU Typist  - interactive typing tutor program for UNIX systems
 *
 * Copyright (C) 2003, 2004, 2008, 2009, 2011, 2012, 2013, 2014, 2016,
 *               2017, 2018, 2019, 2020
 *               Hynek Hanke, Paul Goins, Felix Natter, Tim Marston,
 *               Mihai Gătejescu
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

//	Header for some interface details.
#ifndef GTYPIST_H
#define GTYPIST_H

/* some screen positions */
#define	MESSAGE_LINE	(LINES - 1)
#define B_TOP_LINE		0
#define T_TOP_LINE		(B_TOP_LINE + 1)
#define I_TOP_LINE		(T_TOP_LINE)
#define DP_TOP_LINE		(I_TOP_LINE + 2)

// Color pairs used
enum
{
   C_NORMAL = 1,	// used by default
   C_BANNER,	// for the top banner
   C_PROG_NAME,	// for the program's name
   C_PROG_VERSION,	// for the program's version
   C_MENU_TITLE
};

/* shortcuts for reverse/normal mode strings */
#define ADDSTR(X) wideaddstr(X)
#define ADDSTR_REV(X) wideaddstr_rev(X)
#define ADDCH(X) wideaddch(X)
#define ADDCH_REV(X) wideaddch_rev(X)

/* get the path to the ~/.gtypistrc config file */
const char *get_config_filename();


#endif /* GTYPIST_H */
