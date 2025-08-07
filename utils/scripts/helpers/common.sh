
# ==============================

#!/bin/bash
# utils/scripts/helpers/common.sh
#
# Purpose:
# =========
# This is an **aggregator** script that:
#   1. Prevents multiple sourcing (so it won't re-import helpers)
#   2. Automatically sources all helper `.sh` scripts in the same folder
#      (except itself).
#   3. Defines common utility functions (e.g., realpath_fallback).
#
# How to use:
# ===========
# In any other script that needs helpers, just add:
#
#   source "$(dirname "$0")/../helpers/common.sh"
#
# Or, if your script might be called from anywhere, use:
#
#   source "$(cd "$(dirname "${BASH_SOURCE[0]}")" && cd ../helpers && pwd)/common.sh"
#
# Once sourced, you can directly call:
#
#   resolved_path="$(realpath_fallback ./relative/path.txt)"
#   echo "Absolute path is: $resolved_path"
#

# -------------------------------------------------------------------------
# Prevent multiple sourcing (idempotent import)
# -------------------------------------------------------------------------
[[ -n "$__COMMON_SH_IMPORTED" ]] && return 0
__COMMON_SH_IMPORTED=1

# -------------------------------------------------------------------------
# Source all helper scripts in this folder, excluding this file
# -------------------------------------------------------------------------
for file in "${BASH_SOURCE%/*}"/*.sh; do
    [[ "$file" != *"/common.sh" ]] && source "$file"
done

# -------------------------------------------------------------------------
# Function: realpath_fallback
#
# Purpose:
#   Resolve an absolute path from a relative or symbolic path.
#   Works even if `realpath` is not installed.
#
# Parameters:
#   $1 → Path to resolve (relative or absolute)
#
# Behavior:
#   1. Uses system `realpath` if available
#   2. Falls back to `readlink -f` (Linux usually)
#   3. Naively resolves via `cd` + `pwd` if neither is available
#
# Example usage:
#   abs_path="$(realpath_fallback ./file.txt)"
#   echo "$abs_path"
# -------------------------------------------------------------------------
realpath_fallback() {
    local target="$1"
    if command -v realpath >/dev/null 2>&1; then
        realpath "$target"
    elif readlink -f / >/dev/null 2>&1; then
        readlink -f "$target"
    else
        ( cd "$(dirname "$target")" >/dev/null 2>&1 && pwd )/$(basename "$target")
    fi
}