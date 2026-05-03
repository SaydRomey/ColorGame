#!/usr/bin/env bash
# File: utils/scripts/test-common-utils.sh

set -Eeuo pipefail

# ===== Script: test-common-utils.sh =====
# 
# Script to test all shared utilities
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

boxed_title "Testing all shared utility functions" 40 double

# -------- logging-formatting.sh ---------------------------------------------
title "Testing logging formatting and boxes"

# -------- Uncomment for man-like info
# logging_help
# -------- 

run_logging_formatting_tests()
{
	_function_tester nl
	_function_tester repeat_char "~" 10
	_function_tester separator 80 "*"
	_function_tester title "Example Title" 60
	_function_tester subtitle "Example subtitle"
	_function_tester boxed_title "Small Box" 20 single
	_function_tester boxed_title "Round Box" 40 rounded
	_function_tester boxed_title "Big Box" 60 double
	_function_tester ascii_box_line 20
	_function_tester ascii_box_title "ASCII is cool!!!" 40
}

run_logging_formatting_tests

# -------- logging.sh --------------------------------------------------------
title "Testing logging utils"

test_logging_utils()
{
	subtitle "no timestamps (default)"
	log_info     "This is an info message"
	log_warn     "This is a warning"
	log_error    "This is an error (goes to stderr)"
	log_success  "This is a success message"
	# ==============================
	# log_info     "info (no ts)"
	# log_warn     "warn (no ts)"
	# log_success  "success (no ts)"
	# log_error    "error (no ts)"
	# ==============================

	# ==============================
	subtitle "one-liner with timestamp"
	with_ts log_info "info (ts one-liner)"

	# ==============================
	subtitle "block with timestamp"
	ts_push
	log_info    "info (ts block)"
	log_warn    "warn (ts block)"
	log_success "success (ts block)"
	log_error   "error (ts block)"
	ts_pop

	# ==============================
	subtitle "back to no timestamps"
	log_info "info (back to no ts)"

	# ==============================
	subtitle "Testing with timestamps (setting LOG_TS=true inside block)"
	(
		LOG_TS=true
		log_info "Timestamped info"
		log_warn "Timestamped warning"
		log_success "Timestamped success"
		log_error "Timestamped error"
	)
	log_info "checking that LOG_TS is false outside scope...\n"

	# log_fatal "PROBLEM"
	# log_info  "should not print"
}

test_logging_utils
log_success "Test logging utils done!"
# ----------------------------------------------------------------------------
# # no timestamps (default)
# log_info     "This is an info message"
# log_warn     "This is a warning"
# log_error    "This is an error (goes to stderr)"
# log_success  "This is a success message"

# # ==============================
# subtitle "Testing with timestamps"
# (
# 	LOG_TS=true
# 	log_info "Timestamped info"
# 	log_warn "Timestamped warning"
# 	log_success "Timestamped success"
# 	log_error "Timestamped error"
# )
# # ==============================
# # # one-liner with timestamp
# with_ts log_info "info (ts one-liner)"

# # block with timestamp
# ts_push
# log_info    "info (ts block)"
# log_warn    "warn (ts block)"
# log_success "success (ts block)"
# log_error   "error (ts block)"
# ts_pop

# # back to no timestamps
# log_info "info (back to no ts)"


# -------- spinner.sh --------------------------------------------------------
title "Testing spinners"

start_spinner "Simulating success..."
sleep 2
true
stop_spinner $?   # expect ✓

# **TODO: Handle stopping the spinner on failure..
start_spinner "Simulating failure..."
sleep 2
false || true     # keep script running
stop_spinner $?   # expect ✗
log_warn "TODO: have the ${RED}[✖]${NC} in this failure test..."
# ----------------------------------------------------------------------------

# -------- fs.sh: ensure_dir, exists, ensure_executable ----------------------
BUILD_DIR="$PROJECT_ROOT/build"
ensure_dir "$BUILD_DIR" && log_success "ensure_dir created or verified: $BUILD_DIR"

TMP_SCRIPT="$BUILD_DIR/test-from-script.sh"
# ==============================
SCRIPT_CONTENT=$(cat <<EOF
#!/bin/bash

# ===== Test Script: $(basename "$TMP_SCRIPT") =====

NC="\033[0m"
CYAN="\033[36m"

echo -e "\nHello from the build directory"
echo -e "Generated from \${CYAN}$PROJECT_ROOT/utils/scripts/test-common-utils.sh\${NC}\n"
EOF
)
echo "$SCRIPT_CONTENT" > "$TMP_SCRIPT"
# ==============================
# cat > "$TMP_SCRIPT" << 'EOF'
# #!/usr/bin/env bash
# echo ""
# echo "Hello from test-from-script.sh"
# echo ""
# EOF
# ==============================
# ensure_executable "$TMP_SCRIPT" && log_success "$(basename "$TMP_SCRIPT") is now executable"
ensure_executable "$TMP_SCRIPT"
exists "$TMP_SCRIPT" && log_success "exists confirms: $TMP_SCRIPT"
# ==============================
# log_info "Generated script content:"
# cat "$TMP_SCRIPT"
# ==============================
log_info "Executing $(basename "$TMP_SCRIPT"): "
"$TMP_SCRIPT"

# mktemp_dir returns a fresh temp dir, with_tempdir sets CG_TMPDIR and cleans at EXIT
TMP_ONE="$(mktemp_dir)"
log_info "mktemp_dir -> ${BBLUE}$TMP_ONE${NC}"
[[ -d "$TMP_ONE" ]] || log_error "mktemp_dir did not create a directory"

# Use a subshell to demonstrate with_tempdir auto-cleanup:
(
	with_tempdir
	log_info "with_tempdir created CG_TMPDIR=${BBLUE}$CG_TMPDIR${NC}"
	[[ -d "$CG_TMPDIR" ]] && touch "$CG_TMPDIR/hello.txt"
	log_info "Leaving subshell; CG_TMPDIR should be removed by trap"
)
# After subshell exits, CG_TMPDIR should be gone; we can’t reference its value here,
# but we can at least show the mechanism worked by not erroring.
# ----------------------------------------------------------------------------

# -------- project-root.sh: locate_project_root -------------------------------
ROOT_FROM_HELPER="$(locate_project_root)"
if [[ "$ROOT_FROM_HELPER" == "$PROJECT_ROOT" ]]; then
  log_success "find_project_root matches: $ROOT_FROM_HELPER"
else
  log_warn "find_project_root mismatch: script=$PROJECT_ROOT helper=$ROOT_FROM_HELPER"
fi
# ----------------------------------------------------------------------------

# -------- realpath_fallback -------------------------------------------------
# Make a relative path and resolve it
REL_PATH="build/../build/test-from-script.sh"
ABS1="$(realpath_fallback "$REL_PATH")"
ABS2="$(realpath_fallback "$TMP_SCRIPT")"
log_info "realpath_fallback('$REL_PATH') -> ${CYAN}$ABS1${NC}"
log_info "realpath_fallback('$TMP_SCRIPT') -> ${CYAN}$ABS2${NC}"
[[ "$ABS2" == "$ABS1" ]] && log_success "realpath_fallback resolves consistently"
# ----------------------------------------------------------------------------

# -------- prompt.sh: yes_no and select_menu --------------------------------
# 
# (TMP, will set this flag with a makefile target..)
INTERACTIVE=1

if [[ "$INTERACTIVE" == "1" ]]; then
	if yes_no "Open repository in browser?" "n"; then
		open_url "https://github.com/SaydRomey/ColorGame" || log_warn "open_url failed (no opener?)"
	else
		log_info "Skipped open_url"
	fi

	if select_menu "Pick a color" "Red" "Green" "Blue"; then
		log_success "You selected: ${BBLUE}${SELECT_MENU_CHOICE}${NC}"
	else
		log_warn "No selection made"
	fi
else
	log_info "Skipping interactive prompt tests (run with INTERACTIVE=1 to enable)"
fi

log_success "All utility tests completed."
# ----------------------------------------------------------------------------
