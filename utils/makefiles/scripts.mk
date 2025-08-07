
# ==============================
##@ 📜 Scripts
# ==============================
PROJECT_ROOT	:= .project-root

# Scripts Paths  (relative to the main Makefile's location)
SCRIPT_DIR		:= ./utils/scripts
SCRIPT_INDEX	:= $(SCRIPT_DIR)/script-index.txt
SCRIPT_UTILS	:= $(SCRIPT_DIR)/helpers

# Script Templates
TEMPLATE_DIR	?= utils/templates
SCRIPT_TEMPLATE	:= $(TEMPLATE_DIR)/new-script.sh.template

# Scripts Logs and Artifacts
SCRIPT_LOG_DIR		:= $(SCRIPT_DIR)/tmp_scripts_logs
SCRIPT_LOG_FILE		:= $(SCRIPT_LOG_DIR)/SCRIPT_$(TIMESTAMP).log
SCRIPT_ARTIFACTS	:= $(SCRIPT_INDEX) $(PROJECT_ROOT)

#** tmp test**
# ifeq ($(call IS_COMMAND_AVAILABLE,realpath),0)
# 	REALPATH = realpath
# else
# 	REALPATH = $(SCRIPT_UTILS)/tmp_realpath-fallback.sh
# endif

# Returns "yes" or empty
CMD_EXISTS = $(shell command -v $(1) >/dev/null 2>&1 && echo yes)

# Tries realpath (Linux), then grealpath (Homebrew coreutils on macOS), then our fallback script.
# 
# REALPATH_CMD is the thing you run in recipes.
# 
# Pick a realpath command once:
REALPATH_CMD := $(if $(call CMD_EXISTS,realpath),realpath,\
                 $(if $(call CMD_EXISTS,grealpath),grealpath,\
                 $(SCRIPT_UTILS)/realpath-fallback.sh))

# ==============================
# Script Related Utilty Macros
# ==============================

# Macro: SCRIPT_LOG_PATH
# Generate a cleaner and more specific log file name per script,
# incorporating:
# 	the script's name
# 	the current timestam
# 
# Parameters:
# $(1): Script filename (e.g. "test-script.sh")
# 
# Output:
# 	$(SCRIPT_LOG_DIR)/test-script_$(TIMESTAMP).log
# 
# Example Usage:
# (In RUN_SCRIPT macro)
# 
# log_file=$(call SCRIPT_LOG_PATH,$(notdir $(2)));
# $(2) >> $$log_file 2>&1;
# 
SCRIPT_LOG_PATH = $(SCRIPT_LOG_DIR)/$(basename $(1))-$(TIMESTAMP).log


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
		$(call ERROR,Script Missing,Script '$(2)' does not exist.); \
		exit 1; \
	fi; \
	if [ ! -x "$(2)" ]; then \
		chmod +x $(2); \
	fi; \
	$(call INFO,Scripts,Running '$(1)' script...); \
	if [ "$(3)" = "true" ]; then \
		log_file=$(call SCRIPT_LOG_PATH,$(notdir $(2))); \
		$(2) >> $$log_file 2>&1; \
		$(call SUCCESS,Scripts,Script '$(1)' executed successfully.); \
		$(call INFO,Scripts,Logged in $$log_file); \
	else \
		$(2); \
		$(call SUCCESS,Scripts,Script '$(1)' executed successfully.); \
	fi
endef

# Macro: NEW_SCRIPT
# Create a new script from template with placeholder replacement and logging
# 
# Parameters:
# $(1): The script name (e.g. "color-demo.sh")
# $(2): The template path to use
#
# Usage:
#   $(call NEW_SCRIPT,color-demo.sh,$(SCRIPT_TEMPLATE))
#
define NEW_SCRIPT
	target_path="$(SCRIPT_DIR)/$(1)"; \
	if [ -e "$$target_path" ]; then \
		$(call ERROR,Script Already exists,Use a different name or delete: $$target_path); \
		exit 1; \
	fi; \
	if [ ! -f "$(2)" ]; then \
		$(call ERROR,Template Missing,Template not found at: $(2)); \
		exit 1; \
	fi; \
	$(MKDIR) "$$(dirname "$$target_path")"; \
	cp "$(2)" "$$target_path"; \
	$(SED_INPLACE) "s/{{SCRIPT_NAME}}/$(1)/g" "$$target_path"; \
	chmod +x "$$target_path"; \
	\
	# Prevent duplicate script entries when rebuilding or recreating \
	grep -qxF "$(1): $$target_path" $(SCRIPT_INDEX) || echo "$(1): $$target_path" >> $(SCRIPT_INDEX);
	$(call SUCCESS,Scripts,New script created and registered: $(SCRIPT_DIR)/$(1))
endef

# **************************************************************************** #

# ==============================
# Script Utility Targets
# ==============================
.PHONY: create-new-script run-script script-index-rebuild

$(PROJECT_ROOT):
	@$(call SENTINEL_MARKER,$(PROJECT_ROOT),print)

create-new-script:
	@$(call NEW_SCRIPT,$(SCRIPT_NAME),$(SCRIPT_TEMPLATE))

run-script:
	@$(call RUN_SCRIPT,$(SCRIPT_TYPE),$(SCRIPT_CHOICE),$(LOG_ENABLED))

## Rebuild script index grouped by folder
script-index-rebuild:
	@$(call INFO,Scripts,Rebuilding script index grouped by category...)
	@> $(SCRIPT_INDEX); \
	find $(SCRIPT_DIR) -type f -name "*.sh" \
		! -path "$(SCRIPT_UTILS)/*" \
		| while read path; do \
		rel_path=$$(realpath --relative-to="$(SCRIPT_DIR)" "$$path"); \
		category=$$(dirname "$$rel_path"); \
		[ "$$category" = "." ] && category="scripts"; \
		label="$$(basename $$path)"; \
		printf "[%s] %s: %s\n" "$$category" "$$label" "$$path"; \
	done >> $(SCRIPT_INDEX)
	@$(call SUCCESS,Scripts,Script index rebuilt: $(SCRIPT_INDEX))

# ==============================
# Script Targets
# ==============================
.PHONY: new-script script script-clean

new-script: $(PROJECT_ROOT) ## Create a new script from the template
	@bash -c '\
		if [ -z "$(name)" ]; then \
			read -p "Enter script name (e.g. color-demo.sh): " script_name; \
		else \
			script_name="$(name)"; \
		fi; \
		read -p "Use default script template '\''$(SCRIPT_TEMPLATE)'\''? [y/Y] for yes, or enter custom: " script_template; \
		if [ "$$script_template" = "y" ] || [ "$$script_template" = "Y" ] || [ -z "$$script_template" ]; then \
			script_template="$(SCRIPT_TEMPLATE)"; \
		fi; \
		exec make create-new-script SCRIPT_NAME="$$script_name" SCRIPT_TEMPLATE="$$script_template"\
		'

script: $(PROJECT_ROOT) script-index-rebuild ## Interactive script selection menu
	@bash -c '\
		# clear; \
		read -p "Do you want to log script output? (y/n): " log_choice; \
		if [ "$$log_choice" = "y" ] || [ "$$log_choice" = "Y" ] || [ -z "$$log_choice" ]; then \
			$(MKDIR) $(SCRIPT_LOG_DIR); \
			LOG_ENABLED=true; \
		else \
			LOG_ENABLED=false; \
		fi; \
		\
		echo ""; \
		echo "📜 Choose a script to run:"; \
		i=0; \
		declare -a labels; \
		declare -a paths; \
		while IFS=: read -r label path; do \
			labels[$$i]=$$label; \
			paths[$$i]=$$path; \
			printf "%2d) %s\n" $$i "$$label"; \
			((i++)); \
		done < $(SCRIPT_INDEX); \
		echo ""; \
		read -p "Enter your choice: " choice; \
		if [[ "$$choice" =~ ^[0-9]+$$ && "$$choice" -ge 0 && "$$choice" -lt $$i ]]; then \
			SCRIPT_TYPE="$${labels[$$choice]}"; \
			SCRIPT_CHOICE="$${paths[$$choice]}"; \
			SCRIPT_NAME=$$(basename "$$SCRIPT_CHOICE"); \
			$(MAKE) run-script SCRIPT_TYPE="$$SCRIPT_NAME" SCRIPT_CHOICE="$$SCRIPT_CHOICE" LOG_ENABLED="$$LOG_ENABLED"; \
		else \
			$(call ERROR,Invalid choice,"$$choice"); \
			exit 1; \
		fi'

script-clean: ## Clean up test artifacts and logs
	@$(call SILENT_CLEANUP,Scripts,Script log files,$(SCRIPT_LOG_DIR))
	@$(call SILENT_CLEANUP,Scripts,Script artifacts,$(SCRIPT_ARTIFACTS))

# ==============================
# Script Misc Utils
# ==============================
.PHONY: list-scripts \
		script-make-exec script-make-exec-silent

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
