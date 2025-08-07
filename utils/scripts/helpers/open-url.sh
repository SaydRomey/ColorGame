#!/bin/bash

# Utility Script: open-url.sh
# 
# Function: open_url
# Description: Opens a URL using xdg-open (Linux) or open (macOS), with fallback/error

open_url() {
	local url="$1"

	if command -v xdg-open >/dev/null 2>&1; then
		xdg-open "$url" >/dev/null 2>&1 &
	elif command -v open >/dev/null 2>&1; then
		open "$url" >/dev/null 2>&1 &
	else
		echo -e "${RED}Error:${NC} Could not find a supported command to open URLs (xdg-open or open)."
		return 1
	fi
}
