#!/usr/bin/env bash

# ===== Utility Script: commands.sh =====
# 
# Command helpers for scripts.
# 
# Designed to be *sourced* (not executed)
# =======================================

require_commands() {
    local missing=0
    for cmd in "$@"; do
        if ! command -v "$cmd" >/dev/null 2>&1; then
            echo "Required command not found: $cmd" >&2
            missing=1
        fi
    done
    return "$missing"
}

detect_first_available_command() {
    local array_name="$1"
    shift

    local cmd
    for cmd in "$@"; do
        if command -v "$cmd" >/dev/null 2>&1; then
            printf -v "$array_name" '%s' "$cmd"
            return 0
        fi
    done

    return 1
}
