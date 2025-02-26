/*
 * GNU Typist  - interactive typing tutor program for UNIX systems
 *
 * Copyright (C) 2012, 2013, 2014, 2016, 2017, 2018, 2019, 2020
 *               Tim Marston, clutton, Mihai Gătejescu
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

#include "config.h"
#include <string.h>
#include <stdlib.h>

#if defined(HAVE_PDCURSES) || defined(OS_BSD)
    #include <curses.h>
#elif defined(HAVE_NCURSES)
    #include <ncurses.h>
#else
    #include <ncursesw/ncurses.h>
#endif

#include "speedbox.h"
#include "utf8.h"

#include "gettext.h"
#define _(String) gettext (String)

// shortcuts for reverse/normal mode strings
#define ADDSTR(X) wideaddstr(X)
#define ADDSTR_REV(X) wideaddstr_rev(X)
#define ADDCH(X) wideaddch(X)
#define ADDCH_REV(X) wideaddch_rev(X)

// constants
#define	SPEED_LINE		 (LINES - 5)
#define MAX_DISPLAY_COLS 1024
#define MAX_DISPLAY_ROWS 64


/*
  Draw the speed box
*/
void do_speed_box( int total_chars, int error_chars,
				   double cpm, double adjusted_cpm, bool scoring_cpm,
				   bool had_best_speed, bool new_best_speed, double best_cpm )
{
  char *messages[ MAX_DISPLAY_COLS ];
  int num_messages = 0;
  char buffer[ MAX_DISPLAY_COLS ], spaces[ MAX_DISPLAY_COLS ];
  int max_len = 0;
  int a, b, len;
  char *p;

  /* set up display strings */
  static char *SPEED_RAW_WPM, *SPEED_RAW_CPM, *SPEED_ADJ_WPM, *SPEED_ADJ_CPM,
	  *SPEED_PCT_ERROR, *SPEED_BEST_WPM, *SPEED_BEST_CPM, *SPEED_BEST_NEW_MSG;
  static bool first_time = TRUE;
  if( first_time ) {
	  first_time = FALSE;
	  /* TRANSLATORS: a '|' character in this message divides it in to two
	   * halves, which are aligned to the left and right sides of the dialog */
	  SPEED_RAW_WPM = _("Raw speed|= %6.2f wpm");
	  /* TRANSLATORS: a '|' character in this message divides it in to two
	   * halves, which are aligned to the left and right sides of the dialog */
	  SPEED_RAW_CPM = _("Raw speed|= %7.2f cpm");
	  /* TRANSLATORS: a '|' character in this message divides it in to two
	   * halves, which are aligned to the left and right sides of the dialog */
	  SPEED_ADJ_WPM = _("Adjusted speed|= %6.2f wpm");
	  /* TRANSLATORS: a '|' character in this message divides it in to two
	   * halves, which are aligned to the left and right sides of the dialog */
	  SPEED_ADJ_CPM = _("Adjusted speed|= %7.2f cpm");
	  /* TRANSLATORS: a '|' character in this message divides it in to two
	   * halves, which are aligned to the left and right sides of the dialog */
	  SPEED_PCT_ERROR = _("|with %.1f%% errors");
	  /* TRANSLATORS: a '|' character in this message divides it in to two
	   * halves, which are aligned to the left and right sides of the dialog */
	  SPEED_BEST_WPM = _("Personal best|= %6.2f wpm");
	  /* TRANSLATORS: a '|' character in this message divides it in to two
	   * halves, which are aligned to the left and right sides of the dialog */
	  SPEED_BEST_CPM = _("Personal best|= %7.2f cpm");
	  /* TRANSLATORS: a '|' character in this message divides it in to two
	   * halves, which are aligned to the left and right sides of the dialog */
	  SPEED_BEST_NEW_MSG = _("|new personal best");
  }

  /* build a list of messages to display */
  if( scoring_cpm )
    sprintf( buffer, SPEED_RAW_CPM, cpm );
  else
    sprintf( buffer, SPEED_RAW_WPM, cpm / (double)5.0 );
  messages[ num_messages++ ] = strdup( buffer );
  if( scoring_cpm )
    sprintf( buffer, SPEED_ADJ_CPM, adjusted_cpm );
  else
    sprintf( buffer, SPEED_ADJ_WPM, adjusted_cpm / (double)5.0 );
  messages[ num_messages++ ] = strdup( buffer );
  sprintf( buffer, SPEED_PCT_ERROR,
           (double)100.0 * (double)error_chars / (double)total_chars );
  messages[ num_messages++ ] = strdup( buffer );
  if( had_best_speed )
  {
    if( scoring_cpm )
    sprintf( buffer, SPEED_BEST_CPM, best_cpm );
    else
    sprintf( buffer, SPEED_BEST_WPM, best_cpm / (double)5.0 );
	  messages[ num_messages++ ] = strdup( buffer );
  }
  if( new_best_speed )
	  messages[ num_messages++ ] = strdup( SPEED_BEST_NEW_MSG );

  /* calculate the length of the longest message s daisadias disajd oajdoisajd
   * oisajd oisad oisajd oisajd */
  for( a = 0; a < num_messages; a++ )
  {
	  /* the length of the string may include a '|' which we include because it
	   * will need to be replaced with at least one space, unless one of the
	   * string's halves is empty, in which case no space would be added */
	  len = utf8len( messages[ a ] );
	  p = strchr( messages[ a ], '|' );
	  if( p && ( p == messages[ a ] || *( p + 1 ) == '\0' ) )
		  len--;

	  if( len > max_len ) max_len = len;
  }

  /* adjust all the messages */
  for( a = 0; a < num_messages; a++ )
  {
	  /* figure out if the string contains a '|' and, if it does, replace it
	   * for a null-terminator to separate the halves */
	  p = strchr( messages[ a ], '|' );
	  if( p ) *p = '\0';

	  /* calculate the length of the displayed string(s) */
	  len = utf8len( messages[ a ] ) + ( p? utf8len( p + 1 ) : 0 );

	  /* create padding */
	  spaces[ 0 ] = '\0';
	  for( b = 0; b < max_len - len; b++ )
		  strcat( spaces, " " );

	  /* adjust the message */
	  sprintf( buffer, " %s%s%s ", messages[ a ], spaces, p? p + 1 : "" );
	  free( messages[ a ] );
	  messages[ a ] = strdup( buffer );
  }

  /* display the messages */
  for( a = 0; a < num_messages; a++ ) {
	  move( LINES - num_messages + a - 2, COLS - max_len - 3 );
	  ADDSTR_REV( messages[ a ] );
  }

  /* cleanup */
  for( a = 0; a < num_messages; a++ )
	  free( messages[ a ] );
}
