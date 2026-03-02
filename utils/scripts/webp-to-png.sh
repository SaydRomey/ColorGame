#!/usr/bin/env bash
# File: utils/scripts/webp-to-png.sh

set -Eeuo pipefail

# ===== Script: webp-to-png.sh =====
# 
# Description:
#   Converts all .webp files in a specified directory (default: current directory)
#   to .png format. Supports the following tools, in this order of preference:
#     - magick (ImageMagick v7+)
#     - convert (ImageMagick v6)
#     - ffmpeg
#
#   Features:
#     - Prompts user for directory (defaults to current)
#     - Lists .webp files and asks for confirmation before converting
#     - Converts each file to .png using the best available tool
#     - Displays a summary of original and newly created files
#     - Handles missing tools with a helpful message
#
# Optional flags:
#   --show-tool    Print the converter selected by the script
# 
# 
# Utility functions and macros sourced via utils/scripts/helpers/common.sh.
# 
# ----------------------------------------------------------------------------

# -------- Shared utility sourcing -------------------------------------------
# Locate the project root via '.project-root' or '.git'
find_project_root() {
	local dir="$PWD"
	while [[ "$dir" != "/" ]]; do
		[[ -f "$dir/.project-root" ]] && { echo "$dir"; return 0; }
		[[ -d "$dir/.git" ]] && { echo "$dir"; return 0; }
		dir="$(dirname "$dir")"
	done
	echo "Error: .project-root not found." >&2
	return 1
}
PROJECT_ROOT="$(find_project_root)" || exit 1

# Source all shared utilities through the aggregator
source "$PROJECT_ROOT/utils/scripts/helpers/common.sh"
# ----------------------------------------------------------------------------

# -------- Script logic starts here ------------------------------------------
# log_info "Project root detected: ${BPURPLE}$PROJECT_ROOT${NC}"
# log_info "Utilities sourced from: ${BBLUE}$PROJECT_ROOT/utils/scripts/helpers/common.sh${NC}"
# log_success "Script ${BGREEN}webp-to-png.sh${NC} is working!"

SHOW_TOOL=false

for arg in "$@"; do
    case "$arg" in
        --show-tool)
            SHOW_TOOL=true
            ;;
        *)
            echo "Unknown option: $arg" >&2
            echo "Usage: $0 [--show-tool]" >&2
            exit 1
            ;;
    esac
done

if ! detect_first_available_command CONVERT_CMD magick convert ffmpeg; then
    echo "No suitable image conversion tool found."
    echo "Please install one of the following:"
    echo "  sudo apt install imagemagick"
    echo "  or"
    echo "  sudo apt install ffmpeg"
    exit 1
fi

if [[ "$SHOW_TOOL" == true ]]; then
    echo "Using converter: $CONVERT_CMD"
fi

prompt_for_directory "Enter directory to process [default: current]: " || exit 1

find_files_by_extension "$DIR" "webp" WEBP_FILES

if [[ "${#WEBP_FILES[@]}" -eq 0 ]]; then
    echo "No .webp files found in $DIR"
    exit 0
fi

print_file_list "Found the following .webp files:" "${WEBP_FILES[@]}"

if ! confirm_action "Do you want to convert these files to .png? (y/n): "; then
    echo "Operation cancelled."
    exit 0
fi

PNG_FILES=()

for file in "${WEBP_FILES[@]}"; do
    png_file="${file%.webp}.png"

    if [[ "$CONVERT_CMD" == "ffmpeg" ]]; then
        ffmpeg -loglevel error -y -i "$file" "$png_file"
    else
        "$CONVERT_CMD" "$file" "$png_file"
    fi

    if [[ -f "$png_file" ]]; then
        PNG_FILES+=("$png_file")
    else
        echo "Failed to convert: $(basename "$file")" >&2
    fi
done

echo
print_file_list "Original .webp files:" "${WEBP_FILES[@]}"

echo
print_file_list "New .png files:" "${PNG_FILES[@]}"
