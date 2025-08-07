#!/bin/bash

# Function: open_url
# Description: Opens a URL using xdg-open (Linux) or open (macOS), with fallback/error
# 
# Usage:
# Can be used in other scripts on same directory level like this:
#	source "$(dirname "$0")/open_url.sh"
# 
# Or if the script is called from a different working dir), use:
# 	source "$(cd "$(dirname "${BASH_SOURCE[0]}")" && cd <path-from-calling-script-to-/common-utilities> && pwd)/open_url.sh"

source "$(dirname "$0")/ansi_colors.sh"

open_url() {
	local url="$1"

	if command -v xdg-open >/dev/null 2>&1; then
		echo -e "${PURPLE}Here${NC}"
		xdg-open "$url" >/dev/null 2>&1 &
	elif command -v open >/dev/null 2>&1; then
		echo -e "${PINK}Here${NC}"
		open "$url" >/dev/null 2>&1 &
	else
		# echo -e "\033[0;31mError:\033[0m Could not find a supported command to open URLs (xdg-open or open)."
		echo -e "${RED}Error:${NC} Could not find a supported command to open URLs (xdg-open or open)."
		return 1
	fi
}
