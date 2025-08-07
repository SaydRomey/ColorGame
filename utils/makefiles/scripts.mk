
# ==============================
##@ 📜 Scripts
# ==============================
SCRIPT_TEMPLATE	:= utils/templates/new-script.sh.template
PROJECT_ROOT	:= .project-root

# Scripts Paths  (relative to the main Makefile's location)
SCRIPT_DIR		:= ./utils/scripts
SCRIPT_MISC		:= $(SCRIPT_DIR)/misc-scripts
SCRIPT_COLOR	:= $(SCRIPT_DIR)/color-scripts

# Scripts
SHOW_COLORS		:= $(SCRIPT_MISC)/show-colors.sh
TEST_SCRIPT		:= $(SCRIPT_DIR)/test-script.sh

# Color-related Scripts
COLOR_PIXEL_PNG	:= $(SCRIPT_COLOR)/color-pixel-png.sh
COLOR_INFO		:= $(SCRIPT_COLOR)/color-info.sh

# Scripts Logs and Artifacts
SCRIPT_LOG_DIR	:= ./utils/scripts/tmp_scripts_logs
SCRIPT_LOG_FILE	:= $(SCRIPT_LOG_DIR)/SCRIPT_$(TIMESTAMP).log
# SCRIPT_ARTIFACTS	:= 

# ==============================
# Script Related Utilty Macros
# ==============================

# Macro: RUN_SCRIPT
# Run a script with optional logging
# 
# Parameters:
# $(1): Name of the script (for logging and clarity).
# $(2): Path to the script.
# $(3): Boolean to enable logging
# 
# Behavior:
# Ensures the script exists and is executable.
# Runs the script.
# If logging is enabled, appends the output to a log file.
# Displays appropriate success messages based on logging status.
# 
# Example Usage:
# $(call RUN_SCRIPT,Create Users,$(SHOW_COLORS))
# $(call RUN_SCRIPT,Create Users,$(SHOW_COLORS),true)
# 
define RUN_SCRIPT
	if [ ! -f "$(2)" ]; then \
		$(call ERROR,Script Missing: ,Script '$(2)' does not exist.); \
		exit 1; \
	fi; \
	if [ ! -x "$(2)" ]; then \
		chmod +x $(2); \
	fi; \
	$(call INFO,Scripts,$(ORANGE)Running '$(1)' script...); \
	if [ "$(3)" = "true" ]; then \
		$(2) >> $(SCRIPT_LOG_FILE) 2>&1; \
		$(call SUCCESS,Scripts,Script '$(1)' executed successfully.); \
		$(call INFO,Scripts,Logged in $(SCRIPT_LOG_FILE)); \
	else \
		$(2); \
		$(call SUCCESS,Scripts,Script '$(1)' executed successfully.); \
	fi
endef

# **************************************************************************** #

run-script:
	@$(call RUN_SCRIPT,$(SCRIPT_TYPE),$(SCRIPT_CHOICE),$(LOG_ENABLED))

script: | $(SCRIPT_LOG_DIR) ## Interactive script selection menu
	@bash -c '\
		clear; \
		read -p "Do you want to log script output? (y/n): " log_choice; \
		if [ "$$log_choice" = "y" ] || [ "$$log_choice" = "Y" ] || [ -z "$$log_choice" ]; then \
			LOG_ENABLED=true; \
		else \
			LOG_ENABLED=false; \
		fi; \
		\
		echo ""; \
		echo "📜 Choose a script to run:"; \
		echo "Misc"; \
		echo "0) Display Terminal Colors"; \
		echo "42) Try a tester script"; \
		echo "Color Utilities"; \
		echo "1) Check specific color info"; \
		read -p "Enter your choice: " choice; \
		case "$$choice" in \
			0) SCRIPT_TYPE="Show Colors"; SCRIPT_CHOICE="$(SHOW_COLORS)";; \
			1) SCRIPT_TYPE="Color Info"; SCRIPT_CHOICE="$(COLOR_INFO)";; \
			2) SCRIPT_TYPE="Generate 1x1 png"; SCRIPT_CHOICE="$(COLOR_PIXEL_PNG)";; \
			42) SCRIPT_TYPE="Test script"; SCRIPT_CHOICE="$(TEST_SCRIPT)";; \
			*) echo "[ERROR] Invalid choice."; exit 1;; \
		esac; \
		\
		# Export LOG_ENABLED for use in nested call \
		export LOG_ENABLED="$$LOG_ENABLED"; \
		$(MAKE) run-script SCRIPT_TYPE="$$SCRIPT_TYPE" SCRIPT_CHOICE="$$SCRIPT_CHOICE" LOG_ENABLED="$$LOG_ENABLED" \
	'

script-clean: ## Clean up test artifacts and logs
	@if [ -d $(SCRIPT_LOG_DIR) ]; then \
		$(call CLEANUP,Scripts,script log files,$(SCRIPT_LOG_DIR),"Scripts logs removed.","No logs to remove."); \
	fi
#	@$(call CLEANUP,Scripts,script artifacts,$(SCRIPT_ARTIFACTS),"All scripts artifacts removed.","No artifacts to clean.")

$(SCRIPT_LOG_DIR):
	@$(MKDIR) $(SCRIPT_LOG_DIR)

new-script: init-project-root ## Create a new script from the template
	@if [ -z "$(name)" ]; then \
		read -p "Enter script name (e.g. color-demo.sh): " name; \
	fi; \
	target_path="$(SCRIPT_DIR)/$$name"; \
	if [ -e "$$target_path" ]; then \
		$(call ERROR,Script already exists,Script already exists at: $$target_path); \
		exit 1; \
	fi; \
	if [ ! -f "$(SCRIPT_TEMPLATE)" ]; then \
		$(call ERROR,Template Missing,Template not found at: $(SCRIPT_TEMPLATE)); \
		exit 1; \
	fi; \
	$(MKDIR) "$$(dirname "$$target_path")"; \
	cp "$(SCRIPT_TEMPLATE)" "$$target_path"; \
	if sed --version >/dev/null 2>&1; then \
		sed -i "s/{{SCRIPT_NAME}}/$$name/g" "$$target_path"; \
	else \
		sed -i '' "s/{{SCRIPT_NAME}}/$$name/g" "$$target_path"; \
	fi; \
	chmod +x "$$target_path"; \
	$(call SUCCESS,Scripts,New script created at: $$target_path)

init-project-root: # Create the .project-root sentinel file
	@if [ ! -f $(PROJECT_ROOT) ]; then \
		touch $(PROJECT_ROOT); \
		echo "✅ $(PROJECT_ROOT) created."; \
	fi

list-scripts: ## List available scripts
	@find $(SCRIPT_DIR) -type f -name "*.sh" | sort

script-make-exec: ## Make all scripts in SCRIPT_DIR executable
	@$(call INFO,Scripts,Making all scripts in $(SCRIPT_DIR) executable...)
	@count_file=$$(mktemp); \
	echo 0 > $$count_file; \
	find $(SCRIPT_DIR) -type f -name "*.sh" | while read script; do \
		if [ -x "$$script" ]; then \
			echo "$(YELLOW)Already executable: $$(basename "$$script")$(RESET)"; \
		else \
			chmod +x $$script; \
			echo "$(GREEN)Made executable: $$(basename "$$script")$(RESET)"; \
			count=$$(cat $$count_file); \
			count=$$((count + 1)); \
			echo $$count > $$count_file; \
		fi; \
	done; \
	total=$$(cat $$count_file); \
	rm -f $$count_file; \
	echo "$(CYAN)Total scripts made executable: $$total$(RESET)"

script-make-exec-silent: ## Run script-make-exec but suppress all output
	@$(MAKE) script-make-exec $(STDOUT_NULL) $(STDERR_STDOUT)

.PHONY: script script-clean script-new init-project-root \
		list-scripts script-make-exec \
		script-make-exec-silent
