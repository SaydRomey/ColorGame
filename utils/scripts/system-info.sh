#!/usr/bin/env bash
# File: utils/scripts/system-info.sh

set -Eeuo pipefail

# ===== Script: system-info.sh =====
# 
# Description:
#   Displays basic system information:
#     - System overview
#     - RAM
#     - Disk space
#     - CPU info
#     - GPU info
#     - OS info
#
# Optional flags:
#   --strict    Fail if optional commands are missing
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
# log_success "Script ${BGREEN}system-info.sh${NC} is working!"

STRICT=false

for arg in "$@"; do
    case "$arg" in
        --strict)
            STRICT=true
            ;;
        *)
            echo "Unknown option: $arg" >&2
            echo "Usage: $0 [--strict]" >&2
            exit 1
            ;;
    esac
done

PROJECT_ROOT="$(locate_project_root 2>/dev/null || true)"
if [[ -n "${PROJECT_ROOT:-}" && -f "$PROJECT_ROOT/utils/scripts/helpers/common.sh" ]]; then
    # shellcheck source=/dev/null
    source "$PROJECT_ROOT/utils/scripts/helpers/common.sh"
else
    SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
    # shellcheck source=/dev/null
    source "$SCRIPT_DIR/common.sh"
fi

# Core commands that should exist on most Linux systems
require_commands uname awk grep sed tr df free || exit 1

# Optional commands
OPTIONAL_CMDS=(lscpu lspci glxinfo lsb_release)
MISSING_OPTIONAL=()

for cmd in "${OPTIONAL_CMDS[@]}"; do
    if ! command -v "$cmd" >/dev/null 2>&1; then
        MISSING_OPTIONAL+=("$cmd")
    fi
done

if [[ "${#MISSING_OPTIONAL[@]}" -gt 0 ]]; then
    if [[ "$STRICT" == true ]]; then
        log_fatal "Missing optional command(s): ${MISSING_OPTIONAL[*]}"
    else
        log_warn "Some optional commands are missing: ${MISSING_OPTIONAL[*]}"
    fi
fi

echo "=== System Info ==="

# -----------------------------------------------------------------------------
# System Overview
# -----------------------------------------------------------------------------
echo
echo "🖥️  System Overview:"
hostname="$(uname -n)"
kernel="$(uname -r)"
arch="$(uname -m)"

echo "Hostname: $hostname"
echo "Kernel Version: $kernel"
echo "Architecture: $arch"

# -----------------------------------------------------------------------------
# RAM
# -----------------------------------------------------------------------------
echo
echo "🧠 RAM:"
if command -v free >/dev/null 2>&1; then
    free -h | awk '/^Mem:/ { print "Available:", $7, "/ Total:", $2 }'
else
    log_warn "free not available; skipping RAM section"
fi

# -----------------------------------------------------------------------------
# Disk Space
# -----------------------------------------------------------------------------
echo
echo "💾 Disk Space:"
if command -v df >/dev/null 2>&1; then
    df -h --output=source,target,avail,size | grep -v tmpfs
else
    log_warn "df not available; skipping disk space section"
fi

# -----------------------------------------------------------------------------
# CPU Info
# -----------------------------------------------------------------------------
echo
echo "⚙️  CPU Info:"
if command -v lscpu >/dev/null 2>&1; then
    lscpu | awk -F: '
        /Model name/ {gsub(/^[ \t]+/, "", $2); print "Model:", $2}
        /^CPU\(s\)/ {gsub(/^[ \t]+/, "", $2); print "Cores:", $2}
    '
else
    log_warn "lscpu not available; skipping CPU section"
fi

# -----------------------------------------------------------------------------
# GPU Info
# -----------------------------------------------------------------------------
echo
echo "🎮 GPU Info:"
gpu_printed=false

if command -v lspci >/dev/null 2>&1; then
    lspci | grep -i 'vga' | sed 's/^/VGA: /' || true
    gpu_printed=true
fi

if command -v glxinfo >/dev/null 2>&1; then
    glxinfo 2>/dev/null | grep "OpenGL renderer" | sed 's/OpenGL renderer string: /OpenGL Renderer: /' || true
    glxinfo 2>/dev/null | grep -E "OpenGL version" | sed 's/OpenGL version string: /OpenGL Version: /' || true
    gpu_printed=true
fi

if [[ "$gpu_printed" == false ]]; then
    log_warn "No GPU info commands available; skipping GPU section"
fi

# -----------------------------------------------------------------------------
# OS Info
# -----------------------------------------------------------------------------
echo
echo "💻 OS:"
if command -v lsb_release >/dev/null 2>&1; then
    lsb_release -a 2>/dev/null | awk -F: '
        /Description/ {gsub(/^[ \t]+/, "", $2); printf "OS: %s ", $2}
        /Codename/ {gsub(/^[ \t]+/, "", $2); print "Codename:", $2}
    '
else
    log_warn "lsb_release not available; skipping OS section"
fi
