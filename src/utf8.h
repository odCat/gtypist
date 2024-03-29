/*
 * GNU Typist  - interactive typing tutor program for UNIX systems
 *
 * Copyright (C) 2011, 2012, 2013, 2014, 2016, 2017, 2018, 2019
 *               2020 Felix Natter, Tim Marston, Mihai Gătejescu
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

#ifndef UTF8_H
#define UTF8_H

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <wchar.h>

/*
   ncurses' KEY_BACKSPACE (0x107) collides with polish "c with acute (0x107)
   => we need to encode KEY_BACKSPACE!
*/
#define GTYPIST_KEY_BACKSPACE 0x0008


extern wchar_t* widen(const char* text);
extern char* convertUTF8ToCurrentEncoding(const char* UTF8Input);
extern wchar_t* convertFromUTF8(const char* UTF8Text);
extern void mvwideaddstr(int y, int x, const char* UTF8Text);
extern void wideaddstr(const char* UTF8Text);
extern void wideaddstr_rev(const char* UTF8Text);
extern void wideaddch(wchar_t c);
extern void wideaddch_rev(wchar_t c);
extern int utf8len(const char* UTF8Text);
extern int iswideupper(wchar_t c);
extern wchar_t towideupper(wchar_t c);
extern int get_widech(int* c);

#endif /* !UTF8_H */
