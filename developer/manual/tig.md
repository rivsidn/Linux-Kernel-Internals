TIG(1)                                 Tig Manual                                 TIG(1)

NAME
       tig - text-mode interface for Git
             git的文本模式接口

SYNOPSIS
       tig        [options] [revisions] [--] [paths]
       tig log    [options] [revisions] [--] [paths]
       tig show   [options] [revisions] [--] [paths]
       tig blame  [options] [rev] [--] path
       tig grep   [options] [pattern]
       tig refs
       tig stash
       tig status
       tig <      [Git command output]

DESCRIPTION(描述)
       Tig is an ncurses-based text-mode interface for git(1). It functions mainly as a
       Git repository browser, but can also assist in staging changes for commit at
       chunk level and act as a pager for output from various Git commands.
       主要作为git 的版本库浏览器，还可以在块级别暂存更改用于提交，还可以作为各种Git命令
       的分页器.

OPTIONS(选项)
       Command line options recognized by Tig include all valid git-log(1) and
       git-diff(1) options, as well as the following subcommands and Tig-specific
       options. The first command line parameter not starting with "-" is interpreted as
       being either a revision specification or a path and will end the option parsing.
       All additional options will be passed to the underlying Git command.

       show
           Open diff view using the given git-show(1) options.

       blame
           Show given file annotated by commits. Takes zero or more git-blame(1)
           options. Optionally limited from given revision.

       status
           Start up in status view.

       log
           Start up in log view, displaying git-log(1) output.

       refs
           Start up in refs view.

       stash
           Start up in stash view.

       grep
           Open the grep view. Supports the same options as git-grep(1).

       +<number>
           Show the first view with line <number> visible and selected.

       -v, --version
           Show version and exit.

       -h, --help
           Show help message and exit.

PAGER MODE
       Tig enters pager mode when input is provided via stdin and supports the following
       subcommands and options:

       •   When the show subcommand is specified and the --stdin option is given, stdin
           is assumed to be a list of commit IDs and will be forwarded to the diff
           view’s underlying git-show(1) command. For example:

           $ git rev-list --author=vivien HEAD | tig show --stdin

       •   When --stdin is given, stdin is assumed to be a list of commit IDs and will
           be forwarded to the main view’s underlying git-log(1) command. For example:

           $ tig --no-walk --stdin < cherry-picks.txt

       •   When --pretty=raw is given, stdin is assumed to be a "pretty=raw" formatted
           output similar to that of git-log(1). For example:

           $ git reflog --pretty=raw | tig --pretty=raw

       When no subcommands nor options are given, the pager view will be used for
       displaying the Git command input given on stdin. The pager view assumes the input
       is either from git-log(1) or git-diff(1) and will highlight it similar to the log
       and diff views. For example:

           $ git log -Schange -p --raw | tig

EXAMPLES
       Display the list of commits for the current branch:

           $ tig

       Display commits from one or more branches:

           $ tig test master

       Pretend as if all the refs in refs/ are listed on the command line:

           $ tig --all

       Display differences between two branches:

           $ tig test..master

       Display changes for sub-module versions:

           $ tig --submodule

       Display changes for a single file:

           $ tig -- README

       Display contents of the README file in a specific revision:

           $ tig show tig-0.8:README

       Display revisions between two dates for a specific file:

           $ tig --after="2004-01-01" --before="2006-05-16" -- README

       Blame file with copy detection enabled:

           $ tig blame -C README

       Display the list of stashes:

           $ tig stash

       Grep all files for lines containing DEFINE_ENUM:

           $ tig grep -p DEFINE_ENUM

       Show references (branches, remotes and tags):

           $ tig refs

ENVIRONMENT VARIABLES
       In addition to environment variables used by Git (e.g. GIT_DIR), Tig defines the
       ones below. The command related environment variables have access to the internal
       state of Tig via replacement variables, such as %(commit) and %(blob). See
       tigrc(5) for a full list.

       TIGRC_USER
           Path of the user configuration file (defaults to ~/.tigrc or
           $XDG_CONFIG_HOME/tig/config).

       TIGRC_SYSTEM
           Path of the system wide configuration file (defaults to {sysconfdir}/tigrc).
           Define to empty string to use built-in configuration.

       TIG_LS_REMOTE
           Command for retrieving all repository references. The command should output
           data in the same format as git-ls-remote(1).

       TIG_DIFF_OPTS
           The diff options to use in the diff view. The diff view uses git-show(1) for
           formatting and always passes --patch-with-stat. You may also set the
           diff-options setting in the configuration file.

       TIG_TRACE
           Path for trace file where information about Git commands are logged.

       TIG_SCRIPT
           Path to script that should be executed automatically on startup. If this
           environment variable is defined to the empty string, the script is read from
           stdin. The script is interpreted line-by-line and can contain prompt commands
           and key mappings.

       TIG_NO_DISPLAY
           Open Tig without rendering anything to the terminal. This force Ncurses to
           write to /dev/null. The main use is for automated testing of Tig.

FILES
       $XDG_CONFIG_HOME/tig/config, ~/.config/tig/config, ~/.tigrc
           The Tig user configuration file is loaded in the following way. If
           $XDG_CONFIG_HOME is set, read user configuration from
           $XDG_CONFIG_HOME/tig/config. If $XDG_CONFIG_HOME is empty or undefined, read
           user configuration from ~/.config/tig/config if it exists and fall back to
           ~/.tigrc if it does not exist. See tigrc(5) for examples.

       /etc/tigrc
           System wide configuration file.

       $GIT_DIR/config, ~/.gitconfig, /etc/gitconfig
           Git configuration files. Read on start-up with the help of git-config(1).

       $XDG_DATA_HOME/tig/history, ~/.local/share/tig/history, ~/.tig_history
           When compiled with readline support, Tig writes a persistent command and
           search history. The location of the history file is determined in the
           following way. If $XDG_DATA_HOME is set and $XDG_DATA_HOME/tig/ exists, store
           history to $XDG_DATA_HOME/tig/history. If $XDG_DATA_HOME is empty or
           undefined, store history to ~/.local/share/tig/history if the directory
           ~/.local/share/tig/ exists, and fall back to ~/.tig_history if it does not
           exist.

BUGS
       Please visit Tig’s home page[1] or main Git repository[2] for information about
       new releases and how to report bugs or feature request.

COPYRIGHT
       Copyright (c) 2006-2014 Jonas Fonseca <jonas.fonseca@gmail.com[3]>

       This program is free software; you can redistribute it and/or modify it under the
       terms of the GNU General Public License as published by the Free Software
       Foundation; either version 2 of the License, or (at your option) any later
       version.

SEE ALSO
       tigrc(5), tigmanual(7), git(7)

NOTES
        1. home page
           https://jonas.github.io/tig

        2. main Git repository
           https://github.com/jonas/tig

        3. jonas.fonseca@gmail.com
           mailto:jonas.fonseca@gmail.com

Tig 2.4.1                              11/04/2019                                 TIG(1)
