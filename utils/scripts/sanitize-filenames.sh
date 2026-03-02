#!/usr/bin/env bash
# File: utils/scripts/sanitize-filenames.sh

set -Eeuo pipefail

# ===== Script: sanitize-filenames.sh =====
# 
# Description:
#   Renames files in a specified directory so filenames become:
#     - lowercase
#     - ASCII-only
#     - normalized with underscores between words
#     - stripped of emoji / other non-ASCII chars
#
# Examples:
#   "🧬 Hello___World!!.pdf"
#   -> "hello_world.pdf"
#
#   "--Strange Name-- .doc"
#   -> "strange_name.doc"
#
# Requirements:
#   bash, iconv, sed, tr
#
# Optional flags:
#   --dry-run       Show what would change without renaming
#   --show-changes  Print each rename as it happens
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
# log_success "Script ${BGREEN}sanitize-filenames.sh${NC} is working!"

PROJECT_ROOT="$(locate_project_root 2>/dev/null || true)"
if [[ -n "${PROJECT_ROOT:-}" && -f "$PROJECT_ROOT/utils/scripts/helpers/common.sh" ]]; then
    # shellcheck source=/dev/null
    source "$PROJECT_ROOT/utils/scripts/helpers/common.sh"
else
    SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
    # shellcheck source=/dev/null
    source "$SCRIPT_DIR/common.sh"
fi

DRY_RUN=false
SHOW_CHANGES=false

for arg in "$@"; do
    case "$arg" in
        --dry-run)
            DRY_RUN=true
            ;;
        --show-changes)
            SHOW_CHANGES=true
            ;;
        *)
            echo "Unknown option: $arg" >&2
            echo "Usage: $0 [--dry-run] [--show-changes]" >&2
            exit 1
            ;;
    esac
done

require_commands iconv sed tr || exit 1

prompt_for_directory "Enter directory to process [default: current]: " || exit 1

shopt -s nullglob
FILES=("$DIR"/*)
shopt -u nullglob

if [[ "${#FILES[@]}" -eq 0 ]]; then
    echo "No files found in $DIR"
    exit 0
fi

sanitize_name() {
    local name="$1"
    local base ext ascii_base sanitized

    if [[ "$name" == *.* && "$name" != .* ]]; then
        base="${name%.*}"
        ext=".${name##*.}"
    else
        base="$name"
        ext=""
    fi

    # Normalize common Unicode dash variants to spaces before ASCII conversion,
    # so they become token separators rather than being dropped awkwardly.
    ascii_base="$(
        printf '%s' "$base" \
        | sed 's/[‐-‒–—−]/ /g' \
        | iconv -f UTF-8 -t ASCII//TRANSLIT 2>/dev/null
    )"

    # Convert to snake_case while preserving underscores as separators.
    sanitized="$(to_snake "$ascii_base")"

    # Fallback if basename becomes empty
    if [[ -z "$sanitized" ]]; then
        sanitized="file"
    fi

    ext="$(printf '%s' "$ext" | tr '[:upper:]' '[:lower:]')"

    printf '%s%s\n' "$sanitized" "$ext"
}

OLD_FILES=()
NEW_FILES=()

for path in "${FILES[@]}"; do
    [[ -f "$path" ]] || continue

    old_name="$(basename "$path")"
    dir_name="$(dirname "$path")"
    new_name="$(sanitize_name "$old_name")"

    [[ "$old_name" == "$new_name" ]] && continue

    target="$(safe_target_name "$dir_name" "$new_name")"

    OLD_FILES+=("$path")
    NEW_FILES+=("$target")
done

if [[ "${#OLD_FILES[@]}" -eq 0 ]]; then
    echo "No files need renaming in $DIR"
    exit 0
fi

echo "Planned renames:"
for i in "${!OLD_FILES[@]}"; do
    echo "  $(basename "${OLD_FILES[$i]}")"
    echo "    -> $(basename "${NEW_FILES[$i]}")"
done

if [[ "$DRY_RUN" == true ]]; then
    echo
    echo "Dry run only. No files were renamed."
    exit 0
fi

if ! confirm_action "Do you want to rename these files? (y/n): "; then
    echo "Operation cancelled."
    exit 0
fi

RENAMED=0
for i in "${!OLD_FILES[@]}"; do
    mv -- "${OLD_FILES[$i]}" "${NEW_FILES[$i]}"
    ((RENAMED++))
    if [[ "$SHOW_CHANGES" == true ]]; then
        echo "Renamed: $(basename "${OLD_FILES[$i]}") -> $(basename "${NEW_FILES[$i]}")"
    fi
done

echo
echo "Renamed $RENAMED file(s)."
