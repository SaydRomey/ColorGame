#!/usr/bin/env bash
# File: utils/scripts/docx-to-txt.sh

set -Eeuo pipefail

# ===== Script: docx-to-txt.sh =====
#
# Description:
#   Converts all .docx files in a specified directory (default: current directory)
#   to .txt format. Supports the following tools, in this order of preference:
#     - pandoc
#     - docx2txt
#     - libreoffice (headless mode)
#
#   Features:
#     - Prompts user for directory (defaults to current)
#     - Lists .docx files and asks for confirmation before converting
#     - Converts each file to .txt using the best available tool
#     - Displays a summary of original and newly created files
#     - Handles missing tools with a helpful message
#
# Optional flags:
#   --show-tool    Print the converter selected by the script
# 
# Notes:
#   - Formatting, images, tables, headers/footers, and tracked changes may not
#     survive cleanly in plain text output.
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
# log_success "Script ${BGREEN}docx-to-txt.sh${NC} is working!"

SHOW_TOOL=false

for arg in "$@"; do
    case "$arg" in
        --show-tool)
            SHOW_TOOL=true
            ;;
        *)
            echo "Unknown option: $arg"
            echo "Usage: $0 [--show-tool]"
            exit 1
            ;;
    esac
done

if detect_first_available_command CONVERT_CMD pandoc docx2txt libreoffice; then
    :
else
    echo "No suitable .docx conversion tool found."
    echo "Please install one of: pandoc, docx2txt, libreoffice"
    exit 1
fi

if [ "$SHOW_TOOL" = true ]; then
    echo "Using converter: $CONVERT_CMD"
fi

prompt_for_directory || exit 1

find_files_by_extension "$DIR" "docx" DOCX_FILES

if [ "${#DOCX_FILES[@]}" -eq 0 ]; then
    echo "No .docx files found in $DIR"
    exit 0
fi

print_file_list "Found the following .docx files:" "${DOCX_FILES[@]}"

confirm_action "Do you want to convert these files to .txt? (y/n): " || {
    echo "Operation cancelled."
    exit 0
}

TXT_FILES=()

for file in "${DOCX_FILES[@]}"; do
    txt_file="${file%.docx}.txt"

    case "$CONVERT_CMD" in
        pandoc)
            pandoc "$file" -t plain -o "$txt_file"
            ;;
        docx2txt)
            docx2txt "$file" - > "$txt_file"
            ;;
        libreoffice)
            outdir="$(dirname "$file")"
            libreoffice --headless --convert-to txt:Text --outdir "$outdir" "$file" >/dev/null 2>&1
            ;;
    esac

    [ -f "$txt_file" ] && TXT_FILES+=("$txt_file")
done

echo
print_file_list "Original .docx files:" "${DOCX_FILES[@]}"
echo
print_file_list "New .txt files:" "${TXT_FILES[@]}"
