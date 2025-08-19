#!/usr/bin/env bash
# File: utils/scripts/godot-scripts/gd-cpp-new-module.sh

# **TODO: Use new 'case.sh' helper for normalization

set -Eeuo pipefail

# ===== Script: test-common-utils.sh =====
# 
# (w.i.p)
# Automates GDExtension module creation with templates
# 
# ----------------------------------------------------------------------------

# -------- Shared utility sourcing -------------------------------------------
# Locate the project root via '.project-root' or '.git'
find_project_root() {
    local dir="$PWD"
    while [[ "$dir" != "/" ]]; do
        [[ -f "$dir/.project-root" ]] && { echo "$dir"; return 0; }
        [[ -d "$dir/.git" ]] 		  && { echo "$dir"; return 0; }
        dir="$(dirname "$dir")"
    done
    echo "Error: .project-root not found." >&2
    return 1
}
PROJECT_ROOT="$(find_project_root)" || exit 1

# Source all shared utilities through the aggregator
source "$PROJECT_ROOT/utils/scripts/helpers/common.sh"
# ----------------------------------------------------------------------------

escape_sed_repl() {
    # Escapes / & \ which are special in sed replacement
      printf '%s' "$1" | sed -e 's/[\/&\\]/\\&/g'
}

# ==============================
GAME_DIR="game"
GDEXT_TEMPLATE_DIR="utils/templates/gdext-templates"
SRC_ROOT="gdext/src"

# ---- Name input & normalization ------------------------------------------------
read -rp "Module/Class name (e.g., ExampleClass or example_class): " USER_INPUT
if [[ -z "${USER_INPUT:-}" ]]; then
    log_fatal "Module name cannot be empty. Exiting"
fi

# 1) Normalize to snake_case as an intermediate form.
#    - Split CamelCase -> snake (handles acronyms reasonably well)
#    - Convert separators (space, -, ., etc.) -> underscore
#    - Collapse multiple underscores; trim edges; lowercase
snake=$(
  printf '%s' "$USER_INPUT" \
  | sed -E '
      s/[^A-Za-z0-9]+/_/g;                       # non-alnum -> _
      s/([A-Z]+)([A-Z][a-z])/\1_\2/g;            # ABCd -> AB_Cd  (acronyms)
      s/([a-z0-9])([A-Z])/\1_\2/g;               # aB  -> a_B     (camel)
      s/_+/_/g; s/^_+//; s/_+$//;                # collapse/trim _
    ' \
  | tr '[:upper:]' '[:lower:]'
)

if [[ -z "$snake" ]]; then
    log_fatal "Name reduces to empty after normalization. Choose a different name."
fi

# 2) Tokens from snake_case
IFS='_' read -r -a _parts <<< "$snake"

# 3) MOD_NAME: all lowercase, no separators (exampleclass)
MOD_NAME="$(printf '%s' "${_parts[@]}")"

# If MOD_NAME would start with a digit, prefix with an underscore to make it a valid C symbol stem.
if [[ "$MOD_NAME" =~ ^[0-9] ]]; then
    MOD_NAME="_$MOD_NAME"
    log_warning "Note:${NC} name started with a digit; using '${MOD_NAME}' for symbols/paths."
fi

# 4) CLASS_NAME: PascalCase (ExampleClass)
CLASS_NAME=""
for w in "${_parts[@]}"; do
    # ^ = uppercase first char (bash 4+), rest stays lowercase because we normalized
    CLASS_NAME+="${w^}"
done

# 5) CLASS_NAME_UPPER: SCREAMING_SNAKE_CASE (EXAMPLE_CLASS)
CLASS_NAME_UPPER="$(tr '[:lower:]' '[:upper:]' <<< "$snake")"

# 6) (Optional) ENTRY_SYMBOL: consistent with MOD_NAME
ENTRY_SYMBOL="${MOD_NAME}_init"

# 7) Where to write
MODULE_DIR="${SRC_ROOT}/${MOD_NAME}"

# Show a quick summary
# echo -e "${CYAN}→ Resolved names:${NC}
#   MOD_NAME         = ${GREEN}${MOD_NAME}${NC}
#   CLASS_NAME       = ${GREEN}${CLASS_NAME}${NC}
#   CLASS_NAME_UPPER = ${GREEN}${CLASS_NAME_UPPER}${NC}
#   ENTRY_SYMBOL     = ${GREEN}${ENTRY_SYMBOL}${NC}
#   MODULE_DIR       = ${GREEN}${MODULE_DIR}${NC}"
# --------------------------------------------------------------------------------

if [ -d "$MODULE_DIR" ]; then
    log_fatal "Module '${MOD_NAME}' already exists at ${MODULE_DIR}."
fi

log_info "Creating GDExtension module '$CLASS_NAME'..."
mkdir -p "$MODULE_DIR"

# Generate files from templates
declare -A templates=(
    ["class.cpp.template"]="${CLASS_NAME}.cpp"
    ["class.h.template"]="${CLASS_NAME}.h"
    ["godot_includes.h.template"]="godot_includes.h"
    ["register_types.cpp.template"]="register_types.cpp"
    ["register_types.h.template"]="register_types.h"
    ["SConscript.template"]="SConscript"
)

MOD_NAME_E=$(escape_sed_repl "$MOD_NAME")
ENTRY_SYMBOL_E=$(escape_sed_repl "$ENTRY_SYMBOL")
CLASS_NAME_E=$(escape_sed_repl "$CLASS_NAME")
CLASS_NAME_UPPER_E=$(escape_sed_repl "$CLASS_NAME_UPPER")
GAME_DIR_E=$(escape_sed_repl "$GAME_DIR")

# Replace the placeholders in the templates
for tpl in "${!templates[@]}"; do
    src="${GDEXT_TEMPLATE_DIR}/${tpl}"
    dst="${MODULE_DIR}/${templates[$tpl]}"
    if [ ! -f "$src" ]; then
        log_fatal "Missing template: $src"
    fi

    sed \
        -e "s/{{LIB_NAME}}/${MOD_NAME_E}/g" \
        -e "s/{{ENTRY_SYMBOL}}/${ENTRY_SYMBOL_E}/g" \
        -e "s/{{CLASS_NAME}}/${CLASS_NAME_E}/g" \
        -e "s/{{CLASS_NAME_UPPER}}/${CLASS_NAME_UPPER_E}/g" \
        -e "s|{{GAME_DIR}}|${GAME_DIR_E}|g" \
        "$src" > "$dst"

    # sed \
    #     -e "s/{{LIB_NAME}}/${MOD_NAME}/g" \
    #     -e "s/{{ENTRY_SYMBOL}}/${ENTRY_SYMBOL}/g" \
    #     -e "s/{{CLASS_NAME}}/${CLASS_NAME}/g" \
    #     -e "s/{{CLASS_NAME_UPPER}}/${CLASS_NAME_UPPER}/g" \
    #     -e "s|{{GAME_DIR}}|${GAME_DIR}|g" \
    #     "$src" > "$dst"
    
    log_success "Generated: $dst"
done

# Generate the .gdextension file in game's bin/ directory
GAME_DIR_BIN="${GAME_DIR}/bin"
mkdir -p "$GAME_DIR_BIN"
GDEXT_TPL="${GDEXT_TEMPLATE_DIR}/libname.gdextension.template"
GDEXT_OUT="${GAME_DIR_BIN}/${MOD_NAME}.gdextension"

if [ ! -f "$GDEXT_TPL" ]; then
    log_fatal "Missing template: $GDEXT_TPL"
fi

sed \
    -e "s/{{LIB_NAME}}/${MOD_NAME}/g" \
    -e "s/{{ENTRY_SYMBOL}}/${ENTRY_SYMBOL}/g" \
    -e "s/{{GAME_DIR}}/${GAME_DIR}/g" \
    "$GDEXT_TPL" > "$GDEXT_OUT"

log_success "Wrote descriptor: ${GDEXT_OUT}"

log_success "GDExtension C++ module '${MOD_NAME}' created at '${MODULE_DIR}'."
