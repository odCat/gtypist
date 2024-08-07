/*
  File autogenerated by gengetopt version 2.22.6
  generated with the following command:
  gengetopt -i cmdline.ggo --default-optional --conf-parser --unamed-opts=SCRIPT --strict-hidden

  The developers of gengetopt consider the fixed text that goes in all
  gengetopt output files to be in the public domain:
  we make no copyright claims on it.
*/

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FIX_UNUSED
#define FIX_UNUSED(X) (void) (X) /* avoid warnings for unused params */
#endif

#include <getopt.h>

#include "cmdline.h"

const char *gengetopt_args_info_purpose =
"GNU Typist is a typing tutor with several lessons for different keyboards and\n"
"languages.  New lessons can be written by the user easily.";

const char *gengetopt_args_info_usage = "Usage: " CMDLINE_PARSER_PACKAGE " [OPTIONS]... [SCRIPT]...";

const char *gengetopt_args_info_versiontext =
"Copyright (C) 2021, 2022, 2023, 2024 Felix Natter, Mihai Gătejescu\n"
"Created by Simon Baldwin\n"
"License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n"
"This is free software: you are free to change and redistribute it.\n"
"There is NO WARRANTY, to the extent permitted by law.";

const char *gengetopt_args_info_description = "";

const char *gengetopt_args_info_help[] = {
  "  -h, --help                   Print help and exit",
  "  -V, --version                Print version and exit",
  "  -b, --personal-best          track personal best typing speeds  (default=off)",
  "  -e, --max-error=FLOAT        default maximum error percentage; valid values\n                                 are between 0.0 and 100.0  (default=`3.0')",
  "  -n, --notimer                turn off WPM timer in drills  (default=off)",
  "  -t, --term-cursor            use the terminal's hardware cursor\n                                 (default=off)",
  "  -f, --curs-flash=P           cursor flash period P*.1 sec; valid values are\n                                 between 0 and 512; this is ignored if -t is\n                                 specified  (default=`10')",
  "  -c, --colours=F,B            set (F)orground and (B)ackground colours, where\n                                 available  (default=`7,0')",
  "  -s, --silent                 don't beep on errors  (default=off)",
  "  -q, --quiet                  same as --silent  (default=off)",
  "  -l, --start-label=LABEL      start the lesson at the given label",
  "  -w, --word-processor         try to mimic word processors  (default=off)",
  "  -k, --no-skip                forbid the user to skip exercises  (default=off)",
  "  -i, --show-errors            highlight errors with reverse video\n                                 (default=off)",
  "  -a, --sync-ahead             try to sync ahead (i.e. h_s if you type hs)\n                                 (default=on)",
  "  -S, --always-sure            do not ask confirmation questions  (default=off)",
  "      --banner-colors=F,B,P,V  set top banner colours: (F)oreground,\n                                 (B)ackground, (P)ackage and (V)ersion\n                                 (default=`6,0,5,1')",
  "      --scoring=MODE           set scoring mode; valid values are \"wpm\"\n                                 (words per minute) and \"cpm\" (characters per\n                                 minute)  (possible values=\"wpm\", \"cpm\")",
  "      --no-welcome-screen      don't show beginner tutorial message at start-up\n                                 (default=off)",
  "\nIf not supplied, script-file defaults to the 'gtypist.typ' that came with this\n"
      "software.  If you specify a script, the path $GTYPIST_PATH is searched for\n"
      "script files.\n\nExamples:\n\nTo run the default lesson in english 'gtypist.typ':\n  gtypist\n\n"
      "To run the lesson in spanish:\n  gtypist esp.typ\n\n"
      "To instruct gtypist to look for lesson 'bar.typ' in a non standard directory:\n  GTYPIST_PATH=\"/home/foo\" gtypist bar.typ\n"
      "\nTo run the lesson in the file '/tmp/test.typ', starting at label 'TEST1', using\nthe terminal's cursor, and run silently:\n"
      "  gtypist -t -q -l TEST1 /temp/test.typ\n\nReport bugs to <bug-gtypist@gnu.org>.",
    0
};

typedef enum {ARG_NO
  , ARG_FLAG
  , ARG_STRING
  , ARG_INT
  , ARG_FLOAT
  , ARG_ENUM
} cmdline_parser_arg_type;

static
void clear_given (struct gengetopt_args_info *args_info);
static
void clear_args (struct gengetopt_args_info *args_info);

static int
cmdline_parser_internal (int argc, char **argv, struct gengetopt_args_info *args_info,
                        struct cmdline_parser_params *params, const char *additional_error);

struct line_list
{
  char * string_arg;
  struct line_list * next;
};

static struct line_list *cmd_line_list = 0;
static struct line_list *cmd_line_list_tmp = 0;

static void
free_cmd_list(void)
{
  /* free the list of a previous call */
  if (cmd_line_list)
    {
      while (cmd_line_list) {
        cmd_line_list_tmp = cmd_line_list;
        cmd_line_list = cmd_line_list->next;
        free (cmd_line_list_tmp->string_arg);
        free (cmd_line_list_tmp);
      }
    }
}


const char *cmdline_parser_scoring_values[] = {"wpm", "cpm", 0}; /*< Possible values for scoring. */

static char *
gengetopt_strdup (const char *s);

static
void clear_given (struct gengetopt_args_info *args_info)
{
  args_info->help_given = 0 ;
  args_info->version_given = 0 ;
  args_info->personal_best_given = 0 ;
  args_info->max_error_given = 0 ;
  args_info->notimer_given = 0 ;
  args_info->term_cursor_given = 0 ;
  args_info->curs_flash_given = 0 ;
  args_info->colours_given = 0 ;
  args_info->silent_given = 0 ;
  args_info->quiet_given = 0 ;
  args_info->start_label_given = 0 ;
  args_info->word_processor_given = 0 ;
  args_info->no_skip_given = 0 ;
  args_info->show_errors_given = 0 ;
  args_info->sync_ahead_given = 0 ;
  args_info->always_sure_given = 0 ;
  args_info->banner_colors_given = 0 ;
  args_info->scoring_given = 0 ;
  args_info->no_welcome_screen_given = 0 ;
}

static
void clear_args (struct gengetopt_args_info *args_info)
{
  FIX_UNUSED (args_info);
  args_info->personal_best_flag = 0;
  args_info->max_error_arg = 3.0;
  args_info->max_error_orig = NULL;
  args_info->notimer_flag = 0;
  args_info->term_cursor_flag = 0;
  args_info->curs_flash_arg = 10;
  args_info->curs_flash_orig = NULL;
  args_info->colours_arg = gengetopt_strdup ("7,0");
  args_info->colours_orig = NULL;
  args_info->silent_flag = 0;
  args_info->quiet_flag = 0;
  args_info->start_label_arg = NULL;
  args_info->start_label_orig = NULL;
  args_info->word_processor_flag = 0;
  args_info->no_skip_flag = 0;
  args_info->show_errors_flag = 0;
  args_info->sync_ahead_flag = 1;
  args_info->always_sure_flag = 0;
  args_info->banner_colors_arg = gengetopt_strdup ("6,0,5,1");
  args_info->banner_colors_orig = NULL;
  args_info->scoring_arg = scoring__NULL;
  args_info->scoring_orig = NULL;
  args_info->no_welcome_screen_flag = 0;

}

static
void init_args_info(struct gengetopt_args_info *args_info)
{


  args_info->help_help = gengetopt_args_info_help[0] ;
  args_info->version_help = gengetopt_args_info_help[1] ;
  args_info->personal_best_help = gengetopt_args_info_help[2] ;
  args_info->max_error_help = gengetopt_args_info_help[3] ;
  args_info->notimer_help = gengetopt_args_info_help[4] ;
  args_info->term_cursor_help = gengetopt_args_info_help[5] ;
  args_info->curs_flash_help = gengetopt_args_info_help[6] ;
  args_info->colours_help = gengetopt_args_info_help[7] ;
  args_info->silent_help = gengetopt_args_info_help[8] ;
  args_info->quiet_help = gengetopt_args_info_help[9] ;
  args_info->start_label_help = gengetopt_args_info_help[10] ;
  args_info->word_processor_help = gengetopt_args_info_help[11] ;
  args_info->no_skip_help = gengetopt_args_info_help[12] ;
  args_info->show_errors_help = gengetopt_args_info_help[13] ;
  args_info->sync_ahead_help = gengetopt_args_info_help[14] ;
  args_info->always_sure_help = gengetopt_args_info_help[15] ;
  args_info->banner_colors_help = gengetopt_args_info_help[16] ;
  args_info->scoring_help = gengetopt_args_info_help[17] ;
  args_info->no_welcome_screen_help = gengetopt_args_info_help[18] ;

}

void
cmdline_parser_print_version (void)
{
  printf ("%s %s\n",
     (strlen(CMDLINE_PARSER_PACKAGE_NAME) ? CMDLINE_PARSER_PACKAGE_NAME : CMDLINE_PARSER_PACKAGE),
     CMDLINE_PARSER_VERSION);

  if (strlen(gengetopt_args_info_versiontext) > 0)
    printf("%s\n", gengetopt_args_info_versiontext);
}

static void print_help_common(void) {
  cmdline_parser_print_version ();

  if (strlen(gengetopt_args_info_purpose) > 0)
    printf("\n%s\n", gengetopt_args_info_purpose);

  if (strlen(gengetopt_args_info_usage) > 0)
    printf("\n%s\n", gengetopt_args_info_usage);

  printf("\n");

  if (strlen(gengetopt_args_info_description) > 0)
    printf("%s\n\n", gengetopt_args_info_description);
}

void
cmdline_parser_print_help (void)
{
  int i = 0;
  print_help_common();
  while (gengetopt_args_info_help[i])
    printf("%s\n", gengetopt_args_info_help[i++]);
}

void
cmdline_parser_init (struct gengetopt_args_info *args_info)
{
  clear_given (args_info);
  clear_args (args_info);
  init_args_info (args_info);

  args_info->inputs = 0;
  args_info->inputs_num = 0;
}

void
cmdline_parser_params_init(struct cmdline_parser_params *params)
{
  if (params)
    {
      params->override = 0;
      params->initialize = 1;
      params->check_required = 1;
      params->check_ambiguity = 0;
      params->print_errors = 1;
    }
}

struct cmdline_parser_params *
cmdline_parser_params_create(void)
{
  struct cmdline_parser_params *params =
    (struct cmdline_parser_params *)malloc(sizeof(struct cmdline_parser_params));
  cmdline_parser_params_init(params);
  return params;
}

static void
free_string_field (char **s)
{
  if (*s)
    {
      free (*s);
      *s = 0;
    }
}


static void
cmdline_parser_release (struct gengetopt_args_info *args_info)
{
  unsigned int i;
  free_string_field (&(args_info->max_error_orig));
  free_string_field (&(args_info->curs_flash_orig));
  free_string_field (&(args_info->colours_arg));
  free_string_field (&(args_info->colours_orig));
  free_string_field (&(args_info->start_label_arg));
  free_string_field (&(args_info->start_label_orig));
  free_string_field (&(args_info->banner_colors_arg));
  free_string_field (&(args_info->banner_colors_orig));
  free_string_field (&(args_info->scoring_orig));


  for (i = 0; i < args_info->inputs_num; ++i)
    free (args_info->inputs [i]);

  if (args_info->inputs_num)
    free (args_info->inputs);

  clear_given (args_info);
}

/**
 * @param val the value to check
 * @param values the possible values
 * @return the index of the matched value:
 * -1 if no value matched,
 * -2 if more than one value has matched
 */
static int
check_possible_values(const char *val, const char *values[])
{
  int i, found, last;
  size_t len;

  if (!val)   /* otherwise strlen() crashes below */
    return -1; /* -1 means no argument for the option */

  found = last = 0;

  for (i = 0, len = strlen(val); values[i]; ++i)
    {
      if (strncmp(val, values[i], len) == 0)
        {
          ++found;
          last = i;
          if (strlen(values[i]) == len)
            return i; /* exact macth no need to check more */
        }
    }

  if (found == 1) /* one match: OK */
    return last;

  return (found ? -2 : -1); /* return many values or none matched */
}


static void
write_into_file(FILE *outfile, const char *opt, const char *arg, const char *values[])
{
  int found = -1;
  if (arg) {
    if (values) {
      found = check_possible_values(arg, values);
    }
    if (found >= 0)
      fprintf(outfile, "%s=\"%s\" # %s\n", opt, arg, values[found]);
    else
      fprintf(outfile, "%s=\"%s\"\n", opt, arg);
  } else {
    fprintf(outfile, "%s\n", opt);
  }
}


int
cmdline_parser_dump(FILE *outfile, struct gengetopt_args_info *args_info)
{
  int i = 0;

  if (!outfile)
    {
      fprintf (stderr, "%s: cannot dump options to stream\n", CMDLINE_PARSER_PACKAGE);
      return EXIT_FAILURE;
    }

  if (args_info->help_given)
    write_into_file(outfile, "help", 0, 0 );
  if (args_info->version_given)
    write_into_file(outfile, "version", 0, 0 );
  if (args_info->personal_best_given)
    write_into_file(outfile, "personal-best", 0, 0 );
  if (args_info->max_error_given)
    write_into_file(outfile, "max-error", args_info->max_error_orig, 0);
  if (args_info->notimer_given)
    write_into_file(outfile, "notimer", 0, 0 );
  if (args_info->term_cursor_given)
    write_into_file(outfile, "term-cursor", 0, 0 );
  if (args_info->curs_flash_given)
    write_into_file(outfile, "curs-flash", args_info->curs_flash_orig, 0);
  if (args_info->colours_given)
    write_into_file(outfile, "colours", args_info->colours_orig, 0);
  if (args_info->silent_given)
    write_into_file(outfile, "silent", 0, 0 );
  if (args_info->quiet_given)
    write_into_file(outfile, "quiet", 0, 0 );
  if (args_info->start_label_given)
    write_into_file(outfile, "start-label", args_info->start_label_orig, 0);
  if (args_info->word_processor_given)
    write_into_file(outfile, "word-processor", 0, 0 );
  if (args_info->no_skip_given)
    write_into_file(outfile, "no-skip", 0, 0 );
  if (args_info->show_errors_given)
    write_into_file(outfile, "show-errors", 0, 0 );
  if (args_info->sync_ahead_given)
    write_into_file(outfile, "sync-ahead", 0, 0 );
  if (args_info->always_sure_given)
    write_into_file(outfile, "always-sure", 0, 0 );
  if (args_info->banner_colors_given)
    write_into_file(outfile, "banner-colors", args_info->banner_colors_orig, 0);
  if (args_info->scoring_given)
    write_into_file(outfile, "scoring", args_info->scoring_orig, cmdline_parser_scoring_values);
  if (args_info->no_welcome_screen_given)
    write_into_file(outfile, "no-welcome-screen", 0, 0 );


  i = EXIT_SUCCESS;
  return i;
}

int
cmdline_parser_file_save(const char *filename, struct gengetopt_args_info *args_info)
{
  FILE *outfile;
  int i = 0;

  outfile = fopen(filename, "w");

  if (!outfile)
    {
      fprintf (stderr, "%s: cannot open file for writing: %s\n", CMDLINE_PARSER_PACKAGE, filename);
      return EXIT_FAILURE;
    }

  i = cmdline_parser_dump(outfile, args_info);
  fclose (outfile);

  return i;
}

void
cmdline_parser_free (struct gengetopt_args_info *args_info)
{
  cmdline_parser_release (args_info);
}

/** @brief replacement of strdup, which is not standard */
char *
gengetopt_strdup (const char *s)
{
  char *result = 0;
  if (!s)
    return result;

  result = (char*)malloc(strlen(s) + 1);
  if (result == (char*)0)
    return (char*)0;
  strcpy(result, s);
  return result;
}

int
cmdline_parser (int argc, char **argv, struct gengetopt_args_info *args_info)
{
  return cmdline_parser2 (argc, argv, args_info, 0, 1, 1);
}

int
cmdline_parser_ext (int argc, char **argv, struct gengetopt_args_info *args_info,
                   struct cmdline_parser_params *params)
{
  int result;
  result = cmdline_parser_internal (argc, argv, args_info, params, 0);

  if (result == EXIT_FAILURE)
    {
      cmdline_parser_free (args_info);
      exit (EXIT_FAILURE);
    }

  return result;
}

int
cmdline_parser2 (int argc, char **argv, struct gengetopt_args_info *args_info, int override, int initialize, int check_required)
{
  int result;
  struct cmdline_parser_params params;

  params.override = override;
  params.initialize = initialize;
  params.check_required = check_required;
  params.check_ambiguity = 0;
  params.print_errors = 1;

  result = cmdline_parser_internal (argc, argv, args_info, &params, 0);

  if (result == EXIT_FAILURE)
    {
      cmdline_parser_free (args_info);
      exit (EXIT_FAILURE);
    }

  return result;
}

int
cmdline_parser_required (struct gengetopt_args_info *args_info, const char *prog_name)
{
  FIX_UNUSED (args_info);
  FIX_UNUSED (prog_name);
  return EXIT_SUCCESS;
}


static char *package_name = 0;

/**
 * @brief updates an option
 * @param field the generic pointer to the field to update
 * @param orig_field the pointer to the orig field
 * @param field_given the pointer to the number of occurrence of this option
 * @param prev_given the pointer to the number of occurrence already seen
 * @param value the argument for this option (if null no arg was specified)
 * @param possible_values the possible values for this option (if specified)
 * @param default_value the default value (in case the option only accepts fixed values)
 * @param arg_type the type of this option
 * @param check_ambiguity @see cmdline_parser_params.check_ambiguity
 * @param override @see cmdline_parser_params.override
 * @param no_free whether to free a possible previous value
 * @param multiple_option whether this is a multiple option
 * @param long_opt the corresponding long option
 * @param short_opt the corresponding short option (or '-' if none)
 * @param additional_error possible further error specification
 */
static
int update_arg(void *field, char **orig_field,
               unsigned int *field_given, unsigned int *prev_given,
               char *value, const char *possible_values[],
               const char *default_value,
               cmdline_parser_arg_type arg_type,
               int check_ambiguity, int override,
               int no_free, int multiple_option,
               const char *long_opt, char short_opt,
               const char *additional_error)
{
  char *stop_char = 0;
  const char *val = value;
  int found;
  char **string_field;
  FIX_UNUSED (field);

  stop_char = 0;
  found = 0;

  if (!multiple_option && prev_given && (*prev_given || (check_ambiguity && *field_given)))
    {
      if (short_opt != '-')
        fprintf (stderr, "%s: `--%s' (`-%c') option given more than once%s\n",
               package_name, long_opt, short_opt,
               (additional_error ? additional_error : ""));
      else
        fprintf (stderr, "%s: `--%s' option given more than once%s\n",
               package_name, long_opt,
               (additional_error ? additional_error : ""));
      return 1; /* failure */
    }

  if (possible_values && (found = check_possible_values((value ? value : default_value), possible_values)) < 0)
    {
      if (short_opt != '-')
        fprintf (stderr, "%s: %s argument, \"%s\", for option `--%s' (`-%c')%s\n",
          package_name, (found == -2) ? "ambiguous" : "invalid", value, long_opt, short_opt,
          (additional_error ? additional_error : ""));
      else
        fprintf (stderr, "%s: %s argument, \"%s\", for option `--%s'%s\n",
          package_name, (found == -2) ? "ambiguous" : "invalid", value, long_opt,
          (additional_error ? additional_error : ""));
      return 1; /* failure */
    }

  if (field_given && *field_given && ! override)
    return 0;
  if (prev_given)
    (*prev_given)++;
  if (field_given)
    (*field_given)++;
  if (possible_values)
    val = possible_values[found];

  switch(arg_type) {
  case ARG_FLAG:
    *((int *)field) = !*((int *)field);
    break;
  case ARG_INT:
    if (val) *((int *)field) = strtol (val, &stop_char, 0);
    break;
  case ARG_FLOAT:
    if (val) *((float *)field) = (float)strtod (val, &stop_char);
    break;
  case ARG_ENUM:
    if (val) *((int *)field) = found;
    break;
  case ARG_STRING:
    if (val) {
      string_field = (char **)field;
      if (!no_free && *string_field)
        free (*string_field); /* free previous string */
      *string_field = gengetopt_strdup (val);
    }
    break;
  default:
    break;
  };

  /* check numeric conversion */
  switch(arg_type) {
  case ARG_INT:
  case ARG_FLOAT:
    if (val && !(stop_char && *stop_char == '\0')) {
      fprintf(stderr, "%s: invalid numeric value: %s\n", package_name, val);
      return 1; /* failure */
    }
    break;
  default:
    ;
  };

  /* store the original value */
  switch(arg_type) {
  case ARG_NO:
  case ARG_FLAG:
    break;
  default:
    if (value && orig_field) {
      if (no_free) {
        *orig_field = value;
      } else {
        if (*orig_field)
          free (*orig_field); /* free previous string */
        *orig_field = gengetopt_strdup (value);
      }
    }
  };

  return 0; /* OK */
}


int
cmdline_parser_internal (
  int argc, char **argv, struct gengetopt_args_info *args_info,
                        struct cmdline_parser_params *params, const char *additional_error)
{
  int c;	/* Character of the parsed option.  */

  int error = 0;
  struct gengetopt_args_info local_args_info;

  int override;
  int initialize;
  int check_required;
  int check_ambiguity;

  package_name = argv[0];

  override = params->override;
  initialize = params->initialize;
  check_required = params->check_required;
  check_ambiguity = params->check_ambiguity;

  if (initialize)
    cmdline_parser_init (args_info);

  cmdline_parser_init (&local_args_info);

  optarg = 0;
  optind = 0;
  opterr = params->print_errors;
  optopt = '?';

  while (1)
    {
      int option_index = 0;

      static struct option long_options[] = {
        { "help",	0, NULL, 'h' },
        { "version",	0, NULL, 'V' },
        { "personal-best",	0, NULL, 'b' },
        { "max-error",	1, NULL, 'e' },
        { "notimer",	0, NULL, 'n' },
        { "term-cursor",	0, NULL, 't' },
        { "curs-flash",	1, NULL, 'f' },
        { "colours",	1, NULL, 'c' },
        { "silent",	0, NULL, 's' },
        { "quiet",	0, NULL, 'q' },
        { "start-label",	1, NULL, 'l' },
        { "word-processor",	0, NULL, 'w' },
        { "no-skip",	0, NULL, 'k' },
        { "show-errors",	0, NULL, 'i' },
        { "sync-ahead",	0, NULL, 'a' },
        { "always-sure",	0, NULL, 'S' },
        { "banner-colors",	1, NULL, 0 },
        { "scoring",	1, NULL, 0 },
        { "no-welcome-screen",	0, NULL, 0 },
        { 0,  0, 0, 0 }
      };

      c = getopt_long (argc, argv, "hVbe:ntf:c:sql:wkiaS", long_options, &option_index);

      if (c == -1) break;	/* Exit from `while (1)' loop.  */

      switch (c)
        {
        case 'h':	/* Print help and exit.  */
          cmdline_parser_print_help ();
          cmdline_parser_free (&local_args_info);
          exit (EXIT_SUCCESS);

        case 'V':	/* Print version and exit.  */
          cmdline_parser_print_version ();
          cmdline_parser_free (&local_args_info);
          exit (EXIT_SUCCESS);

        case 'b':	/* track personal best typing speeds.  */


          if (update_arg((void *)&(args_info->personal_best_flag), 0, &(args_info->personal_best_given),
              &(local_args_info.personal_best_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "personal-best", 'b',
              additional_error))
            goto failure;

          break;
        case 'e':	/* default maximum error percentage; valid values are between 0.0 and 100.0.  */


          if (update_arg( (void *)&(args_info->max_error_arg),
               &(args_info->max_error_orig), &(args_info->max_error_given),
              &(local_args_info.max_error_given), optarg, 0, "3.0", ARG_FLOAT,
              check_ambiguity, override, 0, 0,
              "max-error", 'e',
              additional_error))
            goto failure;

          break;
        case 'n':	/* turn off WPM timer in drills.  */


          if (update_arg((void *)&(args_info->notimer_flag), 0, &(args_info->notimer_given),
              &(local_args_info.notimer_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "notimer", 'n',
              additional_error))
            goto failure;

          break;
        case 't':	/* use the terminal's hardware cursor.  */


          if (update_arg((void *)&(args_info->term_cursor_flag), 0, &(args_info->term_cursor_given),
              &(local_args_info.term_cursor_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "term-cursor", 't',
              additional_error))
            goto failure;

          break;
        case 'f':	/* cursor flash period P*.1 sec; valid values are between 0 and 512; this is ignored if -t is specified.  */


          if (update_arg( (void *)&(args_info->curs_flash_arg),
               &(args_info->curs_flash_orig), &(args_info->curs_flash_given),
              &(local_args_info.curs_flash_given), optarg, 0, "10", ARG_INT,
              check_ambiguity, override, 0, 0,
              "curs-flash", 'f',
              additional_error))
            goto failure;

          break;
        case 'c':	/* set (F)orground and (B)ackground colours, where available.  */


          if (update_arg( (void *)&(args_info->colours_arg),
               &(args_info->colours_orig), &(args_info->colours_given),
              &(local_args_info.colours_given), optarg, 0, "7,0", ARG_STRING,
              check_ambiguity, override, 0, 0,
              "colours", 'c',
              additional_error))
            goto failure;

          break;
        case 's':	/* don't beep on errors.  */


          if (update_arg((void *)&(args_info->silent_flag), 0, &(args_info->silent_given),
              &(local_args_info.silent_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "silent", 's',
              additional_error))
            goto failure;

          break;
        case 'q':	/* same as --silent.  */


          if (update_arg((void *)&(args_info->quiet_flag), 0, &(args_info->quiet_given),
              &(local_args_info.quiet_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "quiet", 'q',
              additional_error))
            goto failure;

          break;
        case 'l':	/* start the lesson at the given label.  */


          if (update_arg( (void *)&(args_info->start_label_arg),
               &(args_info->start_label_orig), &(args_info->start_label_given),
              &(local_args_info.start_label_given), optarg, 0, 0, ARG_STRING,
              check_ambiguity, override, 0, 0,
              "start-label", 'l',
              additional_error))
            goto failure;

          break;
        case 'w':	/* try to mimic word processors.  */


          if (update_arg((void *)&(args_info->word_processor_flag), 0, &(args_info->word_processor_given),
              &(local_args_info.word_processor_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "word-processor", 'w',
              additional_error))
            goto failure;

          break;
        case 'k':	/* forbid the user to skip exercises.  */


          if (update_arg((void *)&(args_info->no_skip_flag), 0, &(args_info->no_skip_given),
              &(local_args_info.no_skip_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "no-skip", 'k',
              additional_error))
            goto failure;

          break;
        case 'i':	/* highlight errors with reverse video.  */


          if (update_arg((void *)&(args_info->show_errors_flag), 0, &(args_info->show_errors_given),
              &(local_args_info.show_errors_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "show-errors", 'i',
              additional_error))
            goto failure;

          break;
        case 'a':	/* try to sync ahead (i.e. h_s if you type hs).  */


          if (update_arg((void *)&(args_info->sync_ahead_flag), 0, &(args_info->sync_ahead_given),
              &(local_args_info.sync_ahead_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "sync-ahead", 'a',
              additional_error))
            goto failure;

          break;
        case 'S':	/* do not ask confirmation questions.  */


          if (update_arg((void *)&(args_info->always_sure_flag), 0, &(args_info->always_sure_given),
              &(local_args_info.always_sure_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "always-sure", 'S',
              additional_error))
            goto failure;

          break;

        case 0:	/* Long option with no short option */
          /* set top banner colours: (F)oreground, (B)ackground, (P)ackage and (V)ersion.  */
          if (strcmp (long_options[option_index].name, "banner-colors") == 0)
          {


            if (update_arg( (void *)&(args_info->banner_colors_arg),
                 &(args_info->banner_colors_orig), &(args_info->banner_colors_given),
                &(local_args_info.banner_colors_given), optarg, 0, "6,0,5,1", ARG_STRING,
                check_ambiguity, override, 0, 0,
                "banner-colors", '-',
                additional_error))
              goto failure;

          }
          /* set scoring mode; valid values are \"wpm\" (words per minute) and \"cpm\" (characters per minute).  */
          else if (strcmp (long_options[option_index].name, "scoring") == 0)
          {


            if (update_arg( (void *)&(args_info->scoring_arg),
                 &(args_info->scoring_orig), &(args_info->scoring_given),
                &(local_args_info.scoring_given), optarg, cmdline_parser_scoring_values, 0, ARG_ENUM,
                check_ambiguity, override, 0, 0,
                "scoring", '-',
                additional_error))
              goto failure;

          }
          /* don't show beginner tutorial message at start-up.  */
          else if (strcmp (long_options[option_index].name, "no-welcome-screen") == 0)
          {


            if (update_arg((void *)&(args_info->no_welcome_screen_flag), 0, &(args_info->no_welcome_screen_given),
                &(local_args_info.no_welcome_screen_given), optarg, 0, 0, ARG_FLAG,
                check_ambiguity, override, 1, 0, "no-welcome-screen", '-',
                additional_error))
              goto failure;

          }

          break;
        case '?':	/* Invalid option.  */
          /* `getopt_long' already printed an error message.  */
          goto failure;

        default:	/* bug: option not considered.  */
          fprintf (stderr, "%s: option unknown: %c%s\n", CMDLINE_PARSER_PACKAGE, c, (additional_error ? additional_error : ""));
          abort ();
        } /* switch */
    } /* while */




  cmdline_parser_release (&local_args_info);

  if ( error )
    return (EXIT_FAILURE);

  if (optind < argc)
    {
      int i = 0 ;
      int found_prog_name = 0;
      /* whether program name, i.e., argv[0], is in the remaining args
         (this may happen with some implementations of getopt,
          but surely not with the one included by gengetopt) */

      i = optind;
      while (i < argc)
        if (argv[i++] == argv[0]) {
          found_prog_name = 1;
          break;
        }
      i = 0;

      args_info->inputs_num = argc - optind - found_prog_name;
      args_info->inputs =
        (char **)(malloc ((args_info->inputs_num)*sizeof(char *))) ;
      while (optind < argc)
        if (argv[optind++] != argv[0])
          args_info->inputs[ i++ ] = gengetopt_strdup (argv[optind-1]) ;
    }

  return 0;

failure:

  cmdline_parser_release (&local_args_info);
  return (EXIT_FAILURE);
}

#ifndef CONFIG_FILE_LINE_SIZE
#define CONFIG_FILE_LINE_SIZE 2048
#endif
#define ADDITIONAL_ERROR " in configuration file "

#define CONFIG_FILE_LINE_BUFFER_SIZE (CONFIG_FILE_LINE_SIZE+3)
/* 3 is for "--" and "=" */

static int
_cmdline_parser_configfile (const char *filename, int *my_argc)
{
  FILE* file;
  char my_argv[CONFIG_FILE_LINE_BUFFER_SIZE+1];
  char linebuf[CONFIG_FILE_LINE_SIZE];
  int line_num = 0;
  int result = 0, equal;
  char *fopt, *farg;
  char *str_index;
  size_t len, next_token;
  char delimiter;

  if ((file = fopen(filename, "r")) == 0)
    {
      fprintf (stderr, "%s: Error opening configuration file '%s'\n",
               CMDLINE_PARSER_PACKAGE, filename);
      return EXIT_FAILURE;
    }

  while ((fgets(linebuf, CONFIG_FILE_LINE_SIZE, file)) != 0)
    {
      ++line_num;
      my_argv[0] = '\0';
      len = strlen(linebuf);
      if (len > (CONFIG_FILE_LINE_BUFFER_SIZE-1))
        {
          fprintf (stderr, "%s:%s:%d: Line too long in configuration file\n",
                   CMDLINE_PARSER_PACKAGE, filename, line_num);
          result = EXIT_FAILURE;
          break;
        }

      /* find first non-whitespace character in the line */
      next_token = strspn (linebuf, " \t\r\n");
      str_index  = linebuf + next_token;

      if ( str_index[0] == '\0' || str_index[0] == '#')
        continue; /* empty line or comment line is skipped */

      fopt = str_index;

      /* truncate fopt at the end of the first non-valid character */
      next_token = strcspn (fopt, " \t\r\n=");

      if (fopt[next_token] == '\0') /* the line is over */
        {
          farg  = 0;
          equal = 0;
          goto noarg;
        }

      /* remember if equal sign is present */
      equal = (fopt[next_token] == '=');
      fopt[next_token++] = '\0';

      /* advance pointers to the next token after the end of fopt */
      next_token += strspn (fopt + next_token, " \t\r\n");

      /* check for the presence of equal sign, and if so, skip it */
      if ( !equal )
        if ((equal = (fopt[next_token] == '=')))
          {
            next_token++;
            next_token += strspn (fopt + next_token, " \t\r\n");
          }
      str_index  += next_token;

      /* find argument */
      farg = str_index;
      if ( farg[0] == '\"' || farg[0] == '\'' )
        { /* quoted argument */
          str_index = strchr (++farg, str_index[0] ); /* skip opening quote */
          if (! str_index)
            {
              fprintf
                (stderr,
                 "%s:%s:%d: unterminated string in configuration file\n",
                 CMDLINE_PARSER_PACKAGE, filename, line_num);
              result = EXIT_FAILURE;
              break;
            }
        }
      else
        { /* read up the remaining part up to a delimiter */
          next_token = strcspn (farg, " \t\r\n#\'\"");
          str_index += next_token;
        }

      /* truncate farg at the delimiter and store it for further check */
      delimiter = *str_index, *str_index++ = '\0';

      /* everything but comment is illegal at the end of line */
      if (delimiter != '\0' && delimiter != '#')
        {
          str_index += strspn(str_index, " \t\r\n");
          if (*str_index != '\0' && *str_index != '#')
            {
              fprintf
                (stderr,
                 "%s:%s:%d: malformed string in configuration file\n",
                 CMDLINE_PARSER_PACKAGE, filename, line_num);
              result = EXIT_FAILURE;
              break;
            }
        }

    noarg:
      if (!strcmp(fopt,"include")) {
        if (farg && *farg) {
          result = _cmdline_parser_configfile(farg, my_argc);
        } else {
          fprintf(stderr, "%s:%s:%d: include requires a filename argument.\n",
                  CMDLINE_PARSER_PACKAGE, filename, line_num);
        }
        continue;
      }
      len = strlen(fopt);
      strcat (my_argv, len > 1 ? "--" : "-");
      strcat (my_argv, fopt);
      if (len > 1 && ((farg && *farg) || equal))
        strcat (my_argv, "=");
      if (farg && *farg)
        strcat (my_argv, farg);
      ++(*my_argc);

      cmd_line_list_tmp = (struct line_list *) malloc (sizeof (struct line_list));
      cmd_line_list_tmp->next = cmd_line_list;
      cmd_line_list = cmd_line_list_tmp;
      cmd_line_list->string_arg = gengetopt_strdup(my_argv);
    } /* while */

  if (file)
    fclose(file);
  return result;
}

int
cmdline_parser_configfile (
  const char *filename,
                           struct gengetopt_args_info *args_info,
                           int override, int initialize, int check_required)
{
  struct cmdline_parser_params params;

  params.override = override;
  params.initialize = initialize;
  params.check_required = check_required;
  params.check_ambiguity = 0;
  params.print_errors = 1;

  return cmdline_parser_config_file (filename, args_info, &params);
}

int
cmdline_parser_config_file (const char *filename,
                           struct gengetopt_args_info *args_info,
                           struct cmdline_parser_params *params)
{
  int i, result;
  int my_argc = 1;
  char **my_argv_arg;
  char *additional_error;

  /* store the program name */
  cmd_line_list_tmp = (struct line_list *) malloc (sizeof (struct line_list));
  cmd_line_list_tmp->next = cmd_line_list;
  cmd_line_list = cmd_line_list_tmp;
  cmd_line_list->string_arg = gengetopt_strdup (CMDLINE_PARSER_PACKAGE);

  result = _cmdline_parser_configfile(filename, &my_argc);

  if (result != EXIT_FAILURE) {
    my_argv_arg = (char **) malloc((my_argc+1) * sizeof(char *));
    cmd_line_list_tmp = cmd_line_list;

    for (i = my_argc - 1; i >= 0; --i) {
      my_argv_arg[i] = cmd_line_list_tmp->string_arg;
      cmd_line_list_tmp = cmd_line_list_tmp->next;
    }

    my_argv_arg[my_argc] = 0;

    additional_error = (char *)malloc(strlen(filename) + strlen(ADDITIONAL_ERROR) + 1);
    strcpy (additional_error, ADDITIONAL_ERROR);
    strcat (additional_error, filename);
    result =
      cmdline_parser_internal (my_argc, my_argv_arg, args_info,
                              params,
                              additional_error);

    free (additional_error);
    free (my_argv_arg);
  }

  free_cmd_list();
  if (result == EXIT_FAILURE)
    {
      cmdline_parser_free (args_info);
      exit (EXIT_FAILURE);
    }

  return result;
}
