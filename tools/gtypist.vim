" Vim syntax file
"
" This file is part of GNU Typist
"
" Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003
"               Simon Baldwin (simonb@sco.com)
" Copyright (C) 2003, 2004, 2008, 2009, 2011, 2012, 2013, 2014, 2016,
"               2017, 2018, 2019  Felix Natter
" Copyright (C) 2021 Felix Natter, Mihai Gătejescu
"
" GNU Typist is free software: you can redistribute it and/or modify
" it under the terms of the GNU General Public License as published by
" the Free Software Foundation, either version 3 of the License, or
" (at your option) any later version.
"
" GNU Typist is distributed in the hope that it will be useful,
" but WITHOUT ANY WARRANTY; without even the implied warranty of
" MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
" GNU General Public License for more details.
"
" You should have received a copy of the GNU General Public License
" along with GNU Typist.  If not, see <http://www.gnu.org/licenses/>.
"
"

" Author: Felix Natter <fnatter@gmx.net> (bug-gtypist@gnu.org)
" URL: http://www.gnu.org/software/gtypist/ (tools/gtypist.vim in the
" source-package)
" Filenames: *.typ
" Last Change: (see ChangeLog below)

" README:
" Installation:
" In case you are using the debian package, this file will already
" be installed for you, but you need to enable it explicitly:
"   $ sudo apt-get install vim-addon-manager
"   $ vim-addons install gtypist
"
" 'vimrc' is ~/.vimrc on UNIX, and $HOME/_vimrc on DOS/Windows.
" This command should be at the top of your vimrc:
"  autocmd!  " Remove ALL autocommands for the current group
" (which avoids problems if vimrc is sourced more than once)
" and this should be in there too:
"  syntax on " turn on syntax highlighting
"
" vim 5.x:
" copy this file to where the syntax-files go and use this BEFORE "syntax on":
"  autocmd BufNewFile,BufRead *.typ set ft=gtypist
" (this is also the recommended way to install with vim 6.x on DOS/Windows)
"
" vim >= 6.x:
" create ~/.vim/syntax:
" $ mkdir -p ~/.vim/syntax
" and put this file in there:
" $ mv gtypist.vim ~/.vim/syntax
" put this BEFORE "syntax on" in vimrc:
"  autocmd BufNewFile,BufRead *.typ setf gtypist
"
" You can verify that this syntax highlighting is active by running
" ':set ft?' in vim, which should return 'filetype=gtypist'.

" ChangeLog:
" Sat Oct 20 14:35:44 CEST 2001: initial version
" Sun Oct 21 02:48:24 CEST 2001: use "Error" for gtypistExitCmd

" TODO:
" - E: color number in Float

" For version 5.x: Clear all syntax-items
" For version 6.x: Quit when a syntax-file was already loaded
if version < 600
  syntax clear
elseif exists("b:current_syntax")
  finish
endif

syn case match

syn keyword gtypistKeyword default Default NULL
" this is necessary so that ':' is not colored
syn match gtypistCmdSeparator ":" contained
syn match gtypistCmd "^[A-Za-z ]:" contains=gtypistCmdSeparator
syn match gtypistExitCmd "^X:" contains=gtypistCmdSeparator
syn match gtypistSetLabelCmd "^\*:" contains=gtypistCmdSeparator
syn keyword gtypistTODO TODO FIXME NOTE XXX contained
syn match gtypistComment "^[#!].*" contains=gtypistTODO
syn region gtypistDrillContent start="^[DdSs]:" skip="^ :" end="^" contains=gtypistCmd
syn match gtypistLabel "^\*:.*" contains=gtypistSetLabelCmd
syn match gtypistLabelRef "^[GYNF]:.*" contains=gtypistCmd
syn match gtypistKeybind "^K:[0-9]\+:" contains=gtypistCmd,gtypistCmdSeparator
syn match gtypistKeybindLabelRef "^K:[0-9]\+:.*" contains=gtypistKeybind
syn match gtypistBanner "^B:.*" contains=gtypistCmd

if !exists("did_gtypist_syntax_inits")
  let did_gtypist_syntax_inits = 1
  " note: the links are not very logical (i.e. gtypistLabel != Label),
  " because i.e. Label,Keyword look the same (and aren't readable in the GUI)
  " write to the maintainer if you know a way to make this more logical
  highlight link gtypistKeyword Keyword
  highlight link gtypistCmd SpecialChar
  highlight link gtypistExitCmd Error
  highlight link gtypistComment Comment
  highlight link gtypistDrillContent String
  highlight link gtypistTODO Todo
" Delimiter looks the same as SpecialChar, so this is commented out
"  highlight link gtypistCmdSeparator Delimiter
  highlight link gtypistLabel Type
  highlight link gtypistLabelRef Include
  highlight link gtypistKeybindLabelRef gtypistLabelRef
  highlight gtypistBanner term=bold cterm=bold gui=bold
endif

let b:current_syntax = "gtypist"

