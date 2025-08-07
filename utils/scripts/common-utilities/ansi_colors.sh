#!/bin/bash

# Utility script for color-coded output in scripts
# 
# Usage:
# Can be used in other scripts on same directory level like this:
#	source "$(dirname "$0")/ansi_colors.sh"
# 
# Or if the script is called from a different working dir), use:
# 	source "$(cd "$(dirname "${BASH_SOURCE[0]}")" && cd <path-from-calling-script-to-/common-utilities> && pwd)/ansi_colors.sh"


# Text Reset
NC='\033[0m' # No Color

# Regular Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[0;37m'

# RGB Colors
ORANGE='\033[0;38;5;208m'

PINK='\033[0;38;5;205m'
PINK_HOT='\033[0;38;5;198m'
PINK_LIGHT='\033[0;38;5;200m'
PINK_PASTEL='\033[0;38;5;219m'

# Bold
BRED='\033[1;31m'
BGREEN='\033[1;32m'
BYELLOW='\033[1;33m'
BBLUE='\033[1;34m'
BPURPLE='\033[1;35m'
BCYAN='\033[1;36m'
BWHITE='\033[1;37m'
