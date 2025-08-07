#!/usr/bin/env bash
# POSIX-ish realpath fallback with optional --relative-to=BASE
set -euo pipefail

relto=""
path_arg=""

for arg in "$@"; do
  case "$arg" in
    --relative-to=*)
      relto="${arg#--relative-to=}"
      ;;
    --relative-to)
      # support split form: --relative-to BASE
      shift
      relto="$1"
      ;;
    *)
      path_arg="$arg"
      ;;
  esac
done

if [[ -z "${path_arg:-}" ]]; then
  echo "Usage: $0 [--relative-to=BASE] PATH" >&2
  exit 2
fi

# Try system realpath if it exists (helps if user later installs it)
if command -v realpath >/dev/null 2>&1; then
  if [[ -n "$relto" ]]; then
    exec realpath --relative-to="$relto" "$path_arg"
  else
    exec realpath "$path_arg"
  fi
fi

# Try readlink -f if available (often Linux only)
if readlink -f / >/dev/null 2>&1; then
  abs="$(readlink -f "$path_arg")"
else
  # Naive absolute path resolution
  abs="$(
    cd "$(dirname "$path_arg")" >/dev/null 2>&1 && pwd
  )/$(basename "$path_arg")"
fi

if [[ -n "$relto" ]]; then
  # Compute naive relative path by stripping prefix if applicable
  case "$abs" in
    "$relto"/*) printf "%s\n" "${abs#$relto/}" ;;
    *)          printf "%s\n" "$abs" ;;
  esac
else
  printf "%s\n" "$abs"
fi