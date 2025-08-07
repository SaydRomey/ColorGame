#!/bin/bash
# utils/scripts/helpers/common.sh
# Aggregator: sources all helper scripts in this folder (except itself)

# Prevent multiple sourcing (idempotent import)
[[ -n "$__COMMON_SH_IMPORTED" ]] && return 0
__COMMON_SH_IMPORTED=1

# # Determine directory of this script
# HELPER_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# # Source all .sh files in the helpers dir, excluding this one
# for file in "$HELPER_DIR"/*.sh; do
# 	[[ "$file" != *"/common.sh" ]] && source "$file"
# done

# Automatically source all *.sh files in helpers folder
for file in "${BASH_SOURCE%/*}"/*.sh; do
	[[ "$file" != *"/common.sh" ]] && source "$file"
done

# ==============================
