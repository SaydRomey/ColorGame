#!/usr/bin/env bash

# ===== Utility Script: output.sh =====
# 
# Output helpers for scripts.
# 
# Designed to be *sourced* (not executed)
# =======================================


print_result_summary() {
    local original_heading="$1"
    local new_heading="$2"
    shift 2

    local separator_index="$1"
    shift

    local originals=("${@:1:$separator_index}")
    local news=("${@:$((separator_index + 1))}")

    echo
    echo "$original_heading"
    local f
    for f in "${originals[@]}"; do
        echo "  $(basename "$f")"
    done

    echo
    echo "$new_heading"
    for f in "${news[@]}"; do
        echo "  $(basename "$f")"
    done
}


safe_target_name() {
    local dir="$1"
    local candidate="$2"

    local base ext n target

    if [[ "$candidate" == *.* && "$candidate" != .* ]]; then
        base="${candidate%.*}"
        ext=".${candidate##*.}"
    else
        base="$candidate"
        ext=""
    fi

    target="$dir/$candidate"
    n=1
    while [ -e "$target" ]; do
        target="$dir/${base}-$n$ext"
        ((n++))
    done

    printf '%s\n' "$target"
}
