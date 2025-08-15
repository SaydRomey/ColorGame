#!/bin/bash
# utils/scripts/godot/gd-cpp-new-module.sh

# TODO: take class name as is, then create an all lowercase and all uppercase version. (so we can enter "OtherClass", and obtain "otherclass"/"OTHER_CLASS")

set -Eeuo pipefail

# ===== Script: test-common-utils.sh =====
# This script exercises *all* helpers sourced via helpers/common.sh.

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

# ==============================
GAME_DIR="game"
GDEXT_TEMPLATE_DIR="utils/templates/gdext-templates"
SRC_ROOT="gdext/src"

read -rp "Module name (lowercase): " MOD_NAME
if
 [[ -z "$MOD_NAME" ]]; then
	# log_fatal "Module name cannot be empty."
	echo -e "${RED}Module name cannot be empty.${NC}"
	exit 1
fi

CLASS_NAME="$(tr '[:lower:]' '[:upper:]' <<< ${MOD_NAME:0:1})${MOD_NAME:1}"
CLASS_NAME_UPPER="$(echo "$CLASS_NAME" | tr '[:lower:]' '[:upper:]')"
MODULE_DIR="${SRC_ROOT}/${MOD_NAME}"

if [ -d "$MODULE_DIR" ]; then
	# log_fatal "Module '${MOD_NAME}' already exists at ${MODULE_DIR}."
	echo -e "${RED}Module '${MOD_NAME}' already exists at ${MODULE_DIR}.${NC}"
	exit 1
fi

# log_info "Creating GDExtension module '$CLASS_NAME'..."
echo -e "${CYAN}Creating GDExtension module '$CLASS_NAME'...${NC}"
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

# ["libname.gdextension.template"]="${MOD_NAME}.gdextension"


for tpl in "${!templates[@]}"; do
	src="${GDEXT_TEMPLATE_DIR}/${tpl}"
	dst="${MODULE_DIR}/${templates[$tpl]}"
	if [ ! -f "$src" ]; then
		# log_fatal "Missing template: $src"
		echo -e "${RED}Missing template: $src${NC}"
		exit 1
	fi

	sed \
		-e "s/{{LIB_NAME}}/${MOD_NAME}/g" \
		-e "s/{{ENTRY_SYMBOL}}/${MOD_NAME}_init/g" \
		-e "s/{{CLASS_NAME}}/${CLASS_NAME}/g" \
		-e "s/{{CLASS_NAME_UPPER}}/${CLASS_NAME_UPPER}/g" \
		-e "s/{{GAME_DIR}}/${GAME_DIR}/g" \
		"$src" > "$dst"
	
	# log_success "Generated: $dst"
	echo -e "${GREEN}✔️  Generated: $dst${NC}"
done

# Generate the .gdextension file in game's bin/ directory
GAME_DIR_BIN="${GAME_DIR}/bin"
mkdir -p "$GAME_DIR_BIN"
GDEXT_TPL="${GDEXT_TEMPLATE_DIR}/libname.gdextension.template"
GDEXT_OUT="${GAME_DIR_BIN}/${MOD_NAME}.gdextension"

if [ ! -f "$GDEXT_TPL" ]; then
	echo -e "${RED}Missing template: $GDEXT_TPL${NC}"
	exit 1
fi

sed \
	-e "s/{{LIB_NAME}}/${MOD_NAME}/g" \
	-e "s/{{ENTRY_SYMBOL}}/${MOD_NAME}_init/g" \
	-e "s/{{GAME_DIR}}/${GAME_DIR}/g" \
	"$GDEXT_TPL" > "$GDEXT_OUT"

# log_success "Wrote descriptor: ${GDEXT_OUT}"
echo -e "${GREEN}✔️  Wrote descriptor: ${GDEXT_OUT}${NC}"

# GAME_DIR_BIN="${GAME_DIR}/bin"
# EXTENSION_FILE="${MOD_NAME}.gdextension"
# EXTENSION_FILE_SRC="${MODULE_DIR}/${EXTENSION_FILE}"
# EXTENSION_FILE_DST="${GAME_DIR_BIN}/${EXTENSION_FILE}"
# if [ ! -f "$EXTENSION_FILE_DST" ]; then
# 	mkdir -p "$GAME_DIR_BIN"
# 	cp "$EXTENSION_FILE_SRC" "$EXTENSION_FILE_DST"
# 	# log_success "Copied: $EXTENSION_FILE_SRC to $EXTENSION_FILE_DST"
# 	echo -e "${GREEN}✔️  Copied: $EXTENSION_FILE_SRC to $EXTENSION_FILE_DST${NC}"
# fi

# # Create godot_includes.hpp if not already present (**might remove, now handled with template)
# INCLUDES_FILE="${MODULE_DIR}/godot_includes.h"
# if [ ! -f "$INCLUDES_FILE" ]; then
# 	cat <<EOF > "$INCLUDES_FILE"
# #pragma once

# #include <godot_cpp/core/class_db.hpp>
# #include <godot_cpp/classes/node.hpp>
# #include <godot_cpp/variant/utility_functions.hpp>

# using namespace godot;
# EOF
# 	# log_success "Created: $INCLUDES_FILE"
# 	echo -e "${GREEN}✔️  Created: $INCLUDES_FILE${NC}"
# fi

# log_success "GDExtension C++ module '${MOD_NAME}' created at '${MODULE_DIR}'."
echo -e "${GREEN}GDExtension C++ module '${MOD_NAME}' created at '${MODULE_DIR}'.${NC}"
