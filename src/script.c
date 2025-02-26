/*
 * GNU Typist  - interactive typing tutor program for UNIX systems
 *
 * Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003
 * 				 Simon Baldwin (simonb@sco.com)
 * Copyright (C) 2003, 2004, 2008, 2009, 2011, 2012, 2013, 2014, 2016,
 *               2017, 2018, 2019, 2020
 *               Hynek Hanke, Dmitry Rutsky, Paul Goins, Felix Natter,
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
#include "script.h"

#if defined(HAVE_PDCURSES) || defined(OS_BSD)
    #include <curses.h>
#elif defined(HAVE_NCURSES)
    #include <ncurses.h>
#else
    #include <ncursesw/ncurses.h>
#endif

#include "error.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utf8.h"

#include "gettext.h"
#define _(String) gettext (String)

extern int isUTF8Locale;

int global_line_counter = 0;
struct label_entry *global_label_list[NLHASH];

// Nobody bothers to free this string at exit.
char *__last_label = NULL;

void __update_last_label (const char *label)
{
  if (__last_label)
     free (__last_label);
  __last_label = strdup (label);
  if (!__last_label)
  {
     perror ("strdup");
     fatal_error (_("internal error: strdup"), label);
  }
}

/*
  label hashing function - returns an index for the lists
*/
int hash_label( char *label )
{
  char	*p;				/* pointer through string */
  int	csum = 0;		/* sum of characters */

  /* hash by summing the characters and taking modulo of the
     number of hash lists defined */
  for ( p = label; *p != ASCII_NULL; p++ )
    csum += *p;
  return ( csum % NLHASH );
}

static int line_is_empty (const char *line)
{
  while (*line)
  {
    if (!isspace (*line))
       return 0;
    line ++;
  }

  return 1;
}

/*
  go through the file and convert it from UTF8, to make
  sure that all characters can be converted!
*/
void check_script_file_with_current_encoding( FILE *script )
{
  char line[MAX_SCR_LINE];

  get_script_line( script, line );
  while (! feof( script ))
  {
    wchar_t* lineConverted = convertFromUTF8(line);
    free(lineConverted);
    /* get the next script line */
    get_script_line( script, line );
  }
}

/*
  go through the file, index all the labels we can find and notice if
  we have a menu or not
*/
void build_label_index( FILE *script ) {
  char line[MAX_SCR_LINE];
  char *line_iterator;
  struct label_entry	*new_label = NULL;	/* new label entry */
  struct label_entry	*list_tail[NLHASH];	/* tail tracking */
  int	hash;					/* hash index */
  struct label_entry	*check_label;		/* pointer thru list */

  /* start at the file's beginning */
  rewind( script );
  global_line_counter = 0;

  /* initialize the hash lists */
  for ( hash = 0; hash < NLHASH; hash++ )
  {
    global_label_list[ hash ] = NULL;
    list_tail[ hash ] = NULL;
  }

  /* read until we get to eof */
  get_script_line( script, line );
  while (! feof( script ))
  {
    /* see if this is a label line */
    if ( SCR_COMMAND( line ) == C_LABEL )
    {

      /* note this label's position in the table;
         first, create a new list entry */
      new_label = malloc( sizeof(struct label_entry) );
      if ( new_label == NULL )
        fatal_error( _("internal error: malloc"), line );

      /* remove trailing whitespace from line */
      line_iterator = line + strlen(line) - 1;
      while (line_iterator != line && isspace(*line_iterator))
      {
        *line_iterator = '\0';
        --line_iterator;
      }

      /* check for spaces in the label (these are banned since 2.9 so that
         spaces can be used as field separators in the bestlog) */
      line_iterator = SCR_DATA( line );
      while( *line_iterator != '\0' )
      {
        if( *line_iterator == ' ' )
          fatal_error( _("label contains space"), line );
        ++line_iterator;
      }

      /* make some space for the label string */
      new_label->label =
        malloc( strlen( SCR_DATA( line )) + 1 );
      if ( new_label->label == NULL )
        fatal_error( _("internal error: malloc"), line );

      /* copy the data into the new structure */
      strcpy( new_label->label, SCR_DATA( line ));
      new_label->offset = ftell( script );
      new_label->line_count = global_line_counter;
      new_label->next = NULL;

      /* find the right hash list for the label */
      hash = hash_label( SCR_DATA( line ));

      /* search the linked list for the label, to
         see if it's already there - nice to check */
      for ( check_label = global_label_list[ hash ];
              check_label != NULL;
              check_label = check_label->next )
      {
        if ( strcmp( check_label->label, SCR_DATA( line )) == 0 )
          fatal_error( _("label redefinition"), line );
      }

      /* link everything together */
      if ( list_tail[ hash ] == NULL )
        global_label_list[ hash ] = new_label;
      else
        list_tail[ hash ]->next = new_label;
      list_tail[ hash ] = new_label;
    }

    /* get the next script line */
    get_script_line( script, line );
  }
}

/*
  get the next non-comment, non-blank line from the script file
  and check its basic format
*/
void get_script_line(FILE *script, char *line)
{
  /* get lines until not empty/comment, or eof found */
  do {
      if (NULL == fgets(line, MAX_SCR_LINE, script) && ferror(script))
          fatal_error(_("Error while reading file"), line);
      ++global_line_counter;
  } while (!feof(script) &&
              (line_is_empty(line) || SCR_COMMAND(line) == C_COMMENT ||
               SCR_COMMAND(line) == C_ALT_COMMENT)
          );

  /* if a line was read then check it */
  if (!feof(script))
  {
    /* Get rid of trailing spaces and newline */
    while(*line && isspace(line[strlen(line)-1]))
      line[strlen(line) - 1] = ASCII_NULL;

    // input is UTF-8 !!
    int numChars = utf8len(line);
    if (numChars == -1)
      fatal_error(_("Invalid multibyte sequence (wrong encoding?)"), line);
    if (numChars < MIN_SCR_LINE)
      fatal_error(_("data shortage"), line);
    if (SCR_SEP(line) != C_SEP)
      fatal_error(_("missing ':'"), line);
    if (SCR_COMMAND(line) != C_LABEL && SCR_COMMAND(line) != C_GOTO &&
         SCR_COMMAND(line) != C_YGOTO && SCR_COMMAND(line) != C_NGOTO &&
         utf8len(SCR_DATA(line)) > COLS)
      fatal_error(_("line too long for screen"), line);
  }
}

/*
  buffer up the complete data from a command; used for [Dd], [Pp] and M
*/
char *buffer_command( FILE *script, char *line )
{
  int	total_chars = 0;		/* character counter */
  char	*data = NULL;			/* data string */

  /* get the complete exercise into a single string */
  do
  {
    data = (char*)realloc( data, (data ? strlen( data ) : 0) +
           strlen(SCR_DATA( line )) +
           strlen(STRING_NL) + 1 );
    if ( data == NULL )
      fatal_error( _("internal error: malloc"), line );

    /* store the data in the allocated area */
    if ( total_chars == 0 )
      strcpy( data, "" );
    strcat( data, SCR_DATA( line ) );
    strcat( data, STRING_NL );
    total_chars = strlen( data );

    /* and get the next script line */
    get_script_line( script, line );
  }
  while ( SCR_COMMAND( line ) == C_CONT && ! feof( script ));

  /* return our (malloced) data */
  return( data );
}

/*
  search out a label from the file, and set the file pointer to
  that location

  It also updates __last_label for the returns into menu from lessons.
*/
void seek_label( FILE *script, char *label, char *ref_line )
{
  struct label_entry *check_label;      /* pointer through list */
  int    hash;                 			/* hash index */
  char   err[MAX_SCR_LINE];             /* error message string */

  if (!label) do_exit(script);

  __update_last_label (label);

  /* find the right hash list for the label */
  hash = hash_label( label );

  /* search the linked list for the label */
  for ( check_label = global_label_list[ hash ]; check_label != NULL;
        check_label = check_label->next )
  {
    /* see if this is our label */
    if ( strcmp( check_label->label, label ) == 0 )
      break;
  }

  /* see if the label was not found in the file */
  if ( check_label == NULL )
  {
    sprintf( err, _("label '%s' not found"), label );
    fatal_error( err, ref_line );
  }

  /* move to the label position in the file */
  if ( fseek( script, check_label->offset, SEEK_SET ) == -1 )
    fatal_error( _("internal error: fseek"), ref_line );
  global_line_counter = check_label->line_count;
}

/*
  exit from the program (implied on eof)
*/
void do_exit(FILE *script)
{
  /* close up all files, reset the screen stuff, and exit */
  fclose(script);
  /* if ( cl_colour && has_colors() )*/
  wbkgdset(stdscr, 0);
  clear(); refresh(); endwin();
  if (isUTF8Locale)
  {
      printf(_("Happy Typing!\n\n"));
  } else {
      printf("%s", convertUTF8ToCurrentEncoding(_("Happy Typing!\n\n")));
  }
  exit(0);
}

/*
  Local Variables:
  tab-width: 8
  End:
*/
