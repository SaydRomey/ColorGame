#!/usr/bin/env bash

# ===== Utility Script: _test-utils.sh =====
# 
# Test and debug wrapper functions
# 
# Designed to be *sourced* (not executed)
# ====================================

_function_tester()
{
	local fn=$1
	shift

	local arg_str=
	if (($#)); then
		printf -v arg_str '%q ' "$@"
		arg_str=${arg_str% }
	fi

	printf '\n'
	printf '╭──────────────────────────────────────────────╮\n'
	printf '│ Testing: %-35q │\n' "$fn"

	if (($#)); then
		printf '│ Args:    %-35s │\n' "$arg_str"
	# else
	# 	printf '│ Args:    %-35s │\n' 'none'
	fi

	printf '╰──────────────────────────────────────────────╯\n'
	printf '\n'

	"$fn" "$@"

	printf '\n✓ Done: %q\n' "$fn"
	printf '\n'
}

# Previous versions:

# Prints the function name then executes it
# _function_tester()
# {
# 	printf '\n============================================\n\n'
# 	printf '..... Testing function: %q\nwith args "%s"\n' "${@}" "${@:2}"

# 	"$@"

# 	printf '..... done\n'
# 	printf '\n============================================\n\n'
# }

# # Prints the function name then executes it
# _function_tester()
# {
# 	local fn=$1
# 	shift

# 	local arg_str=
# 	if (($#)); then
# 		printf -v arg_str '%q ' "$@"
# 		arg_str=${arg_str% }
# 	fi

# 	printf '\n============================================\n\n'
# 	printf '..... Testing function: %q\nwith args "%s"\n' "$fn" "$arg_str"

# 	"$fn" "$@"

# 	printf '..... done\n'
# 	printf '\n============================================\n\n'
# }

# _function_tester()
# {
# 	local fn=$1
# 	shift

# 	printf '\n============================================\n\n'

# 	if (($#)); then
# 		local arg_str
# 		printf -v arg_str '%q ' "$@"
# 		arg_str=${arg_str% }

# 		printf '..... Testing function: %q\n' "$fn"
# 		printf '..... With args: %s\n' "$arg_str"
# 	else
# 		printf '..... Testing function: %q\n' "$fn"
# 		# printf '..... With no args\n'
# 	fi

# 	"$fn" "$@"

# 	printf '..... Done\n'
# 	printf '\n============================================\n\n'
# }

# _function_tester()
# {
# 	local fn=$1
# 	shift

# 	printf '\n============================================\n\n'
# 	printf '..... Testing function: %q\n' "$fn"

# 	if (($#)); then
# 		local arg_str
# 		printf -v arg_str '%q ' "$@"
# 		arg_str=${arg_str% }
# 		printf '..... Args: %s\n' "$arg_str"
# 	fi

# 	"$fn" "$@"

# 	printf '..... Done\n'
# 	printf '\n============================================\n\n'
# }
