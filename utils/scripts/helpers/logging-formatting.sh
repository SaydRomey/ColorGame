#!/usr/bin/env bash

# ==============================================================================
# Utility Script: logging-formatting.sh
# ==============================================================================
#
# Console logging and formatting helpers for Bash scripts.
#
# Designed to be sourced:
#
#   source ./logging-formatting.sh
#
#
# This file provides small helpers for printing readable console output:
#
#   nl
#   repeat_char
#   separator
#   title
#   subtitle
#   boxed_title
#   ascii_box_line
#   ascii_box_title
#   logging_help
#
# This file should not print anything when sourced.
#
# ==============================================================================

# nl
# 
# Print a single blank line
nl()
{
    printf '\n'
}

# repeat_char CHAR COUNT
#
# Print CHAR repeated COUNT times.
#
# Arguments:
#   CHAR    The character/string to repeat.
#   COUNT   Number of repetitions.
#
# Example:
#   repeat_char "-" 10
#
# Output:
#   ----------
repeat_char()
{
    local char=${1:-}
    local count=${2:-0}

    local output=""
    local i

    for ((i = 0; i < count; i++)); do
        output+="$char"
    done

    printf '%s' "$output"
}

# separator [WIDTH] [CHAR]
#
# Print a comment-style separator.
#
# Defaults:
#   WIDTH=60
#   CHAR="-"
#
# Example:
#   separator 80 "-"
separator()
{
    local width=${1:-60}
    local char=${2:--}

    printf '\n# %s\n\n' "$(repeat_char "$char" "$width")"
}

# title TEXT [WIDTH]
#
# Print a comment-style title block.
#
# Example:
#   title "Build Started" 60
title()
{
    local text=${1:-}
    local width=${2:-60}

    printf '\n'
    printf '# %s\n' "$(repeat_char "=" "$width")"
    printf '# %s\n' "$text"
    printf '# %s\n' "$(repeat_char "=" "$width")"
    printf '\n'
}

# subtitle TEXT
#
# Print a smaller comment-style subtitle.
# Example:
#   subtitle "Example subtitle"
subtitle()
{
    local text=${1:-}

    printf '\n# --- %s ---\n\n' "$text"
}

# boxed_title TEXT [WIDTH] [STYLE]
#
# Print TEXT centered inside a Unicode box.
#
# Arguments:
#   TEXT    Text to display.
#   WIDTH   Total inner width of the box. Defaults to 50.
#   STYLE   Style of chars used (single, rounded or double). Default is rounded.
# 
# Example calls:
#   boxed_title "Build Started" 40 single
#   boxed_title "Build Started" 40 rounded
#   boxed_title "Build Started" 40 double
boxed_title()
{
    local text=${1:-}
    local width=${2:-50}
    local style=${3:-rounded}

    local horizontal="─"
    local top_left="╭"
    local top_right="╮"
    local bottom_left="╰"
    local bottom_right="╯"

    case "$style" in
        single)
            top_left="┌"
            top_right="┐"
            bottom_left="└"
            bottom_right="┘"
            horizontal="─"
            ;;
        rounded)
            top_left="╭"
            top_right="╮"
            bottom_left="╰"
            bottom_right="╯"
            horizontal="─"
            ;;
        double)
            top_left="╔"
            top_right="╗"
            bottom_left="╚"
            bottom_right="╝"
            horizontal="═"
            ;;
        *)
            printf 'Unknown box style: %s\n' "$style" >&2
            return 1
            ;;
    esac

    local text_length=${#text}
    local inner_width=$width

    if (( text_length > inner_width )); then
        inner_width=$text_length
    fi

    local padding_total=$((inner_width - text_length))
    local padding_left=$((padding_total / 2))
    local padding_right=$((padding_total - padding_left))

    printf '\n'
    printf '%s%s%s\n' "$top_left" "$(repeat_char "$horizontal" "$inner_width")" "$top_right"
    printf '│%s%s%s│\n' \
        "$(repeat_char " " "$padding_left")" \
        "$text" \
        "$(repeat_char " " "$padding_right")"
    printf '%s%s%s\n' "$bottom_left" "$(repeat_char "$horizontal" "$inner_width")" "$bottom_right"
    printf '\n'
}

# ascii_box_line WIDTH [LEFT] [FILL] [RIGHT]
#
# Print a single ASCII box line.
#
# Defaults:
#   LEFT="+"
#   FILL="-"
#   RIGHT="+"
#
# Example:
#   ascii_box_line 20
#
# Output:
#   +--------------------+
ascii_box_line()
{
    local width=${1:-50}
    local left=${2:-+}
    local fill=${3:--}
    local right=${4:-+}

    printf '%s%s%s\n' "$left" "$(repeat_char "$fill" "$width")" "$right"
}

# ascii_box_title TEXT [WIDTH]
#
# Print TEXT centered inside an ASCII box.
#
# Arguments:
#   TEXT    Text to display.
#   WIDTH   Total inner width of the box. Defaults to 50.
#
# Example:
#   ascii_box_title "Build Started" 40
ascii_box_title()
{
    local text=${1:-}
    local width=${2:-50}

    local min_width=$((${#text} + 2))

    if (( min_width > width )); then
        width=$min_width
    fi

    local content_width=$((width - 2))
    local padding_total=$((content_width - ${#text}))
    local padding_left=$((padding_total / 2))
    local padding_right=$((padding_total - padding_left))

    printf '\n'
    ascii_box_line "$width"
    printf '| %s%s%s |\n' \
        "$(repeat_char " " "$padding_left")" \
        "$text" \
        "$(repeat_char " " "$padding_right")"
    ascii_box_line "$width"
    printf '\n'
}

# logging_help
#
# Print man-like documentation for this helper file.
#
# Usage:
#   logging_help
#   logging_help | more
logging_help() {
    cat <<'EOF'
LOGGING-FORMATTING.SH(1)              User Scripts Manual              LOGGING-FORMATTING.SH(1)

NAME
    logging-formatting.sh - console logging and formatting helpers for Bash scripts

SYNOPSIS
    source ./logging-formatting.sh

    nl
    repeat_char CHAR COUNT
    separator [WIDTH] [CHAR]
    title TEXT [WIDTH]
    subtitle TEXT
    # boxed_title
    ascii_box_line WIDTH [LEFT] [FILL] [RIGHT]
    ascii_box_title TEXT [WIDTH]

DESCRIPTION
    logging-formatting.sh provides small Bash helper functions 
    for printing readable console output from scripts.

    The file is designed to be sourced, not executed directly. 
    It should not print anything merely because it was sourced.

FUNCTIONS
    nl
        Print a blank line.

    repeat_char CHAR COUNT
        Print CHAR repeated COUNT times.

        Example:
            repeat_char "-" 10

    separator [WIDTH] [CHAR]
        Print a comment-style separator.

        Defaults:
            WIDTH = 60
            CHAR  = "-"

        Example:
            separator 80 "-"

    title TEXT [WIDTH]
        Print a comment-style title block.

        Defaults:
            WIDTH = 60

        Example:
            title "Build Started" 60

    subtitle TEXT
        Print a smaller comment-style subtitle.

        Example:
            subtitle "Installing dependencies"
    
    ascii_box_line WIDTH [LEFT] [FILL] [RIGHT]
        Print a single ASCII box border line.

        Defaults:
            LEFT  = "+"
            FILL  = "-"
            RIGHT = "+"

    ascii_box_title TEXT [WIDTH]
        Print TEXT centered inside an ASCII box.

        Defaults:
            WIDTH = 50

        Example:
            ascii_box_title "Deploy Started" 50

EXAMPLES
    source ./logging-formatting.sh

    title "Build Started"
    separator 80
    subtitle "Installing dependencies"
    ascii_box_title "Deploy Started" 50

PAGING
    To view this help through a pager:

        logging_help | more

    Or:

        logging_help | less

NOTES
    ASCII box characters are preferred for maximum compatibility with CI logs,
    SSH sessions, minimal terminals, and redirected output.

AUTHOR
    CDumais.

EOF
}

# run_logging_formatting_tests()
# {
# 	_function_tester nl
# 	_function_tester repeat_char "-" 10
# 	_function_tester separator 80 "-"
# 	_function_tester title "Example Title" 60
# 	_function_tester subtitle "Example subtitle"
# 	_function_tester boxed_title "Build Started" 40 single
# 	_function_tester boxed_title "Build Started" 40 rounded
# 	_function_tester boxed_title "Build Started" 40 double
# 	_function_tester ascii_box_line 20
# 	_function_tester ascii_box_title "Build Started" 40
# }

# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------
# (ASCII-only boxes characters)
# 
# +   corners/intersections
# -   horizontal lines
# |   vertical lines
# =   heavier horizontal lines
# #   comment-style separators
# *   decorative separators
# .   light/dotted separators
# :   light/dotted vertical-ish decoration
# 
# ----------------------------------------------------------------------------
# Common ASCII box styles
# 
# +--------------------+
# | Title              |
# +--------------------+
# 
# +--------------------+
# | Title              |
# +--------------------+
# 
# # --------------------
# # Title
# # --------------------
# 
# *--------------------*
# | Title              |
# *--------------------*
# 
# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------
# (Unicode box characters):
# 
# corners/intersections:
#   top-left:          ┌, ╭, ╔
#   top-right:         ┐. ╮, ╗
#   bottom-left:       └, └, ╚ 
#   bottom-left:       ┘. ┘, ╝
#   vertical lines:    |, ├, ┤
#   horizontal lines:  ─, =
# 
# ----------------------------------------------------------------------------
# Common Unicode box styles
# 
# ┌──────────────────────────────┐
# ├──────────────────────────────┤
# └──────────────────────────────┘

# ╭──────────────────────────────╮
# ╰──────────────────────────────╯

# ╔══════════════════════════════╗
# ╚══════════════════════════════╝

# ╭────────────────────────────────────────╮
# │          Example Boxed Title           │
# ╰────────────────────────────────────────╯
# 
# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------


# ----------------------------------------------------------------------------
# Tests with repeat_char variations
# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------
# repeat_char2 CHAR COUNT
# 
# alt version (Efficient & Built-in)
# using only Bash built-ins
# use printf with a field width 
# and tr to replace the resulting spaces with desired character
repeat_char2()
{
    local char=${1:-}
    local n=${2:-0}

    # Creates a string of n spaces and replaces them with the char
    printf "%${n}s" | tr ' ' "$char"
}

# repeat_char3 CHAR COUNT
# 
# alt version (Shortest Syntax)
# using printf in combination with a sequence generator (seq)
repeat_char3()
{
  printf "%.0s$1" $(seq 1 "$2")
}

# repeat_char4 CHAR COUNT
# 
# alt version (Fast)
# using external Tool: head and /dev/zero
# For very large numbers of characters, 
# reading from /dev/zero is extremely fast 
repeat_char4()
{
  # head -c gets the exact number of bytes
  head -c "$2" < /dev/zero | tr '\0' "$1"
}
# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------


# ----------------------------------------------------------------------------
# (deprecated?)
# 
# box_separator()
# {
#     local width=${1:-76}
#     local style=${2:-single}

#     case "$style" in
#         single)
#             printf '┌%s┐\n' "$(repeat_char "─" "$width")"
#             ;;
#         rounded)
#             printf '╭%s╮\n' "$(repeat_char "─" "$width")"
#             ;;
#         double)
#             printf '╔%s╗\n' "$(repeat_char "═" "$width")"
#             ;;
#         *)
#             printf 'Unknown box style: %s\n' "$style" >&2
#             return 1
#             ;;
#     esac
# }

# ----------------------------------------------------------------------------
# (deprecated?)
# 
# box_bottom()
# {
#     local width=${1:-76}
#     local style=${2:-single}

#     case "$style" in
#         single)
#             printf '└%s┘\n' "$(repeat_char "─" "$width")"
#             ;;
#         rounded)
#             printf '╰%s╯\n' "$(repeat_char "─" "$width")"
#             ;;
#         double)
#             printf '╚%s╝\n' "$(repeat_char "═" "$width")"
#             ;;
#         *)
#             printf 'Unknown box style: %s\n' "$style" >&2
#             return 1
#             ;;
#     esac
# }
# ----------------------------------------------------------------------------
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# (deprecated?)
# 
# # 
# # ascii_box_text TEXT WIDTH
# #
# # Print TEXT inside a box row. WIDTH is the total inner width.
# #
# # Example:
# #   ascii_box_text "Hello" 20
# #
# # Output:
# #   | Hello              |
# ascii_box_text()
# {
#     local text=${1:-}
#     local width=${2:-50}

#     local min_width=$((${#text} + 2))

#     if (( min_width > width )); then
#         width=$min_width
#     fi

#     local padding=$((width - ${#text} - 1))

#     printf '| %s%s|\n' "$text" "$(repeat_char " " "$padding")"
# }
# ----------------------------------------------------------------------------
