#!/usr/bin/perl -w

# converts from ktouch's .ktouch.xml to gtypist's .typ-file
# send comments and suggestions to bug-gtypist@gnu.org

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation, either version 3
# of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

package KTouchParser;

use strict qw(subs vars refs);
use Cwd; # Cwd::getcwd
use gtypist;
use XML::Parser::PerlSAX;
#use Unicode::String;
use Text::Iconv;
use Encode qw/encode_utf8 decode_utf8/;

# configurable variables
my $lines_per_drill = 4; # 1-11 for [Dd]: and D:, 1-22 for [Ss]:
my $drill_type = "D:"; # [DdSs]

# some sanity checks
if ($lines_per_drill < 1) {
    die "Invalid lines_per_drill: $lines_per_drill\n";
}
if ($drill_type eq "D:" || $drill_type eq "d:") {
    if ($lines_per_drill > 11) {
	die "Invalid lines_per_drill for [Dd]:: $lines_per_drill\n";
    }
} else {
    if ($drill_type ne "S:" && $drill_type ne "s:") {
	die "Invalid drill_type: $drill_type\n";
    }
    if ($lines_per_drill > 22) {
	die "Invalid lines_per_drill for [Ss]:: $lines_per_drill\n";
    }
}


if ($#ARGV != 0)
{
    printf "Usage: $0 <*.ktouch.xml>\n";
    exit 1;
}

my $ktouchfilename = shift(@ARGV);
if ($ktouchfilename !~ /^.*\.ktouch\.xml$/ || ! (-f $ktouchfilename)) { 
    die "Invalid ktouch lesson filename: $ktouchfilename.\n";
}

my $typfilename = $ktouchfilename;
substr($typfilename, rindex($typfilename, ".")) = ".typ";
print "Converting $ktouchfilename to $typfilename...\n";

my $current_element = '';
my $inside_element = 0;
my %tagContent = ();
my @lessonLines;
my $lessonCounter = 1;
my @lessonNames = ();
my $TYPFILE = undef;
my $converter = Text::Iconv->new("utf-8", "utf-8");

open(TYPFILE, ">$typfilename") ||
    die "Couldn't open $typfilename for writing: $!";

my $handler = KTouchParser->new();

my $parser = XML::Parser::PerlSAX->new(Handler => $handler);

$parser->parse(Source => { 
    'SystemId' => $ktouchfilename,
    'Encoding' => 'utf-8'
               });

sub trim($)
{
    my $string = shift;
    if (!defined($string))
    {
        return undef;
    }
    $string =~ s/^\s+//;
    $string =~ s/\s+$//;
    return $string;
}

sub writeLesson($$)
{
    my $title = shift;
    my $lines = shift;

    print TYPFILE "*:S_LESSON${lessonCounter}\n";
    print TYPFILE "K:12:MENU\n";
    print TYPFILE getBanner($title);

    my $drillCounter = 1;
    my $lineCounter = 0;
    foreach my $line (@$lines)
    {
        my $unicode_line = decode_utf8($line);
        if (length($unicode_line) > 80) {
            $unicode_line = substr($unicode_line, 0, 80);
            # remove the whole word
            while (substr($unicode_line, -1, 1) ne ' ')
            {
                $unicode_line = substr($unicode_line, 0, length($unicode_line) - 1);
            }
        }
        $line = encode_utf8($unicode_line);
        $line =~ s/\s+$//; # remove trailing whitespace

	if ($lineCounter == 0) {
	    print TYPFILE "*:LESSON${lessonCounter}_D$drillCounter\n";
	    print TYPFILE "I:($drillCounter)\n";
	    print TYPFILE "${drill_type}$line\n";
	} else {
	    print TYPFILE " :$line\n";
	}
        
	++$lineCounter;
	if ($lineCounter == $lines_per_drill) {
	    $lineCounter = 0;
            ++$drillCounter;
	}
    }

    print TYPFILE "G:E_LESSON${lessonCounter}\n\n";
}


sub new {
    my $type = shift;
    return bless {}, $type;
}

sub start_element {
    my ($self, $element) = @_;
    $current_element = $element->{Name};
    $inside_element = 1;

    if ($current_element eq 'Levels')
    {
        # start of lessons, write out header
        print TYPFILE "# created by ktouch2typ.pl from " . 
            getAbsoluteFilename($ktouchfilename) . "\n# on " . `date`;
        my $FileTitle = $converter->convert($tagContent{'Title'});
        my $FileComment = $converter->convert($tagContent{'Comment'});
        print TYPFILE "# ktouch title: $FileTitle\n";
        if (defined($FileComment))
        {
            #print TYPFILE "# ktouch comment: $FileComment\n";
            my @lines = split /\r?\n/, $FileComment;
            $lines[0] = "ktouch comment: " . $lines[0];
            foreach my $line (@lines)
            {
                print TYPFILE "# " . $line . "\n";
            }
        }
        print TYPFILE "# ktouch2typ.pl is part of gtypist (http://www.gnu.org/software/gtypist/)\n";
        print TYPFILE "# ktouch can be found at http://edu.kde.org/applications/school/ktouch\n";
        print TYPFILE "# If you have suggestions about these lessons,\n";
        print TYPFILE "# please send mail to haavard\@users.sourceforge.net\n";
        print TYPFILE "# (or whoever is the current ktouch maintainer), with\n";
        print TYPFILE "# cc to bug-gtypist\@gnu.org\n\n";
        print TYPFILE "G:MENU\n\n";
    }
    elsif ($current_element eq 'Level')
    {
        # initialize lesson vars
        @lessonLines = ();
    }

    #print "Start element: $element->{Name}\n";
    $tagContent{$current_element} = '';
}

sub end_element {
    my ($self, $element) = @_;

    my $elementName = $element->{Name};

    if ($elementName eq 'Line')
    {
        push @lessonLines, trim($tagContent{'Line'});
    }
    elsif ($elementName eq 'Level')
    {
        # write out lesson
        my $levelComment = trim($tagContent{'LevelComment'});
        my $newCharacters = trim($tagContent{'NewCharacters'});
        #printf("newChars='%s', levelComment='%s'\n", $newCharacters, $levelComment);
        my $title;
        if (defined($levelComment) and $levelComment !~ /^\s*$/ and length($levelComment) < 40) {
            $title = $levelComment;
        } else {
            $title = $newCharacters;
        }
        if (length($title) > 70) {
            #$title = substr($title, 0, 65) . "...";
            die "title too long!";
        }
        $lessonNames[$lessonCounter] = $title;
        writeLesson("Lesson $lessonCounter: " . $title, \@lessonLines);

        # reset lesson variables
        @lessonLines = ();
        $lessonCounter++;
    }
    elsif ($elementName eq 'Levels')
    {
        generate_jump_table($lessonCounter - 1, \*TYPFILE);
        generate_menu("ktouch lesson: " . $tagContent{'Title'},
                      $lessonCounter - 1, \*TYPFILE, @lessonNames);
    }
    #print "End element: $element->{Name}, line=$tagContent{Line}\n";
    $inside_element = 0;
}

sub characters {
    my ($self, $characters) = @_;
    my $text = $characters->{Data};

    return '' unless $text;

    # do not collect characters that are outside the element: 
    # <Level>
    #   <LevelComment>2 und Anführungszeichen</LevelComment>XXX
    # </Level>
    # do not collect XXX
    return if $inside_element == 0; 

    #printf "text='$text'";

    $tagContent{$current_element} .= $converter->convert($text);
    if (!defined($converter->retval))
    {
        die "ERROR: $ktouchfilename cannot be encoded in UTF-8!";
    }
    #printf(" => [$current_element] '" . $tagContent{$current_element} . "'\n");
}

close(TYPFILE) || die "Couldn't close $typfilename: $!";

# Local Variables:
# compile-command: "./ktouch2typ.pl german.ktouch"
# End:
