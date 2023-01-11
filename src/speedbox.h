/*
 * GNU Typist  - interactive typing tutor program for UNIX systems
 *
 * Copyright (C) 2012, 2013, 2014, 2016, 2017, 2018, 2019, 2020
 *               Tim Marston, Mihai Gătejescu
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
#ifndef SPEEDBOX_H
#define SPEEDBOX_H

void do_speed_box( int total_chars, int error_chars,
				   double cpm, double adjusted_cpm, bool use_cpm,
				   bool had_best_speed, bool new_best_speed, double best_cpm );

#endif /* SPEEDBOX_H */
